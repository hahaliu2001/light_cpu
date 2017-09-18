/*
 * test_inst_type3_ajmp.c
 *
 *  Created on: Sep 16, 2017
 *      Author: jie
 */

#include "cpu_external.h"
#include "mem.h"
#include "cpu_test_helper.h"
#include "unity.h"
#include "unity_fixture.h"

#undef  TESTNAME
#define TESTNAME inst_type3_ajmp

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

SET_TEST(TESTNAME, test_ajmp_without_link_under_EQ_condition)
{
	int InstSize;
    
    //given
	InstSize = 12;
    
    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    //set CPU register
    SET_CPU_REG(0, 60);  SET_CPU_REG(1, 60);
    SET_CPU_REG(2, 60);  SET_CPU_REG(3, 60);
    SET_CPU_REG(4, 30);  SET_CPU_REG(5, 60);
    SET_CPU_REG(10, 70); SET_CPU_REG(11, 80); SET_CPU_REG(12, 90);  
    
    //write instrction memory
    SET_TYPE1_CMP(InstMem[0], 0, 1);
    SET_TYPE3_AJMP(InstMem[1], COND_EQ, 3); //should jump 
    SET_ERROR_INST(InstMem[2]);
    SET_TYPE1_MOVE(InstMem[3], 20, 10);

    SET_TYPE1_CMP(InstMem[4], 2, 3);
    SET_TYPE3_AJMP(InstMem[5], COND_EQ, 7); //should jump 
    SET_ERROR_INST(InstMem[6]);
    SET_TYPE1_MOVE(InstMem[7], 21, 11);

    SET_TYPE1_CMP(InstMem[8], 4, 5);
    SET_TYPE3_AJMP(InstMem[9], COND_EQ, 11); //should not jump 
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

SET_TEST(TESTNAME, test_ajmp_without_link_under_NE_condition)
{
	int InstSize;
    
    //given
	InstSize = 12;
    
    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    //set CPU register
    SET_CPU_REG(0, 50);  SET_CPU_REG(1, 60);
    SET_CPU_REG(2, 50);  SET_CPU_REG(3, 60);
    SET_CPU_REG(4, 60);  SET_CPU_REG(5, 60);
    SET_CPU_REG(10, 70); SET_CPU_REG(11, 80); SET_CPU_REG(12, 90);  
    
    //write instrction memory
    SET_TYPE1_CMP(InstMem[0], 0, 1);
    SET_TYPE3_AJMP(InstMem[1], COND_NE, 3); //should jump 
    SET_ERROR_INST(InstMem[2]);
    SET_TYPE1_MOVE(InstMem[3], 20, 10);

    SET_TYPE1_CMP(InstMem[4], 2, 3);
    SET_TYPE3_AJMP(InstMem[5], COND_NE, 7); //should jump 
    SET_ERROR_INST(InstMem[6]);
    SET_TYPE1_MOVE(InstMem[7], 21, 11);

    SET_TYPE1_CMP(InstMem[8], 4, 5);
    SET_TYPE3_AJMP(InstMem[9], COND_NE, 11); //should not jump 
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

SET_TEST(TESTNAME, test_ajmp_without_link_under_CS_condition)
{
	int InstSize;
    
    //given
	InstSize = 12;
    
    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    //set CPU register
    SET_CPU_REG(0, 60);  SET_CPU_REG(1, 50);
    SET_CPU_REG(2, 60);  SET_CPU_REG(3, 60);
    SET_CPU_REG(4, 30);  SET_CPU_REG(5, 60);
    SET_CPU_REG(10, 70); SET_CPU_REG(11, 80); SET_CPU_REG(12, 90);  
    
    //write instrction memory
    SET_TYPE1_CMP(InstMem[0], 0, 1);
    SET_TYPE3_AJMP(InstMem[1], COND_CS, 3); //should jump 
    SET_ERROR_INST(InstMem[2]);
    SET_TYPE1_MOVE(InstMem[3], 20, 10);

    SET_TYPE1_CMP(InstMem[4], 2, 3);
    SET_TYPE3_AJMP(InstMem[5], COND_CS, 7); //should jump 
    SET_ERROR_INST(InstMem[6]);
    SET_TYPE1_MOVE(InstMem[7], 21, 11);

    SET_TYPE1_CMP(InstMem[8], 4, 5);
    SET_TYPE3_AJMP(InstMem[9], COND_CS, 11); //should not jump 
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

SET_TEST(TESTNAME, test_ajmp_without_link_under_CC_condition)
{
	int InstSize;
    
    //given
	InstSize = 12;
    
    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    //set CPU register
    SET_CPU_REG(0, 60);  SET_CPU_REG(1, 70);
    SET_CPU_REG(2, 60);  SET_CPU_REG(3, 60);
    SET_CPU_REG(4, 30);  SET_CPU_REG(5, 20);
    SET_CPU_REG(10, 70); SET_CPU_REG(11, 80); SET_CPU_REG(12, 90);  
    
    //write instrction memory
    SET_TYPE1_CMP(InstMem[0], 0, 1);
    SET_TYPE3_AJMP(InstMem[1], COND_CC, 3); //should jump 
    SET_ERROR_INST(InstMem[2]);
    SET_TYPE1_MOVE(InstMem[3], 20, 10);

    SET_TYPE1_CMP(InstMem[4], 2, 3);
    SET_TYPE3_AJMP(InstMem[5], COND_CC, 11); //should not jump 
    SET_TYPE1_MOVE(InstMem[6], 21, 11);
    SET_TYPE1_MOVE(InstMem[7], 21, 11);

    SET_TYPE1_CMP(InstMem[8], 4, 5);
    SET_TYPE3_AJMP(InstMem[9], COND_CC, 11); //should not jump 
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

SET_TEST(TESTNAME, test_ajmp_without_link_under_MI_condition)
{
	int InstSize;
    
    //given
	InstSize = 12;
    
    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    //set CPU register
    SET_CPU_REG(0, 60);  SET_CPU_REG(1, 70);
    SET_CPU_REG(2, 60);  SET_CPU_REG(3, 60);
    SET_CPU_REG(4, 30);  SET_CPU_REG(5, 20);
    SET_CPU_REG(10, 70); SET_CPU_REG(11, 80); SET_CPU_REG(12, 90);  
    
    //write instrction memory
    SET_TYPE1_CMP(InstMem[0], 0, 1);
    SET_TYPE3_AJMP(InstMem[1], COND_MI, 3); //should jump 
    SET_ERROR_INST(InstMem[2]);
    SET_TYPE1_MOVE(InstMem[3], 20, 10);

    SET_TYPE1_CMP(InstMem[4], 2, 3);
    SET_TYPE3_AJMP(InstMem[5], COND_MI, 11); //should not jump 
    SET_TYPE1_MOVE(InstMem[6], 21, 11);
    SET_TYPE1_MOVE(InstMem[7], 21, 11);

    SET_TYPE1_CMP(InstMem[8], 4, 5);
    SET_TYPE3_AJMP(InstMem[9], COND_MI, 11); //should not jump 
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

SET_TEST(TESTNAME, test_ajmp_without_link_under_PL_condition)
{
	int InstSize;
    
    //given
	InstSize = 12;
    
    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    //set CPU register
    SET_CPU_REG(0, 60);  SET_CPU_REG(1, 50);
    SET_CPU_REG(2, 60);  SET_CPU_REG(3, 60);
    SET_CPU_REG(4, 30);  SET_CPU_REG(5, 60);
    SET_CPU_REG(10, 70); SET_CPU_REG(11, 80); SET_CPU_REG(12, 90);  
    
    //write instrction memory
    SET_TYPE1_CMP(InstMem[0], 0, 1);
    SET_TYPE3_AJMP(InstMem[1], COND_PL, 3); //should jump 
    SET_ERROR_INST(InstMem[2]);
    SET_TYPE1_MOVE(InstMem[3], 20, 10);

    SET_TYPE1_CMP(InstMem[4], 2, 3);
    SET_TYPE3_AJMP(InstMem[5], COND_PL, 7); //should jump 
    SET_ERROR_INST(InstMem[6]);
    SET_TYPE1_MOVE(InstMem[7], 21, 11);

    SET_TYPE1_CMP(InstMem[8], 4, 5);
    SET_TYPE3_AJMP(InstMem[9], COND_PL, 11); //should not jump 
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

SET_TEST(TESTNAME, test_ajmp_without_link_under_VS_condition)
{
	int InstSize;
    
    //given
	InstSize = 12;
    
    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    //set CPU register
    SET_CPU_REG(0, 0x7fffff60);  SET_CPU_REG(1, 0x81000060);
    SET_CPU_REG(2, 0x81000060);  SET_CPU_REG(3, 0x7fffff60);
    SET_CPU_REG(4, 30);  SET_CPU_REG(5, 60);
    SET_CPU_REG(10, 70); SET_CPU_REG(11, 80); SET_CPU_REG(12, 90);  
    
    //write instrction memory
    SET_TYPE1_CMP(InstMem[0], 0, 1);
    SET_TYPE3_AJMP(InstMem[1], COND_VS, 3); //should jump 
    SET_ERROR_INST(InstMem[2]);
    SET_TYPE1_MOVE(InstMem[3], 20, 10);

    SET_TYPE1_CMP(InstMem[4], 2, 3);
    SET_TYPE3_AJMP(InstMem[5], COND_VS, 7); //should jump 
    SET_ERROR_INST(InstMem[6]);
    SET_TYPE1_MOVE(InstMem[7], 21, 11);

    SET_TYPE1_CMP(InstMem[8], 4, 5);
    SET_TYPE3_AJMP(InstMem[9], COND_VS, 11); //should not jump 
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

SET_TEST(TESTNAME, test_ajmp_without_link_under_VC_condition)
{
	int InstSize;
    
    //given
	InstSize = 12;
    
    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    //set CPU register
    SET_CPU_REG(0, 60);  SET_CPU_REG(1, 60);
    SET_CPU_REG(2, 60);  SET_CPU_REG(3, 60);
    SET_CPU_REG(4, 0x7fffff30);  SET_CPU_REG(5, 0x81000060);
    SET_CPU_REG(10, 70); SET_CPU_REG(11, 80); SET_CPU_REG(12, 90);  
    
    //write instrction memory
    SET_TYPE1_CMP(InstMem[0], 0, 1);
    SET_TYPE3_AJMP(InstMem[1], COND_VC, 3); //should jump 
    SET_ERROR_INST(InstMem[2]);
    SET_TYPE1_MOVE(InstMem[3], 20, 10);

    SET_TYPE1_CMP(InstMem[4], 2, 3);
    SET_TYPE3_AJMP(InstMem[5], COND_VC, 7); //should jump 
    SET_ERROR_INST(InstMem[6]);
    SET_TYPE1_MOVE(InstMem[7], 21, 11);

    SET_TYPE1_CMP(InstMem[8], 4, 5);
    SET_TYPE3_AJMP(InstMem[9], COND_VC, 11); //should not jump 
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

SET_TEST(TESTNAME, test_ajmp_without_link_under_HI_condition)
{
	int InstSize;
    
    //given
	InstSize = 12;
    
    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    //set CPU register
    SET_CPU_REG(0, 60);  SET_CPU_REG(1, 50);
    SET_CPU_REG(2, 60);  SET_CPU_REG(3, 60);
    SET_CPU_REG(4, 30);  SET_CPU_REG(5, 60);
    SET_CPU_REG(10, 70); SET_CPU_REG(11, 80); SET_CPU_REG(12, 90);  
    
    //write instrction memory
    SET_TYPE1_CMP(InstMem[0], 0, 1);
    SET_TYPE3_AJMP(InstMem[1], COND_HI, 3); //should jump 
    SET_ERROR_INST(InstMem[2]);
    SET_TYPE1_MOVE(InstMem[3], 20, 10);

    SET_TYPE1_CMP(InstMem[4], 2, 3);
    SET_TYPE3_AJMP(InstMem[5], COND_HI, 11); //should not jump 
    SET_TYPE1_MOVE(InstMem[6], 21, 11);
    SET_TYPE1_MOVE(InstMem[7], 21, 11);
    
    SET_TYPE1_CMP(InstMem[8], 4, 5);
    SET_TYPE3_AJMP(InstMem[9], COND_HI, 11); //should not jump 
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

SET_TEST(TESTNAME, test_ajmp_without_link_under_LS_condition)
{
	int InstSize;
    
    //given
	InstSize = 12;
    
    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    //set CPU register
    SET_CPU_REG(0, 60);  SET_CPU_REG(1, 70);
    SET_CPU_REG(2, 60);  SET_CPU_REG(3, 60);
    SET_CPU_REG(4, 30);  SET_CPU_REG(5, 20);
    SET_CPU_REG(10, 70); SET_CPU_REG(11, 80); SET_CPU_REG(12, 90);  
    
    //write instrction memory
    SET_TYPE1_CMP(InstMem[0], 0, 1);
    SET_TYPE3_AJMP(InstMem[1], COND_LS, 3); //should jump 
    SET_ERROR_INST(InstMem[2]);
    SET_TYPE1_MOVE(InstMem[3], 20, 10);

    SET_TYPE1_CMP(InstMem[4], 2, 3);
    SET_TYPE3_AJMP(InstMem[5], COND_LS, 7); //should jump 
    SET_ERROR_INST(InstMem[6]);
    SET_TYPE1_MOVE(InstMem[7], 21, 11);

    SET_TYPE1_CMP(InstMem[8], 4, 5);
    SET_TYPE3_AJMP(InstMem[9], COND_LS, 11); //should not jump 
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

SET_TEST(TESTNAME, test_ajmp_without_link_under_GE_condition)
{
	int InstSize;
    
    //given
	InstSize = 12;
    
    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    //set CPU register
    SET_CPU_REG(0, 60);  SET_CPU_REG(1, 50);
    SET_CPU_REG(2, 60);  SET_CPU_REG(3, 60);
    SET_CPU_REG(4, 30);  SET_CPU_REG(5, 60);
    SET_CPU_REG(10, 70); SET_CPU_REG(11, 80); SET_CPU_REG(12, 90);  
    
    //write instrction memory
    SET_TYPE1_CMP(InstMem[0], 0, 1);
    SET_TYPE3_AJMP(InstMem[1], COND_GE, 3); //should jump 
    SET_ERROR_INST(InstMem[2]);
    SET_TYPE1_MOVE(InstMem[3], 20, 10);

    SET_TYPE1_CMP(InstMem[4], 2, 3);
    SET_TYPE3_AJMP(InstMem[5], COND_GE, 7); //should jump 
    SET_ERROR_INST(InstMem[6]);
    SET_TYPE1_MOVE(InstMem[7], 21, 11);

    SET_TYPE1_CMP(InstMem[8], 4, 5);
    SET_TYPE3_AJMP(InstMem[9], COND_GE, 11); //should not jump 
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

SET_TEST(TESTNAME, test_ajmp_without_link_under_LT_condition)
{
	int InstSize;
    
    //given
	InstSize = 12;
    
    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    //set CPU register
    SET_CPU_REG(0, 60);  SET_CPU_REG(1, 70);
    SET_CPU_REG(2, 60);  SET_CPU_REG(3, 60);
    SET_CPU_REG(4, 30);  SET_CPU_REG(5, 20);
    SET_CPU_REG(10, 70); SET_CPU_REG(11, 80); SET_CPU_REG(12, 90);  
    
    //write instrction memory
    SET_TYPE1_CMP(InstMem[0], 0, 1);
    SET_TYPE3_AJMP(InstMem[1], COND_LT, 3); //should jump 
    SET_ERROR_INST(InstMem[2]);
    SET_TYPE1_MOVE(InstMem[3], 20, 10);

    SET_TYPE1_CMP(InstMem[4], 2, 3);
    SET_TYPE3_AJMP(InstMem[5], COND_LT, 11); //should not jump 
    SET_TYPE1_MOVE(InstMem[6], 21, 11);
    SET_TYPE1_MOVE(InstMem[7], 21, 11);

    SET_TYPE1_CMP(InstMem[8], 4, 5);
    SET_TYPE3_AJMP(InstMem[9], COND_LT, 11); //should not jump 
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

SET_TEST(TESTNAME, test_ajmp_without_link_under_GT_condition)
{
	int InstSize;
    
    //given
	InstSize = 12;
    
    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    //set CPU register
    SET_CPU_REG(0, 60);  SET_CPU_REG(1, 50);
    SET_CPU_REG(2, 60);  SET_CPU_REG(3, 60);
    SET_CPU_REG(4, 30);  SET_CPU_REG(5, 60);
    SET_CPU_REG(10, 70); SET_CPU_REG(11, 80); SET_CPU_REG(12, 90);  
    
    //write instrction memory
    SET_TYPE1_CMP(InstMem[0], 0, 1);
    SET_TYPE3_AJMP(InstMem[1], COND_GT, 3); //should jump 
    SET_ERROR_INST(InstMem[2]);
    SET_TYPE1_MOVE(InstMem[3], 20, 10);

    SET_TYPE1_CMP(InstMem[4], 2, 3);
    SET_TYPE3_AJMP(InstMem[5], COND_GT, 11); //should not jump 
    SET_TYPE1_MOVE(InstMem[7], 21, 11);
    SET_TYPE1_MOVE(InstMem[7], 21, 11);

    SET_TYPE1_CMP(InstMem[8], 4, 5);
    SET_TYPE3_AJMP(InstMem[9], COND_GT, 11); //should not jump 
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

SET_TEST(TESTNAME, test_ajmp_without_link_under_LE_condition)
{
	int InstSize;
    
    //given
	InstSize = 12;
    
    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    //set CPU register
    SET_CPU_REG(0, 60);  SET_CPU_REG(1, 70);
    SET_CPU_REG(2, 60);  SET_CPU_REG(3, 60);
    SET_CPU_REG(4, 30);  SET_CPU_REG(5, 20);
    SET_CPU_REG(10, 70); SET_CPU_REG(11, 80); SET_CPU_REG(12, 90);  
    
    //write instrction memory
    SET_TYPE1_CMP(InstMem[0], 0, 1);
    SET_TYPE3_AJMP(InstMem[1], COND_LE, 3); //should jump 
    SET_ERROR_INST(InstMem[2]);
    SET_TYPE1_MOVE(InstMem[3], 20, 10);

    SET_TYPE1_CMP(InstMem[4], 2, 3);
    SET_TYPE3_AJMP(InstMem[5], COND_LE, 7); //should jump 
    SET_ERROR_INST(InstMem[6]);
    SET_TYPE1_MOVE(InstMem[7], 21, 11);

    SET_TYPE1_CMP(InstMem[8], 4, 5);
    SET_TYPE3_AJMP(InstMem[9], COND_LE, 11); //should not jump 
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

SET_TEST(TESTNAME, test_ajmp_without_link_under_AL_condition)
{
	int InstSize;
    
    //given
	InstSize = 12;
    
    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    //set CPU register
    SET_CPU_REG(0, 60);  SET_CPU_REG(1, 50);
    SET_CPU_REG(2, 60);  SET_CPU_REG(3, 60);
    SET_CPU_REG(4, 30);  SET_CPU_REG(5, 60);
    SET_CPU_REG(10, 70); SET_CPU_REG(11, 80); SET_CPU_REG(12, 90);  
    
    //write instrction memory
    SET_TYPE1_CMP(InstMem[0], 0, 1);
    SET_TYPE3_AJMP(InstMem[1], COND_AL, 3); //should jump 
    SET_ERROR_INST(InstMem[2]);
    SET_TYPE1_MOVE(InstMem[3], 20, 10);

    SET_TYPE1_CMP(InstMem[4], 2, 3);
    SET_TYPE3_AJMP(InstMem[5], COND_AL, 7); //should jump 
    SET_ERROR_INST(InstMem[6]);
    SET_TYPE1_MOVE(InstMem[7], 21, 11);

    SET_TYPE1_CMP(InstMem[8], 4, 5);
    SET_TYPE3_AJMP(InstMem[9], COND_AL, 11); //should jump 
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

SET_TEST(TESTNAME, test_ajmp_without_link_under_RSV_condition)
{
	int InstSize;
    
    //given
	InstSize = 12;
    
    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    //set CPU register
    SET_CPU_REG(0, 60);  SET_CPU_REG(1, 50);
    SET_CPU_REG(2, 60);  SET_CPU_REG(3, 60);
    SET_CPU_REG(4, 30);  SET_CPU_REG(5, 60);
    SET_CPU_REG(10, 70); SET_CPU_REG(11, 80); SET_CPU_REG(12, 90);  
    
    //write instrction memory
    SET_TYPE1_CMP(InstMem[0], 0, 1);
    SET_TYPE3_AJMP(InstMem[1], COND_RSV, 11); //should not jump 
    SET_TYPE1_MOVE(InstMem[3], 20, 10);
    SET_TYPE1_MOVE(InstMem[3], 20, 10);

    SET_TYPE1_CMP(InstMem[4], 2, 3);
    SET_TYPE3_AJMP(InstMem[5], COND_RSV, 11); //should not jump 
    SET_TYPE1_MOVE(InstMem[7], 21, 11);
    SET_TYPE1_MOVE(InstMem[7], 21, 11);

    SET_TYPE1_CMP(InstMem[8], 4, 5);
    SET_TYPE3_AJMP(InstMem[9], COND_RSV, 11); //should not jump 
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

SET_TEST(TESTNAME, test_ajmp_with_link_under_AL_condition)
{
	int InstSize;
    
    //given
	InstSize = 5;
    
    //when
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    //set CPU register
    SET_CPU_REG(0, 60);  SET_CPU_REG(1, 50);
    SET_CPU_REG(10, 70); 
    
    //write instrction memory
    SET_TYPE1_CMP(InstMem[0], 0, 1);
    SET_TYPE3_AJMPL(InstMem[1], COND_AL, 3); //should jump 
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

SET_TEST_GROUP_RUNNER(TESTNAME)
{
	printf("test instruction %s \n", GET_STR(TESTNAME));

	SET_RUN_TEST_CASE(TESTNAME, test_ajmp_without_link_under_EQ_condition);
    SET_RUN_TEST_CASE(TESTNAME, test_ajmp_without_link_under_NE_condition);
    SET_RUN_TEST_CASE(TESTNAME, test_ajmp_without_link_under_CS_condition);
    SET_RUN_TEST_CASE(TESTNAME, test_ajmp_without_link_under_CC_condition);
    SET_RUN_TEST_CASE(TESTNAME, test_ajmp_without_link_under_MI_condition);
    SET_RUN_TEST_CASE(TESTNAME, test_ajmp_without_link_under_PL_condition);
    SET_RUN_TEST_CASE(TESTNAME, test_ajmp_without_link_under_VS_condition);
    SET_RUN_TEST_CASE(TESTNAME, test_ajmp_without_link_under_VC_condition);
    SET_RUN_TEST_CASE(TESTNAME, test_ajmp_without_link_under_HI_condition);
    SET_RUN_TEST_CASE(TESTNAME, test_ajmp_without_link_under_LS_condition);
    SET_RUN_TEST_CASE(TESTNAME, test_ajmp_without_link_under_GE_condition);
    SET_RUN_TEST_CASE(TESTNAME, test_ajmp_without_link_under_LT_condition);
    SET_RUN_TEST_CASE(TESTNAME, test_ajmp_without_link_under_GT_condition);
    SET_RUN_TEST_CASE(TESTNAME, test_ajmp_without_link_under_LE_condition);
    SET_RUN_TEST_CASE(TESTNAME, test_ajmp_without_link_under_AL_condition);
    SET_RUN_TEST_CASE(TESTNAME, test_ajmp_without_link_under_RSV_condition);
    SET_RUN_TEST_CASE(TESTNAME, test_ajmp_with_link_under_AL_condition);
}

