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
#include "stack/mac/mac_mcps.h"
#include "stack/source/6lowpan/ws/ws_bootstrap.h"
#include "stack/source/6lowpan/ws/ws_common.h"
#include "stack/source/6lowpan/ws/ws_common_defines.h"
#include "stack/source/6lowpan/ws/ws_mngt.h"
#include "stack/source/6lowpan/ws/ws_ie_lib.h"
#include "stack/source/6lowpan/ws/ws_llc.h"
#include "stack/source/nwk_interface/protocol.h"
#include "common/log.h"
#include "common/trickle.h"

static bool ws_mngt_ie_utt_validate(const struct mcps_data_ie_list *ie_ext,
                                    struct ws_utt_ie *ie_utt,
                                    const char *dbgstr)
{
    if (!ws_wh_utt_read(ie_ext->headerIeList, ie_ext->headerIeListLength, ie_utt)) {
        ERROR("Missing UTT-IE in %s", dbgstr);
        return false;
    }
    return true;
}

static bool ws_mngt_ie_us_validate(struct net_if *net_if,
                                   const struct mcps_data_ie_list *ie_ext,
                                   struct ws_us_ie *ie_us,
                                   const char *dbgstr)
{
    // FIXME: see comment in ws_llc_asynch_indication
    if (!ws_wp_nested_us_read(ie_ext->payloadIeList, ie_ext->payloadIeListLength, ie_us)) {
        ERROR("Missing US-IE in %s", dbgstr);
        return false;
    }
    if (!ws_bootstrap_validate_channel_plan(ie_us, NULL, net_if))
        return false;
    if (!ws_bootstrap_validate_channel_function(ie_us, NULL))
        return false;
    return true;
}

void ws_mngt_pa_analyze(struct net_if *net_if,
                        const struct mcps_data_ind *data,
                        const struct mcps_data_ie_list *ie_ext)
{
    ws_pan_information_t pan_information;
    ws_utt_ie_t ie_utt;
    ws_us_ie_t ie_us;

    if (!ws_mngt_ie_utt_validate(ie_ext, &ie_utt, "PAN Advertisement"))
        return;
    if (!ws_mngt_ie_us_validate(net_if, ie_ext, &ie_us, "PAN Advertisement"))
        return;
    // FIXME: see comment in ws_llc_asynch_indication
    if (!ws_wp_nested_pan_read(ie_ext->payloadIeList, ie_ext->payloadIeListLength, &pan_information)) {
        ERROR("Missing PAN-IE in PAN Advertisement");
        return;
    }

    if (data->SrcPANId != net_if->ws_info->network_pan_id)
        return;

    // Border router routing cost is 0, so "Routing Cost the same or worse" is
    // always true
    if (pan_information.routing_cost != 0xFFFF)
        trickle_consistent_heard(&net_if->ws_info->trickle_pan_advertisement);
}

void ws_mngt_pas_analyze(struct net_if *net_if,
                         const struct mcps_data_ind *data,
                         const struct mcps_data_ie_list *ie_ext)
{
    ws_utt_ie_t ie_utt;
    ws_us_ie_t ie_us;

    if (!ws_mngt_ie_utt_validate(ie_ext, &ie_utt, "PAN Advertisement Solicit"))
        return;
    if (!ws_mngt_ie_us_validate(net_if, ie_ext, &ie_us, "PAN Advertisement Solicit"))
        return;

    trickle_inconsistent_heard(&net_if->ws_info->trickle_pan_advertisement,
                               &net_if->ws_info->trickle_params_pan_discovery);
}

void ws_mngt_pc_analyze(struct net_if *net_if,
                        const struct mcps_data_ind *data,
                        const struct mcps_data_ie_list *ie_ext)
{
    llc_neighbour_req_t neighbor_info;
    uint16_t ws_pan_version;
    ws_utt_ie_t ie_utt;
    ws_bt_ie_t ie_bt;
    ws_us_ie_t ie_us;
    ws_bs_ie_t ie_bs;

    if (!ws_mngt_ie_utt_validate(ie_ext, &ie_utt, "PAN Configuration"))
        return;
    if (!ws_wh_bt_read(ie_ext->headerIeList, ie_ext->headerIeListLength, &ie_bt)) {
        ERROR("Missing BT-IE in PAN Configuration");
        return;
    }
    if (!ws_mngt_ie_us_validate(net_if, ie_ext, &ie_us, "PAN Configuration"))
        return;
    // FIXME: see comment in ws_llc_asynch_indication
    if (!ws_wp_nested_bs_read(ie_ext->payloadIeList, ie_ext->payloadIeListLength, &ie_bs)) {
        ERROR("Missing BS-IE in PAN Configuration");
        return;
    }
    // FIXME: see comment in ws_llc_asynch_indication
    if (!ws_wp_nested_panver_read(ie_ext->payloadIeList, ie_ext->payloadIeListLength, &ws_pan_version)) {
        ERROR("Missing PANVER-IE in PAN configuration");
        return;
    }

    if (data->SrcPANId != net_if->ws_info->network_pan_id)
        return;

    if (net_if->ws_info->pan_information.pan_version == ws_pan_version)
        trickle_consistent_heard(&net_if->ws_info->trickle_pan_config);
    else
        trickle_inconsistent_heard(&net_if->ws_info->trickle_pan_config,
                                   &net_if->ws_info->trickle_params_pan_discovery);

    if (ws_bootstrap_neighbor_info_request(net_if, data->SrcAddr, &neighbor_info, false)) {
        ws_neighbor_class_neighbor_unicast_time_info_update(neighbor_info.ws_neighbor, &ie_utt, data->timestamp, data->SrcAddr);
        ws_neighbor_class_neighbor_unicast_schedule_set(net_if, neighbor_info.ws_neighbor, &ie_us, data->SrcAddr);
        ws_neighbor_class_neighbor_broadcast_time_info_update(neighbor_info.ws_neighbor, &ie_bt, data->timestamp);
        ws_neighbor_class_neighbor_broadcast_schedule_set(net_if, neighbor_info.ws_neighbor, &ie_bs);
    }
}

void ws_mngt_pcs_analyze(struct net_if *net_if,
                         const struct mcps_data_ind *data,
                         const struct mcps_data_ie_list *ie_ext)
{
    llc_neighbour_req_t neighbor_info;
    ws_utt_ie_t ie_utt;
    ws_us_ie_t ie_us;

    if (!ws_mngt_ie_utt_validate(ie_ext, &ie_utt, "PAN Configuration Solicit"))
        return;
    if (!ws_mngt_ie_us_validate(net_if, ie_ext, &ie_us, "PAN Configuration Solicit"))
        return;

    if (data->SrcPANId != net_if->ws_info->network_pan_id)
        return;

    trickle_inconsistent_heard(&net_if->ws_info->trickle_pan_config,
                               &net_if->ws_info->trickle_params_pan_discovery);

    if (ws_bootstrap_neighbor_info_request(net_if, data->SrcAddr, &neighbor_info, false)) {
        ws_neighbor_class_neighbor_unicast_time_info_update(neighbor_info.ws_neighbor, &ie_utt, data->timestamp, data->SrcAddr);
        ws_neighbor_class_neighbor_unicast_schedule_set(net_if, neighbor_info.ws_neighbor, &ie_us, data->SrcAddr);
    }
}