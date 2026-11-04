#include "battle_15.h"

MATCH void func_800ADD44(void) {
    volatile PartyBattler* work;
    /* FAKE: retail holds the armed work pointer in a0. */
    MATCH_REG(PartyBattler*, next, "a0");
    PartyBattler* slotp;
    u8*           base;
    s16*          pair;
    u8*           row;
    u8            slot;

    BATTLE_WORK->unk_29      = 1;
    BATTLE_WORK->unk_25      = 0x1E;
    BATTLE_WORK->unk_26      = 0;
    BATTLE_WORK->unk_24      = 0x80;
    BATTLE_WORK->unk_27      = 0x1B;
    BATTLE_WORK->unk_28      = 1;
    work                     = (volatile PartyBattler*)g_SpadWork;
    work->unk_2B             = 0;
    next                     = (PartyBattler*)g_SpadWork;
    work->unk_2C.signed_half = 2;
    next->unk_2A             = 0;
    work                     = (volatile PartyBattler*)g_SpadWork;
    work->unk_4B             = 0xFF;
    slotp                    = (PartyBattler*)g_SpadWork;
    work->word_3C.word       = 0;
    pair                     = &D_801485EE;
    base                     = (u8*)D_80145518;
    row                      = base + ((*pair + slotp->word_08.byte.unk_09) * 4);
    slot                     = row[slotp->word_08.byte.unk_0A];
    if (slot != GAME_NONE) {
        Actor_SelectScript(slot);
    }
    D_801485FA    = (u16)*pair;
    work          = (volatile PartyBattler*)g_SpadWork;
    work->step_01 = work->step_01 + 1;
}
