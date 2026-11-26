#include "area172_13.h"

MATCH void func_801F31D0(void) {
    SpinEffect* spin;
    u8          i;

    if ((SELF(Actor)->unk_06++ & 3) == 0) {
        Area_ClaimSpawnSlot();
    }
    func_801F36C0(&SELF(Actor)->pos.x, (s16)SELF(Actor)->screen_x, 7);
    func_801F3FAC();
    Area_UpdateSpawnSlots();
    if (SELF(Actor)->tint.steps.delta.r < 64) {
        SELF(Actor)->tint.steps.delta.r++;
    }
    spin = MEM_PTR(SpinEffect, AREA_WORK + 0xC0);
    for (i = 0; i < 32; i++) {
        spin->fade = (s8)SELF(Actor)->tint.bytes.rgb.r >> 1;
        spin++;
    }
    if (--SELF(Actor)->timer == 0) {
        UI_ModeSet(8);
        SELF(Actor)->header.mode++;
    }
}
