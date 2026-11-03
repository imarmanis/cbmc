void f(unsigned count, int x[static count++])
{
  (void)x;
}

int main(void)
{
  int array[4];
  f(3, array);
}
