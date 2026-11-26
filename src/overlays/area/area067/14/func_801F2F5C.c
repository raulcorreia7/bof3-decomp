#include "area067_14.h"

MATCH void func_801F2F5C(void) {
    AreaRippleQuad* quad;
    s16*            row;
    u8              timer;

    quad               = (AreaRippleQuad*)&SELF(Actor)->vx;
    timer              = SELF(Actor)->timer + 1;
    SELF(Actor)->timer = timer;
    quad->height += 64;
    quad->angle += 2;
    if (timer == 15) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 2));
    }
    func_801F358C(quad);
    /* kept: the group header types the family's three-argument form, so this image's no-argument step keeps the cast. */
    ((void (*)(void))func_801F39D8)();
    func_801F3AD8(quad);
    if ((g_FrameCount & 1) != 0) {
        row = func_801F3A9C();
        if (row != NULL) {
            func_801F3D54(row);
        }
    }
    if ((s16)quad->angle >= 0x101) {
        SELF(Actor)->timer = 7;
        SELF(Actor)->header.mode++;
    }
}
