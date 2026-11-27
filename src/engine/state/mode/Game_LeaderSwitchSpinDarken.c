#include "engine/game/00/game_00.h"

/* func_801B207C */
/* Step 1: turns the leader one facing per frame while the timer rises and darkens the mode 3 members; advances when unk_09 is 4. */
MATCH void Game_LeaderSwitchSpinDarken(void) {
    Actor* work;
    s32    limit;
    s32    awake; /* FAKE: constant local orders the loop-invariant hoist (owner-approved dummy). */
    u8     frames;
    u8     i;

    SELF(Actor)->timer += 1;
    SELF(Actor)->direction = (SELF(Actor)->direction + 1) & 0x7;
    Script_Select(SELF(Actor)->direction);
    frames = SELF(Actor)->timer;
    for (i = 1; i < g_PartySize; i++) {
        work   = (Actor*)((u8*)g_Game.members + i * BATTLE_PARTY_STRIDE);
        g_Self = work;
        awake  = 3;
        limit  = -(frames << 5);
        if (work->header.mode == awake && limit < (s8)work->tint.bytes.rgb.r) {
            work->tint.bytes.rgb.r        = limit;
            SELF(Actor)->tint.bytes.rgb.g = SELF(Actor)->tint.bytes.rgb.r;
            SELF(Actor)->tint.bytes.rgb.b = SELF(Actor)->tint.bytes.rgb.r;
        }
    }
    SELF_SET(g_Game.members);
    if (g_Game.members[0].unk_09 == 4) {
        ((PartyMember*)g_Game.members)[0].header.step += 1;
    }
}
