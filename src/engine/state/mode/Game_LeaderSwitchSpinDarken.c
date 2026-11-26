#include "engine/game/00/game_00.h"

/* func_801B207C */
/* Step 1: turns the leader one facing per frame while the timer rises and darkens the mode 3 members; advances when unk_09 is 4. */
MATCH void Game_LeaderSwitchSpinDarken(void) {
    Actor* work;
    s32    limit;
    s32    awake; /* FAKE: constant local orders the loop-invariant hoist (owner-approved dummy). */
    u8     frames;
    u8     i;

    TASK(Actor)->timer += 1;
    TASK(Actor)->direction = (TASK(Actor)->direction + 1) & 0x7;
    Script_Select(TASK(Actor)->direction);
    frames = TASK(Actor)->timer;
    for (i = 1; i < g_PartySize; i++) {
        work   = (Actor*)((u8*)g_Game.members + i * BATTLE_PARTY_STRIDE);
        g_Task = work;
        awake  = 3;
        limit  = -(frames << 5);
        if (work->header.mode == awake && limit < (s8)work->tint.bytes.rgb.r) {
            work->tint.bytes.rgb.r        = limit;
            TASK(Actor)->tint.bytes.rgb.g = TASK(Actor)->tint.bytes.rgb.r;
            TASK(Actor)->tint.bytes.rgb.b = TASK(Actor)->tint.bytes.rgb.r;
        }
    }
    TASK_SET(g_Game.members);
    if (g_Game.members[0].unk_09 == 4) {
        ((PartyMember*)g_Game.members)[0].header.step += 1;
    }
}
