void f(int x[static 4])
  __CPROVER_requires(1)
  __CPROVER_assigns()
{
  (void)x;
}
