#include "boss034_16.h"

MATCH void func_800C1940(void) {
    if (func_8014D978() != 0) {
        g_Task->unk_09 = 0x40;
        g_Task->timer  = 0x20;
        g_Task->unk_03 = 1;
    }
}
