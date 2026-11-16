#include "area168_13.h"

MATCH void func_801F49D4(void) {
    if (g_MessageChoice == 0) {
        g_MessageRequest = MSG_018;
    } else if (g_MessageChoice == 1) {
        g_MessageRequest = MSG_019;
    } else {
        g_MessageRequest = MSG_020;
    }
}
