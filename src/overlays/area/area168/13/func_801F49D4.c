#include "area168_13.h"

MATCH void func_801F49D4(void) {
    if (g_MessageChoice == 0) {
        g_MessageRequest = 0x12;
    } else if (g_MessageChoice == 1) {
        g_MessageRequest = 0x13;
    } else {
        g_MessageRequest = 0x14;
    }
}
