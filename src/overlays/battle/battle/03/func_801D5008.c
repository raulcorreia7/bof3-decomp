#include "battle_03.h"

MATCH void func_801D5008(void) {
    u8* state = &g_Battle.phase.sub_step;
    *state    = *state + 1;
}
