#include "battle_15.h"

MATCH void func_8009EECC(void) {
    g_Battle.target_record->hp_change = Battle_GetActionId(g_Battle.active_battler, g_Battle.target, 0x14, 0);
}
