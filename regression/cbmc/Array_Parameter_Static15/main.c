void consume(unsigned n, int x[static n]);

int main(void)
{
  int larger[6];
  consume(5, larger);
}

void consume(unsigned n, int x[static n])
{
  (void)n;
  (void)x;
}
