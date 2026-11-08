#include "batl_end_00.h"

MATCH void func_801EEFCC(void) {
    if (EMI_LoaderIsReady() != 0) {
        g_Battle.row_cursor = 0;
        g_Battle.ui_state   = 0;
        g_Battle.ui_step += 1;
    }
}
