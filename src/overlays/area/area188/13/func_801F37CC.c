#include "area188_13.h"

MATCH void func_801F37CC(void) {
    u8 mode;
    u8 count;

    count               = SELF(Actor)->unk_06;
    SELF(Actor)->unk_06 = count + 1;
    if (!(count & 0x3)) {
        Area_ClaimSpawnSlot();
    }
    Area_UpdateSpawnSlots();
    func_801F44B4();
    Area_DrawYellowLine(&SELF(Actor)->unk_18, &SELF(Actor)->pos.x, 0x40);
    if (*g_ScriptVars == 3) {
        if (SELF(Actor)->timer == 16) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x16));
        }
        ACTOR_COUNT_DOWN(SELF(Actor), mode, timer);
        if (!(mode & BYTE_MASK)) {
            SELF(Actor)->unk_03 = 0x80;
            SELF(Actor)->header.mode += 1;
        }
    }
}
