#define N 4

int read_last(int x[static N])
{
  return x[N - 1];
}

int main(void)
{
  int array[N];
  return read_last(array);
}
