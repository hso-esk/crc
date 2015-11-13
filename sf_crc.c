#ifdef __cplusplus
extern "C" {
#endif

/**
  @file       sf_crc.c
  @copyright  STACKFORCE GmbH, Heitersheim, Germany, http://www.stackforce.de
  @author     STACKFORCE
  @brief      Functions and types for CRC checks.
*/

/*==============================================================================
                            INCLUDE FILES
==============================================================================*/

/* Global includes */

/* Module includes */
#include "sf_crc.h"

/*==============================================================================
                            DEFINES
==============================================================================*/
/*! x^16 + x^13 + x^12 + x^11 + x^10 + x^8 + x^6 + x^5 + x^2 + 1
    0x13D65 required when manually computing */
#define POLYNOMAL                     0x3D65U

#if (CRC_TABLE == TRUE)
  /*! TRUE if CRC tables have to be used. This is faster than bit-by-bit
      calculation but needs more memory. */

  #warning CRC_TABLE set to TRUE. Untested feature enabled.
#endif /* CRC_TABLE */

/*==============================================================================
                            VARIABLES
==============================================================================*/
#if CRC_TABLE
/* Precalculated CRC table for lookup */
static const uint16_t crc_table[] = {
  0x0000U, 0x3d65U, 0x7acaU, 0x47afU, 0xf594U, 0xc8f1U, 0x8f5eU, 0xb23bU,
  0xd64dU, 0xeb28U, 0xac87U, 0x91e2U, 0x23d9U, 0x1ebcU, 0x5913U, 0x6476U,
  0x91ffU, 0xac9aU, 0xeb35U, 0xd650U, 0x646bU, 0x590eU, 0x1ea1U, 0x23c4U,
  0x47b2U, 0x7ad7U, 0x3d78U, 0x001dU, 0xb226U, 0x8f43U, 0xc8ecU, 0xf589U,
  0x1e9bU, 0x23feU, 0x6451U, 0x5934U, 0xeb0fU, 0xd66aU, 0x91c5U, 0xaca0U,
  0xc8d6U, 0xf5b3U, 0xb21cU, 0x8f79U, 0x3d42U, 0x0027U, 0x4788U, 0x7aedU,
  0x8f64U, 0xb201U, 0xf5aeU, 0xc8cbU, 0x7af0U, 0x4795U, 0x003aU, 0x3d5fU,
  0x5929U, 0x644cU, 0x23e3U, 0x1e86U, 0xacbdU, 0x91d8U, 0xd677U, 0xeb12U,
  0x3d36U, 0x0053U, 0x47fcU, 0x7a99U, 0xc8a2U, 0xf5c7U, 0xb268U, 0x8f0dU,
  0xeb7bU, 0xd61eU, 0x91b1U, 0xacd4U, 0x1eefU, 0x238aU, 0x6425U, 0x5940U,
  0xacc9U, 0x91acU, 0xd603U, 0xeb66U, 0x595dU, 0x6438U, 0x2397U, 0x1ef2U,
  0x7a84U, 0x47e1U, 0x004eU, 0x3d2bU, 0x8f10U, 0xb275U, 0xf5daU, 0xc8bfU,
  0x23adU, 0x1ec8U, 0x5967U, 0x6402U, 0xd639U, 0xeb5cU, 0xacf3U, 0x9196U,
  0xf5e0U, 0xc885U, 0x8f2aU, 0xb24fU, 0x0074U, 0x3d11U, 0x7abeU, 0x47dbU,
  0xb252U, 0x8f37U, 0xc898U, 0xf5fdU, 0x47c6U, 0x7aa3U, 0x3d0cU, 0x0069U,
  0x641fU, 0x597aU, 0x1ed5U, 0x23b0U, 0x918bU, 0xaceeU, 0xeb41U, 0xd624U,
  0x7a6cU, 0x4709U, 0x00a6U, 0x3dc3U, 0x8ff8U, 0xb29dU, 0xf532U, 0xc857U,
  0xac21U, 0x9144U, 0xd6ebU, 0xeb8eU, 0x59b5U, 0x64d0U, 0x237fU, 0x1e1aU,
  0xeb93U, 0xd6f6U, 0x9159U, 0xac3cU, 0x1e07U, 0x2362U, 0x64cdU, 0x59a8U,
  0x3ddeU, 0x00bbU, 0x4714U, 0x7a71U, 0xc84aU, 0xf52fU, 0xb280U, 0x8fe5U,
  0x64f7U, 0x5992U, 0x1e3dU, 0x2358U, 0x9163U, 0xac06U, 0xeba9U, 0xd6ccU,
  0xb2baU, 0x8fdfU, 0xc870U, 0xf515U, 0x472eU, 0x7a4bU, 0x3de4U, 0x0081U,
  0xf508U, 0xc86dU, 0x8fc2U, 0xb2a7U, 0x009cU, 0x3df9U, 0x7a56U, 0x4733U,
  0x2345U, 0x1e20U, 0x598fU, 0x64eaU, 0xd6d1U, 0xebb4U, 0xac1bU, 0x917eU,
  0x475aU, 0x7a3fU, 0x3d90U, 0x00f5U, 0xb2ceU, 0x8fabU, 0xc804U, 0xf561U,
  0x9117U, 0xac72U, 0xebddU, 0xd6b8U, 0x6483U, 0x59e6U, 0x1e49U, 0x232cU,
  0xd6a5U, 0xebc0U, 0xac6fU, 0x910aU, 0x2331U, 0x1e54U, 0x59fbU, 0x649eU,
  0x00e8U, 0x3d8dU, 0x7a22U, 0x4747U, 0xf57cU, 0xc819U, 0x8fb6U, 0xb2d3U,
  0x59c1U, 0x64a4U, 0x230bU, 0x1e6eU, 0xac55U, 0x9130U, 0xd69fU, 0xebfaU,
  0x8f8cU, 0xb2e9U, 0xf546U, 0xc823U, 0x7a18U, 0x477dU, 0x00d2U, 0x3db7U,
  0xc83eU, 0xf55bU, 0xb2f4U, 0x8f91U, 0x3daaU, 0x00cfU, 0x4760U, 0x7a05U,
  0x1e73U, 0x2316U, 0x64b9U, 0x59dcU, 0xebe7U, 0xd682U, 0x912dU, 0xac48U
};
#endif /* CRC_TABLE */

/*==============================================================================
                            FUNCTIONS
==============================================================================*/

#if CRC_TABLE
/*============================================================================*/
/*! crc_calc() */
/*============================================================================*/
uint16_t crc_calc(uint16_t i_init, uint8_t *pc_data, uint16_t i_len)
{
  /* Temporary variable */
  uint16_t i;

  for(i = 0U;i < i_len;i++)
    i_init = (i_init << 8U) ^ crc_table[((i_init >> 8U) & 0xFFU) ^ pc_data[i]];

  return i_init;
} /* crc_calc() */

#else
/*============================================================================*/
/*! crc_calc() */
/*============================================================================*/
uint16_t crc_calc(uint16_t i_init, uint8_t *pc_data, uint16_t i_len)
{
  /* Temporary variables */
  uint16_t i, j, c;
  /* Stores the current calculated crc value */
  uint16_t i_crc;

  i_crc = i_init;

  for(i = 0U;i < i_len;i++)
  {
    c = pc_data[i];

    c <<= 8U;

    i_crc ^= c;

    for(j = 0U;j < 8U;j++)
    {
      if(i_crc & 0x8000U)
        i_crc = (i_crc << 1U) ^ POLYNOMAL;
      else
         i_crc <<= 1U;
    } /* for */

    i_crc &= 0xFFFFU;
  } /* for */

  return i_crc;
} /* crc_calc() */
#endif /* CRC_TABLE */

/*============================================================================*/
/*! crc_calc_finalize() */
/*============================================================================*/
uint16_t crc_calc_finalize(uint8_t *pc_data, uint16_t i_len)
{
  /* Stores the current calculated crc value */
  uint16_t i_crc;

  i_crc = crc_calc(0U, pc_data, i_len);

  i_crc = crc_finalize(i_crc);

  return i_crc;
} /* crc_calc_finalize() */

/*============================================================================*/
/*! crc_finalize() */
/*============================================================================*/
uint16_t crc_finalize(uint16_t i_crc)
{
  /* Stores the current calculated crc value */
  uint16_t i_return;

  i_return = ~(i_crc);

  return i_return;
} /* crc_finalize() */

#ifdef __cplusplus
}
#endif