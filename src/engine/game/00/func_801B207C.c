#include "game_00.h"

MATCH void func_801B207C(void) {
    Actor* work;
    s32    limit;
    s32    awake; /* FAKE: constant local orders the loop-invariant hoist (owner-approved dummy). */
    u8     frames;
    u8     i;

    g_Task->timer += 1;
    g_Task->direction_08 = (g_Task->direction_08 + 1) & 0x7;
    Actor_SelectScript(g_Task->direction_08);
    frames = g_Task->timer;
    for (i = 1; i < g_PartySize; i++) {
        work   = (Actor*)((u8*)g_Game.members + i * BATTLE_PARTY_STRIDE);
        g_Task = work;
        awake  = 3;
        limit  = -(frames << 5);
        if (work->header.mode == awake && limit < (s8)work->tint.bytes.unk_5D) {
            work->tint.bytes.unk_5D   = limit;
            g_Task->tint.bytes.unk_5E = g_Task->tint.bytes.unk_5D;
            g_Task->tint.bytes.unk_5F = g_Task->tint.bytes.unk_5D;
        }
    }
    TASK_SET(g_Game.members);
    if (g_Game.members[0].unk_09 == 4) {
        ((PartyMember*)g_Game.members)[0].header.step += 1;
    }
}
