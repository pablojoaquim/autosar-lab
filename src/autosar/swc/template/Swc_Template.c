/**
 * @file Swc_Template.c
 * @brief Software Component Template - Implementation
 * 
 * Location: src/autosar/swc/template/Swc_Template.c
 */

#include "Swc_Template.h"
#include "Rte.h"
#include <stdio.h>

/* Private variables */
static uint32 execution_counter = 0;

void Swc_Template_Init(void) {
    execution_counter = 0;
    printf("[SWC_Template] Initialized\n");
}

void Swc_Template_Runnable_10ms(void) {
    uint32 inputA, inputB, result;
    
    /* Read inputs from RTE ports */
    Rte_Read_SwcTemplate_InputA(&inputA);
    Rte_Read_SwcTemplate_InputB(&inputB);
    
    /* ================================================
     * YOUR KATA IMPLEMENTATION GOES HERE!
     * ================================================
     * 
     * Example: Simple addition
     * Replace with your kata logic from CodeWars
     */
    result = inputA + inputB;
    
    /* Write output to RTE port */
    Rte_Write_SwcTemplate_Output(result);
    
    execution_counter++;
}

void Swc_Template_Runnable_100ms(void) {
    /* Optional: Print debug information every 100ms */
    if (execution_counter % 10 == 0) {
        printf("[SWC_Template] Heartbeat - executions: %u\n", execution_counter);
    }
}
