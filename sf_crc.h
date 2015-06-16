#ifdef __cplusplus
extern "C"
{
#endif
/**
  @file       sf_crc.h
  @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
  @author     STACKFORCE
  @brief      Functions and types for CRC checks.

*/


#ifndef __CRC_H__
#define __CRC_H__

/*==============================================================================
                            INCLUDES
==============================================================================*/

#include "stdint.h"

/*==============================================================================
                            DEFINES
==============================================================================*/

/*==============================================================================
                            FUNCTIONS
==============================================================================*/

/*============================================================================*/
/*!
 * @brief  Creates the checksum of the data block.
 * @param pc_data  Pointer to an array of data bytes.
 * @param i_len    Number of bytes in the data buffer.
 * @return         Created checksum.
 */
/*============================================================================*/
uint16_t crc_calc_finalize(uint8_t *pc_data, uint16_t i_len);

/*============================================================================*/
/*!
 * @brief  Creates the checksum of data.
 * @param i_init  Initialization of the checksum.
 * @param pc_data Pointer to an array of data bytes.
 * @param i_len   Number of bytes in the data buffer.
 * @return        Created checksum.
 */
/*============================================================================*/
uint16_t crc_calc(uint16_t i_init, uint8_t *pc_data, uint16_t i_len);

/*============================================================================*/
/*!
 * @brief  Finalizes the checksum.
 * @param i_crc   Checksum to finalize.
 * @return        Finalized checksum.
 */
/*============================================================================*/
uint16_t crc_finalize(uint16_t i_crc);

#endif /* __CRC_H__ */

#ifdef __cplusplus
}
#endif
