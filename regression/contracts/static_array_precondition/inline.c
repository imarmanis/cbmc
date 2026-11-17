void f(int x[static 4])
{
  (void)x;
}

int main(void)
{
  int too_small[2];
  f(too_small);
}
