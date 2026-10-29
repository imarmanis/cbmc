void write_last(int *x);

int main(void)
{
  int too_small[2];
  write_last(too_small);
}

void write_last(int x[static 4])
{
  x[3] = 1;
}
