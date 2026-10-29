int read_index(int x[static 4], int i)
{
  return x[i];
}

int main(void)
{
  int larger[8];
  return read_index(larger, 6);
}
