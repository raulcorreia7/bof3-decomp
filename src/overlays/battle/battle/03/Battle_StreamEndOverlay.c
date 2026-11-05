#include "battle_03.h"

/* completes the battle setup pass: waits while a record holds the pending bit, backs the state counter off
 * on an inconsistent selection, otherwise resets each local record's presentation, runs the followups and hands the
 * front end to the EMI loader.
 */
/* func_801D6A14 */
MATCH void Battle_StreamEndOverlay(void) {
    u8  i;
    u8* step;

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
    if ((g_BattleResult & BATTLE_RESULT_DEFEAT) == 0u) {
        i = 0u;
        if (i < g_BattleRowCursor) {
            do {
                PartyBattler* work = &g_BattlePartyBattlers[i];

                g_Task = work;
                if (HAS_STATUS(g_BattlePartyBattlers[i], 0x800u)) {
                    g_BattlePartyBattlers[i].chr.hp        = g_BattlePartyBattlers[i].chr.stats.max_hp;
                    g_BattlePartyBattlers[i].chr.ap        = g_BattlePartyBattlers[i].chr.stats.max_ap;
                    g_BattlePartyBattlers[i].chr.willpower = g_BattlePartyBattlers[i].chr.stats.willpower;
                    func_800A36F0(i, g_BattlePartyBattlers[i].chr.status & ~STATUS_KO);
                }
                func_800A36F0(i, g_BattlePartyBattlers[i].chr.status & STATUS_CURE_MASK);
                GFX_FreePaletteFadeTarget(work);
                func_801DDFEC(i);
                i += 1u;
            } while (i < g_BattlePartyCount);
        }
        g_BattleActionLock = 0u;
    }
    if (g_BattleEncounter == 0u) {
        u8 flags = g_BattleResult;

        if ((flags & 1u) != 0u) {
            g_BattleStep = 2u;
        }
        if ((flags & BATTLE_RESULT_VICTORY) != 0u) {
            g_BattleStep = 1u;
        }
    }
    g_BattleChooseEndingHook();
    SND_SetBankLayout(0u);
    step = &g_BattleStep;
    if (*step == 1u) {
        EMI_LoaderStreamInitSlot(EMI_SLOT_BATL_END);
    }
    if (*step == 2u) {
        EMI_LoaderStreamInitSlot(EMI_SLOT_BATL_OVR);
    }
    g_BattleSubStep = 0u;
}
