unsigned *nondet_uint_pointer(void);

void f(unsigned *count, int x[static *count])
{
  (void)x;
}

int main(void)
{
  int array[4];
#ifdef VALID_COUNT
  unsigned count = 4;
  f(&count, array);
#else
  unsigned *count = nondet_uint_pointer();
  f(count, array);
#endif
}
