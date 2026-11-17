void function(int y[static 4]);

void function(int x[static 2])
  __CPROVER_requires(1)
  __CPROVER_assigns();

int main(void)
{
  int too_small[3];
  function(too_small);
}
