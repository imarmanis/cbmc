void f(unsigned n, int x[static n])
{
  (void)x;
}

int main(void)
{
  int array[8];
  unsigned n;
  __CPROVER_assume(0 < n && n <= 8);
  f(n, array + (8 - n));
}
