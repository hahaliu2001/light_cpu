/*
 * test_inst_type2_move_inner.c
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
#define TESTNAME inst_type2_move_inner

SET_TEST_GROUP(TESTNAME);

SET_TEST_SETUP(TESTNAME)
{
  //This is run before EACH TEST
}

SET_TEST_DOWN(TESTNAME)
{

}

SET_TEST(TESTNAME, test_type2_move_inner_write_to_SR)
{
	int InstSize, Error;
    //int i;
    int m = 0;
	int RB, RD; //, Type;
    unsigned int Value1;//, Value2;
    
	//given
	InstSize = 2;
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

	//when 
    RB = 1;
    RD = 3;
	Value1 = 0x12345678;

    // set register
    SET_CPU_REG(RB, Value1);
    
    //set instruction
    //SET_TYPE4_UNSIGNED_MOV(InstMem[m++], RD, );
    SET_TYPE1_MOVE(InstMem[m], RD, RB);                 m++;
    SET_TYPE2_MOVE_INNER_WRITE(InstMem[m], INTERNAL_REG_SR, RD, RB);    m++;
    
	Error = 0;
	while (!Error)
	{
        Error = run_cpu();
	}

	//expected
   // READ_CPU_SRCH((unsigned char *)&Value2);
	TEST_ASSERT_EQUAL(Value1, GET_CPU_SRCH());
}

SET_TEST(TESTNAME, test_type2_move_inner_write_to_INT_STATUS)
{
	int InstSize, Error;
    int i;
    int m = 0;
	int RB, RD; //, Type;
    unsigned int Value1, Value2;
    unsigned int ExpectedValue;
    
	//given
	InstSize = 2;
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

	//when 
    RB = 1;
    RD = 3;
	Value1 = 0x12345678;

    // set register
    SET_CPU_REG(RB, Value1);
    
    //set instruction
    //SET_TYPE4_UNSIGNED_MOV(InstMem[m++], RD, );
    SET_TYPE1_MOVE(InstMem[m], RD, RB);                 m++;
    SET_TYPE2_MOVE_INNER_WRITE(InstMem[m], INTERNAL_REG_INT_STATUS, RD, RB);    m++;
    
	Error = 0;
	while (!Error)
	{
        Error = run_cpu();
	}

	//expected
    Value2 = GET_CPU_REG(RB);
    for (i = 0; i< 32; i++)
    {
        ExpectedValue = ((Value2 >> (31 - i)) & 1);
        TEST_ASSERT_EQUAL(ExpectedValue, GET_CPU_INT_STATUS(i)); 
    }
}

SET_TEST(TESTNAME, test_type2_move_inner_write_to_INT_MASK)
{
	int InstSize, Error;
    int i;
    int m = 0;
	int RB, RD; //, Type;
    unsigned int Value1, Value2;
    unsigned int ExpectedValue;
    
	//given
	InstSize = 2;
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

	//when 
    RB = 1;
    RD = 3;
	Value1 = 0x12345678;

    // set register
    SET_CPU_REG(RB, Value1);
    
    //set instruction
    //SET_TYPE4_UNSIGNED_MOV(InstMem[m++], RD, );
    SET_TYPE1_MOVE(InstMem[m], RD, RB);                 m++;
    SET_TYPE2_MOVE_INNER_WRITE(InstMem[m], INTERNAL_REG_INT_MASK, RD, RB);    m++;
    
	Error = 0;
	while (!Error)
	{
        Error = run_cpu();
	}

	//expected
    Value2 = GET_CPU_REG(RB);
    for (i = 0; i< 32; i++)
    {
        ExpectedValue = ((Value2 >> (31 - i)) & 1);
        TEST_ASSERT_EQUAL(ExpectedValue, GET_CPU_INT_MASK(i)); 
    }
}

SET_TEST(TESTNAME, test_type2_move_inner_write_to_INT_PRIORITY)
{
	int InstSize, Error;
    int i;
    int m = 0;
	int RB1, RB2, RD; //, Type;
    unsigned int Value1, Value2;
    unsigned int ExpectedValue;
    
	//given
	InstSize = 9;
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

	//when 
    RB1 = 1; RB2 = 2;
    RD = 23;
	Value1 = 0x12345678;

    // set register
    SET_CPU_REG(RB1, Value1);
    SET_CPU_REG((RB2 + 0), 0);
    SET_CPU_REG((RB2 + 1), 1);
    SET_CPU_REG((RB2 + 2), 2);
    SET_CPU_REG((RB2 + 3), 3);
    SET_CPU_REG((RB2 + 4), 4);
    SET_CPU_REG((RB2 + 5), 5);
    SET_CPU_REG((RB2 + 6), 6);
    SET_CPU_REG((RB2 + 7), 7);

    
    //set instruction
    //SET_TYPE4_UNSIGNED_MOV(InstMem[m++], RD, );
    SET_TYPE1_MOVE(InstMem[m], RD, RB1);                 m++;
    SET_TYPE2_MOVE_INNER_WRITE(InstMem[m], INTERNAL_REG_INT_PRIORITY, RD, (RB2 + 0));    m++;
    SET_TYPE2_MOVE_INNER_WRITE(InstMem[m], INTERNAL_REG_INT_PRIORITY, RD, (RB2 + 1));    m++;
    SET_TYPE2_MOVE_INNER_WRITE(InstMem[m], INTERNAL_REG_INT_PRIORITY, RD, (RB2 + 2));    m++;
    SET_TYPE2_MOVE_INNER_WRITE(InstMem[m], INTERNAL_REG_INT_PRIORITY, RD, (RB2 + 3));    m++;
    SET_TYPE2_MOVE_INNER_WRITE(InstMem[m], INTERNAL_REG_INT_PRIORITY, RD, (RB2 + 4));    m++;
    SET_TYPE2_MOVE_INNER_WRITE(InstMem[m], INTERNAL_REG_INT_PRIORITY, RD, (RB2 + 5));    m++;
    SET_TYPE2_MOVE_INNER_WRITE(InstMem[m], INTERNAL_REG_INT_PRIORITY, RD, (RB2 + 6));    m++;
    SET_TYPE2_MOVE_INNER_WRITE(InstMem[m], INTERNAL_REG_INT_PRIORITY, RD, (RB2 + 7));    m++;
    
	Error = 0;
	while (!Error)
	{
        Error = run_cpu();
	}

	//expected
    Value2 = GET_CPU_REG(RB1);
    for (i = 0; i< 4; i++)
    {
        ExpectedValue = ((Value2 >> (24 - i * 8)) & 0xFF);
        TEST_ASSERT_EQUAL(ExpectedValue, GET_CPU_INT_PRIORITY(i + 4 * 0)); 
        TEST_ASSERT_EQUAL(ExpectedValue, GET_CPU_INT_PRIORITY(i + 4 * 1)); 
        TEST_ASSERT_EQUAL(ExpectedValue, GET_CPU_INT_PRIORITY(i + 4 * 2)); 
        TEST_ASSERT_EQUAL(ExpectedValue, GET_CPU_INT_PRIORITY(i + 4 * 3)); 
        TEST_ASSERT_EQUAL(ExpectedValue, GET_CPU_INT_PRIORITY(i + 4 * 4)); 
        TEST_ASSERT_EQUAL(ExpectedValue, GET_CPU_INT_PRIORITY(i + 4 * 5)); 
        TEST_ASSERT_EQUAL(ExpectedValue, GET_CPU_INT_PRIORITY(i + 4 * 6)); 
        TEST_ASSERT_EQUAL(ExpectedValue, GET_CPU_INT_PRIORITY(i + 4 * 7)); 
    }
}

SET_TEST(TESTNAME, test_type2_move_inner_write_IMM_to_INT_PRIORITY)
{
	int InstSize, Error;
    int i;
    int m = 0;
	int RB1, RB2, RD; //, Type;
    unsigned int Value1, Value2;
    unsigned int ExpectedValue;
    
	//given
	InstSize = 9;
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

	//when 
    RB1 = 1; RB2 = 2;
    RD = 23;
	Value1 = 0x12345678;

    // set register
    SET_CPU_REG(RB1, Value1);
    SET_CPU_REG((RB2 + 0), 0);
    SET_CPU_REG((RB2 + 1), 1);
    SET_CPU_REG((RB2 + 2), 2);
    SET_CPU_REG((RB2 + 3), 3);
    SET_CPU_REG((RB2 + 4), 4);
    SET_CPU_REG((RB2 + 5), 5);
    SET_CPU_REG((RB2 + 6), 6);
    SET_CPU_REG((RB2 + 7), 7);

    
    //set instruction
    //SET_TYPE4_UNSIGNED_MOV(InstMem[m++], RD, );
    SET_TYPE1_MOVE(InstMem[m], RD, RB1);                 m++;
    SET_TYPE2_MOVE_INNER_WRITE_IMM(InstMem[m], INTERNAL_REG_INT_PRIORITY, RD, 0);    m++;
    SET_TYPE2_MOVE_INNER_WRITE_IMM(InstMem[m], INTERNAL_REG_INT_PRIORITY, RD, 1);    m++;
    SET_TYPE2_MOVE_INNER_WRITE_IMM(InstMem[m], INTERNAL_REG_INT_PRIORITY, RD, 2);    m++;
    SET_TYPE2_MOVE_INNER_WRITE_IMM(InstMem[m], INTERNAL_REG_INT_PRIORITY, RD, 3);    m++;
    SET_TYPE2_MOVE_INNER_WRITE_IMM(InstMem[m], INTERNAL_REG_INT_PRIORITY, RD, 4);    m++;
    SET_TYPE2_MOVE_INNER_WRITE_IMM(InstMem[m], INTERNAL_REG_INT_PRIORITY, RD, 5);    m++;
    SET_TYPE2_MOVE_INNER_WRITE_IMM(InstMem[m], INTERNAL_REG_INT_PRIORITY, RD, 6);    m++;
    SET_TYPE2_MOVE_INNER_WRITE_IMM(InstMem[m], INTERNAL_REG_INT_PRIORITY, RD, 7);    m++;
    
	Error = 0;
	while (!Error)
	{
        Error = run_cpu();
	}

	//expected
    Value2 = GET_CPU_REG(RB1);
    for (i = 0; i< 4; i++)
    {
        ExpectedValue = ((Value2 >> (24 - i * 8)) & 0xFF);
        TEST_ASSERT_EQUAL(ExpectedValue, GET_CPU_INT_PRIORITY(i + 4 * 0)); 
        TEST_ASSERT_EQUAL(ExpectedValue, GET_CPU_INT_PRIORITY(i + 4 * 1)); 
        TEST_ASSERT_EQUAL(ExpectedValue, GET_CPU_INT_PRIORITY(i + 4 * 2)); 
        TEST_ASSERT_EQUAL(ExpectedValue, GET_CPU_INT_PRIORITY(i + 4 * 3)); 
        TEST_ASSERT_EQUAL(ExpectedValue, GET_CPU_INT_PRIORITY(i + 4 * 4)); 
        TEST_ASSERT_EQUAL(ExpectedValue, GET_CPU_INT_PRIORITY(i + 4 * 5)); 
        TEST_ASSERT_EQUAL(ExpectedValue, GET_CPU_INT_PRIORITY(i + 4 * 6)); 
        TEST_ASSERT_EQUAL(ExpectedValue, GET_CPU_INT_PRIORITY(i + 4 * 7)); 
    }
}

SET_TEST(TESTNAME, test_type2_move_inner_write_to_INT_RETURN_PC)
{
	int InstSize, Error;
    int i;
    int m = 0;
	int RB1, RB2, RD; //, Type;
    unsigned int Value1; //, Value2;
    unsigned int ExpectedValue;
    
	//given
	InstSize = CPU_MAX_INT_NUM * 2 + 1;
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

	//when 
    RB1 = 1; RB2 = 2;
    RD = 23;
	Value1 = 0x12345678;

    // set register
    SET_CPU_REG(RB1, Value1);
    
    //set instruction
    //SET_TYPE4_UNSIGNED_MOV(InstMem[m++], RD, );
    SET_TYPE1_MOVE(InstMem[m], RD, RB1);                 m++;
    for (i = 0; i< CPU_MAX_INT_NUM; i++)
    {
        SET_TYPE4_SIGNED_MOV(InstMem[m], RB2, i);    m++;
        SET_TYPE2_MOVE_INNER_WRITE(InstMem[m], INTERNAL_REG_INT_RETURN_PC, RD, RB2);    m++; 
    }
    
	Error = 0;
	while (!Error)
	{
        Error = run_cpu();
	}

	//expected
    ExpectedValue = GET_CPU_REG(RB1);
    for (i = 0; i< CPU_MAX_INT_NUM; i++)
    {
        TEST_ASSERT_EQUAL(ExpectedValue, GET_CPU_ACTIVE_INT_RETURN_PC(i)); 
    }
}

SET_TEST(TESTNAME, test_type2_move_inner_write_to_ACTIVE_INT_ID)
{
	int InstSize, Error;
    int i;
    int m = 0;
	int RB1, RB2, RD; //, Type;
    unsigned int Value1; //, Value2;
    unsigned int ExpectedValue;
    
	//given
	InstSize = CPU_MAX_INT_NUM * 2 + 1;
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

	//when 
    RB1 = 1; RB2 = 2;
    RD = 23;
	Value1 = 0x12;

    // set register
    SET_CPU_REG(RB1, Value1);
    
    //set instruction
    //SET_TYPE4_UNSIGNED_MOV(InstMem[m++], RD, );
    SET_TYPE1_MOVE(InstMem[m], RD, RB1);                 m++;
    for (i = 0; i< CPU_MAX_INT_NUM; i++)
    {
        SET_TYPE4_SIGNED_MOV(InstMem[m], RB2, i);    m++;
        SET_TYPE2_MOVE_INNER_WRITE(InstMem[m], INTERNAL_REG_ACTIVE_INT_ID, RD, RB2);    m++; 
    }
    
	Error = 0;
	while (!Error)
	{
        Error = run_cpu();
	}

	//expected
    ExpectedValue = GET_CPU_REG(RB1);
    for (i = 0; i< CPU_MAX_INT_NUM; i++)
    {
        TEST_ASSERT_EQUAL(ExpectedValue, GET_CPU_ACTIVE_INT_PRIORITY(i)); 
    }
}

SET_TEST(TESTNAME, test_type2_move_inner_read_from_SR)
{
	int InstSize, Error;
    //int i;
    int m = 0;
	int RB, RD, RA; //, Type;
    unsigned int Value1, ExpectedValue;//, Value2;
    
	//given
	InstSize = 1;
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

	//when 
    RB = 1; RA = 28;
    RD = 23;
	Value1 = 0x12345678;

    // set register
    SET_CPU_REG(RA, Value1);
    SET_CPU_SRCH(Value1);
    
    //set instruction
    SET_TYPE2_MOVE_INNER_READ(InstMem[m], INTERNAL_REG_SR, RD, RB);    m++;
    
	Error = 0;
	while (!Error)
	{
        Error = run_cpu();
	}

	//expected
    ExpectedValue = GET_CPU_REG(RA);
	TEST_ASSERT_EQUAL(ExpectedValue, GET_CPU_REG(RD));
}

SET_TEST(TESTNAME, test_type2_move_inner_read_from_INT_INPUT)
{
	int InstSize, Error;
    int i;
    int m = 0;
    int RB, RD; //, Type;
    
    //given
	InstSize = 1;
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

	//when 
    RB = 1; 
    RD = 23;
	
    // set register
    for (i = 0; i< CPU_MAX_INT_NUM; i++)
    {
        SET_CPU_INT_INPUT(i, (i & 1)); 
    }
    
    //set instruction
    SET_TYPE2_MOVE_INNER_READ(InstMem[m], INTERNAL_REG_INT_INPUT, RD, RB);    m++; 
    
	Error = 0;
	while (!Error)
	{
        Error = run_cpu();
	}

	//expected
    TEST_ASSERT_EQUAL(0x55555555, GET_CPU_REG(RD));
}

SET_TEST(TESTNAME, test_type2_move_inner_read_from_INT_STATUS)
{
	int InstSize, Error;
    int i;
    int m = 0;
    int RB, RD; //, Type;
    
    //given
	InstSize = 1;
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

	//when 
    RB = 1; 
    RD = 23;
	
    // set register
    for (i = 0; i< CPU_MAX_INT_NUM; i++)
    {
        SET_CPU_INT_STATUS(i, (i & 1)); 
    }
    
    //set instruction
    SET_TYPE2_MOVE_INNER_READ(InstMem[m], INTERNAL_REG_INT_STATUS, RD, RB);    m++; 
    
	Error = 0;
	while (!Error)
	{
        Error = run_cpu();
	}

	//expected
    TEST_ASSERT_EQUAL(0x55555555, GET_CPU_REG(RD));
}

SET_TEST(TESTNAME, test_type2_move_inner_read_from_INT_MASK)
{
	int InstSize, Error;
    int i;
    int m = 0;
    int RB, RD; //, Type;
    
    //given
	InstSize = 1;
    reset_cpu((unsigned char *)InstMem, InstSize * 4,
			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

	//when 
    RB = 1; 
    RD = 23;
	
    // set register
    for (i = 0; i< CPU_MAX_INT_NUM; i++)
    {
        SET_CPU_INT_MASK(i, (i & 1)); 
    }
    
    //set instruction
    SET_TYPE2_MOVE_INNER_READ(InstMem[m], INTERNAL_REG_INT_MASK, RD, RB);    m++; 
    
	Error = 0;
	while (!Error)
	{
        Error = run_cpu();
	}

	//expected
    TEST_ASSERT_EQUAL(0x55555555, GET_CPU_REG(RD));
}

SET_TEST(TESTNAME, test_type2_move_inner_read_from_INT_PRIORITY)
{
	int InstSize, Error;
    int i;
    int m = 0;
    int RA, RB, RD; //, Type;
    unsigned int Value, ExpectedValue;
    
    for (i = 0; i< CPU_MAX_INT_NUM/4; i++)
    {
        //given
        InstSize = 2;
        reset_cpu((unsigned char *)InstMem, InstSize * 4,
    			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
    			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    	//when 
        RB = 1; 
        RD = 23;
        RA = 28;
        Value = 0x12345678;
    	
        // set register
        SET_CPU_REG(RA, Value);
        SET_CPU_INT_PRIORITY(i * 4 + 0,  ((Value >> 24) & 0xFF));
        SET_CPU_INT_PRIORITY(i * 4 + 1,  ((Value >> 16) & 0xFF));
        SET_CPU_INT_PRIORITY(i * 4 + 2,  ((Value >> 8 ) & 0xFF));
        SET_CPU_INT_PRIORITY(i * 4 + 3,  ((Value >> 0 ) & 0xFF));
        
        //set instruction
        m = 0;
        SET_TYPE4_SIGNED_MOV(InstMem[m], RB, i);    m++;
        SET_TYPE2_MOVE_INNER_READ(InstMem[m], INTERNAL_REG_INT_PRIORITY, RD, RB);    m++; 
        
    	Error = 0;
    	while (!Error)
    	{
            Error = run_cpu();
    	}

    	//expected
        ExpectedValue = GET_CPU_REG(RA);
        TEST_ASSERT_EQUAL(ExpectedValue, GET_CPU_REG(RD));

    }
    
}

SET_TEST(TESTNAME, test_type2_move_inner_IMM_read_from_INT_PRIORITY)
{
	int InstSize, Error;
    int i;
    int m = 0;
    int RA, RB, RD; //, Type;
    unsigned int Value, ExpectedValue;
    
    for (i = 0; i< CPU_MAX_INT_NUM/4; i++)
    {
        //given
        InstSize = 2;
        reset_cpu((unsigned char *)InstMem, InstSize * 4,
    			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
    			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    	//when 
        RB = 1; 
        RD = 23;
        RA = 28;
        Value = 0x12345678;
    	
        // set register
        SET_CPU_REG(RA, Value);
        SET_CPU_INT_PRIORITY(i * 4 + 0,  ((Value >> 24) & 0xFF));
        SET_CPU_INT_PRIORITY(i * 4 + 1,  ((Value >> 16) & 0xFF));
        SET_CPU_INT_PRIORITY(i * 4 + 2,  ((Value >> 8 ) & 0xFF));
        SET_CPU_INT_PRIORITY(i * 4 + 3,  ((Value >> 0 ) & 0xFF));
        
        //set instruction
        m = 0;
        SET_TYPE4_SIGNED_MOV(InstMem[m], RB, i);    m++;
        SET_TYPE2_MOVE_INNER_READ_IMM(InstMem[m], INTERNAL_REG_INT_PRIORITY, RD, i);    m++; 
        
    	Error = 0;
    	while (!Error)
    	{
            Error = run_cpu();
    	}

    	//expected
        ExpectedValue = GET_CPU_REG(RA);
        TEST_ASSERT_EQUAL(ExpectedValue, GET_CPU_REG(RD));

    }
    
}

SET_TEST(TESTNAME, test_type2_move_inner_read_from_ACTIVE_INT_RETURN_PC)
{
	int InstSize, Error;
    int i;
    int m = 0;
    int RA, RB, RD; //, Type;
    unsigned int Value, ExpectedValue;
    
    for (i = 0; i< CPU_MAX_INT_NUM; i++)
    {
        //given
        InstSize = 3;
        reset_cpu((unsigned char *)InstMem, InstSize * 4,
    			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
    			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    	//when 
        RB = 1; 
        RD = 23;
        RA = 28;
        Value = 0x12345678;
    	
        // set register
        SET_CPU_REG(RA, Value);
        SET_CPU_ACTIVE_INT_RETURN_PC(i,  Value);
        SET_CPU_ACTIVE_INT_POS(1);
        
        //set instruction
        m = 0;
        SET_TYPE4_SIGNED_MOV(InstMem[m], RB, i);    m++;
        SET_TYPE2_MOVE_INNER_READ(InstMem[m], INTERNAL_REG_INT_RETURN_PC, RD, RB);    m++; 
        SET_TYPE2_MOVE_INNER_READ(InstMem[m], INTERNAL_REG_ACTIVE_INT_POS, RB, 0);    m++; 
        
    	Error = 0;
    	while (!Error)
    	{
            Error = run_cpu();
    	}

    	//expected
        ExpectedValue = GET_CPU_REG(RA);
        TEST_ASSERT_EQUAL(ExpectedValue, GET_CPU_REG(RD));
        TEST_ASSERT_EQUAL(1, GET_CPU_REG(RB));
        TEST_ASSERT_EQUAL(1, GET_CPU_ACTIVE_INT_POS());

    }
    
}

SET_TEST(TESTNAME, test_type2_move_inner_read_from_ACTIVE_INT_ID)
{
	int InstSize, Error;
    int i;
    int m = 0;
    int RA, RB, RD; //, Type;
    unsigned int Value, ExpectedValue;
    
    for (i = 0; i< CPU_MAX_INT_NUM; i++)
    {
        //given
        InstSize = 2;
        reset_cpu((unsigned char *)InstMem, InstSize * 4,
    			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
    			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    	//when 
        RB = 1; 
        RD = 23;
        RA = 28;
        Value = 0x12;
    	
        // set register
        SET_CPU_REG(RA, Value);
        SET_CPU_ACTIVE_INT_PRIORITY(i,  Value);
        
        //set instruction
        m = 0;
        SET_TYPE4_SIGNED_MOV(InstMem[m], RB, i);    m++;
        SET_TYPE2_MOVE_INNER_READ(InstMem[m], INTERNAL_REG_ACTIVE_INT_ID, RD, RB);    m++; 
        
    	Error = 0;
    	while (!Error)
    	{
            Error = run_cpu();
    	}

    	//expected
        ExpectedValue = GET_CPU_REG(RA);
        TEST_ASSERT_EQUAL(ExpectedValue, GET_CPU_REG(RD));

    }
    
}

SET_TEST(TESTNAME, test_type2_move_inner_read_from_RETI)
{
	int InstSize, Error;
    int i;
    int m = 0;
    int RA, RB, RD; //, Type;
    unsigned int Value, ExpectedValue;
    
    for (i = 0; i< CPU_MAX_INT_NUM; i++)
    {
        //given
        InstSize = 2;
        reset_cpu((unsigned char *)InstMem, InstSize * 4,
    			(unsigned char *)DataMem, DATA_MEM_SIZE * 4,
    			(unsigned char *)StackMem, STACK_MEM_SIZE * 4);

    	//when 
        RB = 1; 
        RD = 23;
        RA = 28;
        Value = 0x12345678;
    	
        // set register
        SET_CPU_REG(RA, Value);
        SET_CPU_ACTIVE_INT_RETURN_PC(i,  Value);
        SET_CPU_ACTIVE_INT_POS(1);
        
        //set instruction
        m = 0;
        SET_TYPE4_SIGNED_MOV(InstMem[m], RB, i);    m++;
        SET_TYPE2_MOVE_INNER_READ(InstMem[m], INTERNAL_REG_RETI, RD, RB);    m++; 
        
    	Error = 0;
    	while (!Error)
    	{
            Error = run_cpu();
    	}

    	//expected
        ExpectedValue = GET_CPU_REG(RA);
        TEST_ASSERT_EQUAL(ExpectedValue, GET_CPU_REG(RD));
        TEST_ASSERT_EQUAL(0, GET_CPU_ACTIVE_INT_POS());
    }
    
}

SET_TEST_GROUP_RUNNER(TESTNAME)
{
	printf("test instruction %s \n", GET_STR(TESTNAME));

	SET_RUN_TEST_CASE(TESTNAME, test_type2_move_inner_write_to_SR);
    SET_RUN_TEST_CASE(TESTNAME, test_type2_move_inner_write_to_INT_STATUS);
    SET_RUN_TEST_CASE(TESTNAME, test_type2_move_inner_write_to_INT_MASK);
    SET_RUN_TEST_CASE(TESTNAME, test_type2_move_inner_write_to_INT_PRIORITY);
    SET_RUN_TEST_CASE(TESTNAME, test_type2_move_inner_write_IMM_to_INT_PRIORITY);
    SET_RUN_TEST_CASE(TESTNAME, test_type2_move_inner_write_to_INT_RETURN_PC);
    SET_RUN_TEST_CASE(TESTNAME, test_type2_move_inner_write_to_ACTIVE_INT_ID);
    SET_RUN_TEST_CASE(TESTNAME, test_type2_move_inner_read_from_SR);
    SET_RUN_TEST_CASE(TESTNAME, test_type2_move_inner_read_from_INT_INPUT);
    SET_RUN_TEST_CASE(TESTNAME, test_type2_move_inner_read_from_INT_STATUS);
    SET_RUN_TEST_CASE(TESTNAME, test_type2_move_inner_read_from_INT_MASK);
    SET_RUN_TEST_CASE(TESTNAME, test_type2_move_inner_read_from_INT_PRIORITY);
    SET_RUN_TEST_CASE(TESTNAME, test_type2_move_inner_IMM_read_from_INT_PRIORITY);
    SET_RUN_TEST_CASE(TESTNAME, test_type2_move_inner_read_from_ACTIVE_INT_RETURN_PC);
    SET_RUN_TEST_CASE(TESTNAME, test_type2_move_inner_read_from_ACTIVE_INT_ID);
    SET_RUN_TEST_CASE(TESTNAME, test_type2_move_inner_read_from_RETI);
}
