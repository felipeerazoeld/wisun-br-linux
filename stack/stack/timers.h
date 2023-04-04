#ifndef NS_TIMERS_H
#define NS_TIMERS_H

#include <stdbool.h>

#define TIMER_GLOBAL_PERIOD_MS 50

enum timer_id {
    TIMER_MONOTONIC_TIME,
    TIMER_MPL_FAST,
    TIMER_MPL_SLOW,
    TIMER_RPL_FAST,
    TIMER_RPL_SLOW,
    TIMER_IPV6_DESTINATION,
    TIMER_IPV6_ROUTE,
    TIMER_IPV6_FRAG,
    TIMER_CIPV6_FRAG,
    TIMER_ICMP_FAST,
    TIMER_6LOWPAN_MLD_FAST,
    TIMER_6LOWPAN_MLD_SLOW,
    TIMER_6LOWPAN_ADDR_FAST,
    TIMER_6LOWPAN_ADDR_SLOW,
    TIMER_6LOWPAN_ND,
    TIMER_6LOWPAN_ETX,
    TIMER_6LOWPAN_ADAPTATION,
    TIMER_6LOWPAN_NEIGHBOR,
    TIMER_6LOWPAN_NEIGHBOR_SLOW,
    TIMER_6LOWPAN_NEIGHBOR_FAST,
    TIMER_6LOWPAN_CONTEXT,
    TIMER_6LOWPAN_BOOTSTRAP,
    TIMER_6LOWPAN_REACHABLE_TIME,
    TIMER_WS_COMMON_FAST,
    TIMER_WS_COMMON_SLOW,
    TIMER_PAE_FAST,
    TIMER_PAE_SLOW,
    TIMER_DHCPV6_SOCKET,
#ifdef HAVE_WS_BORDER_ROUTER
    TIMER_LPA,
#endif
    TIMER_COUNT,
};

extern int g_monotonic_time_100ms;

void timer_start(enum timer_id id);
void timer_stop(enum timer_id id);

// FIXME: This API exists only for LPA scheduling.
void timer_start_timeout(enum timer_id id, int timeout);
bool timer_is_running(enum timer_id id);

void timer_global_tick();

#endif
