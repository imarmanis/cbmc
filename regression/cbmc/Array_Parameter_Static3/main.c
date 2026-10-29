void consume(int x[static 4])
{
  (void)x;
}

int main(void)
{
  consume((int *)0);
}
