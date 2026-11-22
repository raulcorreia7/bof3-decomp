#include "area188_13.h"

MATCH void func_801F37CC(void) {
    u8 mode;
    u8 count;

    count               = TASK(Actor)->unk_06;
    TASK(Actor)->unk_06 = count + 1;
    if (!(count & 0x3)) {
        Area_ClaimSpawnSlot();
    }
    Area_UpdateSpawnSlots();
    func_801F44B4();
    Area_DrawYellowLine(&TASK(Actor)->unk_18, &TASK(Actor)->pos.x, 0x40);
    if (*g_ScriptVars == 3) {
        if (TASK(Actor)->timer == 16) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x16));
        }
        ACTOR_COUNT_DOWN(TASK(Actor), mode, timer);
        if (!(mode & BYTE_MASK)) {
            TASK(Actor)->unk_03 = 0x80;
            TASK(Actor)->header.mode += 1;
        }
    }
}
