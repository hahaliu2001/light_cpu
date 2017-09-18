/*
 * test_inst_type4_mov.c
 *
 *  Created on: Sep 17, 2017
 *      Author: jie
 */

#include "cpu_external.h"
#include "mem.h"
#include "cpu_test_helper.h"
#include "unity.h"
#include "unity_fixture.h"

#undef  TESTNAME
#define TESTNAME inst_type4_move

SET_TEST_GROUP(TESTNAME);

SET_TEST_SETUP(TESTNAME)
{
  //This is run before EACH TEST
}

SET_TEST_DOWN(TESTNAME)
{

}

SET_TEST(TESTNAME, test_move_unsigned_imm)
{
	int InstSize;
	int RD1, RD2;
    unsigned int Value1, Value2;

	//given
	InstSize = 2;
	Value1 = 567; Value2 = 0x89ab;
    RD1 = 10; RD2 = 20;
    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    //set CPU register
    
    //write instrction memory
    SET_TYPE4_UNSIGNED_MOV(InstMem[0], RD1, Value1);
    SET_TYPE4_UNSIGNED_MOV(InstMem[1], RD2, Value2);
    
    while (!run_cpu())
	{
	}

    //expected
    TEST_ASSERT_EQUAL(Value1, GET_CPU_REG(RD1));
    TEST_ASSERT_EQUAL(Value2, GET_CPU_REG(RD2));
}

SET_TEST(TESTNAME, test_move_signed_imm)
{
	int InstSize;
	int RD1, RD2;
    unsigned int Value1, Value2;

	//given
	InstSize = 2;
	Value1 = 567; Value2 = 0x89ab;
    RD1 = 10; RD2 = 20;
    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    //set CPU register
    
    //write instrction memory
    SET_TYPE4_SIGNED_MOV(InstMem[0], RD1, Value1);
    SET_TYPE4_SIGNED_MOV(InstMem[1], RD2, Value2);
    
    while (!run_cpu())
	{
	}

    //expected
    TEST_ASSERT_EQUAL(Value1, GET_CPU_REG(RD1));
    TEST_ASSERT_EQUAL((unsigned int)(((int)(Value2 << 16)) >> 16), GET_CPU_REG(RD2));
}

SET_TEST_GROUP_RUNNER(TESTNAME)
{
	printf("test instruction %s \n", GET_STR(TESTNAME));

	SET_RUN_TEST_CASE(TESTNAME, test_move_unsigned_imm);
    SET_RUN_TEST_CASE(TESTNAME, test_move_signed_imm);
}


