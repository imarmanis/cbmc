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

#endif // CPROVER_UTIL_C_STATIC_ARRAY_PARAMETERS_H
