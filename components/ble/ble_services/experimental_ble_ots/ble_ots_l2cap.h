
#ifndef BLE_OTS_L2CAP_H__
#define BLE_OTS_L2CAP_H__

#include <stdint.h>
#include "ble_ots.h"

/**@brief Function for initializing the Object Transfer Service l2cap module.
 *
 * @param[out]  p_ots_l2cap         Object Transfer Service l2cap structure. This structure will have to be
 *                                  supplied by the application. It will be initialized by this function,
 *                                  and will later be used to identify this particular instance.
 * @param[in]   p_ots_l2cap_init    Information needed to initialize the module.
 *
 * @return      NRF_SUCCESS on successful initialization, otherwise an error code.
 */
uint32_t ble_ots_l2cap_init(ble_ots_l2cap_t * p_ots_l2cap, ble_ots_l2cap_init_t * p_ots_l2cap_init);


/**@brief Function for handling the Application's BLE Stack events.
 *
 * @details Handles all events from the BLE stack of interest to the l2cap module.
 *
 * @param[in]   p_ots_l2cap Object transfer service l2cap module structure.
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 */
void ble_ots_l2cap_on_ble_evt(ble_ots_l2cap_t * p_ots_l2cap, ble_evt_t const * p_ble_evt);


/**@brief Function starting to send the data in the transfer buffer.
 *
 * @param[in]   p_ots_l2cap Object transfer service l2cap module structure.
 * @param[in]   p_data      Pointer to the data to be sent.
 * @param[in]   data_len    The length of the data to be sent.
 *
 * @return      NRF_SUCCESS             If the transmission was started.
 * @return      NRF_ERROR_INVALID_STATE When in an invalid state. Otherwise an other error code.
 */
uint32_t ble_ots_l2cap_obj_send(ble_ots_l2cap_t * p_ots_l2cap, uint8_t * p_data, uint16_t data_len);


/**@brief Function starting to receive data to the transfer buffer.
 *
 * @param[in]   p_ots_l2cap     Object transfer service l2cap module structure.
 * @param[in]   len             The length of the data to be received.
 *
 * @return      NRF_SUCCESS             If the transmission was started.
 * @return      NRF_ERROR_INVALID_STATE When in an invalid state. Otherwise an other error code.
 */
uint32_t ble_ots_l2cap_start_recv(ble_ots_l2cap_t * p_ots_l2cap, uint16_t len);


/**@brief Function that checks if the channel is available for transmission.
 *
 * @param[in]   p_ots_l2cap     Object transfer service l2cap module structure.
 *
 * @return      true if the channel is available.
 */
bool ble_ots_l2cap_is_channel_available(ble_ots_l2cap_t * p_ots_l2cap);


/**@brief Function starting to abort the current transmission.
 *
 * @param[in]   p_ots_l2cap     Object transfer service l2cap module structure.
 *
 * @return      NRF_SUCCESS             If the transmission was aborted.
 * @return      NRF_ERROR_INVALID_STATE When in an invalid state. Otherwise an other error code.
 */
uint32_t ble_ots_l2cap_abort_transmission(ble_ots_l2cap_t * p_ots_l2cap);

#endif // BLE_OTS_L2CAP_H__

/** @} */ // End tag for the file.

