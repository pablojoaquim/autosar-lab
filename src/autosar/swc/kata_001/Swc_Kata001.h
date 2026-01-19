/**
 * @file Swc_Kata001.h
 * @brief Software Component - Kata 001 (Add Two Numbers)
 * @details Example kata implementation
 * 
 * Location: src/autosar/swc/kata_001/Swc_Kata001.h
 * 
 * KATA DESCRIPTION:
 * Create a function that takes two numbers as arguments and returns their sum.
 * 
 * Examples:
 * addition(3, 2) ➞ 5
 * addition(-3, -6) ➞ -9
 * addition(7, 3) ➞ 10
 */

#ifndef SWC_KATA001_H
#define SWC_KATA001_H

#include "Std_Types.h"

/**
 * @brief SWC Initialization
 */
void Swc_Kata001_Init(void);

/**
 * @brief 10ms periodic runnable
 * @details Reads two inputs and writes their sum
 */
void Swc_Kata001_Runnable_10ms(void);

/**
 * @brief 100ms periodic runnable
 * @details Status monitoring
 */
void Swc_Kata001_Runnable_100ms(void);

#endif /* SWC_KATA001_H */
