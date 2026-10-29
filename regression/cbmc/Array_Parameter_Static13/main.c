#include <stdint.h>

int read_truncated(int x[static 4])
{
  return *(int *)(unsigned)(uintptr_t)x;
}

int main(void)
{
  int array[4];
  return read_truncated(array);
}
