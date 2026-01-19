/**
 * @file test_kata001.c
 * @brief Unit tests for Kata001 - Add Two Numbers
 * @details Example showing how to test AUTOSAR SWCs
 * 
 * Location: test/autosar/test_kata001.c
 * 
 * To compile and run:
 *   gcc -I../../src/autosar/swc/kata_001 \
 *       -I../../src/autosar/rte \
 *       -I../../src/autosar/bsw/os \
 *       test_kata001.c \
 *       ../../src/autosar/swc/kata_001/Swc_Kata001.c \
 *       -o test_kata001
 *   ./test_kata001
 */

#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdint.h>

/* Mock RTE for testing */
typedef uint32_t uint32;
typedef int32_t sint32;
typedef bool boolean;
typedef uint8_t Std_ReturnType;

#define E_OK 0
#define E_NOT_OK 1
#define TRUE true
#define FALSE false

/* Test data storage */
static uint32 test_input1 = 0;
static uint32 test_input2 = 0;
static uint32 test_output = 0;

/* Mock RTE functions */
Std_ReturnType Rte_Read(uint8_t componentId, uint8_t portId, void* data) {
    (void)componentId;
    
    if (portId == 0) {
        *(uint32*)data = test_input1;
    } else if (portId == 1) {
        *(uint32*)data = test_input2;
    }
    
    return E_OK;
}

Std_ReturnType Rte_Write(uint8_t componentId, uint8_t portId, const void* data) {
    (void)componentId;
    (void)portId;
    
    test_output = *(const uint32*)data;
    return E_OK;
}

/* Include the SWC under test */
#define Rte_Read_SwcKata001_Input1(data) Rte_Read(1, 0, (void*)(data))
#define Rte_Read_SwcKata001_Input2(data) Rte_Read(1, 1, (void*)(data))
#define Rte_Write_SwcKata001_Sum(data) Rte_Write(1, 0, (const void*)&(data))

/* SWC functions */
void Swc_Kata001_Init(void);
void Swc_Kata001_Runnable_10ms(void);

/* Test cases */
typedef struct {
    const char* name;
    uint32 input1;
    uint32 input2;
    uint32 expected;
} TestCase;

static const TestCase test_cases[] = {
    {"Simple addition", 2, 3, 5},
    {"Add with zero", 10, 0, 10},
    {"Zero plus zero", 0, 0, 0},
    {"Large numbers", 1000000, 2000000, 3000000},
    {"Max uint32 half", 0x7FFFFFFF, 0x7FFFFFFF, 0xFFFFFFFE},
};

static const uint32 NUM_TESTS = sizeof(test_cases) / sizeof(test_cases[0]);

/* Test runner */
void run_test(const TestCase* tc) {
    /* Setup */
    test_input1 = tc->input1;
    test_input2 = tc->input2;
    test_output = 0;
    
    /* Execute */
    Swc_Kata001_Runnable_10ms();
    
    /* Assert */
    if (test_output == tc->expected) {
        printf("✓ PASS: %s (%u + %u = %u)\n", 
               tc->name, tc->input1, tc->input2, test_output);
    } else {
        printf("✗ FAIL: %s\n", tc->name);
        printf("  Input1: %u, Input2: %u\n", tc->input1, tc->input2);
        printf("  Expected: %u, Got: %u\n", tc->expected, test_output);
        assert(false && "Test failed");
    }
}

int main(void) {
    printf("========================================\n");
    printf("  Unit Tests: Kata001 - Add Two Numbers\n");
    printf("========================================\n\n");
    
    /* Initialize SWC */
    Swc_Kata001_Init();
    
    /* Run all test cases */
    uint32 passed = 0;
    for (uint32 i = 0; i < NUM_TESTS; i++) {
        run_test(&test_cases[i]);
        passed++;
    }
    
    printf("\n========================================\n");
    printf("  Test Summary\n");
    printf("========================================\n");
    printf("Total: %u, Passed: %u, Failed: %u\n", 
           NUM_TESTS, passed, NUM_TESTS - passed);
    printf("Success rate: %.1f%%\n", (float)passed / NUM_TESTS * 100.0f);
    
    if (passed == NUM_TESTS) {
        printf("\n✓ All tests passed!\n");
        return 0;
    } else {
        printf("\n✗ Some tests failed!\n");
        return 1;
    }
}
