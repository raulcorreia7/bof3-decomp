#include "battle_03.h"

/* completes the battle setup pass: waits while a record holds the pending bit, backs the state counter off
 * on an inconsistent selection, otherwise resets each local record's presentation, runs the followups and hands the
 * front end to the EMI loader.
 */
/* func_801D6A14 */
MATCH void Battle_LoadEndOverlay(void) {
    u8  i;
    u8* step;

    i = 0u;
    if (g_BattlePartyCount != 0u) {
        do {
            if ((g_Game.members[i].u.turn.damage_flags.value & COMBATANT_FLAG_FORM_EFFECT_PLAYING) != 0u) {
                return;
            }
            i += 1u;
        } while (i < g_BattlePartyCount);
    }
    if (g_BattleRowCursor != g_Battle.party_count) {
        g_BattleSubStep -= 1u;
        return;
    }
    if ((g_Battle.outcome.result & BATTLE_RESULT_DEFEAT) == 0u) {
        i = 0u;
        if (i < g_BattleRowCursor) {
            do {
                PartyMember* work = &g_Game.members[i];

                g_Task = work;
                if (HAS_STATUS(g_Game.members[i], 0x800u)) {
                    g_Game.members[i].chr.hp        = g_Game.members[i].chr.stats.max_hp;
                    g_Game.members[i].chr.ap        = g_Game.members[i].chr.stats.max_ap;
                    g_Game.members[i].chr.willpower = g_Game.members[i].chr.stats.willpower;
                    func_800A36F0(i, g_Game.members[i].chr.status & ~STATUS_KO);
                }
                func_800A36F0(i, g_Game.members[i].chr.status & STATUS_CURE_MASK);
                GFX_FreePaletteFadeTarget(work);
                Battle_GetTurnCursor(i);
                i += 1u;
            } while (i < g_Battle.party_count);
        }
        g_Battle.action_lock = 0u;
    }
    if (BATTLE_IS_RANDOM()) {
        u8 flags = g_Battle.outcome.result;

        if ((flags & 0x1u) != 0u) {
            g_Battle.phase.step = 2u;
        }
        if ((flags & BATTLE_RESULT_VICTORY) != 0u) {
            g_Battle.phase.step = 1u;
        }
    }
    g_BattleChooseEndingHook();
    SND_SetBankLayout(0u);
    step = &g_Battle.phase.step;
    if (*step == 1u) {
        EMI_LoadArchive(EMI_SLOT_BATL_END);
    }
    if (*step == 2u) {
        EMI_LoadArchive(EMI_SLOT_BATL_OVR);
    }
    g_Battle.phase.sub_step = 0u;
}
