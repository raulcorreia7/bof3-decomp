#include "battle_03.h"

MATCH void func_801D67EC(void) {
    u8 count = g_BattleSubStep;

    g_UiPanelMode           = 0;
    g_Battle.row_cursor     = 0;
    g_Battle.phase.sub_step = count + 1;
}
