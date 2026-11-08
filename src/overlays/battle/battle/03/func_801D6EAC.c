#include "battle_03.h"

MATCH void func_801D6EAC(void) {
    if (EMI_IsReady() != 0) {
        volatile u8* state = &g_BattleSubStep;

        *state += 1;
    }
}
