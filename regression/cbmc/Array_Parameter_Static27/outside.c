#define N 4

int read_exact(int x[static N], unsigned i)
{
  return x[i];
}

int main(void)
{
  int array[N];
  unsigned i;
  __CPROVER_assume(i >= N);
  return read_exact(array, i);
}
