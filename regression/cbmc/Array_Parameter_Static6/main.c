#define N 4

int plain(int x[static N])
{
  int result = x[0];
  if(x[1] > result)
    result = x[1];
  if(x[2] > result)
    result = x[2];
  if(x[3] > result)
    result = x[3];
  __CPROVER_assert(result >= x[0] && result >= x[3], "plain result");
  return result;
}

int qualified(int x[static const N])
{
  int result = x[0];
  if(x[1] > result)
    result = x[1];
  if(x[2] > result)
    result = x[2];
  if(x[3] > result)
    result = x[3];
  __CPROVER_assert(result >= x[0] && result >= x[3], "qualified result");
  return result;
}

int main(void)
{
  int buffer[8];
  unsigned offset;
  __CPROVER_assume(offset <= 8 - N);
  plain(buffer + offset);
  qualified(buffer + offset);
  return 0;
}
