#include "area098_13.h"

MATCH void func_801F3994(void) {
    SpinEffect* spin;
    u8          timer;
    u8          i;

    SELF(Actor)->angle_z += 0xC0000;
    SELF(Actor)->screen_x -= 6;
    GFX_DrawColorFan(&SELF(Actor)->angle_x, (s16)SELF(Actor)->screen_x, 6);
    ACTOR_COUNT_DOWN(SELF(Actor), timer, timer);
    if ((timer & BYTE_MASK) == 0) {
        SELF(Actor)->timer  = 0x20;
        SELF(Actor)->unk_06 = 0;
        SELF(Actor)->header.mode += 1;
        Area_ClearWorkColumn();
        SELF(Actor)->pos.x.fixed = SELF(Actor)->angle_x;
        SELF(Actor)->pos.y.fixed = SELF(Actor)->angle_y;
        SELF(Actor)->pos.z.fixed = SELF(Actor)->angle_z;
        spin                     = MEM_PTR(SpinEffect, AREA_WORK + 0xC0);
        i                        = 0;
        do {
            Area_InitSpin(spin);
            i += 1;
            spin += 1;
        } while ((i & BYTE_MASK) < 0x10U);
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x7));
    }
}
