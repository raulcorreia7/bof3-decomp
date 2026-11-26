#include "area098_13.h"

MATCH void func_801F3CDC(void) {
    u8 value;

    value               = SELF(Actor)->unk_06;
    SELF(Actor)->unk_06 = value + 1;
    if (!(value & 0x3)) {
        Area_ClaimSpawnSlot();
    }
    Area_UpdateSpawnSlots();
    func_801F5940();
    Area_DrawYellowLine(&SELF(Actor)->unk_18, &SELF(Actor)->pos.x, 0x40);
    if (*g_ScriptVars == 0x18) {
        SELF(Actor)->unk_03 = 0x80;
        SELF(Actor)->timer  = 8;
        SELF(Actor)->header.mode += 1;
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x08));
    }
}
