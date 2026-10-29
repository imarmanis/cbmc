void write_last(int x[static 4])
{
  x[3] = 1;
}

int main(void)
{
  int too_small[2];
#pragma CPROVER check push
#pragma CPROVER check disable "pointer"
  write_last(too_small);
#pragma CPROVER check pop
}
