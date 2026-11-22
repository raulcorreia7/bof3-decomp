#include "batl_end_00.h"

MATCH void func_801EF77C(void) {
    if (g_PadStates[0].held != 0) {
        g_Battle.selection = 0;
        g_Battle.ui_mode += 1;
    }
}
