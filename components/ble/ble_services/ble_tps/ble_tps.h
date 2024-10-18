
#ifndef BLE_TPS_H__
#define BLE_TPS_H__

#include <stdint.h>
#include "ble.h"
#include "ble_srv_common.h"
#include "nrf_sdh_ble.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief   Macro for defining a ble_tps instance.
 *
 * @param   _name   Name of the instance.
 * @hideinitializer
 */
#define BLE_TPS_DEF(_name)                                                                          \
static ble_tps_t _name;                                                                             \
NRF_SDH_BLE_OBSERVER(_name ## _obs,                                                                 \
                     BLE_TPS_BLE_OBSERVER_PRIO,                                                     \
                     ble_tps_on_ble_evt, &_name)


/**@brief TX Power Service init structure. This contains all options and data needed for
 *        initialization of the service. */
typedef struct
{
    int8_t          initial_tx_power_level;   /**< Initial value of the TX Power Level characteristic (in dBm). */
    security_req_t  tpl_rd_sec;               /**< Security requirement for reading TX Power Level characteristic. */
} ble_tps_init_t;

/**@brief TX Power Service structure. This contains various status information for the service. */
typedef struct
{
    uint16_t                  service_handle;           /**< Handle of TX Power Service (as provided by the BLE stack). */
    ble_gatts_char_handles_t  tx_power_level_handles;   /**< Handles related to the TX Power Level characteristic. */
    uint16_t                  conn_handle;              /**< Handle of the current connection (as provided by the BLE stack, is BLE_CONN_HANDLE_INVALID if not in a connection). */
} ble_tps_t;


/**@brief Function for initializing the TX Power Service.
 *
 * @param[out]  p_hrs       TX Power Service structure. This structure will have to be supplied by
 *                          the application. It will be initialized by this function, and will later
 *                          be used to identify this particular service instance.
 * @param[in]   p_tps_init  Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on successful initialization of service, otherwise an error code.
 */
uint32_t ble_tps_init(ble_tps_t * p_hrs, const ble_tps_init_t * p_tps_init);


/**@brief Function for handling the Application's BLE Stack events.
 *
 * @details Handles all events from the BLE stack of interest to the TX Power Service.
 *
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 * @param[in]   p_context   TX Power Service structure.
 */
void ble_tps_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context);


/**@brief Function for setting the value of the TX Power Level characteristic.
 *
 * @param[in]   p_tps            TX Power Service structure.
 * @param[in]   tx_power_level   New TX Power Level (unit dBm, range -100 to 20).
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
uint32_t ble_tps_tx_power_level_set(ble_tps_t * p_tps, int8_t tx_power_level);


#ifdef __cplusplus
}
#endif

#endif // BLE_TPS_H__

/** @} */
