int read_volatile(int x[volatile static 4])
{
  return x[0];
}

int main(void)
{
  int array[4];
  return read_volatile(array);
}
