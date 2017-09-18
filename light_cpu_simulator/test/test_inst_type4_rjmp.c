/*
 * test_inst_type4_rjmp.c
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
#define TESTNAME inst_type4_rjmp

SET_TEST_GROUP(TESTNAME);

SET_TEST_SETUP(TESTNAME)
{
  //This is run before EACH TEST
    init_mem((unsigned char *)InstMem, INSTRUCTION_MEM_SIZE);
    init_mem((unsigned char *)DataMem, DATA_MEM_SIZE);
    init_mem((unsigned char *)StackMem, STACK_MEM_SIZE);
}

SET_TEST_DOWN(TESTNAME)
{

}

SET_TEST(TESTNAME, test_rjmp_without_link_under_EQ_condition)
{
	int InstSize, RD;
    
    //given
	InstSize = 12;
    
    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    //set CPU register
    RD = 6; SET_CPU_REG(RD, 1 * 4);
    SET_CPU_REG(0, 60);  SET_CPU_REG(1, 60);
    SET_CPU_REG(2, 60);  SET_CPU_REG(3, 60);
    SET_CPU_REG(4, 30);  SET_CPU_REG(5, 60);
    SET_CPU_REG(10, 70); SET_CPU_REG(11, 80); SET_CPU_REG(12, 90);  
    
    //write instrction memory
    SET_TYPE1_CMP(InstMem[0], 0, 1);
    SET_TYPE4_RJMP(InstMem[1], COND_EQ, RD, 1); //should jump 
    SET_ERROR_INST(InstMem[2]);
    SET_TYPE1_MOVE(InstMem[3], 20, 10);

    SET_TYPE1_CMP(InstMem[4], 2, 3);
    SET_TYPE4_RJMP(InstMem[5], COND_EQ, RD, 1); //should jump 
    SET_ERROR_INST(InstMem[6]);
    SET_TYPE1_MOVE(InstMem[7], 21, 11);

    SET_TYPE1_CMP(InstMem[8], 4, 5);
    SET_TYPE4_RJMP(InstMem[9], COND_EQ, RD, 1); //should not jump 
    SET_TYPE1_MOVE(InstMem[10], 22, 12);
    SET_ERROR_INST(InstMem[11]);
    
    
    
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL(0, GET_CPU_LR_REG());
    TEST_ASSERT_EQUAL(70, GET_CPU_REG(20));
    TEST_ASSERT_EQUAL(80, GET_CPU_REG(21));
    TEST_ASSERT_EQUAL(90, GET_CPU_REG(22));
}

SET_TEST(TESTNAME, test_rjmp_without_link_under_NE_condition)
{
	int InstSize, RD;
    
    //given
	InstSize = 12;
    
    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    //set CPU register
    RD = 6; SET_CPU_REG(RD, 1 * 4);
    SET_CPU_REG(0, 50);  SET_CPU_REG(1, 60);
    SET_CPU_REG(2, 50);  SET_CPU_REG(3, 60);
    SET_CPU_REG(4, 60);  SET_CPU_REG(5, 60);
    SET_CPU_REG(10, 70); SET_CPU_REG(11, 80); SET_CPU_REG(12, 90);  
    
    //write instrction memory
    SET_TYPE1_CMP(InstMem[0], 0, 1);
    SET_TYPE4_RJMP(InstMem[1], COND_NE, RD, 1); //should jump 
    SET_ERROR_INST(InstMem[2]);
    SET_TYPE1_MOVE(InstMem[3], 20, 10);

    SET_TYPE1_CMP(InstMem[4], 2, 3);
    SET_TYPE4_RJMP(InstMem[5], COND_NE, RD, 1); //should jump 
    SET_ERROR_INST(InstMem[6]);
    SET_TYPE1_MOVE(InstMem[7], 21, 11);

    SET_TYPE1_CMP(InstMem[8], 4, 5);
    SET_TYPE4_RJMP(InstMem[9], COND_NE, RD, 1); //should not jump 
    SET_TYPE1_MOVE(InstMem[10], 22, 12);
    SET_ERROR_INST(InstMem[11]);
    
    
    
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL(0, GET_CPU_LR_REG());
    TEST_ASSERT_EQUAL(70, GET_CPU_REG(20));
    TEST_ASSERT_EQUAL(80, GET_CPU_REG(21));
    TEST_ASSERT_EQUAL(90, GET_CPU_REG(22));
}

SET_TEST(TESTNAME, test_rjmp_without_link_under_CS_condition)
{
	int InstSize, RD;
    
    //given
	InstSize = 12;
    
    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    //set CPU register
    RD = 6; SET_CPU_REG(RD, 1 * 4);
    SET_CPU_REG(0, 60);  SET_CPU_REG(1, 50);
    SET_CPU_REG(2, 60);  SET_CPU_REG(3, 60);
    SET_CPU_REG(4, 30);  SET_CPU_REG(5, 60);
    SET_CPU_REG(10, 70); SET_CPU_REG(11, 80); SET_CPU_REG(12, 90);  
    
    //write instrction memory
    SET_TYPE1_CMP(InstMem[0], 0, 1);
    SET_TYPE4_RJMP(InstMem[1], COND_CS, RD, 1); //should jump 
    SET_ERROR_INST(InstMem[2]);
    SET_TYPE1_MOVE(InstMem[3], 20, 10);

    SET_TYPE1_CMP(InstMem[4], 2, 3);
    SET_TYPE4_RJMP(InstMem[5], COND_CS, RD, 1); //should jump 
    SET_ERROR_INST(InstMem[6]);
    SET_TYPE1_MOVE(InstMem[7], 21, 11);

    SET_TYPE1_CMP(InstMem[8], 4, 5);
    SET_TYPE4_RJMP(InstMem[9], COND_CS, RD, 1); //should not jump 
    SET_TYPE1_MOVE(InstMem[10], 22, 12);
    SET_ERROR_INST(InstMem[11]);
    
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL(0, GET_CPU_LR_REG());
    TEST_ASSERT_EQUAL(70, GET_CPU_REG(20));
    TEST_ASSERT_EQUAL(80, GET_CPU_REG(21));
    TEST_ASSERT_EQUAL(90, GET_CPU_REG(22));
}

SET_TEST(TESTNAME, test_rjmp_without_link_under_CC_condition)
{
	int InstSize, RD;
    
    //given
	InstSize = 12;
    
    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    //set CPU register
    RD = 6; SET_CPU_REG(RD, 1 * 4);
    SET_CPU_REG(0, 60);  SET_CPU_REG(1, 70);
    SET_CPU_REG(2, 60);  SET_CPU_REG(3, 60);
    SET_CPU_REG(4, 30);  SET_CPU_REG(5, 20);
    SET_CPU_REG(10, 70); SET_CPU_REG(11, 80); SET_CPU_REG(12, 90);  
    
    //write instrction memory
    SET_TYPE1_CMP(InstMem[0], 0, 1);
    SET_TYPE4_RJMP(InstMem[1], COND_CC, RD, 1); //should jump 
    SET_ERROR_INST(InstMem[2]);
    SET_TYPE1_MOVE(InstMem[3], 20, 10);

    SET_TYPE1_CMP(InstMem[4], 2, 3);
    SET_TYPE4_RJMP(InstMem[5], COND_CC, RD, 5); //should not jump 
    SET_TYPE1_MOVE(InstMem[6], 21, 11);
    SET_TYPE1_MOVE(InstMem[7], 21, 11);

    SET_TYPE1_CMP(InstMem[8], 4, 5);
    SET_TYPE4_RJMP(InstMem[9], COND_CC, RD, 1); //should not jump 
    SET_TYPE1_MOVE(InstMem[10], 22, 12);
    SET_ERROR_INST(InstMem[11]);
    
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL(0, GET_CPU_LR_REG());
    TEST_ASSERT_EQUAL(70, GET_CPU_REG(20));
    TEST_ASSERT_EQUAL(80, GET_CPU_REG(21));
    TEST_ASSERT_EQUAL(90, GET_CPU_REG(22));
}

SET_TEST(TESTNAME, test_rjmp_without_link_under_MI_condition)
{
	int InstSize, RD;
    
    //given
	InstSize = 12;
    
    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    //set CPU register
    RD = 6; SET_CPU_REG(RD, 1 * 4);
    SET_CPU_REG(0, 60);  SET_CPU_REG(1, 70);
    SET_CPU_REG(2, 60);  SET_CPU_REG(3, 60);
    SET_CPU_REG(4, 30);  SET_CPU_REG(5, 20);
    SET_CPU_REG(10, 70); SET_CPU_REG(11, 80); SET_CPU_REG(12, 90);  
    
    //write instrction memory
    SET_TYPE1_CMP(InstMem[0], 0, 1);
    SET_TYPE4_RJMP(InstMem[1], COND_MI, RD, 1); //should jump 
    SET_ERROR_INST(InstMem[2]);
    SET_TYPE1_MOVE(InstMem[3], 20, 10);

    SET_TYPE1_CMP(InstMem[4], 2, 3);
    SET_TYPE4_RJMP(InstMem[5], COND_MI, RD, 5); //should not jump 
    SET_TYPE1_MOVE(InstMem[6], 21, 11);
    SET_TYPE1_MOVE(InstMem[7], 21, 11);

    SET_TYPE1_CMP(InstMem[8], 4, 5);
    SET_TYPE4_RJMP(InstMem[9], COND_MI, RD, 1); //should not jump 
    SET_TYPE1_MOVE(InstMem[10], 22, 12);
    SET_ERROR_INST(InstMem[11]);
    
    
    
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL(0, GET_CPU_LR_REG());
    TEST_ASSERT_EQUAL(70, GET_CPU_REG(20));
    TEST_ASSERT_EQUAL(80, GET_CPU_REG(21));
    TEST_ASSERT_EQUAL(90, GET_CPU_REG(22));
}

SET_TEST(TESTNAME, test_rjmp_without_link_under_PL_condition)
{
	int InstSize, RD;
    
    //given
	InstSize = 12;
    
    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    //set CPU register
    RD = 6; SET_CPU_REG(RD, 1 * 4);
    SET_CPU_REG(0, 60);  SET_CPU_REG(1, 50);
    SET_CPU_REG(2, 60);  SET_CPU_REG(3, 60);
    SET_CPU_REG(4, 30);  SET_CPU_REG(5, 60);
    SET_CPU_REG(10, 70); SET_CPU_REG(11, 80); SET_CPU_REG(12, 90);  
    
    //write instrction memory
    SET_TYPE1_CMP(InstMem[0], 0, 1);
    SET_TYPE4_RJMP(InstMem[1], COND_PL, RD, 1); //should jump 
    SET_ERROR_INST(InstMem[2]);
    SET_TYPE1_MOVE(InstMem[3], 20, 10);

    SET_TYPE1_CMP(InstMem[4], 2, 3);
    SET_TYPE4_RJMP(InstMem[5], COND_PL, RD, 1); //should jump 
    SET_ERROR_INST(InstMem[6]);
    SET_TYPE1_MOVE(InstMem[7], 21, 11);

    SET_TYPE1_CMP(InstMem[8], 4, 5);
    SET_TYPE4_RJMP(InstMem[9], COND_PL, RD, 1); //should not jump 
    SET_TYPE1_MOVE(InstMem[10], 22, 12);
    SET_ERROR_INST(InstMem[11]);
    
    
    
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL(0, GET_CPU_LR_REG());
    TEST_ASSERT_EQUAL(70, GET_CPU_REG(20));
    TEST_ASSERT_EQUAL(80, GET_CPU_REG(21));
    TEST_ASSERT_EQUAL(90, GET_CPU_REG(22));
}

SET_TEST(TESTNAME, test_rjmp_without_link_under_VS_condition)
{
	int InstSize, RD;
    
    //given
	InstSize = 12;
    
    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    //set CPU register
    RD = 6; SET_CPU_REG(RD, 1 * 4);
    SET_CPU_REG(0, 0x7fffff60);  SET_CPU_REG(1, 0x81000060);
    SET_CPU_REG(2, 0x81000060);  SET_CPU_REG(3, 0x7fffff60);
    SET_CPU_REG(4, 30);  SET_CPU_REG(5, 60);
    SET_CPU_REG(10, 70); SET_CPU_REG(11, 80); SET_CPU_REG(12, 90);  
    
    //write instrction memory
    SET_TYPE1_CMP(InstMem[0], 0, 1);
    SET_TYPE4_RJMP(InstMem[1], COND_VS, RD, 1); //should jump 
    SET_ERROR_INST(InstMem[2]);
    SET_TYPE1_MOVE(InstMem[3], 20, 10);

    SET_TYPE1_CMP(InstMem[4], 2, 3);
    SET_TYPE4_RJMP(InstMem[5], COND_VS, RD, 1); //should jump 
    SET_ERROR_INST(InstMem[6]);
    SET_TYPE1_MOVE(InstMem[7], 21, 11);

    SET_TYPE1_CMP(InstMem[8], 4, 5);
    SET_TYPE4_RJMP(InstMem[9], COND_VS, RD, 1); //should not jump 
    SET_TYPE1_MOVE(InstMem[10], 22, 12);
    SET_ERROR_INST(InstMem[11]);
    
    
    
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL(0, GET_CPU_LR_REG());
    TEST_ASSERT_EQUAL(70, GET_CPU_REG(20));
    TEST_ASSERT_EQUAL(80, GET_CPU_REG(21));
    TEST_ASSERT_EQUAL(90, GET_CPU_REG(22));
}

SET_TEST(TESTNAME, test_rjmp_without_link_under_VC_condition)
{
	int InstSize, RD;
    
    //given
	InstSize = 12;
    
    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    //set CPU register
    RD = 6; SET_CPU_REG(RD, 1 * 4);
    SET_CPU_REG(0, 60);  SET_CPU_REG(1, 60);
    SET_CPU_REG(2, 60);  SET_CPU_REG(3, 60);
    SET_CPU_REG(4, 0x7fffff30);  SET_CPU_REG(5, 0x81000060);
    SET_CPU_REG(10, 70); SET_CPU_REG(11, 80); SET_CPU_REG(12, 90);  
    
    //write instrction memory
    SET_TYPE1_CMP(InstMem[0], 0, 1);
    SET_TYPE4_RJMP(InstMem[1], COND_VC, RD, 1); //should jump 
    SET_ERROR_INST(InstMem[2]);
    SET_TYPE1_MOVE(InstMem[3], 20, 10);

    SET_TYPE1_CMP(InstMem[4], 2, 3);
    SET_TYPE4_RJMP(InstMem[5], COND_VC, RD, 1); //should jump 
    SET_ERROR_INST(InstMem[6]);
    SET_TYPE1_MOVE(InstMem[7], 21, 11);

    SET_TYPE1_CMP(InstMem[8], 4, 5);
    SET_TYPE4_RJMP(InstMem[9], COND_VC, RD, 1); //should not jump 
    SET_TYPE1_MOVE(InstMem[10], 22, 12);
    SET_ERROR_INST(InstMem[11]);
    
    
    
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL(0, GET_CPU_LR_REG());
    TEST_ASSERT_EQUAL(70, GET_CPU_REG(20));
    TEST_ASSERT_EQUAL(80, GET_CPU_REG(21));
    TEST_ASSERT_EQUAL(90, GET_CPU_REG(22));
}

SET_TEST(TESTNAME, test_rjmp_without_link_under_HI_condition)
{
	int InstSize, RD;
    
    //given
	InstSize = 12;
    
    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    //set CPU register
    RD = 6; SET_CPU_REG(RD, 1 * 4);
    SET_CPU_REG(0, 60);  SET_CPU_REG(1, 50);
    SET_CPU_REG(2, 60);  SET_CPU_REG(3, 60);
    SET_CPU_REG(4, 30);  SET_CPU_REG(5, 60);
    SET_CPU_REG(10, 70); SET_CPU_REG(11, 80); SET_CPU_REG(12, 90);  
    
    //write instrction memory
    SET_TYPE1_CMP(InstMem[0], 0, 1);
    SET_TYPE4_RJMP(InstMem[1], COND_HI, RD, 1); //should jump 
    SET_ERROR_INST(InstMem[2]);
    SET_TYPE1_MOVE(InstMem[3], 20, 10);

    SET_TYPE1_CMP(InstMem[4], 2, 3);
    SET_TYPE4_RJMP(InstMem[5], COND_HI, RD, 5); //should not jump 
    SET_TYPE1_MOVE(InstMem[6], 21, 11);
    SET_TYPE1_MOVE(InstMem[7], 21, 11);
    
    SET_TYPE1_CMP(InstMem[8], 4, 5);
    SET_TYPE4_RJMP(InstMem[9], COND_HI, RD, 1); //should not jump 
    SET_TYPE1_MOVE(InstMem[10], 22, 12);
    SET_ERROR_INST(InstMem[11]);
    
    
    
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL(0, GET_CPU_LR_REG());
    TEST_ASSERT_EQUAL(70, GET_CPU_REG(20));
    TEST_ASSERT_EQUAL(80, GET_CPU_REG(21));
    TEST_ASSERT_EQUAL(90, GET_CPU_REG(22));
}

SET_TEST(TESTNAME, test_rjmp_without_link_under_LS_condition)
{
	int InstSize, RD;
    
    //given
	InstSize = 12;
    
    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    //set CPU register
    RD = 6; SET_CPU_REG(RD, 1 * 4);
    SET_CPU_REG(0, 60);  SET_CPU_REG(1, 70);
    SET_CPU_REG(2, 60);  SET_CPU_REG(3, 60);
    SET_CPU_REG(4, 30);  SET_CPU_REG(5, 20);
    SET_CPU_REG(10, 70); SET_CPU_REG(11, 80); SET_CPU_REG(12, 90);  
    
    //write instrction memory
    SET_TYPE1_CMP(InstMem[0], 0, 1);
    SET_TYPE4_RJMP(InstMem[1], COND_LS, RD, 1); //should jump 
    SET_ERROR_INST(InstMem[2]);
    SET_TYPE1_MOVE(InstMem[3], 20, 10);

    SET_TYPE1_CMP(InstMem[4], 2, 3);
    SET_TYPE4_RJMP(InstMem[5], COND_LS, RD, 1); //should jump 
    SET_ERROR_INST(InstMem[6]);
    SET_TYPE1_MOVE(InstMem[7], 21, 11);

    SET_TYPE1_CMP(InstMem[8], 4, 5);
    SET_TYPE4_RJMP(InstMem[9], COND_LS, RD, 1); //should not jump 
    SET_TYPE1_MOVE(InstMem[10], 22, 12);
    SET_ERROR_INST(InstMem[11]);
    
    
    
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL(0, GET_CPU_LR_REG());
    TEST_ASSERT_EQUAL(70, GET_CPU_REG(20));
    TEST_ASSERT_EQUAL(80, GET_CPU_REG(21));
    TEST_ASSERT_EQUAL(90, GET_CPU_REG(22));
}

SET_TEST(TESTNAME, test_rjmp_without_link_under_GE_condition)
{
	int InstSize, RD;
    
    //given
	InstSize = 12;
    
    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    //set CPU register
    RD = 6; SET_CPU_REG(RD, 1 * 4);
    SET_CPU_REG(0, 60);  SET_CPU_REG(1, 50);
    SET_CPU_REG(2, 60);  SET_CPU_REG(3, 60);
    SET_CPU_REG(4, 30);  SET_CPU_REG(5, 60);
    SET_CPU_REG(10, 70); SET_CPU_REG(11, 80); SET_CPU_REG(12, 90);  
    
    //write instrction memory
    SET_TYPE1_CMP(InstMem[0], 0, 1);
    SET_TYPE4_RJMP(InstMem[1], COND_GE, RD, 1); //should jump 
    SET_ERROR_INST(InstMem[2]);
    SET_TYPE1_MOVE(InstMem[3], 20, 10);

    SET_TYPE1_CMP(InstMem[4], 2, 3);
    SET_TYPE4_RJMP(InstMem[5], COND_GE, RD, 1); //should jump 
    SET_ERROR_INST(InstMem[6]);
    SET_TYPE1_MOVE(InstMem[7], 21, 11);

    SET_TYPE1_CMP(InstMem[8], 4, 5);
    SET_TYPE4_RJMP(InstMem[9], COND_GE, RD, 1); //should not jump 
    SET_TYPE1_MOVE(InstMem[10], 22, 12);
    SET_ERROR_INST(InstMem[11]);
    
    
    
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL(0, GET_CPU_LR_REG());
    TEST_ASSERT_EQUAL(70, GET_CPU_REG(20));
    TEST_ASSERT_EQUAL(80, GET_CPU_REG(21));
    TEST_ASSERT_EQUAL(90, GET_CPU_REG(22));
}

SET_TEST(TESTNAME, test_rjmp_without_link_under_LT_condition)
{
	int InstSize, RD;
    
    //given
	InstSize = 12;
    
    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    //set CPU register
    RD = 6; SET_CPU_REG(RD, 1 * 4);
    SET_CPU_REG(0, 60);  SET_CPU_REG(1, 70);
    SET_CPU_REG(2, 60);  SET_CPU_REG(3, 60);
    SET_CPU_REG(4, 30);  SET_CPU_REG(5, 20);
    SET_CPU_REG(10, 70); SET_CPU_REG(11, 80); SET_CPU_REG(12, 90);  
    
    //write instrction memory
    SET_TYPE1_CMP(InstMem[0], 0, 1);
    SET_TYPE4_RJMP(InstMem[1], COND_LT, RD, 1); //should jump 
    SET_ERROR_INST(InstMem[2]);
    SET_TYPE1_MOVE(InstMem[3], 20, 10);

    SET_TYPE1_CMP(InstMem[4], 2, 3);
    SET_TYPE4_RJMP(InstMem[5], COND_LT, RD, 5); //should not jump 
    SET_TYPE1_MOVE(InstMem[6], 21, 11);
    SET_TYPE1_MOVE(InstMem[7], 21, 11);

    SET_TYPE1_CMP(InstMem[8], 4, 5);
    SET_TYPE4_RJMP(InstMem[9], COND_LT, RD, 1); //should not jump 
    SET_TYPE1_MOVE(InstMem[10], 22, 12);
    SET_ERROR_INST(InstMem[11]);
    
    
    
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL(0, GET_CPU_LR_REG());
    TEST_ASSERT_EQUAL(70, GET_CPU_REG(20));
    TEST_ASSERT_EQUAL(80, GET_CPU_REG(21));
    TEST_ASSERT_EQUAL(90, GET_CPU_REG(22));
}

SET_TEST(TESTNAME, test_rjmp_without_link_under_GT_condition)
{
	int InstSize, RD;
    
    //given
	InstSize = 12;
    
    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    //set CPU register
    RD = 6; SET_CPU_REG(RD, 1 * 4);
    SET_CPU_REG(0, 60);  SET_CPU_REG(1, 50);
    SET_CPU_REG(2, 60);  SET_CPU_REG(3, 60);
    SET_CPU_REG(4, 30);  SET_CPU_REG(5, 60);
    SET_CPU_REG(10, 70); SET_CPU_REG(11, 80); SET_CPU_REG(12, 90);  
    
    //write instrction memory
    SET_TYPE1_CMP(InstMem[0], 0, 1);
    SET_TYPE4_RJMP(InstMem[1], COND_GT, RD, 1); //should jump 
    SET_ERROR_INST(InstMem[2]);
    SET_TYPE1_MOVE(InstMem[3], 20, 10);

    SET_TYPE1_CMP(InstMem[4], 2, 3);
    SET_TYPE4_RJMP(InstMem[5], COND_GT, RD, 5); //should not jump 
    SET_TYPE1_MOVE(InstMem[7], 21, 11);
    SET_TYPE1_MOVE(InstMem[7], 21, 11);

    SET_TYPE1_CMP(InstMem[8], 4, 5);
    SET_TYPE4_RJMP(InstMem[9], COND_GT, RD, 1); //should not jump 
    SET_TYPE1_MOVE(InstMem[10], 22, 12);
    SET_ERROR_INST(InstMem[11]);
    
    
    
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL(0, GET_CPU_LR_REG());
    TEST_ASSERT_EQUAL(70, GET_CPU_REG(20));
    TEST_ASSERT_EQUAL(80, GET_CPU_REG(21));
    TEST_ASSERT_EQUAL(90, GET_CPU_REG(22));
}

SET_TEST(TESTNAME, test_rjmp_without_link_under_LE_condition)
{
	int InstSize, RD;
    
    //given
	InstSize = 12;
    
    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    //set CPU register
    RD = 6; SET_CPU_REG(RD, 1 * 4);
    SET_CPU_REG(0, 60);  SET_CPU_REG(1, 70);
    SET_CPU_REG(2, 60);  SET_CPU_REG(3, 60);
    SET_CPU_REG(4, 30);  SET_CPU_REG(5, 20);
    SET_CPU_REG(10, 70); SET_CPU_REG(11, 80); SET_CPU_REG(12, 90);  
    
    //write instrction memory
    SET_TYPE1_CMP(InstMem[0], 0, 1);
    SET_TYPE4_RJMP(InstMem[1], COND_LE, RD, 1); //should jump 
    SET_ERROR_INST(InstMem[2]);
    SET_TYPE1_MOVE(InstMem[3], 20, 10);

    SET_TYPE1_CMP(InstMem[4], 2, 3);
    SET_TYPE4_RJMP(InstMem[5], COND_LE, RD, 1); //should jump 
    SET_ERROR_INST(InstMem[6]);
    SET_TYPE1_MOVE(InstMem[7], 21, 11);

    SET_TYPE1_CMP(InstMem[8], 4, 5);
    SET_TYPE4_RJMP(InstMem[9], COND_LE, RD, 1); //should not jump 
    SET_TYPE1_MOVE(InstMem[10], 22, 12);
    SET_ERROR_INST(InstMem[11]);
    
    
    
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL(0, GET_CPU_LR_REG());
    TEST_ASSERT_EQUAL(70, GET_CPU_REG(20));
    TEST_ASSERT_EQUAL(80, GET_CPU_REG(21));
    TEST_ASSERT_EQUAL(90, GET_CPU_REG(22));
}

SET_TEST(TESTNAME, test_rjmp_without_link_under_AL_condition)
{
	int InstSize, RD;
    
    //given
	InstSize = 12;
    
    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    //set CPU register
    RD = 6; SET_CPU_REG(RD, 1 * 4);
    SET_CPU_REG(0, 60);  SET_CPU_REG(1, 50);
    SET_CPU_REG(2, 60);  SET_CPU_REG(3, 60);
    SET_CPU_REG(4, 30);  SET_CPU_REG(5, 60);
    SET_CPU_REG(10, 70); SET_CPU_REG(11, 80); SET_CPU_REG(12, 90);  
    
    //write instrction memory
    SET_TYPE1_CMP(InstMem[0], 0, 1);
    SET_TYPE4_RJMP(InstMem[1], COND_AL, RD, 1); //should jump 
    SET_ERROR_INST(InstMem[2]);
    SET_TYPE1_MOVE(InstMem[3], 20, 10);

    SET_TYPE1_CMP(InstMem[4], 2, 3);
    SET_TYPE4_RJMP(InstMem[5], COND_AL, RD, 1); //should jump 
    SET_ERROR_INST(InstMem[6]);
    SET_TYPE1_MOVE(InstMem[7], 21, 11);

    SET_TYPE1_CMP(InstMem[8], 4, 5);
    SET_TYPE4_RJMP(InstMem[9], COND_AL, RD, 1); //should jump 
    SET_ERROR_INST(InstMem[10]);
    SET_TYPE1_MOVE(InstMem[11], 22, 12);
    
    
    
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL(0, GET_CPU_LR_REG());
    TEST_ASSERT_EQUAL(70, GET_CPU_REG(20));
    TEST_ASSERT_EQUAL(80, GET_CPU_REG(21));
    TEST_ASSERT_EQUAL(90, GET_CPU_REG(22));
}

SET_TEST(TESTNAME, test_rjmp_without_link_under_RSV_condition)
{
	int InstSize, RD;
    
    //given
	InstSize = 12;
    
    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    //set CPU register
    RD = 6; SET_CPU_REG(RD, 1 * 4);
    SET_CPU_REG(0, 60);  SET_CPU_REG(1, 50);
    SET_CPU_REG(2, 60);  SET_CPU_REG(3, 60);
    SET_CPU_REG(4, 30);  SET_CPU_REG(5, 60);
    SET_CPU_REG(10, 70); SET_CPU_REG(11, 80); SET_CPU_REG(12, 90);  
    
    //write instrction memory
    SET_TYPE1_CMP(InstMem[0], 0, 1);
    SET_TYPE4_RJMP(InstMem[1], COND_RSV, RD, 9); //should not jump 
    SET_TYPE1_MOVE(InstMem[3], 20, 10);
    SET_TYPE1_MOVE(InstMem[3], 20, 10);

    SET_TYPE1_CMP(InstMem[4], 2, 3);
    SET_TYPE4_RJMP(InstMem[5], COND_RSV, RD, 5); //should not jump 
    SET_TYPE1_MOVE(InstMem[7], 21, 11);
    SET_TYPE1_MOVE(InstMem[7], 21, 11);

    SET_TYPE1_CMP(InstMem[8], 4, 5);
    SET_TYPE4_RJMP(InstMem[9], COND_RSV, RD, 1); //should not jump 
    SET_TYPE1_MOVE(InstMem[10], 22, 12);
    SET_ERROR_INST(InstMem[11]);
    
    
    
    
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL(0, GET_CPU_LR_REG());
    TEST_ASSERT_EQUAL(70, GET_CPU_REG(20));
    TEST_ASSERT_EQUAL(80, GET_CPU_REG(21));
    TEST_ASSERT_EQUAL(90, GET_CPU_REG(22));
}

SET_TEST(TESTNAME, test_rjmp_with_link_under_AL_condition)
{
	int InstSize, RD;
    
    //given
	InstSize = 5;
    
    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    //set CPU register
    RD = 6; SET_CPU_REG(RD, 1 * 4);
    SET_CPU_REG(0, 60);  SET_CPU_REG(1, 50);
    SET_CPU_REG(10, 70); 
    
    //write instrction memory
    SET_TYPE1_CMP(InstMem[0], 0, 1);
    SET_TYPE4_RJMPL(InstMem[1], COND_AL, RD, 1); //should jump 
    SET_ERROR_INST(InstMem[2]);
    SET_TYPE1_MOVE(InstMem[3], 20, 10);
    SET_ERROR_INST(InstMem[4]);
    
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL(2 * 4, GET_CPU_LR_REG());
    TEST_ASSERT_EQUAL(70, GET_CPU_REG(20));
    
}

SET_TEST(TESTNAME, test_rjmp_ahead_without_link_under_AL_condition)
{
	int InstSize, RD;
    
    //given
	InstSize = 12;
    
    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    //set CPU register
    RD = 6; SET_CPU_REG(RD, 1 * 4);
    SET_CPU_REG(0, 60);  SET_CPU_REG(1, 50);
    SET_CPU_REG(2, 60);  SET_CPU_REG(3, 60);
    SET_CPU_REG(4, 30);  SET_CPU_REG(5, 60);
    SET_CPU_REG(10, 70); SET_CPU_REG(11, 80); SET_CPU_REG(12, 90);  
    
    //write instrction memory
    SET_TYPE1_CMP(InstMem[0], 0, 1);
    SET_TYPE4_RJMP(InstMem[1], COND_AL, RD, 5); //should jump 
    SET_ERROR_INST(InstMem[2]);
    SET_TYPE1_MOVE(InstMem[3], 20, 10);

    SET_TYPE1_CMP(InstMem[4], 2, 3);
    SET_TYPE4_RJMP(InstMem[5], COND_AL, RD, 5); //should jump 
    SET_ERROR_INST(InstMem[6]);
    SET_TYPE1_MOVE(InstMem[7], 21, 11);

    SET_TYPE1_CMP(InstMem[8], 4, 5);
    SET_TYPE4_RJMP(InstMem[9], COND_AL, RD, (unsigned int)(-7)); //should jump 
    SET_ERROR_INST(InstMem[10]);
    SET_TYPE1_MOVE(InstMem[11], 22, 12);
    
    
    
	while (!run_cpu())
	{
	}

	//expected
    TEST_ASSERT_EQUAL(0, GET_CPU_LR_REG());
    TEST_ASSERT_EQUAL(70, GET_CPU_REG(20));
    TEST_ASSERT_EQUAL(80, GET_CPU_REG(21));
    TEST_ASSERT_EQUAL(90, GET_CPU_REG(22));
    
}

SET_TEST_GROUP_RUNNER(TESTNAME)
{
	printf("test instruction %s \n", GET_STR(TESTNAME));

	SET_RUN_TEST_CASE(TESTNAME, test_rjmp_without_link_under_EQ_condition);
    SET_RUN_TEST_CASE(TESTNAME, test_rjmp_without_link_under_NE_condition);
    SET_RUN_TEST_CASE(TESTNAME, test_rjmp_without_link_under_CS_condition);
    SET_RUN_TEST_CASE(TESTNAME, test_rjmp_without_link_under_CC_condition);
    SET_RUN_TEST_CASE(TESTNAME, test_rjmp_without_link_under_MI_condition);
    SET_RUN_TEST_CASE(TESTNAME, test_rjmp_without_link_under_PL_condition);
    SET_RUN_TEST_CASE(TESTNAME, test_rjmp_without_link_under_VS_condition);
    SET_RUN_TEST_CASE(TESTNAME, test_rjmp_without_link_under_VC_condition);
    SET_RUN_TEST_CASE(TESTNAME, test_rjmp_without_link_under_HI_condition);
    SET_RUN_TEST_CASE(TESTNAME, test_rjmp_without_link_under_LS_condition);
    SET_RUN_TEST_CASE(TESTNAME, test_rjmp_without_link_under_GE_condition);
    SET_RUN_TEST_CASE(TESTNAME, test_rjmp_without_link_under_LT_condition);
    SET_RUN_TEST_CASE(TESTNAME, test_rjmp_without_link_under_GT_condition);
    SET_RUN_TEST_CASE(TESTNAME, test_rjmp_without_link_under_LE_condition);
    SET_RUN_TEST_CASE(TESTNAME, test_rjmp_without_link_under_AL_condition);
    SET_RUN_TEST_CASE(TESTNAME, test_rjmp_without_link_under_RSV_condition);
    SET_RUN_TEST_CASE(TESTNAME, test_rjmp_with_link_under_AL_condition);
    SET_RUN_TEST_CASE(TESTNAME, test_rjmp_ahead_without_link_under_AL_condition);
}

