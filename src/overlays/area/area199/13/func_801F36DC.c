#include "area199_13.h"

/* Draws the rising glow: a disc that grows and brightens with the timer and four rings that close in on it. */
MATCH void func_801F36DC(void) {
    s32 radius;
    s32 size;

    GFX_ADD_DITHERED_DRAW_MODE(4, getTPage(1, 1, 320, 256));

    if (SELF(Actor)->timer < 0xFF) {
        SELF(Actor)->timer++;
    }

    if (SELF(Actor)->timer < 0x15) {
        radius = 0x20;
    } else {
        radius = (SELF(Actor)->timer - 0x14) * 20 + 0x20;
    }
    radius = radius > 0x1F4 ? 0x1F4 : radius;
    if (SELF(Actor)->timer >= 0x15) {
        size = (SELF(Actor)->timer - 0x14) * 12 + 0x80;
    } else {
        size = 0x80;
    }
    size = size > 0xFF ? 0xFF : size;
    func_801F3EA0(0x82, SELF(Actor)->timer + 0xA, radius, size);

    size = SELF(Actor)->timer * 12;
    size = size > 0x30 ? 0x30 : size;

    func_801F3AB0(0x82 + rsin(0x100) * (0x10E - SELF(Actor)->timer * 9) / ONE, SELF(Actor)->timer + 0xA + rcos(0x100) * (0x10E - SELF(Actor)->timer * 9) / ONE, 0x40, size);
    func_801F3AB0(0x82 + rsin(0x100) * (0xF0 - SELF(Actor)->timer * 8) / ONE, SELF(Actor)->timer + 0xA + rcos(0x100) * (0xF0 - SELF(Actor)->timer * 8) / ONE, 0x20, size);
    func_801F3AB0(0x82 + rsin(0x100) * (0xB4 - SELF(Actor)->timer * 6) / ONE, SELF(Actor)->timer + 0xA + rcos(0x100) * (0xB4 - SELF(Actor)->timer * 6) / ONE, 8, size);
    func_801F3AB0(0x82 + rsin(0x100) * (0x78 - SELF(Actor)->timer * 4) / ONE, SELF(Actor)->timer + 0xA + rcos(0x100) * (0x78 - SELF(Actor)->timer * 4) / ONE, 0x10, size);
}
