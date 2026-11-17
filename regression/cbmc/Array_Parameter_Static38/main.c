#include <stdint.h>

void f(__CPROVER_size_t n, int x[static n])
{
  (void)x;
}

int main(void)
{
  int one;
  f(SIZE_MAX / sizeof(int) + 1, &one);
}
