
#ifndef BLE_LINK_CTX_MANAGER_H__
#define BLE_LINK_CTX_MANAGER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "ble_conn_state.h"
#include "sdk_errors.h"


/**@brief Macro for defining a blcm_link_ctx_storage instance.
 *
 * @param[in]   _name            Name of the instance.
 * @param[in]   _max_clients     Maximum number of clients connected at a time.
 * @param[in]   _link_ctx_size   Context size in bytes for a single link.
 */
#define BLE_LINK_CTX_MANAGER_DEF(_name, _max_clients, _link_ctx_size)                               \
    STATIC_ASSERT((_max_clients) <= BLE_CONN_STATE_MAX_CONNECTIONS);                                \
    static uint32_t CONCAT_2(_name, _ctx_data_pool)[(_max_clients)*BYTES_TO_WORDS(_link_ctx_size)]; \
    static blcm_link_ctx_storage_t _name =                                                          \
    {                                                                                               \
        .p_ctx_data_pool = CONCAT_2(_name, _ctx_data_pool),                                         \
        .max_links_cnt   = (_max_clients),                                                          \
        .link_ctx_size   = sizeof(CONCAT_2(_name, _ctx_data_pool))/(_max_clients)                   \
    }


/**
 * @brief Type of description that is used for registry of all current connections.
 */
typedef struct
{
    void   * const p_ctx_data_pool; /**< Pointer to links context memory pool. */
    uint8_t  const max_links_cnt;   /**< Maximum number of concurrent links. */
    uint16_t const link_ctx_size;   /**< Context size in bytes for a single link (word-aligned). */
} blcm_link_ctx_storage_t;


/**
 * @brief Function for getting the link context from the link registry.
 *
 * This function finds the link context in the registry. The link to find is identified by the
 * connection handle within the registry.
 *
 * The context is preserved for the lifetime of the connection. When a new connection occurs, the
 * value of its context is undefined, and should be initialized.
 *
 * @param[in]  p_link_ctx_storage  Pointer to the link storage descriptor.
 * @param[in]  conn_handle         Connection whose context to find.
 * @param[out] pp_ctx_data         Pointer to data with context for the connection.
 *
 * @retval NRF_ERROR_NULL          If \p p_link_ctx_storage is NULL or contains a NULL pointer, or if
 *                                 \p pp_ctx_data is NULL.
 * @retval NRF_ERROR_INVALID_PARAM If \p p_link_ctx_storage::link_ctx_size is not multiple of word
 *                                 size.
 * @retval NRF_ERROR_NOT_FOUND     If \p conn_handle does not refer to an active or recently
 *                                 disconnected link.
 * @retval NRF_ERROR_NO_MEM        If there is not enough memory to store context for the given
 *                                 connection handle. This can happen if the number of links is
 *                                 greater than \p p_link_ctx_storage::max_links_cnt.
 * @retval NRF_SUCCESS             If the operation was successful.
 */
ret_code_t blcm_link_ctx_get(blcm_link_ctx_storage_t const * const p_link_ctx_storage,
                             uint16_t                        const conn_handle,
                             void                         ** const pp_ctx_data);


#ifdef __cplusplus
}
#endif

#endif // BLE_LINK_CTX_MANAGER_H__

