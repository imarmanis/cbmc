int f(int x[static 4])
  __CPROVER_requires(__CPROVER_is_fresh(x, 4 * sizeof(*x)))
  __CPROVER_assigns()
{
  __CPROVER_assert(0, "implementation is reachable");
  return x[3];
}

int main(void)
{
  int *x;
  return f(x);
}
