#define N 4

int read_plain(int *x, int i)
{
  __CPROVER_assume(0 <= i && i < N);
  return x[i];
}

int read_static(int x[static N], int i)
{
  __CPROVER_assume(0 <= i && i < N);
  return x[i];
}

int main(void)
{
  int array[N];
  int i;
  (void)read_plain(array, i);
  return read_static(array, i);
}
