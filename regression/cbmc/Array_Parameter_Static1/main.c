#define N 4

void plain_static(int x[static N])
{
  x[0] = 1;
}

void const_static(int x[const static N])
{
  x[1] = 2;
}

void static_const(int x[static const N])
{
  x[2] = 3;
}

void runtime_bound(unsigned n, int x[static n])
{
  x[n - 1] = 4;
}

int main(void)
{
  int exact[N];
  int larger[N + 3];

  plain_static(exact);
  plain_static(larger);
  plain_static(larger + 1);
  const_static(larger);
  static_const(larger);
  runtime_bound(N, exact);
  runtime_bound(N, larger + 2);
}
