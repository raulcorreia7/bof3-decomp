#include "game_00.h"

MATCH void func_801A2788(s32 step_index) {
    ObjectFunc* slot;

    slot = &D_801C83D8[step_index & BYTE_MASK];
    (*slot)(g_CurrentActor);
}
