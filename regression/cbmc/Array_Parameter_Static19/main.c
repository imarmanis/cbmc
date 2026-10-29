extern const void *__CPROVER_deallocated;

int read_after_deallocation_mark(int x[static 4])
{
  __CPROVER_deallocated = x;
  return x[0];
}

int main(void)
{
  int array[4];
  return read_after_deallocation_mark(array);
}
