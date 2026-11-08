#include "boss055_16.h"

MATCH void func_800C20A4(void) {
    D_800C35D8[g_Task->header.step]();
    if (g_Task->header.mode == 8 && g_Task->header.step < 3) {
        func_800C227C();
    }
}
