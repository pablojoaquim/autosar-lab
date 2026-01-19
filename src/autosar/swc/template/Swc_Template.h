/**
 * @file Swc_Template.h
 * @brief Software Component Template - Header
 * @details Template for creating new kata SWCs
 * 
 * Location: src/autosar/swc/template/Swc_Template.h
 * 
 * HOW TO USE:
 * 1. Copy this template directory: cp -r template kata_XXX
 * 2. Rename files: Swc_Template.* -> Swc_KataXXX.*
 * 3. Update component name in all occurrences
 * 4. Implement your kata logic in the runnable functions
 */

#ifndef SWC_TEMPLATE_H
#define SWC_TEMPLATE_H

#include "Std_Types.h"

/**
 * @brief SWC Initialization
 * @details Called once at system startup
 */
void Swc_Template_Init(void);

/**
 * @brief 10ms periodic runnable
 * @details Called every 10ms by the OS
 * 
 * THIS IS WHERE YOU IMPLEMENT YOUR KATA!
 */
void Swc_Template_Runnable_10ms(void);

/**
 * @brief 100ms periodic runnable
 * @details Called every 100ms by the OS
 * Use this for less frequent operations
 */
void Swc_Template_Runnable_100ms(void);

#endif /* SWC_TEMPLATE_H */
