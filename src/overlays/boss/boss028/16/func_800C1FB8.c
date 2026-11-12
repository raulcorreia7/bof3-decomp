#include "boss028_16.h"
#include "area/spad.h"

MATCH void func_800C1FB8(void) {
    D_800C21BC[g_Task->header.step]();
    if (g_Task->header.flags & 0x1) {
        func_8014D290();
    }
}
