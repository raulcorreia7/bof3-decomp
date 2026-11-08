#include "game_00.h"

MATCH void func_801B72B0(void) {
    func_801C2438();
    g_Task->tint.signed_bytes.unk_5D       = -0x80;
    g_Task->tint.signed_bytes.unk_5E       = -0x80;
    g_Task->tint.signed_bytes.unk_5F       = -0x80;
    g_Task->tint.bytes.flags               = 1;
    g_GameState->u.field.mode_12B.u8_value = 7;
    g_Task->header.flags &= ~ACTOR_FLAG_HIDDEN;
    g_Task->unk_03 = 1;
}
