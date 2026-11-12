#include "area080_13.h"

MATCH void func_801F3870(void) {
    u8  index;
    s16 height;
    /* FAKE: unused frame, 16 bytes. */
    FAKE_STACK_PADS(u8, 16);

    D_801F44A4 = g_AreaSparks;
    index      = 0u;
    do {
        if (D_801F44A4->active) {
            D_801F44A4->pos.x.fixed += D_801F44A4->velocity_x;
            D_801F44A4->pos.y.fixed += D_801F44A4->velocity_y;
            height                  = Area_SampleHeight(D_801F44A4->pos.x.fixed, D_801F44A4->pos.y.fixed);
            D_801F44A4->pos.z.fixed = TO_COORD(height);
            func_801F352C(D_801F44A4);
            if (--D_801F44A4->life == 0) {
                D_801F44A4->active = 0;
            }
        }
        index += 1;
        D_801F44A4++;
    } while ((index & BYTE_MASK) < AREA_SPARK_SLOT_COUNT);
}
