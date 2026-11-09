#include "battle_15.h"

/* Four-byte battle slot rows. */

MATCH void func_800A6488(void) {
    u8* counter = (u8*)&g_Battle.ui_state;

    D_80145518[*(s16*)&D_801485EC + D_801485EE].slot_00 =
        g_BattleTargetRows[g_BattleTargetCursorCol + D_801485CA].slot_00;
    D_80145518[*(s16*)&D_801485EC + D_801485EE].slot_01 =
        g_BattleTargetRows[g_BattleTargetCursorCol + D_801485CA].slot_01;
    D_80145518[*(s16*)&D_801485EC + D_801485EE].slot_02 =
        g_BattleTargetRows[g_BattleTargetCursorCol + D_801485CA].slot_02;
    D_80145518[*(s16*)&D_801485EC + D_801485EE].gate_03 =
        g_BattleTargetRows[g_BattleTargetCursorCol + D_801485CA].gate_03;
    *counter = *counter + 1;
}
