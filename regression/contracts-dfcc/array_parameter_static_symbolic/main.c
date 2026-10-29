#define C 10

void f(int x[const static C], int i)
  __CPROVER_requires(__CPROVER_is_fresh(x, C * sizeof(int)))
  __CPROVER_requires(i >= 0 && i < C)
  __CPROVER_assigns(__CPROVER_object_upto(x, C * sizeof(int)))
{
  x[i] = 1;
}

int main(void)
{
  int *x;
  int i;
  f(x, i);
}
