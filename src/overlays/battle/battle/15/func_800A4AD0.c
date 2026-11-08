#include "battle_15.h"

/* @initializes several global state variables.
 */
MATCH void func_800A4AD0(void) {
    u8 value = g_BattleRowCursor;

    g_Battle.ui_state           = 0;
    g_Battle.cursor.panel_entry = 0;
    g_Battle.ui_step            = value + 3;
    g_Battle.row_cursor         = value | BATTLE_SELECTION_ACTIVE;
}
