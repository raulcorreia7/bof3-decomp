#include "battle_03.h"

MATCH void func_801D67EC(void) {
    u8 count = g_BattleSubStep;

    g_UIPanelMode           = 0;
    g_Battle.selection      = 0;
    g_Battle.phase.sub_step = count + 1;
}
