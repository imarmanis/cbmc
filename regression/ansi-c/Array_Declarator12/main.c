void assign_parameter(int x[static const 4], int y[static 4])
{
  x = y;
}

int main(void)
{
  int a[4];
  int b[4];
  assign_parameter(a, b);
}
