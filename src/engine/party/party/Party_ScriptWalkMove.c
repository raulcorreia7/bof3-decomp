#include "engine/game/00/game_00.h"

/* func_801B6F1C */
/* Moves the actor for its remaining step frames, then reads the next record. */
MATCH void Party_ScriptWalkMove(void) {
    u8  count;
    u8  wait;
    u8  flags;
    u32 saved;

    count = SELF(Actor)->timer;
    if (count != 0) {
        SELF(Actor)->timer = (count - 1);
        Actor_MovementUpdate();
        return;
    }
    wait = g_Game.current->u.field.wait;
    if (wait == 0) {
        Party_ScriptWalkRead();
        return;
    }
    saved                        = SELF(Actor)->vz;
    g_Game.current->u.field.wait = (wait - 1);
    Area_RunWalk();
    flags = g_Game.current->u.field.flags;
    if (flags & 0x80) {
        SELF(Actor)->vz = saved;
    }
    count              = SELF(Actor)->timer;
    SELF(Actor)->timer = (count - 1);
    Actor_MovementUpdate();
}
