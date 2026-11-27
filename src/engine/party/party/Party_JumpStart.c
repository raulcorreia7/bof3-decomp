#include "engine/game/00/game_00.h"

/* func_801B73F4 */
/* Starts the jump animation for the actor's facing. */
MATCH void Party_JumpStart(void) {
    u32 route;

    route = SELF(Actor)->direction;
    if (route == FACING_RIGHT) {
        Script_Request(0x38);
    } else {
        Script_Request(0x39);
    }
    g_Game.current->u.field.counter.unsigned_value = 3;
    SELF(Actor)->unk_03                            = PARTY_JUMP_STEP_LAUNCH;
}
