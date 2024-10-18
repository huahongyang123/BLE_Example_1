
#ifndef BLE_OTS_OBJECT_H__
#define BLE_OTS_OBJECT_H__

#include <stdint.h>
#include "ble_ots.h"

/**@brief Function for initializing the Object Transfer Object representation characteristics.
 *
 * @param[out]  p_ots_object_chars Object Transfer Service object characteristics representation structure. *                                        This structure will have to be supplied by the application. It *                                        will be initialized by this function, and will later be used to *                                        identify this particular instance.
 * @param[in]   p_ots_object_chars_init   Information needed to initialize the module.
 *
 * @return      NRF_SUCCESS on successful initialization, otherwise an error code.
 */
uint32_t ble_ots_object_representation_init(ble_ots_object_chars_t      * p_ots_object_chars,
                                            ble_ots_object_chars_init_t * p_ots_object_chars_init);

/**@brief Refresh the characteristics of the current object.
 * @param[in] p_ots_object_chars Pointer the the object characteristics.
 * @return NRF_SUCCESS if everything was refreshed.
 */
uint32_t ble_ots_object_refresh_current(ble_ots_object_chars_t * p_ots_object_chars);


/**@brief Function for handling the Application's BLE Stack events.
 *
 * @details Handles all events from the BLE stack of interest to the list filter module.
 *
 * @param[in]  p_ots_object_chars   Pointer the the object characteristics.
 * @param[in]  p_ble_evt            Event received from the BLE stack.
 */
void ble_ots_object_on_ble_evt(ble_ots_object_chars_t * p_ots_object_chars,
                               ble_evt_t const * p_ble_evt);

#endif // BLE_OTS_OBJECT_H__

/** @} */ // End tag for the file.
