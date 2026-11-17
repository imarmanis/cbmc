int f(int *a[static 10000])
{
  __CPROVER_assert(a[0] == a[9999], "pointer elements are nondet");
  return 0;
}
