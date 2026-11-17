void consume(unsigned n, int x[static n]);

int main(void)
{
  int too_small[4];
  consume(5, too_small);
}

void consume(unsigned size, int *values)
{
  (void)size;
  (void)values;
}
