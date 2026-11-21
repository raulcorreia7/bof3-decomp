#include "batl_end_00.h"

MATCH void func_801EEEE0(void) {
    if (g_PadStates[0].held != 0) {
        volatile u8* counter = &g_Battle.ui_mode;
        *counter += 1;
    }
}
