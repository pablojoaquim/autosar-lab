/*===========================================================================*/
/**
 * @file Rte.c
 *
 *  The purpose of the AUTOSAR Runtime Environment (RTE) is to act as a middleware 
 *  that enables communication between different AUTOSAR software components (SWCs) 
 *  and between SWCs and the basic software (BSW).
 *
 *------------------------------------------------------------------------------
 *
 *------------------------------------------------------------------------------
 *
 * @section DESC DESCRIPTION:
 *
 * @todo Divide this file content using an abstraction layers concept
 *
 * @section ABBR ABBREVIATIONS:
 *   - @todo List any abbreviations, precede each with a dash ('-').
 *
 * @section TRACE TRACEABILITY INFO:
 *   - Design Document(s):
 *     - @todo Update list of design document(s).
 *
 *   - Requirements Document(s):
 *     - @todo Update list of requirements document(s)
 *
 *   - Applicable Standards (in order of precedence: highest first):
 *     - @todo Update list of other applicable standards
 *
 */
/*==========================================================================*/

/*===========================================================================*
 * Header Files
 *===========================================================================*/
#include "Rte.h"
#include "NvM.h"

/*===========================================================================*
 * Local Preprocessor #define Constants
 *===========================================================================*/

/*===========================================================================*
 * Local Preprocessor #define MACROS
 *===========================================================================*/

/*===========================================================================*
 * Local Type Declarations
 *===========================================================================*/

/*===========================================================================*
 * Local Variables Definitions
 *===========================================================================*/
static uint16_t Rte_Buffer_VehicleSpeed = 0;

/*===========================================================================*
 * Local Function Prototypes
 *===========================================================================*/

/*===========================================================================*
 * Local Inline Function Definitions and Function-Like Macros
 *===========================================================================*/

/*===========================================================================*
 * Function Definitions
 *===========================================================================*/

/***************************************************************************//**
* @fn         Rte_Write_VehicleSpeed
* @brief      The Sender writes the value to the RTE
* @param [in] value - The value to send to the RTE
* @return     RTE_E_OK
******************************************************************************/
Std_ReturnType Rte_Write_VehicleSpeed(uint16_t value)
{
    Rte_Buffer_VehicleSpeed = value;
    return RTE_E_OK;
}

/***************************************************************************//**
* @fn         Rte_Read_VehicleSpeed
* @brief      The received reads the value from the RTE
* @param [in] value - pointer to receive the value from the RTE
* @return     RTE_E_OK
******************************************************************************/
Std_ReturnType Rte_Read_VehicleSpeed(uint16_t *value)
{
    *value = Rte_Buffer_VehicleSpeed;
    return RTE_E_OK;
}

/***************************************************************************//**
* @fn         Rte_Call_NvM_WriteBlock
* @brief      The received reads the value from the RTE
* @param [in] blockId - Where to store the data
* @param [in] value - The value of the data
* @return     void
******************************************************************************/
void Rte_Call_NvM_WriteBlock(uint16_t blockId, uint8_t value)
{
    NvM_Write(blockId, value);
}

/***************************************************************************//**
* @fn         Rte_Call_NvM_ReadBlock
* @brief      Read the value from the NvM via the RTE
* @param [in] blockId - From where retrieve the data
* @return     The value of the data
******************************************************************************/
uint8_t Rte_Call_NvM_ReadBlock(uint16_t blockId)
{
    return NvM_Read(blockId);
}

