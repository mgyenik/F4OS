#include "types.h"
#include "string.h"
#include "task.h"
#include "semaphore.h"
#include "usart.h"
#include "shell.h"
#include "uname.h"

void uname(int argc, char **argv) {
    if (argc > 1) {
        if (!strncmp(argv[1], "-a", SHELL_ARG_BUF_MAX)) {
            printf("F40S rev %d %s\r\n", BUILD_REV, BUILD_TIME);
        }
        else if (!strncmp(argv[1], "-r", SHELL_ARG_BUF_MAX)) {
            printf("rev %d\r\n", BUILD_REV);
        }
        else {
            printf("%s: unrecognized option '%s'\r\n", argv[0], argv[1]);
        }
    }
    else {
        printf("F4OS\r\n");
    }
}
