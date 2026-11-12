#include "area080_13.h"

MATCH void func_801F3834(void) {
    s32 index;

    D_801F44A4 = g_AreaSparks;
    index      = 0;
    do {
        index += 1;
        D_801F44A4->active = 0;
    } while ((index & BYTE_MASK) < AREA_SPARK_SLOT_COUNT);
}
