void two_declarations(int x[static 4]);
void two_declarations(int x[static 8]);

void runtime_largest(unsigned n, int x[static n]);
void runtime_largest(unsigned m, int x[static m + 2]);
void runtime_largest(unsigned k, int *x)
{
  (void)k;
  (void)x;
}

int main(void)
{
  int four[4];
  int five[5];
  two_declarations(four);
  runtime_largest(3, five);
  runtime_largest(3, four);
}
