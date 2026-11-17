int f(int x[static 4])
  __CPROVER_requires(__CPROVER_is_fresh(x, 4 * sizeof(*x)))
  __CPROVER_assigns()
{
  return x[0];
}

int main(void)
{
  int *x;
  return f(x);
}
