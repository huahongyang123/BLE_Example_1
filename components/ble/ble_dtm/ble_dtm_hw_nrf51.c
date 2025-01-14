
#include "ble_dtm_hw.h"
#include "ble_dtm.h"
#include <stdbool.h>
#include <string.h>
#include "nrf.h"


void dtm_turn_off_test()
{
    NRF_RADIO->TEST = 0;
}


void dtm_constant_carrier()
{
    NRF_RADIO->TEST = (RADIO_TEST_PLL_LOCK_Enabled << RADIO_TEST_PLL_LOCK_Pos) |
                      (RADIO_TEST_CONST_CARRIER_Enabled << RADIO_TEST_CONST_CARRIER_Pos);
}


uint32_t dtm_radio_validate(int32_t           m_tx_power, uint8_t           m_radio_mode)
{
    // Handle BLE Radio tuning parameters from production for DTM if required.
    // Only needed for DTM without SoftDevice, as the SoftDevice normally handles this.
    // PCN-083.
    if ( ((NRF_FICR->OVERRIDEEN) & FICR_OVERRIDEEN_BLE_1MBIT_Msk) == FICR_OVERRIDEEN_BLE_1MBIT_Override)
    {
        NRF_RADIO->OVERRIDE0 = NRF_FICR->BLE_1MBIT[0];
        NRF_RADIO->OVERRIDE1 = NRF_FICR->BLE_1MBIT[1];
        NRF_RADIO->OVERRIDE2 = NRF_FICR->BLE_1MBIT[2];
        NRF_RADIO->OVERRIDE3 = NRF_FICR->BLE_1MBIT[3];
        NRF_RADIO->OVERRIDE4 = NRF_FICR->BLE_1MBIT[4];
    }

    // Initializing code below is quite generic - for BLE, the values are fixed, and expressions
    // are constant. Non-constant values are essentially set in radio_prepare().
    if (!(m_tx_power == RADIO_TXPOWER_TXPOWER_0dBm     ||
          m_tx_power == RADIO_TXPOWER_TXPOWER_Pos4dBm  ||
          m_tx_power == RADIO_TXPOWER_TXPOWER_Neg30dBm ||
          m_tx_power == RADIO_TXPOWER_TXPOWER_Neg20dBm ||
          m_tx_power == RADIO_TXPOWER_TXPOWER_Neg16dBm ||
          m_tx_power == RADIO_TXPOWER_TXPOWER_Neg12dBm ||
          m_tx_power == RADIO_TXPOWER_TXPOWER_Neg8dBm  ||
          m_tx_power == RADIO_TXPOWER_TXPOWER_Neg4dBm
        ) ||
        (m_radio_mode > RADIO_MODE_MODE_Ble_1Mbit) // Values 0 - 2: Proprietary mode, 3 (last valid): BLE
       )
    {
        return DTM_ERROR_ILLEGAL_CONFIGURATION;
    }

    return DTM_SUCCESS;
}
