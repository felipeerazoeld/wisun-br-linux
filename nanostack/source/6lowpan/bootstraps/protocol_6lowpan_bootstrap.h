/*
 * Copyright (c) 2015-2018, Pelion and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * \file protocol_6lowpan_bootstrap.h
 *
 */

#ifndef PROTOCOL_6LOWPAN_BOOTSTRAP_H_
#define PROTOCOL_6LOWPAN_BOOTSTRAP_H_
#include "nanostack/net_interface.h"

struct protocol_interface_info_entry;
struct nd_router;

#define MLE_NEIGHBOR_PURGE_NBR                3
#define MLE_NEIGHBOR_PURGE_TIMER_TIMEOUT      4       // Times advertisement timeout

#define MLE_ROUTER_DEFAULT_LIFETIME           128
#define MLE_ROUTER_HOST_LIFETIME              400

#define MLE_NBR_OF_NEIGHBOR_MAX_LIMIT         0
#define MLE_NBR_OF_NEIGHBOR_LOWER_THRESHOLD   0
#define MLE_NBR_OF_NEIGHBOR_UPPER_THRESHOLD   0
#define MLE_TOKEN_BUCKET_SIZE                 0
#define MLE_TOKEN_BUCKET_RATE                 0
#define MLE_TOKEN_BUCKET_COUNT                0

#define MLE_LINK_REQ_TOKEN_BUCKET_SIZE        3

#define LOWPAN_MAX_FRAME_RETRIES 4

// Waiting Scan confirm from MAC (ms)
#define BOOTSTRAP_SCAN_TIMEOUT  30000
// Waiting Start confirm from MAC (ms)
#define BOOTSTRAP_START_TIMEOUT  10000

typedef struct mle_6lowpan_data {
    uint16_t router_lifetime;               // default lifetime for router neighbor
    uint16_t host_lifetime;                 // default lifetime for host neighbor

    uint16_t nbr_of_neigh_lower_threshold;  // start to limit addition of neighbors to neighbor list
    uint16_t nbr_of_neigh_upper_threshold;  // only priority neighbors are added to neighbor list
    uint16_t nbr_of_neigh_max;              // maximum number of neighbors in neighbor list

    uint8_t token_bucket_size;              // MLE token bucket size
    uint8_t token_bucket_rate;              // Rate in which tokens are added to bucket (0.1 seconds * rate)
    uint8_t token_bucket_count;             // Count of tokens added to bucket at a time

    uint8_t link_req_token_bucket;          // Token bucket for MLE link request with non-valid security counter
} mle_6lowpan_data_t;

void arm_6lowpan_bootstrap_init(struct protocol_interface_info_entry *cur);
uint8_t *protocol_6lowpan_nd_border_router_address_get(nwk_interface_id nwk_id);
uint8_t protocol_6lowpan_rf_link_scalability_from_lqi(uint8_t lqi);
void protocol_6lowpan_bootstrap_re_start(struct protocol_interface_info_entry *interface);
void protocol_6lowpan_link_advertise_handle(struct nd_router *cur, struct protocol_interface_info_entry *cur_interface, uint16_t tick);
void protocol_6lowpan_bootstrap_nd_ready(struct protocol_interface_info_entry *cur_interface);
void protocol_6lowpan_nd_borderrouter_connection_down(struct protocol_interface_info_entry *interface);
int protocol_6lowpan_del_ll16(struct protocol_interface_info_entry *cur, uint16_t mac_short_address);
bool lowpan_neighbour_data_clean(int8_t interface_id, const uint8_t *link_local_address);
void bootstrap_timer_handle(uint16_t ticks);

#endif /* PROTOCOL_6LOWPAN_BOOTSTRAP_H_ */
