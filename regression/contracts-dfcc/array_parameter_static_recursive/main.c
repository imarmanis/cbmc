int f(int x[static 4], int n)
  __CPROVER_requires(0 <= n && n <= 1)
  __CPROVER_requires(__CPROVER_r_ok(x, 2 * sizeof(int)))
  __CPROVER_assigns()
{
  if(n == 0)
    return 0;
  return f(x + 4, n - 1);
}

int main(void)
{
  int buffer[6];
  return f(buffer, 1);
}
