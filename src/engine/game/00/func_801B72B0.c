#include "game_00.h"

MATCH void func_801B72B0(void) {
    func_801C2438();
    g_Task->tint.signed_bytes.delta.red       = -0x80;
    g_Task->tint.signed_bytes.delta.green     = -0x80;
    g_Task->tint.signed_bytes.delta.blue      = -0x80;
    g_Task->tint.bytes.flags                  = 1;
    g_Game.current->u.field.mode_12B.u8_value = 7;
    g_Task->header.flags &= ~ACTOR_FLAG_HIDDEN;
    g_Task->unk_03 = 1;
}
