
#include "ble_link_ctx_manager.h"
#include "sdk_common.h"


ret_code_t blcm_link_ctx_get(blcm_link_ctx_storage_t const * const p_link_ctx_storage,
                             uint16_t                        const conn_handle,
                             void                         ** const pp_ctx_data)
{
    uint8_t conn_id;

    if (pp_ctx_data == NULL)
    {
        return NRF_ERROR_NULL;
    }
    else
    {
        *pp_ctx_data = NULL;
    }

    VERIFY_PARAM_NOT_NULL(p_link_ctx_storage);
    VERIFY_PARAM_NOT_NULL(p_link_ctx_storage->p_ctx_data_pool);
    VERIFY_TRUE((p_link_ctx_storage->link_ctx_size % BYTES_PER_WORD) == 0, NRF_ERROR_INVALID_PARAM);

    conn_id = ble_conn_state_conn_idx(conn_handle);

    if (conn_id == BLE_CONN_STATE_MAX_CONNECTIONS)
    {
        return NRF_ERROR_NOT_FOUND;
    }

    if (conn_id >= p_link_ctx_storage->max_links_cnt)
    {
        return NRF_ERROR_NO_MEM;
    }

    *pp_ctx_data = (void *) ((uint8_t *) p_link_ctx_storage->p_ctx_data_pool + 
                             conn_id * p_link_ctx_storage->link_ctx_size);
    return NRF_SUCCESS;
}

