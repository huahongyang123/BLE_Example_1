
#ifndef NRF_BLE_QUEUED_WRITES_H__
#define NRF_BLE_QUEUED_WRITES_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "nordic_common.h"
#include "sdk_common.h"
#include "ble.h"
#include "ble_srv_common.h"

/**@brief   Macro for defining a nrf_ble_qwr instance.
 *
 * @param   _name   Name of the instance.
 * @hideinitializer
 */
#define NRF_BLE_QWR_DEF(_name)                          \
    static nrf_ble_qwr_t _name;                         \
    NRF_SDH_BLE_OBSERVER(_name ## _obs,                 \
                         NRF_BLE_QWR_BLE_OBSERVER_PRIO, \
                         nrf_ble_qwr_on_ble_evt,        \
                         &_name)

/**@brief   Macro for defining an array of nrf_ble_qwr instance.
 *
 * @param   _name   Name of the array.
 * @param   _cnt    Size of the array.
 * @hideinitializer
 */
#define NRF_BLE_QWRS_DEF(_name, _cnt)                    \
    static nrf_ble_qwr_t _name[_cnt];                    \
    NRF_SDH_BLE_OBSERVERS(_name ## _obs,                 \
                          NRF_BLE_QWR_BLE_OBSERVER_PRIO, \
                          nrf_ble_qwr_on_ble_evt,        \
                          &_name,                        \
                          _cnt)


#define NRF_BLE_QWR_REJ_REQUEST_ERR_CODE    BLE_GATT_STATUS_ATTERR_APP_BEGIN + 0 //!< Error code used by the module to reject prepare write requests on non-registered attributes.


/**@brief Queued Writes module event types. */
typedef enum
{
    NRF_BLE_QWR_EVT_EXECUTE_WRITE, //!< Event that indicates that an execute write command was received for a registered handle and that the received data was actually written and is now ready.
    NRF_BLE_QWR_EVT_AUTH_REQUEST,  //!< Event that indicates that an execute write command was received for a registered handle and that the write request must now be accepted or rejected.
} nrf_ble_qwr_evt_type_t;

/**@brief Queued Writes module events. */
typedef struct
{
    nrf_ble_qwr_evt_type_t evt_type;    //!< Type of the event.
    uint16_t               attr_handle; //!< Handle of the attribute to which the event relates.
} nrf_ble_qwr_evt_t;

// Forward declaration of the nrf_ble_qwr_t type.
struct nrf_ble_qwr_t;

/**@brief Queued Writes module event handler type.
 *
 * If the provided event is of type @ref NRF_BLE_QWR_EVT_AUTH_REQUEST,
 * this function must accept or reject the execute write request by returning
 * one of the @ref BLE_GATT_STATUS_CODES.*/
typedef uint16_t (* nrf_ble_qwr_evt_handler_t) (struct nrf_ble_qwr_t * p_qwr,
                                                nrf_ble_qwr_evt_t    * p_evt);

/**@brief Queued Writes structure.
 * @details This structure contains status information for the Queued Writes module. */
typedef struct nrf_ble_qwr_t
{
    uint8_t                   initialized;                                //!< Flag that indicates whether the module has been initialized.
    uint16_t                  conn_handle;                                //!< Connection handle.
    ble_srv_error_handler_t   error_handler;                              //!< Error handler.
    bool                      is_user_mem_reply_pending;                  //!< Flag that indicates whether a mem_reply is pending (because a previous attempt returned busy).
#if (NRF_BLE_QWR_MAX_ATTR > 0)
    uint16_t                  attr_handles[NRF_BLE_QWR_MAX_ATTR];         //!< List of handles for registered attributes, for which the module accepts and handles prepare write operations.
    uint8_t                   nb_registered_attr;                         //!< Number of registered attributes.
    uint16_t                  written_attr_handles[NRF_BLE_QWR_MAX_ATTR]; //!< List of attribute handles that have been written to during the current prepare write or execute write operation.
    uint8_t                   nb_written_handles;                         //!< Number of attributes that have been written to during the current prepare write or execute write operation.
    ble_user_mem_block_t      mem_buffer;                                 //!< Memory buffer that is provided to the SoftDevice on an ON_USER_MEM_REQUEST event.
    nrf_ble_qwr_evt_handler_t callback;                                   //!< Event handler function that is called for events concerning the handles of all registered attributes.
#endif
} nrf_ble_qwr_t;

/**@brief Queued Writes init structure.
 * @details This structure contains all information
 *          that is needed to initialize the Queued Writes module. */
typedef struct
{
    ble_srv_error_handler_t   error_handler; //!< Error handler.
#if (NRF_BLE_QWR_MAX_ATTR > 0)
    ble_user_mem_block_t      mem_buffer;    //!< Memory buffer that is provided to the SoftDevice on an ON_USER_MEM_REQUEST event.
    nrf_ble_qwr_evt_handler_t callback;      //!< Event handler function that is called for events concerning the handles of all registered attributes.
#endif
} nrf_ble_qwr_init_t;


/**@brief Function for initializing the Queued Writes module.
 *
 * @details Call this function in the main entry of your application to
 * initialize the Queued Writes module. It must be called only once with a
 * given Queued Writes structure.
 *
 * @param[out]  p_qwr     Queued Writes structure. This structure must be
 *                        supplied by the application. It is initialized by this function
 *                        and is later used to identify the particular Queued Writes instance.
 * @param[in]  p_qwr_init Initialization structure.
 *
 * @retval NRF_SUCCESS             If the Queued Writes module was initialized successfully.
 * @retval NRF_ERROR_NULL          If any of the given pointers is NULL.
 * @retval NRF_ERROR_INVALID_STATE If the given context has already been initialized.
 */
ret_code_t nrf_ble_qwr_init(nrf_ble_qwr_t            * p_qwr,
                            nrf_ble_qwr_init_t const * p_qwr_init);


/**@brief Function for assigning a connection handle to a given instance of the Queued Writes module.
 *
 * @details   Call this function when a link with a peer has been established to
 *            associate this link to the instance of the module. This makes it
 *            possible to handle several links and associate each link to a particular
 *            instance of this module.
 *
 * @param[in]  p_qwr       Queued Writes structure.
 * @param[in]  conn_handle Connection handle to be associated with the given Queued Writes instance.
 *
 * @retval NRF_SUCCESS             If the assignment was successful.
 * @retval NRF_ERROR_NULL          If any of the given pointers is NULL.
 * @retval NRF_ERROR_INVALID_STATE If the given context has not been initialized.
 */
ret_code_t nrf_ble_qwr_conn_handle_assign(nrf_ble_qwr_t * p_qwr,
                                          uint16_t        conn_handle);


/**@brief Function for handling BLE stack events.
 *
 * @details Handles all events from the BLE stack that are of interest to the Queued Writes module.
 *
 * @param[in]  p_ble_evt    Event received from the BLE stack.
 * @param[in]  p_context    Queued Writes structure.
 */
void nrf_ble_qwr_on_ble_evt(ble_evt_t const * p_ble_evt, void * p_context);


#if (NRF_BLE_QWR_MAX_ATTR > 0)
/**@brief Function for registering an attribute with the Queued Writes module.
 *
 * @details Call this function for each attribute that you want to enable for
 * Queued Writes (thus a series of prepare write and execute write operations).
 *
 * @param[in]  p_qwr       Queued Writes structure.
 * @param[in]  attr_handle Handle of the attribute to register.
 *
 * @retval NRF_SUCCESS             If the registration was successful.
 * @retval NRF_ERROR_NO_MEM        If no more memory is available to add this registration.
 * @retval NRF_ERROR_NULL          If any of the given pointers is NULL.
 * @retval NRF_ERROR_INVALID_STATE If the given context has not been initialized.
 */
ret_code_t nrf_ble_qwr_attr_register(nrf_ble_qwr_t * p_qwr, uint16_t attr_handle);


/**@brief Function for retrieving the received data for a given attribute.
 *
 * @details Call this function after receiving an @ref NRF_BLE_QWR_EVT_AUTH_REQUEST
 * event to retrieve a linear copy of the data that was received for the given attribute.
 *
 * @param[in]     p_qwr       Queued Writes structure.
 * @param[in]     attr_handle Handle of the attribute.
 * @param[out]    p_mem       Pointer to the application buffer where the received data will be copied.
 * @param[in,out] p_len       Input: length of the input buffer. Output: length of the received data.
 *
 *
 * @retval NRF_SUCCESS             If the data was retrieved and stored successfully.
 * @retval NRF_ERROR_NO_MEM        If the provided buffer was smaller than the received data.
 * @retval NRF_ERROR_NULL          If any of the given pointers is NULL.
 * @retval NRF_ERROR_INVALID_STATE If the given context has not been initialized.
 */
ret_code_t nrf_ble_qwr_value_get(nrf_ble_qwr_t * p_qwr,
                                 uint16_t        attr_handle,
                                 uint8_t       * p_mem,
                                 uint16_t      * p_len);
#endif // (NRF_BLE_QWR_MAX_ATTR > 0)


#ifdef __cplusplus
}
#endif

#endif // NRF_BLE_QUEUED_WRITES_H__

/** @} */
