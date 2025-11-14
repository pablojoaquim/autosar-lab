/*===========================================================================*/
/**
 * @file SpeedDisplay.c
 *
 *  A SWC that emulates showing the speed sensor current value
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
static uint8_t NvM_BlockStorage[10] = {0};

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
* @fn         NvM_Write
* @brief      Write data in the non volatile memory
* @param [in] blockId - Where to store the data
* @param [in] value - The value of the data
* @return     void
******************************************************************************/
void NvM_Write(uint16_t blockId, uint8_t value) 
{
    NvM_BlockStorage[blockId] = value;
}

/***************************************************************************//**
* @fn         NvM_Read
* @brief      Read data from the non volatile memory
* @param [in] blockId - From where retrieve the data
* @return     The value of the data
******************************************************************************/
uint8_t NvM_Read(uint16_t blockId) 
{
    return NvM_BlockStorage[blockId];
}
