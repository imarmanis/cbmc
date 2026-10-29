void f(unsigned n, int x[static n])
{
  (void)x;
}

int main(void)
{
  int short_array[2];
  void (*function_pointer)(unsigned, int *) = f;
  function_pointer(4, short_array);
}
