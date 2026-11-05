#include "battle_03.h"

/* waits until the sixteen hand-off markers D_8018E140[16..23] are clear, then either performs the
 * configured reset or reinitialises the panel rows, stream slot and first three battler slots and clears the battle
 * bits.
 */
MATCH void func_801D656C(void) {
    u8 i;

    for (i = 16; i < 24; i++) {
        if (D_8018E140[i] != 0) {
            return;
        }
    }
    if (g_BattleEncounter != 0 && g_BossBattleEventHook(2U) == GAME_NONE) {
        return;
    }
    if (g_BattleResult != 0) {
        D_80148354    = 0;
        D_801483C0    = 0;
        D_80148378[0] = 0;
        D_801484E0    = 0;
        D_801484BC    = 0;
        D_80148498    = 0;
        D_80148474    = 0;
        D_80148450    = 0;
        D_8014842C    = 0;
        D_80148408    = 0;
        D_801483E4    = 0;
        g_BattleMode  = 5;
        g_BattleStep  = 0;
        g_BattleState &= ~BATTLE_STATE_COMMAND_ARMED;
    } else {
        if (!(g_BattleState & BATTLE_STATE_COMMAND_ARMED)) {
            for (i = 1; i < 7; i++) {
                g_BattlePanelWidths[i] = 0;
            }
            g_BattlePanelWidths[0] = 8;
            g_BattlePanelSlot      = 0;
            EMI_LoaderStreamInitSlot(EMI_SLOT_COMN_SE);
        }
        func_801DB494();
        for (i = 0; i < BATTLE_PARTY_SLOT_COUNT; i++) {
            if (!Battle_SlotIsBlocked(i)) {
                g_BattlePartyBattlers[i].mode = 2;
            }
        }
        g_BattleSurprise = 0;
        g_BattleMode     = 1;
        g_BattleStep     = 0;
        g_BattleSubStep  = 0;
        g_BattleState &= 0xFFF7;
    }
}
