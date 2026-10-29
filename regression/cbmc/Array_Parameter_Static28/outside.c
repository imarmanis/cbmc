#define N 4

int read_past(int x[static N])
{
  return x[N];
}

int main(void)
{
  int array[N];
  return read_past(array);
}
