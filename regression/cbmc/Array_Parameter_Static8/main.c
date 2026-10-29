#include <stdlib.h>

int read_after_free(int x[static const 4])
{
  free(x);
  return x[0];
}

int main(void)
{
  int *array = malloc(4 * sizeof(*array));
  return read_after_free(array);
}
