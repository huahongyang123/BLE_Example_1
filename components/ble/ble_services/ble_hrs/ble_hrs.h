
#ifndef BLE_HRS_H__
#define BLE_HRS_H__

#include <stdint.h>
#include <stdbool.h>
#include "ble.h"
#include "ble_srv_common.h"
#include "nrf_sdh_ble.h"
#include "nrf_ble_gatt.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief   Macro for defining a ble_hrs instance.
 *
 * @param   _name   Name of the instance.
 * @hideinitializer
 */
#define BLE_HRS_DEF(_name)                                                                          \
static ble_hrs_t _name;                                                                             \
NRF_SDH_BLE_OBSERVER(_name ## _obs,                                                                 \
                     BLE_HRS_BLE_OBSERVER_PRIO,                                                     \
                     ble_hrs_on_ble_evt, &_name)

// Body Sensor Location values
#define BLE_HRS_BODY_SENSOR_LOCATION_OTHER      0
#define BLE_HRS_BODY_SENSOR_LOCATION_CHEST      1
#define BLE_HRS_BODY_SENSOR_LOCATION_WRIST      2
#define BLE_HRS_BODY_SENSOR_LOCATION_FINGER     3
#define BLE_HRS_BODY_SENSOR_LOCATION_HAND       4
#define BLE_HRS_BODY_SENSOR_LOCATION_EAR_LOBE   5
#define BLE_HRS_BODY_SENSOR_LOCATION_FOOT       6

#define BLE_HRS_MAX_BUFFERED_RR_INTERVALS       20      /**< Size of RR Interval buffer inside service. */


/**@brief Heart Rate Service event type. */
typedef enum
{
    BLE_HRS_EVT_NOTIFICATION_ENABLED,   /**< Heart Rate value notification enabled event. */
    BLE_HRS_EVT_NOTIFICATION_DISABLED   /**< Heart Rate value notification disabled event. */
} ble_hrs_evt_type_t;

/**@brief Heart Rate Service event. */
typedef struct
{
    ble_hrs_evt_type_t evt_type;    /**< Type of event. */
} ble_hrs_evt_t;

// Forward declaration of the ble_hrs_t type.
typedef struct ble_hrs_s ble_hrs_t;

/**@brief Heart Rate Service event handler type. */
typedef void (*ble_hrs_evt_handler_t) (ble_hrs_t * p_hrs, ble_hrs_evt_t * p_evt);

/**@brief Heart Rate Service init structure. This contains all options and data needed for
 *        initialization of the service. */
typedef struct
{
    ble_hrs_evt_handler_t        evt_handler;                                          /**< Event handler to be called for handling events in the Heart Rate Service. */
    bool                         is_sensor_contact_supported;                          /**< Determines if sensor contact detection is to be supported. */
    uint8_t *                    p_body_sensor_location;                               /**< If not NULL, initial value of the Body Sensor Location characteristic. */
    security_req_t               hrm_cccd_wr_sec;                                      /**< Security requirement for writing the HRM characteristic CCCD. */
    security_req_t               bsl_rd_sec;                                           /**< Security requirement for reading the BSL characteristic value. */
} ble_hrs_init_t;

/**@brief Heart Rate Service structure. This contains various status information for the service. */
struct ble_hrs_s
{
    ble_hrs_evt_handler_t        evt_handler;                                          /**< Event handler to be called for handling events in the Heart Rate Service. */
    bool                         is_expended_energy_supported;                         /**< TRUE if Expended Energy measurement is supported. */
    bool                         is_sensor_contact_supported;                          /**< TRUE if sensor contact detection is supported. */
    uint16_t                     service_handle;                                       /**< Handle of Heart Rate Service (as provided by the BLE stack). */
    ble_gatts_char_handles_t     hrm_handles;                                          /**< Handles related to the Heart Rate Measurement characteristic. */
    ble_gatts_char_handles_t     bsl_handles;                                          /**< Handles related to the Body Sensor Location characteristic. */
    ble_gatts_char_handles_t     hrcp_handles;                                         /**< Handles related to the Heart Rate Control Point characteristic. */
    uint16_t                     conn_handle;                                          /**< Handle of the current connection (as provided by the BLE stack, is BLE_CONN_HANDLE_INVALID if not in a connection). */
    bool                         is_sensor_contact_detected;                           /**< TRUE if sensor contact has been detected. */
    uint16_t                     rr_interval[BLE_HRS_MAX_BUFFERED_RR_INTERVALS];       /**< Set of RR Interval measurements since the last Heart Rate Measurement transmission. */
    uint16_t                     rr_interval_count;                                    /**< Number of RR Interval measurements since the last Heart Rate Measurement transmission. */
    uint8_t                      max_hrm_len;                                          /**< Current maximum HR measurement length, adjusted according to the current ATT MTU. */
};


/**@brief Function for initializing the Heart Rate Service.
 *
 * @param[out]  p_hrs       Heart Rate Service structure. This structure will have to be supplied by
 *                          the application. It will be initialized by this function, and will later
 *                          be used to identify this particular service instance.
 * @param[in]   p_hrs_init  Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on successful initialization of service, otherwise an error code.
 */
uint32_t ble_hrs_init(ble_hrs_t * p_hrs, ble_hrs_init_t const * p_hrs_init);


/**@brief Function for handling the GATT module's events.
 *
 * @details Handles all events from the GATT module of interest to the Heart Rate Service.
 *
 * @param[in]   p_hrs      Heart Rate Service structure.
 * @param[in]   p_gatt_evt  Event received from the GATT module.
 */
void ble_hrs_on_gatt_evt(ble_hrs_t * p_hrs, nrf_ble_gatt_evt_t const * p_gatt_evt);


/**@brief Function for handling the Application's BLE Stack events.
 *
 * @details Handles all events from the BLE stack of interest to the Heart Rate Service.
 *
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 * @param[in]   p_context   Heart Rate Service structure.
 */
void ble_hrs_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context);


/**@brief Function for sending heart rate measurement if notification has been enabled.
 *
 * @details The application calls this function after having performed a heart rate measurement.
 *          If notification has been enabled, the heart rate measurement data is encoded and sent to
 *          the client.
 *
 * @param[in]   p_hrs                    Heart Rate Service structure.
 * @param[in]   heart_rate               New heart rate measurement.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
uint32_t ble_hrs_heart_rate_measurement_send(ble_hrs_t * p_hrs, uint16_t heart_rate);


/**@brief Function for adding a RR Interval measurement to the RR Interval buffer.
 *
 * @details All buffered RR Interval measurements will be included in the next heart rate
 *          measurement message, up to the maximum number of measurements that will fit into the
 *          message. If the buffer is full, the oldest measurement in the buffer will be deleted.
 *
 * @param[in]   p_hrs        Heart Rate Service structure.
 * @param[in]   rr_interval  New RR Interval measurement (will be buffered until the next
 *                           transmission of Heart Rate Measurement).
 */
void ble_hrs_rr_interval_add(ble_hrs_t * p_hrs, uint16_t rr_interval);


/**@brief Function for checking if RR Interval buffer is full.
 *
 * @param[in]   p_hrs        Heart Rate Service structure.
 *
 * @return      true if RR Interval buffer is full, false otherwise.
 */
bool ble_hrs_rr_interval_buffer_is_full(ble_hrs_t * p_hrs);


/**@brief Function for setting the state of the Sensor Contact Supported bit.
 *
 * @param[in]   p_hrs                        Heart Rate Service structure.
 * @param[in]   is_sensor_contact_supported  New state of the Sensor Contact Supported bit.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
uint32_t ble_hrs_sensor_contact_supported_set(ble_hrs_t * p_hrs, bool is_sensor_contact_supported);


/**@brief Function for setting the state of the Sensor Contact Detected bit.
 *
 * @param[in]   p_hrs                        Heart Rate Service structure.
 * @param[in]   is_sensor_contact_detected   TRUE if sensor contact is detected, FALSE otherwise.
 */
void ble_hrs_sensor_contact_detected_update(ble_hrs_t * p_hrs, bool is_sensor_contact_detected);


/**@brief Function for setting the Body Sensor Location.
 *
 * @details Sets a new value of the Body Sensor Location characteristic. The new value will be sent
 *          to the client the next time the client reads the Body Sensor Location characteristic.
 *
 * @param[in]   p_hrs                 Heart Rate Service structure.
 * @param[in]   body_sensor_location  New Body Sensor Location.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
uint32_t ble_hrs_body_sensor_location_set(ble_hrs_t * p_hrs, uint8_t body_sensor_location);


#ifdef __cplusplus
}
#endif

#endif // BLE_HRS_H__

/** @} */
