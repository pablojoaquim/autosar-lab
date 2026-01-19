/**
 * @file Os.h
 * @brief AUTOSAR OS Abstraction Layer - Header
 * @details Simple cooperative scheduler mimicking AUTOSAR OS
 * 
 * Location: src/autosar/bsw/os/Os.h
 */

#ifndef OS_H
#define OS_H

#include "Std_Types.h"

/* Task IDs */
typedef enum {
    TASK_IDLE = 0,
    TASK_1MS,
    TASK_10MS,
    TASK_100MS,
    TASK_COUNT
} TaskType;

/* Task States */
typedef enum {
    TASK_STATE_SUSPENDED = 0,
    TASK_STATE_READY,
    TASK_STATE_RUNNING
} TaskStateType;

/* Task function pointer */
typedef void (*TaskFunc)(void);

/* Task Control Block */
typedef struct {
    TaskType id;
    TaskStateType state;
    uint32 period_ms;
    uint32 next_activation;
    TaskFunc func;
    const char* name;
} TaskControlBlock;

/* OS Status */
typedef enum {
    OS_STATUS_OK = 0,
    OS_STATUS_ERROR
} StatusType;

/**
 * @brief Initialize the OS
 * @return OS_STATUS_OK if successful
 */
StatusType Os_Init(void);

/**
 * @brief Start the OS scheduler
 * @details Never returns - runs forever
 */
void Os_Start(void);

/**
 * @brief Activate a task
 * @param task Task to activate
 * @return OS_STATUS_OK if successful
 */
StatusType Os_ActivateTask(TaskType task);

/**
 * @brief Terminate the calling task
 * @return OS_STATUS_OK if successful
 */
StatusType Os_TerminateTask(void);

/**
 * @brief Get current tick count (in ms)
 * @return Current system tick
 */
uint32 Os_GetTick(void);

/**
 * @brief Delay for specified milliseconds
 * @param ms Milliseconds to delay
 */
void Os_Delay(uint32 ms);

/**
 * @brief Register a task with the scheduler
 * @param task Task ID
 * @param func Task function pointer
 * @param period_ms Task period in milliseconds
 * @param name Task name for debugging
 * @return OS_STATUS_OK if successful
 */
StatusType Os_RegisterTask(TaskType task, TaskFunc func, uint32 period_ms, const char* name);

#endif /* OS_H */
