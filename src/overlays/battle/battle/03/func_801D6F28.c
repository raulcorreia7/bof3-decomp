#include "battle_03.h"

MATCH void func_801D6F28(void) {
    u8 i;

    i = 0u;
    if (g_BattlePartyCount != 0u) {
        do {
            if ((g_BattlePartyBattlers[i].damage_flags.value & 0x2000u) != 0u) {
                return;
            }
            i += 1u;
        } while (i < g_BattlePartyCount);
    }
    if (g_BattleRowCursor != g_BattlePartyCount) {
        g_BattleSubStep -= 1u;
        return;
    }
    SND_SetBankLayout(0u);
    i = 0u;
    if (g_BattlePartyCount != 0u) {
        do {
            func_800A36F0(i, g_BattlePartyBattlers[i].chr.status & STATUS_CURE_MASK);
            GFX_FreePaletteFadeTarget(&g_BattlePartyBattlers[i]);
            i += 1u;
        } while (i < g_BattlePartyCount);
    }
    for (i = 0u; i < g_BattlePartyCount; i++) {
        if (ACTOR_IN_USE(g_BattlePartyBattlers[i])) {
            PartyBattler* work = &g_BattlePartyBattlers[i];
            u16           half = work->unk_58;

            g_Task = work;
            Actor_StageScriptRecord(work->unk_4B, (u16)(half - 2u), (u8*)0x800F0800u, 0x1800);
        }
    }
    EMI_StreamFamilyArchive(g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK, EMI_FAMILY_PL);
    {
        volatile u8* state = &g_BattleSubStep;

        *state += 1u;
    }
}
