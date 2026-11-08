#include "batl_end_00.h"

/* func_801EEFCC */
MATCH void Battle_InitVictoryMenu(void) {
    if (EMI_IsReady() != 0) {
        g_Battle.row_cursor = 0;
        g_Battle.ui_state   = 0;
        g_Battle.ui_step += 1;
    }
}
