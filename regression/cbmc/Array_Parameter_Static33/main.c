int f(int a[static 100000])
{
  __CPROVER_assert(a[0] == a[99999], "elements are nondet");
  return a[99999];
}
