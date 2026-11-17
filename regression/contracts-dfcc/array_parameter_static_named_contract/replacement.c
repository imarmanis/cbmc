void contract(int x[static 2])
  __CPROVER_requires(1)
  __CPROVER_assigns();

void function(int x[static 4])
{
  (void)x;
}

void caller(void)
{
  int too_small[2];
  function(too_small);
}

int main(void)
{
  caller();
}
