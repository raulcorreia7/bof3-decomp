#include "area168_13.h"

MATCH void func_801F49D4(void) {
    if (g_UiMessageChoice == 0) {
        g_UiMessageRequest = MSG_AREA168_NAVIGATOR_EXPLAIN;
    } else if (g_UiMessageChoice == 1) {
        g_UiMessageRequest = MSG_AREA168_NAVIGATOR_ALREADY_HAVE;
    } else {
        g_UiMessageRequest = MSG_AREA168_020;
    }
}
