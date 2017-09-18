/*
 * test_inst_type1_move.c
 *
 *  Created on: Sep 13, 2017
 *      Author: jie
 */
#include "cpu_external.h"
#include "mem.h"
#include "cpu_test_helper.h"
#include "unity.h"
#include "unity_fixture.h"

#undef  TESTNAME
#define TESTNAME inst_type1_move

SET_TEST_GROUP(TESTNAME);

SET_TEST_SETUP(TESTNAME)
{
  //This is run before EACH TEST
}

SET_TEST_DOWN(TESTNAME)
{

}

SET_TEST(TESTNAME, test_type1_move)
{
	int InstSize, i,Value;
	int RB, RD;

	//given
	InstSize = 1;
	Value = 5;
	for (i=0; i < 28; i++)
	{
		reset_cpu((unsigned char *)InstMem, InstSize * 4,
				(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
				(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

		//get

		//when
		RB = i ;
		RD = i + 1;

		SET_TYPE1_MOVE(InstMem[0], RD, RB);
		SET_CPU_REG(RB, Value);

		while (!run_cpu())
		{
		}

		//expected
		TEST_ASSERT_EQUAL(Value, GET_CPU_REG(RD));

		//update
		Value *= 2;
	}
}

SET_TEST_GROUP_RUNNER(TESTNAME)
{
	printf("test instruction %s \n", GET_STR(TESTNAME));

	SET_RUN_TEST_CASE(TESTNAME, test_type1_move);

}

