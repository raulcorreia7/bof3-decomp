#include "battle_15.h"

MATCH void func_8009DD50(void) {
    s16              value;
    BattlePanelTask* panel;

    if (g_Game.members[g_Battle.active_battler].chr.character_id == CHAR_ID_WHELP) {
        Battle_MarkDamageApplied();
        ((BattlePanelTask*)g_Battle.target_record)->x.signed_half = 0x270F;
    } else {
        value                                                     = func_800A4294(3) - ENEMY_COMBATANT(g_Battle.target).stats.defense;
        ((BattlePanelTask*)g_Battle.target_record)->x.signed_half = value;
    }
    panel = (BattlePanelTask*)g_Battle.target_record;
    CLAMP_MIN(panel->x.signed_half, 0);
}
