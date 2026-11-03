#define N 4

int read_known(int x[static N])
{
  return x[0] + x[1] + x[2] + x[3];
}

int read_dynamic(int x[static N], unsigned i)
{
  __CPROVER_assume(i < N);
  return x[i];
}

int main(void)
{
  int array[N];
  unsigned i;
  return read_known(array) + read_dynamic(array, i);
}
