#include "battle_15.h"

MATCH void func_8009DD50(void) {
    s16              value;
    BattlePanelTask* panel;

    if (D_80145F09[g_BattleActiveBattler * BATTLE_PARTY_STRIDE] == CHAR_ID_WHELP) {
        func_800A3F28();
        ((BattlePanelTask*)g_BattleTargetRecord)->x.signed_half = 0x270F;
    } else {
        value = func_800A4294(3) - ENEMY_COMBATANT(g_BattleTarget).stats.defense;
        ((BattlePanelTask*)g_BattleTargetRecord)->x.signed_half = value;
    }
    panel = (BattlePanelTask*)g_BattleTargetRecord;
    CLAMP_MIN(panel->x.signed_half, 0);
}
