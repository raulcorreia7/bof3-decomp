#include "game_00.h"

MATCH bool func_801C27E0(s8 tuning_delta) {
    if (func_801C2894(tuning_delta) & BYTE_MASK) {
        GFX_StagePalette((u32)((g_Task->unk_05 << 6) + (s32)MEM_PTR(u8, 0x80035600u)), 0);
        g_Task->flags &= ~ACTOR_FLAG_SEMI_TRANSPARENT;
        ACTOR_CLEAR_TINT();
        g_Task->tint.bytes.flags = 0;
        return true;
    }
    return false;
}
