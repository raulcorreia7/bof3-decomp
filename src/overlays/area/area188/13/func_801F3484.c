#include "area188_13.h"

MATCH void func_801F3484(void) {
    SpinEffect* spin;
    u8          timer;
    u8          i;

    TASK(Actor)->angle_z += 0xC0000;
    TASK(Actor)->screen_x -= 6;
    GFX_DrawColorFan(&TASK(Actor)->angle_x, (s16)TASK(Actor)->screen_x, 6);
    ACTOR_COUNT_DOWN(TASK(Actor), timer, timer);
    if ((timer & BYTE_MASK) == 0) {
        TASK(Actor)->timer  = 0x20;
        TASK(Actor)->unk_06 = 0;
        TASK(Actor)->header.mode += 1;
        Area_ClearWorkColumn();
        TASK(Actor)->pos.x.fixed = TASK(Actor)->angle_x;
        TASK(Actor)->pos.y.fixed = TASK(Actor)->angle_y;
        TASK(Actor)->pos.z.fixed = TASK(Actor)->angle_z;
        spin                     = MEM_PTR(SpinEffect, AREA_WORK + 0xC0);
        i                        = 0;
        do {
            Area_InitSpin(spin);
            i += 1;
            spin += 1;
        } while ((i & BYTE_MASK) < 0x10U);
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x15));
    }
}
