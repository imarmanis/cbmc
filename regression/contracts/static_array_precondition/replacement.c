int f(int x[static 4])
  __CPROVER_requires(__CPROVER_is_fresh(x, sizeof(*x)))
  __CPROVER_assigns()
{
  return x[0];
}

int main(void)
{
  int too_small[1];
  return f(too_small);
}
