int read_beyond_minimum(int x[static 4])
{
  return x[4];
}

int main(void)
{
  int array[4];
  return read_beyond_minimum(array);
}
