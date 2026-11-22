#include "game_00.h"

MATCH void func_801A2788(s32 mode_index) {
    ActorModeCallback* slot;

    slot = &D_801C83D8[mode_index & BYTE_MASK];
    (*slot)(g_CurrentActor);
}
