#include "engine/game/00/game_00.h"

/* func_801B76F4 */
/* Lets the actor fall until it reaches the ground, then starts the landing animation. */
MATCH void Party_JumpFall(void) {
    s16 dist;

    SELF(Actor)->vz += SELF(Actor)->gravity;
    Actor_MovementUpdate();
    dist = Area_HeightRead(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed);
    if ((s16)COORD_INT(SELF(Actor)->pos.z) < dist) {
        COORD_INT(SELF(Actor)->pos.z) = dist;
        if (SELF(Actor)->vz < -0x80) {
            Script_Request((SELF(Actor)->direction >> 1) + 0x34);
        } else if (SELF(Actor)->direction == FACING_RIGHT) {
            Script_Request(0x38);
        } else {
            Script_Request(0x39);
        }
        SELF(Actor)->vz      = 0;
        SELF(Actor)->gravity = 0;
        SELF(Actor)->unk_03  = PARTY_JUMP_STEP_LAND;
    }
    if ((SELF(Actor)->unk_05 == 0) && (((g_Game.flags | g_Game.walk_flags) & (GAME_FLAG_SCROLL_LOCK | AREA_WALK_ENTRY_ACTIVE)) == 0)) {
        Area_ScrollAdvance((s16)COORD_INT(SELF(Actor)->pos.z));
    }
    Script_AnimStepLoop();
}
