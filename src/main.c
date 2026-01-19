/**
 * @file main.c
 * @brief AUTOSAR Lab - Main Application
 * @details System initialization and startup
 * 
 * Location: src/autosar/main.c
 */

#include "Os.h"
#include "Com.h"
#include "Rte.h"
#include "Swc_Template.h"
#include "Swc_Kata001.h"
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

/* Global running flag */
static volatile boolean running = TRUE;

/* Signal handler for graceful shutdown */
void signal_handler(int signum) {
    printf("\n[MAIN] Caught signal %d, shutting down...\n", signum);
    running = FALSE;
    exit(0);
}

/* Initialize all BSW modules */
static void BSW_Init(void) {
    printf("========================================\n");
    printf("  AUTOSAR LAB - BSW Initialization\n");
    printf("========================================\n");
    
    if (Os_Init() != OS_STATUS_OK) {
        printf("[ERROR] OS initialization failed!\n");
        exit(1);
    }
    
    if (Com_Init() != E_OK) {
        printf("[ERROR] COM initialization failed!\n");
        exit(1);
    }
    
    printf("\n");
}

/* Initialize RTE */
static void RTE_Init_And_Start(void) {
    printf("========================================\n");
    printf("  AUTOSAR LAB - RTE Initialization\n");
    printf("========================================\n");
    
    if (Rte_Init() != E_OK) {
        printf("[ERROR] RTE initialization failed!\n");
        exit(1);
    }
    
    if (Rte_Start() != E_OK) {
        printf("[ERROR] RTE start failed!\n");
        exit(1);
    }
    
    printf("\n");
}

/* Initialize all application SWCs */
static void SWC_Init(void) {
    printf("========================================\n");
    printf("  AUTOSAR LAB - SWC Initialization\n");
    printf("========================================\n");
    
    /* Initialize SWC Template */
    Swc_Template_Init();
    
    /* Initialize Kata001 */
    Swc_Kata001_Init();
    
    /* Add more SWC initializations here as you create katas */
    
    printf("\n");
}

/* Register SWC runnables with OS */
static void Register_SWC_Runnables(void) {
    printf("========================================\n");
    printf("  AUTOSAR LAB - Registering Tasks\n");
    printf("========================================\n");
    
    /* Register Template SWC runnables */
    Os_RegisterTask(TASK_10MS, Swc_Template_Runnable_10ms, 10, "SWC_Template_10ms");
    Os_RegisterTask(TASK_100MS, Swc_Template_Runnable_100ms, 100, "SWC_Template_100ms");
    
    /* Register Kata001 SWC runnables */
    // Uncomment when you want to run Kata001 instead of template
    // Os_RegisterTask(TASK_10MS, Swc_Kata001_Runnable_10ms, 10, "SWC_Kata001_10ms");
    // Os_RegisterTask(TASK_100MS, Swc_Kata001_Runnable_100ms, 100, "SWC_Kata001_100ms");
    
    /* Register COM main function */
    Os_RegisterTask(TASK_1MS, Com_MainFunction, 1, "COM_MainFunction");
    
    printf("\n");
}

/* Set initial values for testing */
static void Set_Test_Inputs(void) {
    printf("========================================\n");
    printf("  AUTOSAR LAB - Setting Test Inputs\n");
    printf("========================================\n");
    
    /* Set some initial test values */
    Com_SendSignal(COM_SIGNAL_INPUT_A, 42);
    Com_SendSignal(COM_SIGNAL_INPUT_B, 58);
    
    printf("[MAIN] Input A = 42\n");
    printf("[MAIN] Input B = 58\n");
    printf("[MAIN] Expected Sum = 100\n");
    printf("\n");
}

int main(void) {
    /* Setup signal handler for Ctrl+C */
    signal(SIGINT, signal_handler);
    
    printf("\n");
    printf("╔════════════════════════════════════════╗\n");
    printf("║   AUTOSAR LAB - Kata Training System  ║\n");
    printf("║         Embedded Software Practice     ║\n");
    printf("╚════════════════════════════════════════╝\n");
    printf("\n");
    
    /* System initialization sequence */
    BSW_Init();
    RTE_Init_And_Start();
    SWC_Init();
    Register_SWC_Runnables();
    Set_Test_Inputs();
    
    printf("========================================\n");
    printf("  AUTOSAR LAB - Starting System\n");
    printf("========================================\n");
    printf("[MAIN] Press Ctrl+C to stop\n");
    printf("\n");
    
    /* Start the OS scheduler - this never returns */
    Os_Start();
    
    /* Should never reach here */
    return 0;
}
