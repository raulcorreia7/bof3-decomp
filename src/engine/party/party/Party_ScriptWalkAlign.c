#include "engine/game/00/game_00.h"

/* func_801B6AB0 */
/* Snaps the actor onto the half-cell grid, then starts reading its script. */
MATCH void Party_ScriptWalkAlign(void) {
    s32 x;

    x = SELF(Actor)->pos.x.fixed;
    if ((((x & 0x7FFF) != 0) || ((SELF(Actor)->pos.y.fixed & 0x7FFF) != 0)) && ((SELF(Actor)->active_flags & 0x20) == 0)) {
        SELF(Actor)->pos.x.fixed      = (x + 0x4800) & ~0x7FFF;
        SELF(Actor)->pos.y.fixed      = (SELF(Actor)->pos.y.fixed + 0x4800) & ~0x7FFF;
        COORD_INT(SELF(Actor)->pos.z) = Area_HeightReadStep(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, SELF(Actor)->direction);
        Script_Request((SELF(Actor)->direction + 8) & BYTE_MASK);
        if (((SELF(Actor)->pos.x.fixed & 0x7FFF) == 0) && ((SELF(Actor)->pos.y.fixed & 0x7FFF) == 0)) {
            Script_Request(SELF(Actor)->direction);
        }
    } else {
        Actor_ClearVelocity();
        SELF(Actor)->unk_03++;
        Party_ScriptWalkRead();
    }
}
