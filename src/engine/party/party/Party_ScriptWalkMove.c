#include "engine/game/00/game_00.h"

/* func_801B6F1C */
/* Moves the actor for its remaining step frames, then reads the next record. */
MATCH void Party_ScriptWalkMove(void) {
    u8  count;
    u8  wait;
    u8  flags;
    u32 saved;

    count = TASK(Actor)->timer;
    if (count != 0) {
        TASK(Actor)->timer = (count - 1);
        Actor_MovementUpdate();
        return;
    }
    wait = g_Game.current->u.field.wait;
    if (wait == 0) {
        Party_ScriptWalkRead();
        return;
    }
    saved                        = TASK(Actor)->vz;
    g_Game.current->u.field.wait = (wait - 1);
    Area_RunWalk();
    flags = g_Game.current->u.field.flags;
    if (flags & 0x80) {
        TASK(Actor)->vz = saved;
    }
    count              = TASK(Actor)->timer;
    TASK(Actor)->timer = (count - 1);
    Actor_MovementUpdate();
}
