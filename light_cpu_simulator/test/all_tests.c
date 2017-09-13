#include "unity_fixture.h"

static void RunAllTests(void)
{
  RUN_TEST_GROUP(inst_type1_add);
  RUN_TEST_GROUP(inst_type1_sub);
}

int main(int argc, const char * argv[])
{
  return UnityMain(argc, argv, RunAllTests);
}
