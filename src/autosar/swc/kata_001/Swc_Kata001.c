/**
 * @file Swc_Kata001.c
 * @brief Software Component - Kata 001 Implementation
 * 
 * Location: src/autosar/swc/kata_001/Swc_Kata001.c
 */

#include "Swc_Kata001.h"
#include "Rte.h"
#include <stdio.h>

/* Private state */
static struct {
    uint32 total_calculations;
    uint32 last_result;
} kata001_state;

void Swc_Kata001_Init(void) {
    kata001_state.total_calculations = 0;
    kata001_state.last_result = 0;
    printf("[SWC_Kata001] Initialized - Ready for addition operations\n");
}

void Swc_Kata001_Runnable_10ms(void) {
    uint32 input1, input2, sum;
    
    /* Read inputs via RTE */
    Rte_Read_SwcKata001_Input1(&input1);
    Rte_Read_SwcKata001_Input2(&input2);
    
    /* KATA SOLUTION: Add two numbers */
    sum = input1 + input2;
    
    /* Write result via RTE */
    Rte_Write_SwcKata001_Sum(sum);
    
    /* Update state */
    kata001_state.total_calculations++;
    kata001_state.last_result = sum;
}

void Swc_Kata001_Runnable_100ms(void) {
    /* Status output every second (10 * 100ms) */
    static uint32 counter = 0;
    
    if (++counter >= 10) {
        printf("[SWC_Kata001] Status: %u calculations, last result: %u\n",
               kata001_state.total_calculations,
               kata001_state.last_result);
        counter = 0;
    }
}
