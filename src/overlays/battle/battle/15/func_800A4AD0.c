#include "battle_15.h"

/* @initializes several global state variables.
 */
MATCH void func_800A4AD0(void) {
    u8 value = g_BattleRowCursor;

    g_BattleUIState    = 0;
    g_BattlePanelEntry = 0;
    g_BattleUIStep     = value + 3;
    g_BattleRowCursor  = value | BATTLE_SELECTION_ACTIVE;
}
