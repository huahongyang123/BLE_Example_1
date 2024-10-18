
#ifndef NRF_DRV_GPIOTE_H__
#define NRF_DRV_GPIOTE_H__

#include <nrfx_gpiote.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup nrf_drv_gpiote GPIOTE driver - legacy layer
 * @{
 * @ingroup nrf_gpiote
 * @brief Layer providing compatibility with the former API.
 */

/** @brief Type definition for forwarding the new implementation. */
typedef nrfx_gpiote_in_config_t nrf_drv_gpiote_in_config_t;
/** @brief Type definition for forwarding the new implementation. */
typedef nrfx_gpiote_pin_t nrf_drv_gpiote_pin_t;
/** @brief Type definition for forwarding the new implementation. */
typedef nrfx_gpiote_out_config_t nrf_drv_gpiote_out_config_t;
/** @brief Type definition for forwarding the new implementation. */
typedef nrfx_gpiote_evt_handler_t nrf_drv_gpiote_evt_handler_t;

/** @brief Macro for forwarding the new implementation. */
#define GPIOTE_CONFIG_IN_SENSE_LOTOHI     NRFX_GPIOTE_CONFIG_IN_SENSE_LOTOHI
/** @brief Macro for forwarding the new implementation. */
#define GPIOTE_CONFIG_IN_SENSE_HITOLO     NRFX_GPIOTE_CONFIG_IN_SENSE_HITOLO
/** @brief Macro for forwarding the new implementation. */
#define GPIOTE_CONFIG_IN_SENSE_TOGGLE     NRFX_GPIOTE_CONFIG_IN_SENSE_TOGGLE
/** @brief Macro for forwarding the new implementation. */
#define GPIOTE_RAW_CONFIG_IN_SENSE_LOTOHI NRFX_GPIOTE_RAW_CONFIG_IN_SENSE_LOTOHI
/** @brief Macro for forwarding the new implementation. */
#define GPIOTE_RAW_CONFIG_IN_SENSE_HITOLO NRFX_GPIOTE_RAW_CONFIG_IN_SENSE_HITOLO
/** @brief Macro for forwarding the new implementation. */
#define GPIOTE_RAW_CONFIG_IN_SENSE_TOGGLE NRFX_GPIOTE_RAW_CONFIG_IN_SENSE_TOGGLE
/** @brief Macro for forwarding the new implementation. */
#define GPIOTE_CONFIG_OUT_SIMPLE          NRFX_GPIOTE_CONFIG_OUT_SIMPLE
/** @brief Macro for forwarding the new implementation. */
#define GPIOTE_CONFIG_OUT_TASK_LOW        NRFX_GPIOTE_CONFIG_OUT_TASK_LOW
/** @brief Macro for forwarding the new implementation. */
#define GPIOTE_CONFIG_OUT_TASK_HIGH       NRFX_GPIOTE_CONFIG_OUT_TASK_HIGH
/** @brief Macro for forwarding the new implementation. */
#define GPIOTE_CONFIG_OUT_TASK_TOGGLE     NRFX_GPIOTE_CONFIG_OUT_TASK_TOGGLE

/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_gpiote_init               nrfx_gpiote_init
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_gpiote_is_init            nrfx_gpiote_is_init
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_gpiote_uninit             nrfx_gpiote_uninit
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_gpiote_out_init           nrfx_gpiote_out_init
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_gpiote_out_uninit         nrfx_gpiote_out_uninit
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_gpiote_out_set            nrfx_gpiote_out_set
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_gpiote_out_clear          nrfx_gpiote_out_clear
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_gpiote_out_toggle         nrfx_gpiote_out_toggle
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_gpiote_out_task_enable    nrfx_gpiote_out_task_enable
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_gpiote_out_task_disable   nrfx_gpiote_out_task_disable
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_gpiote_out_task_addr_get  nrfx_gpiote_out_task_addr_get
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_gpiote_in_init            nrfx_gpiote_in_init
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_gpiote_in_uninit          nrfx_gpiote_in_uninit
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_gpiote_in_event_enable    nrfx_gpiote_in_event_enable
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_gpiote_in_event_disable   nrfx_gpiote_in_event_disable
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_gpiote_in_is_set          nrfx_gpiote_in_is_set
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_gpiote_in_event_addr_get  nrfx_gpiote_in_event_addr_get
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_gpiote_set_task_addr_get  nrfx_gpiote_set_task_addr_get
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_gpiote_clr_task_addr_get  nrfx_gpiote_clr_task_addr_get
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_gpiote_out_task_force     nrfx_gpiote_out_task_force
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_gpiote_out_task_trigger   nrfx_gpiote_out_task_trigger
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_gpiote_set_task_trigger   nrfx_gpiote_set_task_trigger
/** @brief Macro for forwarding the new implementation. */
#define nrf_drv_gpiote_clr_task_trigger   nrfx_gpiote_clr_task_trigger

/** @} */

#ifdef __cplusplus
}
#endif

#endif //NRF_DRV_GPIOTE_H__
