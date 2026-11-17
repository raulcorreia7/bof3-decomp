#include "game_00.h"

MATCH void func_801B72B0(void) {
    func_801C2438();
    g_Task->tint.steps.delta.r                  = -0x80;
    g_Task->tint.steps.delta.g                  = -0x80;
    g_Task->tint.steps.delta.b                  = -0x80;
    g_Task->tint.bytes.flags                    = 1;
    g_Game.current->u.field.mode.unsigned_value = 7;
    g_Task->header.flags &= ~ACTOR_FLAG_HIDDEN;
    g_Task->unk_03 = 1;
}
