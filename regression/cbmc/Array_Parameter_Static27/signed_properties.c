#define N 4

int read_exact_signed(int x[static N], int i)
{
  return x[i];
}

int main(void)
{
  int array[N];
  int i;
  __CPROVER_assume(0 <= i && i < N);
  return read_exact_signed(array, i);
}
