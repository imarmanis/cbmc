void write_first();

int main(void)
{
  write_first();
}

void write_first(int x[static 4])
{
  x[0] = 1;
}
