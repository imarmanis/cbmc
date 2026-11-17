void contract(int x[static 3])
  __CPROVER_requires(__CPROVER_is_fresh(x, 3 * sizeof(*x)))
  __CPROVER_assigns();

void function(int x[static 3])
{
  (void)x[2];
}

int main(void)
{
  int *x;
  function(x);
}
