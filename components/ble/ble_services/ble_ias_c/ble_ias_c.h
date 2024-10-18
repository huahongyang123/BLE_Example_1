
#ifndef BLE_IAS_C_H__
#define BLE_IAS_C_H__

#include <stdint.h>
#include "ble_srv_common.h"
#include "ble_gattc.h"
#include "ble.h"
#include "ble_db_discovery.h"
#include "nrf_ble_gq.h"
#include "nrf_sdh_ble.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief   Macro for defining a ble_ias_c instance.
 *
 * @param   _name   Name of the instance.
 * @hideinitializer
 */
#define BLE_IAS_C_DEF(_name)                                                                        \
static ble_ias_c_t _name;                                                                           \
NRF_SDH_BLE_OBSERVER(_name ## _obs,                                                                 \
                     BLE_IAS_C_BLE_OBSERVER_PRIO,                                                   \
                     ble_ias_c_on_ble_evt, &_name)

/** @brief Macro for defining multiple ble_ias_c instances.
 *
 * @param   _name   Name of the array of instances.
 * @param   _cnt    Number of instances to define.
 * @hideinitializer
 */
#define BLE_IAS_C_ARRAY_DEF(_name, _cnt)                 \
static ble_ias_c_t _name[_cnt];                          \
NRF_SDH_BLE_OBSERVERS(_name ## _obs,                     \
                      BLE_IAS_C_BLE_OBSERVER_PRIO,       \
                      ble_ias_c_on_ble_evt, &_name, _cnt)


// Forward declaration of the ble_ias_c_t type.
typedef struct ble_ias_c_s ble_ias_c_t;

/**@brief Immediate Alert Service client event type. */
typedef enum
{
    BLE_IAS_C_EVT_DISCOVERY_COMPLETE,             /**< Event indicating that the Immediate Alert Service is found at the peer. */
    BLE_IAS_C_EVT_DISCOVERY_FAILED,               /**< Event indicating that the Immediate Alert Service is not found at the peer. */
    BLE_IAS_C_EVT_DISCONN_COMPLETE                /**< Event indicating that the Immediate Alert Service Client module completed the processing of BLE_GAP_EVT_DISCONNECTED event. This event is triggered only if a valid instance of IAS was found at the peer during the discovery phase. The application can use this event to do a cleanup related to the IAS Client.*/
} ble_ias_c_evt_type_t;

/**@brief Immediate Alert Service client event. */
typedef struct
{
    ble_ias_c_evt_type_t evt_type;                /**< Type of event. */
    uint16_t             conn_handle;             /**< Connection handle on which the IAS service was discovered on the peer device. This is filled if the evt_type is @ref BLE_IAS_C_EVT_DISCOVERY_COMPLETE.*/
    ble_gattc_char_t     alert_level;             /**< Information on the discovered Alert Level characteristic discovered. This is filled if the evt_type is @ref BLE_IAS_C_EVT_DISCOVERY_COMPLETE.*/
} ble_ias_c_evt_t;

/**@brief Immediate Alert Service client event handler type. */
typedef void (*ble_ias_c_evt_handler_t) (ble_ias_c_t * p_ias_c, ble_ias_c_evt_t * p_evt);

/**@brief IAS Client structure. Contains various status information for the client. */
struct ble_ias_c_s
{
    ble_ias_c_evt_handler_t   evt_handler;        /**< Event handler to be called for handling events in the Immediate Alert Service client. */
    ble_srv_error_handler_t   error_handler;      /**< Function to be called in case of an error. */
    uint16_t                  conn_handle;        /**< Handle of the current connection. Set with @ref ble_ias_c_handles_assign when connected. */
    ble_uuid_t                service_uuid;       /**< The GATT Service holding the discovered Immediate Service. */
    ble_gattc_char_t          alert_level_char;   /**< IAS Alert Level Characteristic. Stores data about the alert characteristic found on the peer. */
    nrf_ble_gq_t            * p_gatt_queue;       /**< Pointer to the BLE GATT Queue instance. */
};

/**@brief IAS Client init structure. Contains all options and data needed for the initialization of
 *        the client.*/
typedef struct
{
    ble_ias_c_evt_handler_t   evt_handler;        /**< Event handler to be called for handling events from the Immediate Alert Service client. */
    ble_srv_error_handler_t   error_handler;      /**< Function to be called in case of an error. */
    nrf_ble_gq_t            * p_gatt_queue;       /**< Pointer to the BLE GATT Queue instance. */
} ble_ias_c_init_t;


/**@brief Function for initializing the Immediate Alert Service client.
 *
 * @details This call allows the application to initialize the Immediate Alert Service client.
 *
 * @param[out]  p_ias_c      Immediate Alert Service client structure. This structure must
 *                           be supplied by the application. It is initialized by this
 *                           function, and is later used to identify this particular client
 *                           instance.
 * @param[in]   p_ias_c_init Information needed to initialize the Immediate Alert Service client.
 *
 * @return      NRF_SUCCESS on successful initialization of service.
 */
uint32_t ble_ias_c_init(ble_ias_c_t * p_ias_c, ble_ias_c_init_t const * p_ias_c_init);


/**@brief Function for sending alert level to the peer.
 *
 * @details This function allows the application to send an alert to the peer.
 *
 * @param[in]   p_ias_c      Immediate Alert Service client structure.
 * @param[in]   alert_level  Required alert level to be sent to the peer.
 *
 * @retval      NRF_SUCCESS On success. 
 * @retval      err_code    Otherwise, this API propagates the error code returned by function
 *                          @ref nrf_ble_gq_item_add.
 */
uint32_t ble_ias_c_send_alert_level(ble_ias_c_t const * p_ias_c, uint8_t alert_level);


/**@brief Function for handling the Application's BLE Stack events for Immediate Alert Service client.
 *
 * @details Handles all events from the BLE stack of interest to the Immediate Alert Service client.
 *
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 * @param[in]   p_context   Immediate Alert Service client structure.
 */
void ble_ias_c_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context);


/**@brief Function for checking whether the peer's Immediate Alert Service instance and the Alert Level
 *        characteristic have been discovered.
 *
 * @param[in]  p_ias_c      Immediate Alert Service client structure.
 *
 * @return True, if a handle is assigned to alert_level_handle, meaning it must have been discovered.
 * @return False, if the handle is invalid.
 */
static __INLINE bool ble_ias_c_is_discovered(ble_ias_c_t const * p_ias_c)
{
    return (p_ias_c->alert_level_char.handle_value != BLE_GATT_HANDLE_INVALID);
}


/**@brief     Function for handling events from the Database Discovery module.
 *
 * @details   Call this function when you get a callback event from the Database Discovery module.
 *            This function handles an event from the Database Discovery module, and determines
 *            whether it relates to the discovery of Immediate Alert Service at the peer. If it does, the function
 *            calls the application's event handler to indicate that the Immediate Alert Service was
 *            discovered at the peer. The function also populates the event with service-related
 *            information before providing it to the application.
 *
 * @param[in] p_ias_c Pointer to the Immediate Alert client structure instance that will handle
 *                    the discovery.
 * @param[in] p_evt   Pointer to the event received from the Database Discovery module.
 *
 */
void ble_ias_c_on_db_disc_evt(ble_ias_c_t * p_ias_c, ble_db_discovery_evt_t const * p_evt);


/**@brief Function for assigning handles to an instance of ias_c.
 *
 * @details Call this function when a link has been established with a peer to
 *          associate the link to this instance of the module. This makes it
 *          possible to handle several links and associate each link to a particular
 *          instance of this module. The connection handle and attribute handles are
 *          provided from the discovery event @ref BLE_IAS_C_EVT_DISCOVERY_COMPLETE.
 *
 * @param[in] p_ias_c            Pointer to the IAS client structure instance for associating the link.
 * @param[in] conn_handle        Connection handle to associated with the given IAS instance.
 * @param[in] alert_level_handle Attribute handle on the IAS server that you want this IAS_C client to
 *                               interact with.
 *
 * @retval NRF_SUCCESS    If the operation was successful.
 * @retval NRF_ERROR_NULL If a p_ias_c was a NULL pointer.
 * @retval err_code       Otherwise, this API propagates the error code returned by function
 *                        @ref nrf_ble_gq_conn_handle_register.
 */
uint32_t ble_ias_c_handles_assign(ble_ias_c_t * p_ias_c,
                                  uint16_t      conn_handle,
                                  uint16_t      alert_level_handle);


#ifdef __cplusplus
}
#endif

#endif // BLE_IAS_C_H__

/** @} */
