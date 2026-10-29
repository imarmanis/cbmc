void f(unsigned n, int x[static n])
{
  (void)x;
}

int main(void)
{
  int larger[8];
  void (*function_pointer)(unsigned, int *) = f;
  function_pointer(4, larger);
}
