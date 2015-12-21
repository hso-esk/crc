#ifdef __cplusplus
extern "C"
{
#endif
/**
 * @code
 *  ___ _____ _   ___ _  _____ ___  ___  ___ ___
 * / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
 * \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
 * |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
 * embedded.connectivity.solutions.==============
 * @endcode
 *
 * @file
 * @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
 * @author     STACKFORCE
 * @brief      Cyclic Redundancy Check (CRC) error-detecting code.
 */

#ifndef __CRC_H__
#define __CRC_H__

#include "stdint.h"

/*!
 * @brief  Creates the checksum of the data block.
 * @param pc_data  Pointer to an array of data bytes.
 * @param i_len    Number of bytes in the data buffer.
 * @return         Created checksum.
 */
uint16_t crc_calc_finalize(uint8_t *pc_data, uint16_t i_len);

/*!
 * @brief  Creates the checksum of data.
 * @param i_init  Initialization of the checksum.
 * @param pc_data Pointer to an array of data bytes.
 * @param i_len   Number of bytes in the data buffer.
 * @return        Created checksum.
 */
uint16_t crc_calc(uint16_t i_init, uint8_t *pc_data, uint16_t i_len);

/*!
 * @brief  Finalizes the checksum.
 * @param i_crc   Checksum to finalize.
 * @return        Finalized checksum.
 */
uint16_t crc_finalize(uint16_t i_crc);

#endif

#ifdef __cplusplus
}
#endif
