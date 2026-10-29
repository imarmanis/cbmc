#include <stdint.h>

#define N 4

unsigned sum(int x[static N])
{
  unsigned result = 0;
  for(unsigned i = 0; i < N; ++i)
    result += (uint8_t)x[i];
  return result;
}

int main(void)
{
  int array[N];
  sum(array);
}
