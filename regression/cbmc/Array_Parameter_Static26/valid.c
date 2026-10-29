#define N 4

void f(int x[static N])
{
  (void)x;
}

int main(void)
{
  int exact[N];
  int larger[2 * N];

  f(exact);
  f(larger + N);
}
