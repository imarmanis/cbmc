#include <stdint.h>

void f(
  __CPROVER_size_t rows,
  __CPROVER_size_t columns,
  char x[static 1][rows][columns])
{
  (void)x;
}

int main(void)
{
  char one;
  f(SIZE_MAX / 2 + 1, 2, (void *)&one);
}
