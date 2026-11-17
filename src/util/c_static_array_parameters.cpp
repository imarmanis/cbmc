/*******************************************************************\

Module: C Static Array Parameters

Author: Iason Marmanis

\*******************************************************************/

/// \file
/// Construction of the minimum-access preconditions implied by C parameters
/// declared with `[static N]`.

#include "c_static_array_parameters.h"

#include <util/arith_tools.h>
#include <util/bitvector_expr.h>
#include <util/c_types.h>
#include <util/cprover_prefix.h>
#include <util/find_symbols.h>
#include <util/invariant.h>
#include <util/mathematical_expr.h>
#include <util/namespace.h>
#include <util/pointer_expr.h>
#include <util/pointer_offset_size.h>
#include <util/replace_symbol.h>
#include <util/simplify_expr.h>
#include <util/std_expr.h>
#include <util/std_types.h>
#include <util/symbol.h>

#include <algorithm>
#include <set>

/// Replace auxiliary VLA-size symbols by their defining expressions.
exprt expand_c_array_size(exprt size, const namespacet &ns)
{
  std::set<irep_idt> expanded_symbols;
  while(true)
  {
    replace_symbolt replacements;
    for(const auto &symbol_expr : find_symbols(size))
    {
      if(!expanded_symbols.insert(symbol_expr.get_identifier()).second)
        continue;

      const symbolt *symbol;
      if(ns.lookup(symbol_expr.get_identifier(), symbol))
        continue;

      if(
        symbol->is_auxiliary && symbol->value.is_not_nil() &&
        symbol->type.get_bool(ID_C_constant))
      {
        replacements.insert(symbol_expr, symbol->value);
      }
    }

    if(replacements.empty())
      return simplify_expr(size, ns);

    replacements.replace(size);
  }
}

/// Collect conditions excluding overflow in every multiplication in `expr`.
static void add_multiplication_no_overflow_conditions(
  const exprt &expr,
  exprt::operandst &conditions)
{
  for(const auto &operand : expr.operands())
    add_multiplication_no_overflow_conditions(operand, conditions);

  if(
    expr.id() == ID_mult && expr.operands().size() == 2 &&
    (expr.type().id() == ID_signedbv || expr.type().id() == ID_unsignedbv))
  {
    conditions.push_back(not_exprt{
      mult_overflow_exprt{expr.operands()[0], expr.operands()[1]}});
  }
}

std::vector<static_array_parameter_preconditiont>
static_array_parameter_preconditions(
  const code_typet &function_type,
  const irep_idt &function_identifier,
  const namespacet &ns)
{
  std::vector<static_array_parameter_preconditiont> result;

  for(const auto &parameter : function_type.parameters())
  {
    const irept &static_size_irep =
      parameter.type().find(ID_C_static_array_size);
    if(static_size_irep.is_nil() || parameter.type().id() != ID_pointer)
      continue;

    irep_idt parameter_identifier = parameter.get_identifier();
    if(parameter_identifier.empty() && !parameter.get_base_name().empty())
    {
      parameter_identifier = id2string(function_identifier) + "::" +
                             id2string(parameter.get_base_name());
    }
    if(parameter_identifier.empty())
      continue;

    exprt element_count = expand_c_array_size(
      static_cast<const exprt &>(static_size_irep), ns);
    const auto constant_count = numeric_cast<mp_integer>(element_count);
    if(constant_count.has_value() && *constant_count <= 0)
      continue; // Accept GCC's `[static 0]` extension.

    const auto element_size_expr =
      size_of_expr(to_pointer_type(parameter.type()).base_type(), ns);
    CHECK_RETURN(element_size_expr.has_value());
    exprt element_size = expand_c_array_size(*element_size_expr, ns);

    exprt::operandst conditions;
    if(!constant_count.has_value())
    {
      conditions.push_back(binary_relation_exprt{
        element_count, ID_gt, from_integer(0, element_count.type())});
    }
    add_multiplication_no_overflow_conditions(element_size, conditions);

    const exprt element_count_for_size =
      typecast_exprt::conditional_cast(element_count, element_size.type());
    conditions.push_back(not_exprt{
      mult_overflow_exprt{element_count_for_size, element_size}});
    const exprt byte_size = typecast_exprt::conditional_cast(
      mult_exprt{element_count_for_size, element_size}, size_type());
    conditions.push_back(r_ok_exprt{
      symbol_exprt{parameter_identifier, parameter.type()}, byte_size});

    result.push_back(static_array_parameter_preconditiont{
      conjunction(conditions),
      parameter.source_location(),
      "static array parameter " + id2string(parameter.get_base_name()) +
        " must provide access to its declared minimum"});
  }

  return result;
}

void merge_static_array_parameter_sizes(
  code_typet &destination,
  const code_typet &source,
  const irep_idt &function_identifier)
{
  auto &destination_parameters = destination.parameters();
  const auto &source_parameters = source.parameters();
  if(destination_parameters.size() != source_parameters.size())
    return;

  const auto parameter_identifier =
    [&function_identifier](const code_typet::parametert &parameter)
  {
    if(!parameter.get_identifier().empty())
      return parameter.get_identifier();
    if(parameter.get_base_name().empty())
      return irep_idt{};
    return irep_idt{id2string(function_identifier) + "::" +
                    id2string(parameter.get_base_name())};
  };

  replace_symbolt rename;
  std::set<irep_idt> unmappable;
  for(std::size_t index = 0; index < destination_parameters.size(); ++index)
  {
    const irep_idt source_identifier =
      parameter_identifier(source_parameters[index]);
    const irep_idt destination_identifier =
      parameter_identifier(destination_parameters[index]);
    if(source_identifier.empty() || source_identifier == destination_identifier)
      continue;

    if(
      destination_identifier.empty() ||
      source_parameters[index].type() != destination_parameters[index].type())
    {
      unmappable.insert(source_identifier);
      continue;
    }

    rename.insert(
      symbol_exprt{source_identifier, source_parameters[index].type()},
      symbol_exprt{
        destination_identifier, destination_parameters[index].type()});
  }

  for(std::size_t index = 0; index < destination_parameters.size(); ++index)
  {
    const irept &source_size_irep =
      source_parameters[index].type().find(ID_C_static_array_size);
    if(source_size_irep.is_nil())
      continue;

    exprt source_size = static_cast<const exprt &>(source_size_irep);
    const auto source_symbols = find_symbols(source_size);
    if(std::any_of(
         source_symbols.begin(),
         source_symbols.end(),
         [&unmappable](const symbol_exprt &symbol)
         {
           return unmappable.find(symbol.get_identifier()) != unmappable.end();
         }))
    {
      continue;
    }
    rename.replace(source_size);

    typet &destination_type = destination_parameters[index].type();
    const irept &destination_size_irep =
      destination_type.find(ID_C_static_array_size);
    if(destination_size_irep.is_nil())
    {
      destination_type.add(ID_C_static_array_size) = std::move(source_size);
      continue;
    }

    exprt destination_size =
      static_cast<const exprt &>(destination_size_irep);
    if(destination_size == source_size)
      continue;

    const auto destination_constant =
      numeric_cast<mp_integer>(destination_size);
    const auto source_constant = numeric_cast<mp_integer>(source_size);
    if(destination_constant.has_value() && source_constant.has_value())
    {
      if(*source_constant > *destination_constant)
        destination_type.add(ID_C_static_array_size) = std::move(source_size);
      continue;
    }

    source_size = typecast_exprt::conditional_cast(
      std::move(source_size), destination_size.type());
    destination_type.add(ID_C_static_array_size) = if_exprt{
      binary_relation_exprt{destination_size, ID_ge, source_size},
      std::move(destination_size),
      std::move(source_size)};
  }
}

void refresh_static_array_contract_requires(
  code_with_contract_typet &contract_type,
  const code_typet &function_type,
  const irep_idt &function_identifier,
  const namespacet &ns)
{
  merge_static_array_parameter_sizes(
    contract_type, function_type, function_identifier);

  auto &requires = contract_type.c_requires();
  requires.erase(
    std::remove_if(
      requires.begin(),
      requires.end(),
      [](const exprt &requirement)
      {
        return requirement.get_bool(ID_C_static_array_precondition);
      }),
    requires.end());

  binding_exprt::variablest contract_parameters;
  if(contract_type.return_type().id() != ID_empty)
  {
    contract_parameters.emplace_back(
      CPROVER_PREFIX "return_value", contract_type.return_type());
  }
  for(const auto &parameter : contract_type.parameters())
  {
    if(!parameter.get_identifier().empty())
    {
      contract_parameters.emplace_back(
        parameter.get_identifier(), parameter.type());
    }
  }

  for(auto &precondition : static_array_parameter_preconditions(
        contract_type, function_identifier, ns))
  {
    precondition.condition.add_source_location() =
      precondition.source_location;
    lambda_exprt lambda{contract_parameters, precondition.condition};
    lambda.add_source_location() = precondition.source_location;
    lambda.set(ID_C_static_array_precondition, true);
    requires.push_back(std::move(lambda));
  }
}
