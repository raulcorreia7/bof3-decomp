#include "battle_03.h"

MATCH void Battle_ReloadPartySprites(void) {
    u8 i;

    i = 0u;
    if (g_BattlePartyCount != 0u) {
        do {
            if ((g_Game.members[i].u.turn.damage_flags.value & COMBATANT_FLAG_FORM_EFFECT_PLAYING) != 0u) {
                return;
            }
            i += 1u;
        } while (i < g_BattlePartyCount);
    }
    if (g_Battle.row_cursor != g_Battle.party_count) {
        g_BattleSubStep -= 1u;
        return;
    }
    SND_SetBankLayout(0u);
    i = 0u;
    if (g_BattlePartyCount != 0u) {
        do {
            func_800A36F0(i, g_Game.members[i].chr.status & STATUS_CURE_MASK);
            GFX_FreePaletteFadeTarget(&g_Game.members[i]);
            i += 1u;
        } while (i < g_Battle.party_count);
    }
    for (i = 0u; i < g_BattlePartyCount; i++) {
        if (ACTOR_IN_USE(g_Game.members[i])) {
            PartyMember* work = &g_Game.members[i];
            u16          half = work->unk_58;

            g_Task = work;
            Actor_StageScript(work->unk_4B, (u16)(half - 2u), MEM_PTR(u8, BATTLE_SCRIPT_TABLE), 0x1800);
        }
    }
    EMI_GetArchiveId(g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK, EMI_FAMILY_PL);
    {
        volatile u8* state = &g_Battle.phase.sub_step;

        *state += 1u;
    }
}
