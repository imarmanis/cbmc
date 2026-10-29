void write_last(int *x);

int main(void)
{
  int too_small[2];
  write_last(too_small);
}

void write_last(int x[static 4])
{
  __CPROVER_assert(
    x != 0,
    "function parameter does not provide access to its static minimum");
  x[3] = 1;
}
