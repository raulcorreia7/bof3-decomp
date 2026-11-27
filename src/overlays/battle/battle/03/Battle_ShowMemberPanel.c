#include "battle_03.h"

/* func_801E9F18 */
MATCH void Battle_ShowMemberPanel(void) {
    if ((g_Battle.selection_latch != 0) && (((Battle_SlotIsBlocked(g_UIPanelCurrent->unk_0A) & BYTE_MASK) == 0) || (func_80097EB8() & BYTE_MASK) || (func_8009AF7C() & BYTE_MASK))) {
        if (g_BattleActorTurn->command.target == g_UIPanelCurrent->unk_0A) {
            Battle_LightPanel();
        }
        if ((g_BattleActorTurn->command.target & BATTLE_TARGET_PARTY_SIDE) != 0) {
            Battle_LightPanel();
        }
    }
}
