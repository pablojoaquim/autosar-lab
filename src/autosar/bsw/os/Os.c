/**
 * @file Os.c
 * @brief AUTOSAR OS Abstraction Layer - Implementation
 * @details Simple cooperative scheduler
 * 
 * Location: src/autosar/bsw/os/Os.c
 */

#define _POSIX_C_SOURCE 200809L
#define _DEFAULT_SOURCE

#include "Os.h"
#include <stdio.h>
#include <time.h>
#include <unistd.h>

/* Task Control Blocks */
static TaskControlBlock tasks[TASK_COUNT];
static uint32 system_tick = 0;
static TaskType current_task = TASK_IDLE;

/* Platform-specific tick implementation */
static uint32 get_platform_tick_ms(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint32)(ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}

StatusType Os_Init(void) {
    /* Initialize all tasks to suspended state */
    for (uint32 i = 0; i < TASK_COUNT; i++) {
        tasks[i].id = i;
        tasks[i].state = TASK_STATE_SUSPENDED;
        tasks[i].period_ms = 0;
        tasks[i].next_activation = 0;
        tasks[i].func = NULL;
        tasks[i].name = "Uninitialized";
    }
    
    system_tick = get_platform_tick_ms();
    printf("[OS] Initialized at tick %u\n", system_tick);
    
    return OS_STATUS_OK;
}

StatusType Os_RegisterTask(TaskType task, TaskFunc func, uint32 period_ms, const char* name) {
    if (task >= TASK_COUNT || func == NULL) {
        return OS_STATUS_ERROR;
    }
    
    tasks[task].func = func;
    tasks[task].period_ms = period_ms;
    tasks[task].name = name;
    tasks[task].state = TASK_STATE_SUSPENDED;
    tasks[task].next_activation = system_tick + period_ms;
    
    printf("[OS] Registered task '%s' with period %u ms\n", name, period_ms);
    
    return OS_STATUS_OK;
}

StatusType Os_ActivateTask(TaskType task) {
    if (task >= TASK_COUNT) {
        return OS_STATUS_ERROR;
    }
    
    if (tasks[task].state == TASK_STATE_SUSPENDED) {
        tasks[task].state = TASK_STATE_READY;
    }
    
    return OS_STATUS_OK;
}

StatusType Os_TerminateTask(void) {
    if (current_task < TASK_COUNT) {
        tasks[current_task].state = TASK_STATE_SUSPENDED;
    }
    return OS_STATUS_OK;
}

uint32 Os_GetTick(void) {
    return system_tick;
}

void Os_Delay(uint32 ms) {
    usleep(ms * 1000);
}

void Os_Start(void) {
    printf("[OS] Starting scheduler...\n");
    printf("[OS] Tick resolution: 1ms\n\n");
    
    /* Activate all registered tasks */
    for (uint32 i = 0; i < TASK_COUNT; i++) {
        if (tasks[i].func != NULL) {
            Os_ActivateTask(i);
        }
    }
    
    /* Main scheduler loop */
    while (1) {
        /* Update system tick */
        system_tick = get_platform_tick_ms();
        
        /* Check each task for activation */
        for (uint32 i = 0; i < TASK_COUNT; i++) {
            if (tasks[i].state == TASK_STATE_READY && 
                tasks[i].func != NULL &&
                system_tick >= tasks[i].next_activation) {
                
                /* Run the task */
                current_task = i;
                tasks[i].state = TASK_STATE_RUNNING;
                
                tasks[i].func();
                
                /* Task completed - schedule next activation */
                if (tasks[i].state == TASK_STATE_RUNNING) {
                    tasks[i].state = TASK_STATE_READY;
                    tasks[i].next_activation = system_tick + tasks[i].period_ms;
                }
                
                current_task = TASK_IDLE;
            }
        }
        
        /* Sleep to reduce CPU usage (cooperative scheduling) */
        Os_Delay(1);
    }
}