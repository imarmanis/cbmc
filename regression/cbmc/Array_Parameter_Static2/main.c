void consume(int x[static 4])
{
  (void)x;
}

int main(void)
{
  int too_small[3];
  consume(too_small);
}
