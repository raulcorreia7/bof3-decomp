#include "area077_14.h"

MATCH void func_801F3E48(void) {
    u8* spin;
    s32 i;

    /* FAKE: retail reserves 16 bytes of unused stack. */
    FAKE_STACK_PADS(u8, 16);

    SELF(Actor)->pos.x.fixed = 0x738000;
    SELF(Actor)->pos.y.fixed = 0xB8000;
    SELF(Actor)->pos.z.fixed = (Area_HeightSample(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed) << 16) + 0x800000;
    PushMatrix();
    spin = (u8*)(AREA_WORK + 0xD04);
    i    = 0;
    do {
        Area_InitSpin(spin);
        i += 1;
        spin += 0x2C;
    } while ((i & BYTE_MASK) < 0x20U);
    PopMatrix();
    SELF(Actor)->vx = 0;
    SELF(Actor)->header.mode += 1;
}
