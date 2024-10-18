
#ifndef BLE_RSCS_H__
#define BLE_RSCS_H__

#include <stdint.h>
#include <stdbool.h>
#include "ble_srv_common.h"
#include "nrf_sdh_ble.h"

#ifdef __cplusplus
extern "C" {
#endif

/**@brief   Macro for defining a ble_rscs instance.
 *
 * @param   _name   Name of the instance.
 * @hideinitializer
 */
#define BLE_RSCS_DEF(_name)                                                                         \
static ble_rscs_t _name;                                                                            \
NRF_SDH_BLE_OBSERVER(_name ## _obs,                                                                 \
                     BLE_RSCS_BLE_OBSERVER_PRIO,                                                    \
                     ble_rscs_on_ble_evt, &_name)

/**@brief Running Speed and Cadence Service feature bits. */
#define BLE_RSCS_FEATURE_INSTANT_STRIDE_LEN_BIT             (0x01 << 0)     /**< Instantaneous Stride Length Measurement Supported bit. */
#define BLE_RSCS_FEATURE_TOTAL_DISTANCE_BIT                 (0x01 << 1)     /**< Total Distance Measurement Supported bit. */
#define BLE_RSCS_FEATURE_WALKING_OR_RUNNING_STATUS_BIT      (0x01 << 2)     /**< Walking or Running Status Supported bit. */
#define BLE_RSCS_FEATURE_CALIBRATION_PROCEDURE_BIT          (0x01 << 3)     /**< Calibration Procedure Supported bit. */
#define BLE_RSCS_FEATURE_MULTIPLE_SENSORS_BIT               (0x01 << 4)     /**< Multiple Sensor Locations Supported bit. */


/**@brief Running Speed and Cadence Service event type. */
typedef enum
{
    BLE_RSCS_EVT_NOTIFICATION_ENABLED,                                      /**< Running Speed and Cadence value notification enabled event. */
    BLE_RSCS_EVT_NOTIFICATION_DISABLED                                      /**< Running Speed and Cadence value notification disabled event. */
} ble_rscs_evt_type_t;

/**@brief Running Speed and Cadence Service event. */
typedef struct
{
    ble_rscs_evt_type_t evt_type;                                           /**< Type of event. */
} ble_rscs_evt_t;

// Forward declaration of the ble_rsc types.
typedef struct ble_rscs_s      ble_rscs_t;
typedef struct ble_rscs_meas_s ble_rscs_meas_t;

/**@brief Running Speed and Cadence Service event handler type. */
typedef void (*ble_rscs_evt_handler_t) (ble_rscs_t * p_rscs, ble_rscs_evt_t * p_evt);

/**@brief Running Speed and Cadence Service measurement structure. This contains a Running Speed and
 *        Cadence measurement.
 */
struct ble_rscs_meas_s
{
    bool        is_inst_stride_len_present;                                 /**< True if Instantaneous Stride Length is present in the measurement. */
    bool        is_total_distance_present;                                  /**< True if Total Distance is present in the measurement. */
    bool        is_running;                                                 /**< True if running, False if walking. */
    uint16_t    inst_speed;                                                 /**< Instantaneous Speed. */
    uint8_t     inst_cadence;                                               /**< Instantaneous Cadence. */
    uint16_t    inst_stride_length;                                         /**< Instantaneous Stride Length. */
    uint32_t    total_distance;                                             /**< Total Distance. */
};

/**@brief Running Speed and Cadence Service init structure. This contains all options and data
 *        needed for initialization of the service.
 */
typedef struct
{
    ble_rscs_evt_handler_t evt_handler;                                     /**< Event handler to be called for handling events in the Running Speed and Cadence Service. */
    security_req_t         rsc_meas_cccd_wr_sec;                            /**< Security requirement for writing running speed and cadence measurement characteristic CCCD. */
    security_req_t         rsc_feature_rd_sec;                              /**< Security requirement for reading running speed and cadence feature characteristic. */
    uint16_t               feature;                                         /**< Initial value for features of sensor. */
    ble_rscs_meas_t        initial_rcm;                                     /**< Initial Running Speed Cadence Measurement.*/
} ble_rscs_init_t;

/**@brief Running Speed and Cadence Service structure. This contains various status information for
 *        the service.
 */
struct ble_rscs_s
{
    ble_rscs_evt_handler_t       evt_handler;                               /**< Event handler to be called for handling events in the Running Speed and Cadence Service. */
    uint16_t                     service_handle;                            /**< Handle of Running Speed and Cadence Service (as provided by the BLE stack). */
    ble_gatts_char_handles_t     meas_handles;                              /**< Handles related to the Running Speed and Cadence Measurement characteristic. */
    ble_gatts_char_handles_t     feature_handles;                           /**< Handles related to the Running Speed and Cadence feature characteristic. */
    uint16_t                     conn_handle;                               /**< Handle of the current connection (as provided by the BLE stack, is BLE_CONN_HANDLE_INVALID if not in a connection). */
    uint16_t                     feature;                                   /**< Bit mask of features available on sensor. */
};


/**@brief Function for initializing the Running Speed and Cadence Service.
 *
 * @param[out]  p_rscs      Running Speed and Cadence Service structure. This structure will have to
 *                          be supplied by the application. It will be initialized by this function,
 *                          and will later be used to identify this particular service instance.
 * @param[in]   p_rscs_init Information needed to initialize the service.
 *
 * @return      NRF_SUCCESS on successful initialization of service, otherwise an error code.
 */
uint32_t ble_rscs_init(ble_rscs_t * p_rscs, const ble_rscs_init_t * p_rscs_init);


/**@brief Function for handling the Application's BLE Stack events.
 *
 * @details Handles all events from the BLE stack of interest to the Running Speed and Cadence
 *          Service.
 *
 * @param[in]   p_ble_evt   Event received from the BLE stack.
 * @param[in]   p_context   Running Speed and Cadence Service structure.
 */
void ble_rscs_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context);


/**@brief Function for sending running speed and cadence measurement if notification has been enabled.
 *
 * @details The application calls this function after having performed a Running Speed and Cadence
 *          measurement. If notification has been enabled, the measurement data is encoded and sent
 *          to the client.
 *
 * @param[in]   p_rscs         Running Speed and Cadence Service structure.
 * @param[in]   p_measurement  Pointer to new running speed and cadence measurement.
 *
 * @return      NRF_SUCCESS on success, otherwise an error code.
 */
uint32_t ble_rscs_measurement_send(ble_rscs_t * p_rscs, ble_rscs_meas_t * p_measurement);


#ifdef __cplusplus
}
#endif

#endif // BLE_RSCS_H__

/** @} */
