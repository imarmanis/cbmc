typedef int A[10];

// C11 6.7.3p9: the qualifier applies to the element type, so `x` is
// adjusted to `const int *` (not `int *const`) and may be assigned to.
void f1(const A x)
{
  x = 0;
}

// Qualifiers of the adjusted pointer are not part of the function type
// (C11 6.7.6.3p15), so these declarations are compatible.
void f2(int x[const 10]);
void f2(int x[10])
{
  x = 0;
}

void f3(int x[const static 10]);
void f3(int *x)
{
  x = 0;
}

// Only the outermost array derivation is adjusted; the elements of the
// pointed-to array are not const.
void f4(int x[const 3][4])
{
  x[1][2] = 5;
}

int main(void)
{
  int a[10];
  int b[3][4];
  f1(a);
  f2(a);
  f3(a);
  f4(b);
  return 0;
}
