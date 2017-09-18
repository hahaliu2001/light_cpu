#include "unity_fixture.h"

static void RunAllTests(void)
{
  RUN_TEST_GROUP(inst_type1_add);
  RUN_TEST_GROUP(inst_type1_sub);
  RUN_TEST_GROUP(inst_type1_mpy);
  RUN_TEST_GROUP(inst_type1_move);
  RUN_TEST_GROUP(inst_type1_cmp);
  RUN_TEST_GROUP(inst_type1_shift);
  RUN_TEST_GROUP(inst_type1_and);
  RUN_TEST_GROUP(inst_type1_xor);
  RUN_TEST_GROUP(inst_type1_not);
  RUN_TEST_GROUP(inst_type1_ld);
  RUN_TEST_GROUP(inst_type1_st);
  RUN_TEST_GROUP(inst_type2_add);
  RUN_TEST_GROUP(inst_type2_sub);
  RUN_TEST_GROUP(inst_type2_mpy);
  RUN_TEST_GROUP(inst_type2_shift);
  RUN_TEST_GROUP(inst_type2_ld);
  RUN_TEST_GROUP(inst_type2_st);
  RUN_TEST_GROUP(inst_type3_ajmp);
  RUN_TEST_GROUP(inst_type3_rjmp);
  RUN_TEST_GROUP(inst_type4_ajmp);
  RUN_TEST_GROUP(inst_type4_rjmp);
  RUN_TEST_GROUP(inst_type4_move);
  RUN_TEST_GROUP(inst_type4_cmp);
  RUN_TEST_GROUP(inst_type4_ld);
  RUN_TEST_GROUP(inst_type4_st);
}

int main(int argc, const char * argv[])
{
  return UnityMain(argc, argv, RunAllTests);
}
