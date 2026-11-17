void consume(int x[static 4]);

int main(void)
{
  int too_small[2];
  consume(too_small);
}
