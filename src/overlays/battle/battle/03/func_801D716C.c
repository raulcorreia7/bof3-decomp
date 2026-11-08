#include "battle_03.h"

MATCH void func_801D716C(void) {
    if (EMI_IsReady() != 0) {
        g_BattleStep    = 4;
        g_BattleSubStep = 0;
    }
}
