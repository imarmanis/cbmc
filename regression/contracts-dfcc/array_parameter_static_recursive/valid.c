int f(int x[static 4], int n)
  __CPROVER_requires(0 <= n && n <= 1)
  __CPROVER_requires(__CPROVER_r_ok(x, 4 * sizeof(int)))
  __CPROVER_assigns()
{
  if(n == 0)
  {
    __CPROVER_assert(0, "base case is reachable");
    return 0;
  }
  return f(x + 4, n - 1);
}

int main(void)
{
  int buffer[8];
  int n;
  return f(buffer, n);
}
