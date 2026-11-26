#include "area199_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F36DC(void) {
    s32 radius;
    s32 draw_radius;
    s32 shade;
    s32 draw_shade;
    s32 x;

    GFX_ADD_DITHERED_DRAW_MODE(4, getTPage(1, 1, 320, 256));

    if (TASK(Actor)->timer < 0xFF) {
        TASK(Actor)->timer++;
    }

    if (TASK(Actor)->timer < 0x15) {
        radius = 0x20;
    } else {
        radius = (TASK(Actor)->timer - 0x14) * 20 + 0x20;
    }
    draw_radius = radius < 0x1F5 ? radius : 0x1F4;

    if (TASK(Actor)->timer >= 0x15) {
        shade = 0x80 + (TASK(Actor)->timer - 0x14) * 12;
    } else {
        shade = 0x80;
    }
    draw_shade = shade < 0x100 ? shade : 0xFF;
    func_801F3EA0(0x82, TASK(Actor)->timer + 0xA, draw_radius, draw_shade);

    radius      = TASK(Actor)->timer * 12;
    draw_radius = radius < 0x31 ? radius : 0x30;

    shade = rsin(0x100);
    x     = 0x82 + shade * (0x10E - TASK(Actor)->timer * 9) / ONE;
    shade = rcos(0x100);
    shade = TASK(Actor)->timer + 0xA + shade * (0x10E - TASK(Actor)->timer * 9) / ONE;
    func_801F3AB0(x, shade, 0x40, draw_radius);

    shade = rsin(0x100);
    x     = 0x82 + shade * (0xF0 - TASK(Actor)->timer * 8) / ONE;
    shade = rcos(0x100);
    shade = TASK(Actor)->timer + 0xA + shade * (0xF0 - TASK(Actor)->timer * 8) / ONE;
    func_801F3AB0(x, shade, 0x20, draw_radius);

    shade = rsin(0x100);
    x     = 0x82 + shade * (0xB4 - TASK(Actor)->timer * 6) / ONE;
    shade = rcos(0x100);
    shade = TASK(Actor)->timer + 0xA + shade * (0xB4 - TASK(Actor)->timer * 6) / ONE;
    func_801F3AB0(x, shade, 8, draw_radius);

    shade = rsin(0x100);
    x     = 0x82 + shade * (0x78 - TASK(Actor)->timer * 4) / ONE;
    shade = rcos(0x100);
    shade = TASK(Actor)->timer + 0xA + shade * (0x78 - TASK(Actor)->timer * 4) / ONE;
    func_801F3AB0(x, shade, 0x10, draw_radius);
}
#else
INCLUDE_ASM(func_801F36DC);
#endif
