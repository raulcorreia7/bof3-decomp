#include "battle_03.h"

MATCH void func_801E019C(void) {
    if (func_8014DAEC() != 0u) {
        g_Task->unk_03 += 1u;
        if (!HAS_STATUS(*g_Game.current, STATUS_PARALYZED)) {
            func_801DEFE4();
        }
    }
}
