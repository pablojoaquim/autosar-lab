/*===========================================================================*/
/**
 * @file test_autosar_lab.c
 *
 *  Unit tests
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
#include "acutest.h"
#include "Rte.h"
#include "NvM.h"
#include <stdint.h>

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
* @fn         test_read_default
* @brief      Read the default value at init
* @param [in] void
* @return     void
******************************************************************************/
void test_read_default(void)
{
    uint8_t value = NvM_Read(1);
    TEST_CHECK(value == 0);
}

/***************************************************************************//**
* @fn         test_write_and_read
* @brief      Write and read
* @param [in] void
* @return     void
******************************************************************************/
void test_write_and_read(void)
{
    NvM_Write(1, 42);
    uint8_t value = NvM_Read(1);
    TEST_CHECK(value == 42);
}

/***************************************************************************//**
* @fn         test_overwrite
* @brief      Value overwrite
* @param [in] void
* @return     void
******************************************************************************/
void test_overwrite(void)
{
    NvM_Write(1, 77);
    uint8_t value = NvM_Read(1);
    TEST_CHECK(value == 77);
}

/***************************************************************************//**
* @fn         test_block_isolation
* @brief      Block isolation
* @param [in] void
* @return     void
******************************************************************************/
void test_block_isolation(void)
{
    NvM_Write(2, 10);
    NvM_Write(3, 20);

    TEST_CHECK(NvM_Read(2) == 10);
    TEST_CHECK(NvM_Read(3) == 20);
}

/***************************************************************************//**
* @fn         test_Vehicle_Speed
* @brief      Testing the Vehicle Speed interaction via the RTE functions
* @param [in] void
* @return     void
******************************************************************************/
void test_Vehicle_Speed(void) 
{
    uint16_t value;
    TEST_CHECK(RTE_E_OK == Rte_Write_VehicleSpeed(10));
    TEST_CHECK(RTE_E_OK == Rte_Read_VehicleSpeed(&value));
    TEST_CHECK(value == 10);
}

TEST_LIST = {
    { "Testing Vehicle Speed interaction", test_Vehicle_Speed },
    { "Read default value",            test_read_default },
    { "Write and read",                test_write_and_read },
    { "Overwrite block",               test_overwrite },
    { "Block isolation",               test_block_isolation },
    { NULL, NULL }  // terminador
};
