/**
 * @file Rte.h
 * @brief AUTOSAR Runtime Environment - Public API
 * @details Interface between BSW and Application SWCs
 * 
 * Location: src/autosar/rte/Rte.h
 * 
 * The RTE provides two types of communication:
 * 1. Internal (SWC to SWC in same ECU) - via SignalRouter
 * 2. External (SWC to other ECUs) - via COM module + buses
 */

#ifndef RTE_H
#define RTE_H

#include "Std_Types.h"
#include "Rte_Type.h"
#include "SignalRouter.h"

/**
 * @brief Initialize the RTE
 * @return E_OK if successful
 */
Std_ReturnType Rte_Init(void);

/**
 * @brief Start the RTE
 * @details Activates all SWC runnables
 * @return E_OK if successful
 */
Std_ReturnType Rte_Start(void);

/* ============================================
 * Generic RTE Port Communication APIs
 * ============================================ */

/**
 * @brief Generic Read operation
 * @param componentId Component identifier
 * @param portId Port identifier
 * @param data Pointer to data buffer
 * @return E_OK if successful
 */
Std_ReturnType Rte_Read(uint8 componentId, uint8 portId, void* data);

/**
 * @brief Generic Write operation
 * @param componentId Component identifier
 * @param portId Port identifier
 * @param data Pointer to data buffer
 * @return E_OK if successful
 */
Std_ReturnType Rte_Write(uint8 componentId, uint8 portId, const void* data);

/* ============================================
 * Component-Specific RTE APIs (Macros)
 * These would typically be auto-generated
 * ============================================ */

/* Example SWC: Kata Template */
#define Rte_Read_SwcTemplate_InputA(data) \
    Rte_Read(0, 0, (void*)(data))

#define Rte_Read_SwcTemplate_InputB(data) \
    Rte_Read(0, 1, (void*)(data))

#define Rte_Write_SwcTemplate_Output(data) \
    Rte_Write(0, 0, (const void*)&(data))

/* Example SWC: Kata 001 (Add Two Numbers) */
#define Rte_Read_SwcKata001_Input1(data) \
    Rte_Read(1, 0, (void*)(data))

#define Rte_Read_SwcKata001_Input2(data) \
    Rte_Read(1, 1, (void*)(data))

#define Rte_Write_SwcKata001_Sum(data) \
    Rte_Write(1, 0, (const void*)&(data))

#endif /* RTE_H */
