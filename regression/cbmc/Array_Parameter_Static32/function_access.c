int f(unsigned rows, unsigned columns, int x[static rows][columns])
{
  __CPROVER_assume(rows == 2 && columns == 3);
  int *last = &x[0][0] + rows * columns - 1;
  return *last;
}
