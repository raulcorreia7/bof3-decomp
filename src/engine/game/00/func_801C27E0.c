#include "game_00.h"

MATCH bool func_801C27E0(s8 tuning_delta) {
    if (func_801C2894(tuning_delta) & BYTE_MASK) {
        GFX_StagePalette(((g_Task->unk_05 << 6) + GAME_PALETTE_STAGE), 0);
        g_Task->header.flags &= ~ACTOR_FLAG_SEMI_TRANSPARENT;
        ACTOR_CLEAR_TINT();
        g_Task->tint.bytes.flags = 0;
        return true;
    }
    return false;
}
