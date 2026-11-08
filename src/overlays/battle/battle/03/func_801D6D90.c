#include "battle_03.h"

MATCH void func_801D6D90(void) {
    if ((EMI_IsReady() != 0) && (g_InputPressed != 0)) {
        volatile u8* state = &g_Battle.phase.sub_step;

        *state += 1;
    }
}
