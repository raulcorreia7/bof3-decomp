#include "battle_15.h"

MATCH void func_800A2598(void) {
    BattleTurn* record;
    s32         slot;
    u8          mode;

    mode = LOBU(g_Battle.target);
    if (mode < 3u) {
        g_Battle.target_record->hp_change =
            Battle_CalcDamage(g_Battle.active_battler, mode, BATTLE_ELEMENT_FROM_WEAPON);
    } else {
        g_Battle.target_record->hp_change =
            Battle_CalcDamage(g_Battle.active_battler, mode, BATTLE_ELEMENT_FROM_WEAPON);
        slot = LOBU(g_Battle.target);
        slot -= 3;
        if (g_BattleEnemyBattlers[slot].enemy_id.byte.family == ENEMY_FAMILY_DEMON) {
            record = *(BattleTurn**)&g_Battle.target_record;
            record->hp_change *= 2;
        }
    }
}
