#include "battle_15.h"

MATCH void func_8009FEF4(void) {
    BattleTurn* record;
    s16         value;

    g_Battle.action_type                                      = BATTLE_ACTION_ABILITY;
    MEM(u16, 0x801463C0u)                                     = 0x66;
    value                                                     = Battle_GetActionId(g_Battle.active_battler, g_Battle.target, D_801CAF13, 0);
    ((volatile BattleTurn*)g_Battle.target_record)->hp_change = value;
    record                                                    = g_Battle.target_record;
    record->hp_change                                         = (s16)(u16)record->hp_change / 2;
}
