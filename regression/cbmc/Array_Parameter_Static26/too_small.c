#define N 4

void f(int x[static N])
{
  (void)x;
}

int main(void)
{
  int larger[2 * N];
  f(larger + N + 1);
}
