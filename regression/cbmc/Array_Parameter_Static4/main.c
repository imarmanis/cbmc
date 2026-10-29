void consume(unsigned n, int x[static n])
{
  (void)x;
}

int main(void)
{
  int too_small[5];
  consume(6, too_small);
}
