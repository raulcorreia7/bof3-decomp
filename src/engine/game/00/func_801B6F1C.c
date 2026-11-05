#include "game_00.h"

MATCH void func_801B6F1C(void) {
    u8  count;
    u8  wait;
    u8  flags;
    u32 saved;

    count = g_Task->unk_09;
    if (count != 0) {
        g_Task->unk_09 = (count - 1);
        func_801B0DFC();
        return;
    }
    wait = g_GameState->wait_11F;
    if (wait == 0) {
        func_801B6BC8();
        return;
    }
    saved                 = g_Task->vz;
    g_GameState->wait_11F = (wait - 1);
    func_801C24D0();
    flags = g_GameState->flags_118;
    if (flags & 0x80) {
        g_Task->vz = saved;
    }
    count          = g_Task->unk_09;
    g_Task->unk_09 = (count - 1);
    func_801B0DFC();
}
