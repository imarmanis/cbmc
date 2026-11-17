int read_before(int x[static 4])
{
  return x[-1];
}

int main(void)
{
  int array[5];
  return read_before(&array[1]);
}
