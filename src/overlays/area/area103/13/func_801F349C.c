#include "area103_13.h"

MATCH void func_801F349C(void) {
    AreaSpinEffect* effect = (AreaSpinEffect*)AREA_WORK;
    u8              i;
    /* FAKE: retail reserves 0x10 frame bytes nothing in the body uses. */
    FAKE_STACK_PADS(u8, 16);

    for (i = 0; i < 3; i++) {
        effect->pos.x  = TASK(Actor)->pos.x.fixed;
        effect->pos.y  = TASK(Actor)->pos.y.fixed;
        effect->pos.z  = TASK(Actor)->pos.z.fixed + 0x03800000;
        effect->angle  = (i << 12) / 3;
        effect->scale  = 0xC00;
        effect->unk_14 = 0;
        effect++;
    }
}
