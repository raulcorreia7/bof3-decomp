#include "area168_13.h"

MATCH void func_801F49D4(void) {
    if (g_UIMessageChoice == 0) {
        g_UIMessageRequest = MSG_AREA168_NAVIGATOR_EXPLAIN;
    } else if (g_UIMessageChoice == 1) {
        g_UIMessageRequest = MSG_AREA168_NAVIGATOR_ALREADY_HAVE;
    } else {
        g_UIMessageRequest = MSG_AREA168_020;
    }
}
