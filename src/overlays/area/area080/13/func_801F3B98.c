#include "area080_13.h"

MATCH void* func_801F3B98(void) {
    u8 i;

    D_801F44A4 = g_AreaSparks;
    i          = 0u;
    do {
        if (D_801F44A4->active != 0u) {
            D_801F44A4++;
            i += 1u;
        } else {
            return D_801F44A4;
        }
    } while (i < AREA_SPARK_SLOT_COUNT);

    return 0;
}
