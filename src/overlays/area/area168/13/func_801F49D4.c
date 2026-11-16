#include "area168_13.h"

MATCH void func_801F49D4(void) {
    if (g_MessageChoice == 0) {
        g_MessageRequest = AREA168_MSG_NAVIGATOR_EXPLAIN;
    } else if (g_MessageChoice == 1) {
        g_MessageRequest = AREA168_MSG_NAVIGATOR_OWNED;
    } else {
        g_MessageRequest = AREA168_MSG_NAVIGATOR_DECLINED;
    }
}
