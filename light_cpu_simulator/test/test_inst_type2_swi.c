/*
 * test_inst_type2_swi.c
 *
 *  Created on: Sep 20, 2017
 *      Author: jie
 */

#include "cpu_external.h"
#include "mem.h"
#include "cpu_test_helper.h"
#include "unity.h"
#include "unity_fixture.h"

#undef  TESTNAME
#define TESTNAME inst_type2_swi

SET_TEST_GROUP(TESTNAME);

SET_TEST_SETUP(TESTNAME)
{
  //This is run before EACH TEST
}

SET_TEST_DOWN(TESTNAME)
{

}

SET_TEST(TESTNAME, test_type2_swi)
{
	int InstSize;
    int i;
	int RB;
    
	//given
	InstSize = 1 + SWI_NUM * 2;
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

	//when 
    RB = 1;
	
    // set register
    SET_CPU_REG(RB, 0);
    for (i = 0; i < 8; i++)
    {
        //enable first 8 SWI
        SET_CPU_INT_MASK(INTERNAL_INT_NUM + EXTERNAL_INT_NUM + i, 1); 
    }
    //set instruction
    for (i=0; i< SWI_NUM; i++)
    {
        SET_TYPE2_SWI(InstMem[2 * i + 0], RB); 
        SET_TYPE2_UNSIGNED_ADD(InstMem[2 * i + 1], RB, RB, 1);
    }
    
	while (!run_cpu())
	{
	}

	//expected
	TEST_ASSERT_EQUAL(16, GET_CPU_REG(RB));
    for (i = 0; i< INTERNAL_INT_NUM + EXTERNAL_INT_NUM + SWI_NUM; i++)
    {
        if (i < INTERNAL_INT_NUM + EXTERNAL_INT_NUM)
        {
            TEST_ASSERT_EQUAL(0, GET_CPU_INT_STATUS(i)); 
        }
        else if ((i >= INTERNAL_INT_NUM + EXTERNAL_INT_NUM + 8))
        {
            TEST_ASSERT_EQUAL(0, GET_CPU_INT_STATUS(i)); 
        }
        else
        {
            TEST_ASSERT_EQUAL(1, GET_CPU_INT_STATUS(i)); 
        }
    }
}

SET_TEST_GROUP_RUNNER(TESTNAME)
{
	printf("test instruction %s \n", GET_STR(TESTNAME));

	SET_RUN_TEST_CASE(TESTNAME, test_type2_swi);
 
}
