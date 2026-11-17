void before_definition(int x[static 4]);
void before_definition(int *x)
{
  (void)x;
}

void after_definition(int *x)
{
  (void)x;
}
void after_definition(int x[static 4]);

void renamed_bound(unsigned count, int x[static count]);
void renamed_bound(unsigned size, int *x)
{
  (void)size;
  (void)x;
}

void largest_minimum(int x[static 8]);
void largest_minimum(int x[static 4])
{
  (void)x;
}

int main(void)
{
  int two[2];
  int four[4];
  before_definition(two);
  after_definition(two);
  renamed_bound(4, two);
  largest_minimum(four);
}
