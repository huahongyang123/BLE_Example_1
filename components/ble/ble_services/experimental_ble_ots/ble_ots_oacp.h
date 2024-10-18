
#ifndef BLE_OTS_OACP_H__
#define BLE_OTS_OACP_H__

#include <stdint.h>
#include "ble_ots.h"
#include "nrf_ble_gq.h"

/**@brief Function for initializing the Object Transfer OACP characteristic.
 *
 * @param[out]  p_ots_oacp      Object Transfer Service OACP structure. This structure will have
 *                              to be supplied by the application. It will be initialized by this function,
 *                              and will later be used to identify this particular instance.
 * @param[in]   p_ots_oacp_init Information needed to initialize the module.
 *
 * @return      NRF_SUCCESS on successful initialization, otherwise an error code.
 */
uint32_t ble_ots_oacp_init(ble_ots_oacp_t * p_ots_oacp, ble_ots_oacp_init_t * p_ots_oacp_init);

/**@brief Function for handling the Application's BLE Stack events.
 *
 * @details Handles all events from the BLE stack of interest to the OACP module.
 *
 * @param[in]  p_ots_oacp   Object Transfer Service OACP structure
 * @param[in]  p_ble_evt    Event received from the BLE stack.
 */
void ble_ots_oacp_on_ble_evt(ble_ots_oacp_t * p_ots_oacp, ble_evt_t const * p_ble_evt);

/**@brief Execute an Object Action Control Point procedure
 *
 * @param[in]  p_ots_oacp           Object Transfer Service OACP structure.
 * @param[in]  p_oacp_proc          Pointer to the procedure to be applied.
 *
 * @return BLE_OTS_WRITE_SUCCESS on success, otherwise an error.
 */
ble_ots_oacp_res_code_t ble_ots_oacp_do_proc(ble_ots_oacp_t      * p_ots_oacp,
                                             ble_ots_oacp_proc_t * p_oacp_proc);


#endif // BLE_OTS_OACP_H__

/** @} */ // End tag for the file.
