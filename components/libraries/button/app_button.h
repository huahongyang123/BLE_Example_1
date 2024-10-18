
#ifndef APP_BUTTON_H__
#define APP_BUTTON_H__

#include <stdint.h>
#include <stdbool.h>
#include "nrf.h"
#include "app_error.h"
#include "nrf_gpio.h"

#ifdef __cplusplus
extern "C" {
#endif

#define APP_BUTTON_PUSH        1                               /**< Indicates that a button is pushed. */
#define APP_BUTTON_RELEASE     0                               /**< Indicates that a button is released. */
#define APP_BUTTON_ACTIVE_HIGH 1                               /**< Indicates that a button is active high. */
#define APP_BUTTON_ACTIVE_LOW  0                               /**< Indicates that a button is active low. */

/**@brief Button event handler type. */
typedef void (*app_button_handler_t)(uint8_t pin_no, uint8_t button_action);

/**@brief Button configuration structure. */
typedef struct
{
    uint8_t              pin_no;           /**< Pin to be used as a button. */
    uint8_t              active_state;     /**< APP_BUTTON_ACTIVE_HIGH or APP_BUTTON_ACTIVE_LOW. */
#if defined(BUTTON_HIGH_ACCURACY_ENABLED) && (BUTTON_HIGH_ACCURACY_ENABLED == 1)
    bool                 hi_accuracy;      /**< True if GPIOTE high accuracy (IN_EVENT) is used. */
#endif
    nrf_gpio_pin_pull_t  pull_cfg;         /**< Pull-up or -down configuration. */
    app_button_handler_t button_handler;   /**< Handler to be called when button is pushed. */
} app_button_cfg_t;

/**@brief Function for initializing the Buttons.
 *
 * @details This function will initialize the specified pins as buttons, and configure the Button
 *          Handler module as a GPIOTE user (but it will not enable button detection).
 *
 * @note app_button_enable() function must be called in order to enable the button detection.
 *
 * @param[in]  p_buttons           Array of buttons to be used (NOTE: Must be static!).
 * @param[in]  button_count        Number of buttons.
 * @param[in]  detection_delay     Delay from a GPIOTE event until a button is reported as pushed.
 *
 * @return   NRF_SUCCESS on success, otherwise an error code.
 */
uint32_t app_button_init(app_button_cfg_t const *       p_buttons,
                         uint8_t                        button_count,
                         uint32_t                       detection_delay);

/**@brief Function for enabling button detection.
 *
 * @retval NRF_SUCCESS Module successfully enabled.
 */
uint32_t app_button_enable(void);

/**@brief Function for disabling button detection.
 *
 * @retval  NRF_SUCCESS               Button detection successfully disabled. Error code otherwise.
 */
uint32_t app_button_disable(void);

/**@brief Function for checking if a button is currently being pushed.
 *
 * @param[in]  button_id     Button index (in the app_button_cfg_t array given to app_button_init) to be checked.
 *
 * @return     Button state.
 */
bool app_button_is_pushed(uint8_t button_id);


#ifdef __cplusplus
}
#endif

#endif // APP_BUTTON_H__

/** @} */
