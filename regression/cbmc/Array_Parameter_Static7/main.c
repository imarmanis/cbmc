int read_after_reassignment(int x[static 4])
{
  x += 4;
  return x[0];
}

int main(void)
{
  int array[4];
  return read_after_reassignment(array);
}
