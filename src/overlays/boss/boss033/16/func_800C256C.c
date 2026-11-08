#include "boss033_16.h"
#include "area/spad.h"

MATCH void func_800C256C(void) {
    D_800C27D0[g_Task->header.step]();
    if (g_Task->header.flags != 0) {
        func_8014D290();
    }
}
