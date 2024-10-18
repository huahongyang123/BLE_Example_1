
#include "ble_dtm_hw.h"
#include "ble_dtm.h"
#include <stdbool.h>
#include <string.h>
#include "nrf.h"


void dtm_turn_off_test()
{
}


void dtm_constant_carrier()
{
NRF_RADIO->MODECNF0 = (RADIO_MODECNF0_RU_Default << RADIO_MODECNF0_RU_Pos) |
                      (RADIO_MODECNF0_DTX_Center << RADIO_MODECNF0_DTX_Pos);
}


uint32_t dtm_radio_validate(uint32_t m_tx_power, uint8_t m_radio_mode)
{
    // Initializing code below is quite generic - for BLE, the values are fixed, and expressions
    // are constant. Non-constant values are essentially set in radio_prepare().
    if (!(
#if defined(NRF52840_XXAA) || defined(NRF52833_XXAA) || defined(NRF52820_XXAA)
          m_tx_power == RADIO_TXPOWER_TXPOWER_Pos8dBm     ||
          m_tx_power == RADIO_TXPOWER_TXPOWER_Pos7dBm     ||
          m_tx_power == RADIO_TXPOWER_TXPOWER_Pos6dBm     ||
          m_tx_power == RADIO_TXPOWER_TXPOWER_Pos5dBm     ||
#endif //defined(NRF52840_XXAA) || defined(NRF52833_XXAA) || defined(NRF52820_XXAA)
          m_tx_power == RADIO_TXPOWER_TXPOWER_Pos4dBm     ||
          m_tx_power == RADIO_TXPOWER_TXPOWER_Pos3dBm     ||
#if defined(NRF52840_XXAA) || defined(NRF52833_XXAA) || defined(NRF52820_XXAA)
          m_tx_power == RADIO_TXPOWER_TXPOWER_Pos2dBm     ||
#endif //defined(NRF52840_XXAA) || defined(NRF52833_XXAA)A || defined(NRF52820_XXAA)
          m_tx_power == RADIO_TXPOWER_TXPOWER_0dBm        ||
          m_tx_power == RADIO_TXPOWER_TXPOWER_Neg4dBm     ||
          m_tx_power == RADIO_TXPOWER_TXPOWER_Neg8dBm     ||
          m_tx_power == RADIO_TXPOWER_TXPOWER_Neg12dBm    ||
          m_tx_power == RADIO_TXPOWER_TXPOWER_Neg16dBm    ||
          m_tx_power == RADIO_TXPOWER_TXPOWER_Neg20dBm    ||
          m_tx_power == RADIO_TXPOWER_TXPOWER_Neg30dBm    ||
          m_tx_power == RADIO_TXPOWER_TXPOWER_Neg40dBm
          ) ||

         !(
#if defined(NRF52840_XXAA) || defined(NRF52811_XXAA) || defined(NRF52833_XXAA) || defined(NRF52820_XXAA)
           m_radio_mode == RADIO_MODE_MODE_Ble_LR125Kbit  ||
           m_radio_mode == RADIO_MODE_MODE_Ble_LR500Kbit  ||
#endif //defined(NRF52840_XXAA) || defined(NRF52811_XXAA) || defined(NRF52833_XXAA) || defined(NRF52820_XXAA)
           m_radio_mode == RADIO_MODE_MODE_Ble_1Mbit      ||
           m_radio_mode == RADIO_MODE_MODE_Ble_2Mbit
         )
        )
    {
        return DTM_ERROR_ILLEGAL_CONFIGURATION;
    }

    return DTM_SUCCESS;
}
