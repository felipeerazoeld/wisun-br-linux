SRCS += \
	source/6lowpan/adaptation_interface.c \
	source/6lowpan/Bootstraps/Generic/network_lib.c \
	source/6lowpan/Bootstraps/Generic/protocol_6lowpan.c \
	source/6lowpan/Bootstraps/Generic/protocol_6lowpan_bootstrap.c \
	source/6lowpan/Bootstraps/Generic/protocol_6lowpan_interface.c \
	source/6lowpan/Fragmentation/cipv6_fragmenter.c \
	source/6lowpan/IPHC_Decode/6lowpan_iphc.c \
	source/6lowpan/IPHC_Decode/iphc_compress.c \
	source/6lowpan/IPHC_Decode/iphc_decompress.c \
	source/6lowpan/IPHC_Decode/lowpan_context.c \
	source/6lowpan/MAC/beacon_handler.c \
	source/6lowpan/MAC/mac_helper.c \
	source/6lowpan/MAC/mac_ie_lib.c \
	source/6lowpan/MAC/mac_response_handler.c \
	source/6lowpan/MAC/mac_data_poll.c \
	source/6lowpan/MAC/mac_pairwise_key.c \
	source/6lowpan/Mesh/mesh.c \
	source/6lowpan/ND/nd_router_object.c \
	source/6lowpan/NVM/nwk_nvm.c \
	source/6lowpan/ws/ws_ie_lib.c \
	source/6lowpan/ws/ws_llc_data_service.c \
	source/6lowpan/ws/ws_mpx_header.c \
	source/6lowpan/ws/ws_neighbor_class.c \
	source/6lowpan/ws/ws_bootstrap.c \
	source/6lowpan/ws/ws_bootstrap_6lbr.c \
	source/6lowpan/ws/ws_bootstrap_ffn.c \
	source/6lowpan/ws/ws_bootstrap_lfn.c \
	source/6lowpan/ws/ws_common.c \
	source/6lowpan/ws/ws_management_api.c \
	source/6lowpan/ws/ws_bbr_api.c \
	source/6lowpan/ws/ws_test_api.c \
	source/6lowpan/ws/ws_empty_functions.c \
	source/6lowpan/ws/ws_pae_controller.c \
	source/6lowpan/ws/ws_pae_supp.c \
	source/6lowpan/ws/ws_pae_auth.c \
	source/6lowpan/ws/ws_pae_lib.c \
	source/6lowpan/ws/ws_pae_nvm_data.c \
	source/6lowpan/ws/ws_pae_nvm_store.c \
	source/6lowpan/ws/ws_pae_time.c \
	source/6lowpan/ws/ws_pae_timers.c \
	source/6lowpan/ws/ws_pae_key_storage.c \
	source/6lowpan/ws/ws_eapol_relay.c \
	source/6lowpan/ws/ws_eapol_auth_relay.c \
	source/6lowpan/ws/ws_eapol_relay_lib.c \
	source/6lowpan/ws/ws_eapol_pdu.c \
	source/6lowpan/ws/ws_stats.c \
	source/6lowpan/ws/ws_cfg_settings.c \
	source/6lowpan/ws/ws_phy.c \
	source/border_router/border_router.c \
	source/common_protocols/icmpv6.c \
	source/common_protocols/icmpv6_prefix.c \
	source/common_protocols/icmpv6_radv.c \
	source/common_protocols/ipv6.c \
	source/common_protocols/ipv6_resolution.c \
	source/common_protocols/ipv6_fragmentation.c \
	source/common_protocols/ipv6_flow.c \
	source/common_protocols/mld.c \
	source/common_protocols/tcp.c \
	source/common_protocols/udp.c \
	source/core/ns_address_internal.c \
	source/core/ns_monitor.c \
	source/core/buffer_dyn.c \
	source/core/sockbuf.c \
	source/core/ns_socket.c \
	source/ipv6_stack/ipv6_routing_table.c \
	source/ipv6_stack/protocol_ipv6.c \
	source/libNET/src/net_6lowpan_parameter_api.c \
	source/libNET/src/net_ipv6.c \
	source/libNET/src/net_test.c \
	source/libNET/src/net_mle.c \
	source/libNET/src/net_rpl.c \
	source/libNET/src/net_load_balance.c \
	source/libNET/src/net_dns.c \
	source/libNET/src/ns_net.c \
	source/libNET/src/socket_api.c \
	source/libNET/src/multicast_api.c \
	source/mac/rf_driver_storage.c \
	source/mac/IEEE802_15_4/mac_header_helper_functions.c \
	source/mac/IEEE802_15_4/mac_indirect_data.c \
	source/mac/IEEE802_15_4/mac_mcps_sap.c \
	source/mac/IEEE802_15_4/mac_mlme.c \
	source/mac/IEEE802_15_4/mac_filter.c \
	source/mac/IEEE802_15_4/mac_pd_sap.c \
	source/mac/IEEE802_15_4/mac_security_mib.c \
	source/mac/IEEE802_15_4/mac_timer.c \
	source/mac/IEEE802_15_4/sw_mac.c \
	source/mac/IEEE802_15_4/mac_fhss_callbacks.c \
	source/mac/IEEE802_15_4/mac_cca_threshold.c \
	source/mac/IEEE802_15_4/mac_mode_switch.c \
	source/mac/ethernet/ethernet_mac_api.c \
	source/mac/serial/serial_mac_api.c \
	source/mac/virtual_rf/virtual_rf_client.c \
	source/mac/virtual_rf/virtual_rf_driver.c \
	source/mle/mle.c \
	source/mle/mle_tlv.c \
	source/mpl/mpl.c \
	source/nwk_interface/protocol_core.c \
	source/nwk_interface/protocol_core_sleep.c \
	source/nwk_interface/protocol_stats.c \
	source/nwk_interface/protocol_timer.c \
	source/RPL/rpl_control.c \
	source/RPL/rpl_data.c \
	source/RPL/rpl_upward.c \
	source/RPL/rpl_downward.c \
	source/RPL/rpl_objective.c \
	source/RPL/rpl_of0.c \
	source/RPL/rpl_mrhof.c \
	source/RPL/rpl_policy.c \
	source/security/Common/security_lib.c \
	source/security/eapol/eapol_helper.c \
	source/security/eapol/kde_helper.c \
	source/security/kmp/kmp_api.c \
	source/security/kmp/kmp_addr.c \
	source/security/kmp/kmp_eapol_pdu_if.c \
	source/security/kmp/kmp_socket_if.c \
	source/security/protocols/sec_prot_lib.c \
	source/security/protocols/sec_prot_keys.c \
	source/security/protocols/sec_prot_certs.c \
	source/security/protocols/key_sec_prot/key_sec_prot.c \
	source/security/protocols/eap_tls_sec_prot/auth_eap_tls_sec_prot.c \
	source/security/protocols/eap_tls_sec_prot/radius_eap_tls_sec_prot.c \
	source/security/protocols/eap_tls_sec_prot/supp_eap_tls_sec_prot.c \
	source/security/protocols/eap_tls_sec_prot/eap_tls_sec_prot_lib.c \
	source/security/protocols/fwh_sec_prot/auth_fwh_sec_prot.c \
	source/security/protocols/fwh_sec_prot/supp_fwh_sec_prot.c \
	source/security/protocols/gkh_sec_prot/auth_gkh_sec_prot.c \
	source/security/protocols/gkh_sec_prot/supp_gkh_sec_prot.c \
	source/security/protocols/radius_sec_prot/radius_client_sec_prot.c \
	source/security/protocols/radius_sec_prot/avp_helper.c \
	source/security/protocols/msg_sec_prot/msg_sec_prot.c \
	source/security/protocols/tls_sec_prot/tls_sec_prot.c \
	source/security/protocols/tls_sec_prot/tls_sec_prot_lib.c \
	source/security/PANA/eap_protocol.c \
	source/security/PANA/pana.c \
	source/security/PANA/pana_avp.c \
	source/security/PANA/pana_client.c \
	source/security/PANA/pana_eap_header.c \
	source/security/PANA/pana_header.c \
	source/security/PANA/pana_server.c \
	source/security/TLS/tls_lib.c \
	source/security/TLS/tls_ccm_crypt.c \
	source/service_libs/CCM_lib/ccm_security.c \
	source/service_libs/fhss/fhss_channel.c \
	source/service_libs/fhss/fhss_configuration_interface.c \
	source/service_libs/fhss/fhss_statistics.c \
	source/service_libs/fhss/fhss.c \
	source/service_libs/fhss/fhss_ws.c \
	source/service_libs/fhss/fhss_ws_empty_functions.c \
	source/service_libs/fhss/fhss_common.c \
	source/service_libs/fhss/channel_functions.c \
	source/service_libs/fhss/channel_list.c \
	source/service_libs/fhss/fhss_test_api.c \
	source/service_libs/fnv_hash/fnv_hash.c \
	source/service_libs/hmac/hmac_md.c \
	source/service_libs/ieee_802_11/ieee_802_11.c \
	source/service_libs/nist_aes_kw/nist_aes_kw.c \
	source/service_libs/mac_neighbor_table/mac_neighbor_table.c \
	source/service_libs/mle_service/mle_service.c \
	source/service_libs/mle_service/mle_service_buffer.c \
	source/service_libs/mle_service/mle_service_frame_counter_table.c \
	source/service_libs/mle_service/mle_service_interface.c \
	source/service_libs/mle_service/mle_service_security.c \
	source/service_libs/blacklist/blacklist.c \
	source/service_libs/etx/etx.c \
	source/service_libs/Neighbor_cache/neighbor_cache.c \
	source/service_libs/nd_proxy/nd_proxy.c \
	source/service_libs/load_balance/load_balance.c \
	source/service_libs/SHA256_Lib/shalib.c \
	source/service_libs/SHA256_Lib/ns_sha256.c \
	source/service_libs/Trickle/trickle.c \
	source/service_libs/whiteboard/whiteboard.c \
	source/service_libs/pan_blacklist/pan_blacklist.c \
	source/service_libs/random_early_detection/random_early_detection.c \
	source/6lowpan/Thread/thread_management_if.c \
	source/6lowpan/Thread/thread_management_api.c \
	source/6lowpan/Thread/thread_commissioning_api.c \
	source/6lowpan/Thread/thread_border_router_api.c \
	source/6lowpan/Thread/thread_bbr_api.c \
	source/6lowpan/Thread/thread_test_api.c \
	source/6lowpan/Thread/thread_meshcop_lib.c \
	source/6lowpan/Thread/thread_common.c \
	source/6lowpan/Thread/thread_joiner_application.c \
	source/6lowpan/Thread/thread_leader_service.c \
	source/6lowpan/Thread/thread_neighbor_class.c \
	source/6lowpan/Thread/thread_management_server.c \
	source/6lowpan/Thread/thread_management_client.c \
	source/6lowpan/Thread/thread_network_synch.c \
	source/6lowpan/Thread/thread_bootstrap.c \
	source/6lowpan/Thread/thread_dhcpv6_server.c \
	source/6lowpan/Thread/thread_host_bootstrap.c \
	source/6lowpan/Thread/thread_router_bootstrap.c \
	source/6lowpan/Thread/thread_discovery.c \
	source/6lowpan/Thread/thread_commissioning_if.c \
	source/6lowpan/Thread/thread_bbr_commercial.c \
	source/6lowpan/Thread/thread_net_config_api.c \
	source/6lowpan/Thread/thread_network_data_lib.c \
	source/6lowpan/Thread/thread_network_data_storage.c \
	source/6lowpan/Thread/thread_nd.c \
	source/6lowpan/Thread/thread_diagnostic.c \
	source/6lowpan/Thread/thread_resolution_client.c \
	source/6lowpan/Thread/thread_resolution_server.c \
	source/6lowpan/Thread/thread_routing.c \
	source/6lowpan/Thread/thread_mdns.c \
	source/6lowpan/Thread/thread_beacon.c \
	source/6lowpan/Thread/thread_mle_message_handler.c \
	source/6lowpan/Thread/thread_lowpower_api.c \
	source/6lowpan/Thread/thread_lowpower_private_api.c \
	source/6lowpan/Thread/thread_nvm_store.c \
	source/6lowpan/Thread/thread_ccm.c \
	source/dhcpv6_server/dhcpv6_server_service.c \
	source/dhcpv6_client/dhcpv6_client_service.c \
	source/libdhcpv6/dhcp_service_api.c \
	source/libdhcpv6/libdhcpv6.c \
	source/libdhcpv6/libdhcpv6_vendordata.c \
	source/libdhcpv6/libdhcpv6_server.c \
	source/service_libs/utils/ns_crc.c \
	source/service_libs/utils/isqrt.c \
	source/service_libs/utils/ns_file_system.c \
	source/service_libs/utils/ns_time.c \
	source/service_libs/utils/ns_conf.c \
	source/service_libs/mdns/ns_mdns_api.c \
	source/service_libs/mdns/ns_fnet_port.c \
	source/service_libs/mdns/ns_fnet_events.c \
	source/service_libs/mdns/fnet/fnet_stack/services/mdns/fnet_mdns.c \
	source/service_libs/mdns/fnet/fnet_stack/services/poll/fnet_poll.c \
	source/service_libs/mdns/fnet/fnet_stack/stack/fnet_stdlib.c \
	source/service_libs/CCM_lib/mbedOS/aes_mbedtls_adapter.c \


#LAST ONE(S) EXPERIMENTAL (aes_mbedtls_adapter.c last real)

