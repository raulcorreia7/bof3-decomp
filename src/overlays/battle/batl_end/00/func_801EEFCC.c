#include "batl_end_00.h"

MATCH void func_801EEFCC(void) {
    if (EMI_LoaderIsReady() != 0) {
        g_BattleRowCursor = 0;
        g_BattleUIState   = 0;
        g_BattleUIStep += 1;
    }
}
