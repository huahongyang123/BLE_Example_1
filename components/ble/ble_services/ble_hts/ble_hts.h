
#ifndef BLE_HTS_H__
#define BLE_HTS_H__

#include <stdint.h>
#include <stdbool.h>
#include "ble.h"
#include "ble_srv_common.h"
#include "ble_date_time.h"
#include "nrf_sdh_ble.h"
#include "nrf_ble_gq.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief   Macro for defining a ble_hts instance.
 *
 * @param   _name   Name of the instance.
 * @hideinitializer
 */
#define BLE_HTS_DEF(_name)                                                                          \
static ble_hts_t _name;                                                                             \
NRF_SDH_BLE_OBSERVER(_name ## _obs,                                                                 \
                     BLE_HTS_BLE_OBSERVER_PRIO,                                                     \
                     ble_hts_on_ble_evt, &_name)

// Temperature Type measurement locations
#define BLE_HTS_TEMP_TYPE_ARMPIT        1
#define BLE_HTS_TEMP_TYPE_BODY          2
#define BLE_HTS_TEMP_TYPE_EAR           3
#define BLE_HTS_TEMP_TYPE_FINGER        4
#define BLE_HTS_TEMP_TYPE_GI_TRACT      5
#define BLE_HTS_TEMP_TYPE_MOUTH         6
#define BLE_HTS_TEMP_TYPE_RECTUM        7
#define BLE_HTS_TEMP_TYPE_TOE           8
#define BLE_HTS_TEMP_TYPE_EAR_DRUM      9


/**@brief Health Thermometer Service event type. */
typedef enum
{
    BLE_HTS_EVT_INDICATION_ENABLED,                                         /**< Health Thermometer value indication enabled event. */
    BLE_HTS_EVT_INDICATION_DISABLED,                                        /**< Health Thermometer value indication disabled event. */
    BLE_HTS_EVT_INDICATION_CONFIRMED                                        /**< Confirmation of a temperature measurement indication has been received. */
} ble_hts_evt_type_t;

/**@brief Health Thermometer Service event. */
typedef struct
{
    ble_hts_evt_type_t evt_type;                                            /**< Type of event. */
} ble_hts_evt_t;

// Forward declaration of the ble_hts_t type.
typedef struct ble_hts_s ble_hts_t;

/**@brief Health Thermometer Service event handler type. */
typedef void (*ble_hts_evt_handler_t) (ble_hts_t * p_hts, ble_hts_evt_t * p_evt);

/**@brief FLOAT format (IEEE-11073 32-bit FLOAT, defined as a 32-bit value with a 24-bit mantissa
 *        and an 8-bit exponent. */
typedef struct
{
  int8_t  exponent;                                                         /**< Base 10 exponent */
  int32_t mantissa;                                                         /**< Mantissa, should be using only 24 bits */
} ieee_float32_t;

/**@brief Health Thermometer Service init structure. This contains all options and data
 *        needed for initialization of the service. */
typedef struct
{
    ble_hts_evt_handler_t        evt_handler;                               /**< Event handler to be called for handling events in the Health Thermometer Service. */
    ble_srv_error_handler_t      error_handler;                             /**< Function to be called in case of an error. */
    security_req_t               ht_meas_cccd_wr_sec;                       /**< Security requirement for writing health thermometer measurement characteristic CCCD. */
    security_req_t               ht_type_rd_sec;                            /**< Security requirement for reading health thermometer type characteristic. */
    uint8_t                      temp_type_as_characteristic;               /**< Set non-zero if temp type given as characteristic */
    uint8_t                      temp_type;                                 /**< Temperature type if temperature characteristic is used */
    nrf_ble_gq_t               * p_gatt_queue;                              /**< Pointer to BLE GATT Queue instance. */
} ble_hts_init_t;

/**@brief Health Thermometer Service structure. This contains various status information for
 *        the service. */
struct ble_hts_s
{
    ble_hts_evt_handler_t        evt_handler;                               /**< Event handler to be called for handling events in the Health Thermometer Service. */
    ble_srv_error_handler_t      error_handler;                             /**< Function to be called in case of an error. */
    uint16_t                     service_handle;                            /**< Handle of Health Thermometer Service (as provided by the BLE stack). */
    ble_gatts_char_handles_t     meas_handles;                              /**< Handles related to the Health Thermometer Measurement characteristic. */
    ble_gatts_char_handles_t     temp_type_handles;                         /**< Handles related to the Health Thermometer Temperature Type characteristic. */
    uint16_t                     conn_handle;                               /**< Handle of the current connection (as provided by the BLE stack, is BLE_CONN_HANDLE_INVALID if not in a connection). */
    uint8_t                      temp_type;                                 /**< Temperature type indicates where the measurement was taken. */
    nrf_ble_gq_t               * p_gatt_queue;                              /**< Pointer to BLE GATT Queue instance. */
};

/**@brief Health Thermometer Service measurement structure. This contains a Health Thermometer
 *        measurement. */
typedef struct ble_hts_meas_s
{
    bool                         temp_in_fahr_units;                        /**< True if Temperature is in Fahrenheit units, Celcius otherwise. */
    bool                         time_stamp_present;                        /**< True if Time Stamp is present. */
    bool                         temp_type_present;                         /**< True if Temperature Type is present. */
    ieee_float32_t               temp_in_celcius;                           /**< Temperature Measurement Value (Celcius). */
    ieee_float32_t               temp_in_fahr;                              /**< Temperature Measurement Value (Fahrenheit). */
    ble_date_time_t              time_stamp;                                /**< Time Stamp. */
    uint8_t                      temp_type;                                 /**< Temperature Type. */
} ble_hts_meas_t;


/**@brief Function for initializing the Health Thermometer Service.
 *
 * @param[out]  p_hts       Health Thermometer Service structure. This structure will have to
 *                          be supplied by the application. It will be initialized by this function,
 *                          and will later be used to identify this particular service instance.
 * @param[in]   p_hts_init  Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on successful initialization of service, otherwise an error code.
 */
uint32_t ble_hts_init(ble_hts_t * p_hts, const ble_hts_init_t * p_hts_init);


/**@brief Function for handling the Application's BLE Stack events.
 *
 * @details Handles all events from the BLE stack of interest to the Health Thermometer Service.
 *
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 * @param[in]   p_context   Health Thermometer Service structure.
 */
void ble_hts_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context);


/**@brief Function for sending health thermometer measurement if indication has been enabled.
 *
 * @details The application calls this function after having performed a Health Thermometer
 *          measurement. If indication has been enabled, the measurement data is encoded and
 *          sent to the client.
 *
 * @param[in]   p_hts       Health Thermometer Service structure.
 * @param[in]   p_hts_meas  Pointer to new health thermometer measurement.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
uint32_t ble_hts_measurement_send(ble_hts_t * p_hts, ble_hts_meas_t * p_hts_meas);


/**@brief Function for checking if indication of Temperature Measurement is currently enabled.
 *
 * @param[in]   p_hts                  Health Thermometer Service structure.
 * @param[out]  p_indication_enabled   TRUE if indication is enabled, FALSE otherwise.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
uint32_t ble_hts_is_indication_enabled(ble_hts_t * p_hts, bool * p_indication_enabled);


#ifdef __cplusplus
}
#endif

#endif // BLE_HTS_H__

/** @} */
