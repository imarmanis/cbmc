int read_index(int x[static 4], int i)
{
  return x[i];
}

int main(void)
{
  int exact[4];
  return read_index(exact, 4);
}
