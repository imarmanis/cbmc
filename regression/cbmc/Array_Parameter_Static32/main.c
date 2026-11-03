void f(unsigned rows, unsigned columns, int x[static rows][columns])
{
  (void)x;
}

int main(void)
{
#ifdef VALID_EXTENT
  int storage[2][3];
#else
  int storage[1][3];
#endif
  f(2, 3, storage);
}
