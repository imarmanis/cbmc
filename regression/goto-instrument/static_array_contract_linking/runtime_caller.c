void f(unsigned n, int x[static n])
  __CPROVER_requires(1)
  __CPROVER_assigns();

int main(void)
{
  int two[2];
  f(4, two);
}
