#include "game_00.h"

MATCH void func_801A2788(s32 handler_index) {
    ObjectFunc* slot;

    slot = &D_801C83D8[handler_index & 0xFF];
    (*slot)(g_CurrentActor);
}
