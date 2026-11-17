/*******************************************************************\

Module: C Static Array Parameters

Author: Iason Marmanis

\*******************************************************************/

/// \file
/// Construction of the minimum-access preconditions implied by C parameters
/// declared with `[static N]`.

#ifndef CPROVER_UTIL_C_STATIC_ARRAY_PARAMETERS_H
#define CPROVER_UTIL_C_STATIC_ARRAY_PARAMETERS_H

#include <util/expr.h>
#include <util/source_location.h>

#include <string>
#include <vector>

class code_typet;
class code_with_contract_typet;
class namespacet;

struct static_array_parameter_preconditiont
{
  exprt condition;
  source_locationt source_location;
  std::string description;
};

/// Replace auxiliary VLA-size symbols by their defining expressions and
/// simplify the result.
exprt expand_c_array_size(exprt size, const namespacet &ns);

/// Build the preconditions implied by all `[static N]` parameters in a C
/// function type. Each condition includes positivity and size-overflow checks
/// as well as the minimum readable byte range.
std::vector<static_array_parameter_preconditiont>
static_array_parameter_preconditions(
  const code_typet &function_type,
  const irep_idt &function_identifier,
  const namespacet &ns);

/// Preserve the strongest `[static N]` minimum from \p source in
/// \p destination, two compatible types of the function
/// \p function_identifier. Parameter symbols in a bound are renamed by
/// position because each declaration may use different parameter names.
void merge_static_array_parameter_sizes(
  code_typet &destination,
  const code_typet &source,
  const irep_idt &function_identifier);

/// Merge the `[static N]` minima of \p function_type into the code contract
/// \p contract_type of the same function and rebuild the requires clauses
/// generated from them. Minima recorded only on the contract are kept.
void refresh_static_array_contract_requires(
  code_with_contract_typet &contract_type,
  const code_typet &function_type,
  const irep_idt &function_identifier,
  const namespacet &ns);

#endif // CPROVER_UTIL_C_STATIC_ARRAY_PARAMETERS_H
