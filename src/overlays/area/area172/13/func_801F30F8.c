#include "area172_13.h"

MATCH void func_801F30F8(void) {
    s32 i;
    s32 value;

    func_801F36C0(&SELF(Actor)->pos.x, (s16)SELF(Actor)->screen_x, 7);
    if (*g_ScriptVars == 0xA) {
        Area_ClearWorkColumn();
        value = 0x800E48C0;
        PushMatrix();
        i = 0;
        do {
            Area_InitSpin(value);
            i += 1;
            value += 0x2C;
        } while ((i & BYTE_MASK) < 0x20U);
        PopMatrix();
        SELF(Actor)->unk_06           = 0;
        SELF(Actor)->tint.bytes.rgb.r = 8;
        SELF(Actor)->timer            = 120;
        SELF(Actor)->header.mode += 1;
    }
}
