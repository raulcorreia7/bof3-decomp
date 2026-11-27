#include "area199_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F36DC(void) {
    s32 draw_radius;
    s32 draw_shade;
    s32 radius;
    s32 shade;
    s32 size;
    s32 x;

    GFX_ADD_DITHERED_DRAW_MODE(4, getTPage(1, 1, 320, 256));

    if (SELF(Actor)->timer < 0xFF) {
        SELF(Actor)->timer++;
    }

    if (SELF(Actor)->timer < 0x15) {
        radius = 0x20;
    } else {
        radius = (SELF(Actor)->timer - 0x14) * 20 + 0x20;
    }
    draw_radius = radius < 0x1F5 ? radius : 0x1F4;
    if (SELF(Actor)->timer < 0x15) {
        shade = 0x80;
    } else {
        shade = (SELF(Actor)->timer - 0x14) * 12 + 0x80;
    }
    draw_shade = shade < 0x100 ? shade : 0xFF;
    func_801F3EA0(0x82, SELF(Actor)->timer + 0xA, draw_radius, draw_shade);

    shade = SELF(Actor)->timer * 12;
    size  = shade < 0x31 ? shade : 0x30;

    x = 0x82 + rsin(0x100) * (0x10E - SELF(Actor)->timer * 9) / ONE;
    func_801F3AB0(x, SELF(Actor)->timer + 0xA + rcos(0x100) * (0x10E - SELF(Actor)->timer * 9) / ONE, 0x40, size);
    x = 0x82 + rsin(0x100) * (0xF0 - SELF(Actor)->timer * 8) / ONE;
    func_801F3AB0(x, SELF(Actor)->timer + 0xA + rcos(0x100) * (0xF0 - SELF(Actor)->timer * 8) / ONE, 0x20, size);
    x = 0x82 + rsin(0x100) * (0xB4 - SELF(Actor)->timer * 6) / ONE;
    func_801F3AB0(x, SELF(Actor)->timer + 0xA + rcos(0x100) * (0xB4 - SELF(Actor)->timer * 6) / ONE, 8, size);
    x = 0x82 + rsin(0x100) * (0x78 - SELF(Actor)->timer * 4) / ONE;
    func_801F3AB0(x, SELF(Actor)->timer + 0xA + rcos(0x100) * (0x78 - SELF(Actor)->timer * 4) / ONE, 0x10, size);
}
#else
INCLUDE_ASM(func_801F36DC);
#endif
