/*
 * Copyright (c) 2021-2022 Silicon Laboratories Inc. (www.silabs.com)
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of the Silicon Labs Master Software License
 * Agreement (MSLA) available at [1].  This software is distributed to you in
 * Object Code format and/or Source Code format and is governed by the sections
 * of the MSLA applicable to Object Code, Source Code and Modified Open Source
 * Code. By using this software, you agree to the terms of the MSLA.
 *
 * [1]: https://www.silabs.com/about-us/legal/master-software-license-agreement
 */

/* Interface with stack/source/service_libs/fhss that is now relocated to
 * the device.
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "common/endian.h"
#include "common/log.h"
#include "common/spinel_defs.h"
#include "common/spinel_buffer.h"
#include "common/iobuf.h"
#include "common/version.h"
#include "stack/mac/fhss_config.h"
#include "stack/mac/fhss_api.h"

#include "wsbr.h"
#include "wsbr_mac.h"

#include "wsbr_fhss_net.h"

struct fhss_api *ns_fhss_ws_create(const struct fhss_ws_configuration *config,
                                   const fhss_timer_t *fhss_timer)
{
    struct wsbr_ctxt *ctxt = &g_ctxt;
    struct iobuf_write buf = { };

    // fhss_timer is filled by wsbr_configure(). We know we know we pass -1.
    BUG_ON(fhss_timer != (fhss_timer_t *)-1);
    spinel_push_hdr_set_prop(ctxt, &buf, SPINEL_PROP_WS_FHSS_CREATE);
    spinel_push_u8(&buf, config->ws_uc_channel_function);
    spinel_push_u8(&buf, config->ws_bc_channel_function);
    spinel_push_u16(&buf, config->bsi);
    spinel_push_u8(&buf, config->fhss_uc_dwell_interval);
    spinel_push_u32(&buf, config->fhss_broadcast_interval);
    spinel_push_u8(&buf, config->fhss_bc_dwell_interval);
    spinel_push_u8(&buf, config->unicast_fixed_channel);
    spinel_push_u8(&buf, config->broadcast_fixed_channel);
    spinel_push_fixed_u8_array(&buf, config->domain_channel_mask, 32);
    spinel_push_fixed_u8_array(&buf, config->unicast_channel_mask, 32);
    spinel_push_u16(&buf, config->channel_mask_size);
    spinel_push_u8(&buf, config->config_parameters.number_of_channel_retries);
    if (!version_older_than(ctxt->rcp_version_api, 0, 12, 0))
        spinel_push_fixed_u8_array(&buf, config->broadcast_channel_mask, 32);
    rcp_tx(ctxt, &buf);
    iobuf_free(&buf);
    // Upper layers absolutly want something != NULL
    return FHSS_API_PLACEHOLDER;
}

int ns_fhss_delete(struct fhss_api *fhss_api)
{
    struct wsbr_ctxt *ctxt = &g_ctxt;
    struct iobuf_write buf = { };

    BUG_ON(fhss_api != FHSS_API_PLACEHOLDER);
    spinel_push_hdr_set_prop(ctxt, &buf, SPINEL_PROP_WS_FHSS_DELETE);
    rcp_tx(ctxt, &buf);
    iobuf_free(&buf);
    return 0;
}

int ns_fhss_ws_configuration_set(const struct fhss_api *fhss_api,
                                 const struct fhss_ws_configuration *config)
{
    struct wsbr_ctxt *ctxt = &g_ctxt;
    struct iobuf_write buf = { };

    BUG_ON(fhss_api != FHSS_API_PLACEHOLDER);
    spinel_push_hdr_set_prop(ctxt, &buf, SPINEL_PROP_WS_FHSS_SET_CONF);
    spinel_push_u8(&buf, config->ws_uc_channel_function);
    spinel_push_u8(&buf, config->ws_bc_channel_function);
    spinel_push_u16(&buf, config->bsi);
    spinel_push_u8(&buf, config->fhss_uc_dwell_interval);
    spinel_push_u32(&buf, config->fhss_broadcast_interval);
    spinel_push_u8(&buf, config->fhss_bc_dwell_interval);
    spinel_push_u8(&buf, config->unicast_fixed_channel);
    spinel_push_u8(&buf, config->broadcast_fixed_channel);
    spinel_push_fixed_u8_array(&buf, config->domain_channel_mask, 32);
    spinel_push_fixed_u8_array(&buf, config->unicast_channel_mask, 32);
    spinel_push_u16(&buf, config->channel_mask_size);
    spinel_push_u8(&buf, config->config_parameters.number_of_channel_retries);
    if (!version_older_than(ctxt->rcp_version_api, 0, 18, 0))
        spinel_push_fixed_u8_array(&buf, config->broadcast_channel_mask, 32);
    rcp_tx(ctxt, &buf);
    iobuf_free(&buf);
    return 0;
}

int ns_fhss_ws_set_tx_allowance_level(const fhss_api_t *fhss_api,
                                      const fhss_ws_tx_allow_level_e global_level,
                                      const fhss_ws_tx_allow_level_e ef_level)
{
    struct wsbr_ctxt *ctxt = &g_ctxt;
    struct iobuf_write buf = { };

    BUG_ON(fhss_api != FHSS_API_PLACEHOLDER);
    spinel_push_hdr_set_prop(ctxt, &buf, SPINEL_PROP_WS_FHSS_SET_TX_ALLOWANCE_LEVEL);
    spinel_push_uint(&buf, global_level);
    spinel_push_uint(&buf, ef_level);
    rcp_tx(ctxt, &buf);
    iobuf_free(&buf);
    return 0;
}

int ns_fhss_ws_set_parent(const struct fhss_api *fhss_api, const uint8_t eui64[8],
                          const broadcast_timing_info_t *bc_timing_info, const bool force_synch)
{
    struct wsbr_ctxt *ctxt = &g_ctxt;
    struct iobuf_write buf = { };

    BUG_ON(fhss_api != FHSS_API_PLACEHOLDER);
    spinel_push_hdr_set_prop(ctxt, &buf, SPINEL_PROP_WS_FHSS_SET_PARENT);
    spinel_push_fixed_u8_array(&buf, eui64, 8);
    spinel_push_bool(&buf, force_synch);
    spinel_push_u8(&buf, bc_timing_info->broadcast_channel_function);
    spinel_push_u8(&buf, bc_timing_info->broadcast_dwell_interval);
    spinel_push_u16(&buf, bc_timing_info->fixed_channel);
    spinel_push_u16(&buf, bc_timing_info->broadcast_slot);
    spinel_push_u16(&buf, bc_timing_info->broadcast_schedule_id);
    spinel_push_u32(&buf, bc_timing_info->broadcast_interval_offset);
    spinel_push_u32(&buf, bc_timing_info->broadcast_interval);
    spinel_push_u32(&buf, bc_timing_info->bt_rx_timestamp);
    rcp_tx(ctxt, &buf);
    iobuf_free(&buf);
    return 0;
}
void ns_fhss_ws_update_neighbor(const uint8_t eui64[8],
                                fhss_ws_neighbor_timing_info_t *fhss_data)
{
    struct wsbr_ctxt *ctxt = &g_ctxt;
    struct iobuf_write buf = { };

    spinel_push_hdr_set_prop(ctxt, &buf, SPINEL_PROP_WS_FHSS_UPDATE_NEIGHBOR);
    spinel_push_fixed_u8_array(&buf, eui64, 8);
    spinel_push_u8(&buf, fhss_data->clock_drift);
    spinel_push_u8(&buf, fhss_data->timing_accuracy);
    spinel_push_u16(&buf, fhss_data->uc_channel_list.channel_count);
    spinel_push_fixed_u8_array(&buf, fhss_data->uc_channel_list.channel_mask, 32);
    spinel_push_u8(&buf, fhss_data->uc_timing_info.unicast_channel_function);
    spinel_push_u8(&buf, fhss_data->uc_timing_info.unicast_dwell_interval);
    spinel_push_u16(&buf, fhss_data->uc_timing_info.unicast_number_of_channels);
    spinel_push_u16(&buf, fhss_data->uc_timing_info.fixed_channel);
    spinel_push_u32(&buf, fhss_data->uc_timing_info.ufsi);
    spinel_push_u32(&buf, fhss_data->uc_timing_info.utt_rx_timestamp);
    rcp_tx(ctxt, &buf);
    iobuf_free(&buf);
}

void ns_fhss_ws_drop_neighbor(const uint8_t eui64[8])
{
    struct wsbr_ctxt *ctxt = &g_ctxt;
    struct iobuf_write buf = { };

    spinel_push_hdr_set_prop(ctxt, &buf, SPINEL_PROP_WS_FHSS_DROP_NEIGHBOR);
    spinel_push_fixed_u8_array(&buf, eui64, 8);
    rcp_tx(ctxt, &buf);
    iobuf_free(&buf);
}

