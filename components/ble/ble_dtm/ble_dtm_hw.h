
#ifndef BLE_DTM_HW_H__
#define BLE_DTM_HW_H__

#include <stdint.h>
#include <stdbool.h>
#include "nrf.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief Function for turning off radio test.
 *        This function is platform depending. For now only nRF51 requieres this special function.
 */
void dtm_turn_off_test(void);


/**@brief Function for setting constant carrier in radio settings.
 *        This function is used to handle vendor specific command testing continous carrier without
 *        a modulated signal.
 */
void dtm_constant_carrier(void);


/**@brief Function for validating tx power and radio move settings.
 * @param[in] m_tx_power    TX power for transmission test.
 * @param[in] m_radio_mode  Radio mode value.
 *
 * @retval DTM_SUCCESS                     if input parameters values are correct.
 * @retval DTM_ERROR_ILLEGAL_CONFIGURATION if input parameters values are not correct.
 */
uint32_t dtm_radio_validate(uint32_t m_tx_power, uint8_t m_radio_mode);

#ifdef __cplusplus
}
#endif

#endif // BLE_DTM_HW_H__

/** @} */
