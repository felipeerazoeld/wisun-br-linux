/*
 * Copyright (c) 2022 Silicon Laboratories Inc. (www.silabs.com)
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
#include <stdarg.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>

#include <ns3/abort.h>

extern "C" {
#include <gcov.h>
#include "app_wsbrd/libwsbrd.h"
#include "common/utils.h"
#include "common/log.h"
}
#include "wsbrd_ns3.hpp"

int g_simulation_id;

void wsbr_ns3_main(const char *config)
{
    const char *config_filename = "/tmp/wsbrd_ns3.conf";
    int config_fd;
    char *argv[6];
    ssize_t size;

    BUG_ON(g_uart_cb.IsNull());
    BUG_ON(g_uart_fd < 0);

    config_fd = open(config_filename, O_WRONLY | O_CREAT | O_TRUNC,
                     S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    FATAL_ON(config_fd < 0, 1, "open %s: %m", config_filename);
    size = write(config_fd, config, strlen(config));
    FATAL_ON(size < 0, 1, "write %s: %m", config_filename);
    if ((size_t)size < strlen(config))
        FATAL(1, "write %s: Short write", config_filename);
    close(config_fd);

    // Cast to non-const, wsbrd is trusted to not modify its arguments
    argv[0] = (char *)"wsbrd";
    argv[1] = (char *)"-F";
    argv[2] = (char *)config_filename;
    argv[3] = (char *)"-u/dev/null"; // Provide a UART devive so parse_commandline succeeds
    argv[4] = (char *)"-D";
    argv[5] = NULL;

    wsbr_main(ARRAY_SIZE(argv) - 1, argv); // Does not return
}

static char last_error[256];
extern "C" void __wrap___tr_printf(const char *color, const char *fmt, ...)
{
    va_list ap;

    // Hack: ERROR, FATAL and BUG pass "31" (red) or "91" (light red) as output
    // color
    if (!strcmp(color, "91") || !strcmp(color, "31")) {
        va_start(ap, fmt);
        vsnprintf(last_error, sizeof(last_error), fmt, ap);
        va_end(ap);
    }
    va_start(ap, fmt);
    __tr_vprintf(color, fmt, ap);
    va_end(ap);
}

extern "C" sighandler_t __wrap_signal(int signum, sighandler_t handler)
{
    errno = ENOSYS;
    return SIG_ERR;
}

// exit() is not thread-safe, so aborting is preferred.
extern "C" void __wrap_exit(int status)
{
    __gcov_dump();
    if (strlen(last_error))
        fprintf(stderr, "\x1b[31mwsbrd: %s\x1b[0m\n", last_error);
    ns3::FatalImpl::FlushStreams();
    std::terminate();
}
