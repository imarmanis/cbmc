void contract(int x[static 2])
  __CPROVER_requires(__CPROVER_is_fresh(x, 2 * sizeof(*x)))
  __CPROVER_assigns();

void function(int x[static 4])
{
  (void)x[3];
}

int main(void)
{
  int *x;
  function(x);
}
