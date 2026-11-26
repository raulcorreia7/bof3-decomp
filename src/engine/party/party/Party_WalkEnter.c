#include "engine/game/00/game_00.h"

/* func_801B85C0 */
/* Walks the actor in to its spot, then returns it to mode 1. */
MATCH void Party_WalkEnter(void) {
    u8  delay;
    u8* record;

    if (SELF(Actor)->timer == 0) {
        delay               = SELF(Actor)->unk_0A - 1;
        SELF(Actor)->unk_0A = delay;
        if ((delay & BYTE_MASK) == 0) {
            if (SELF(Actor)->unk_05 == 0) {
                g_AreaWalkFlags &= ~AREA_WALK_ENTRY_ACTIVE;
            }
            g_Game.current->u.field.counter.value = 3;
            record                                = (u8*)g_Game.current;
            SELF(Actor)->vx                       = 0;
            SELF(Actor)->vy                       = 0;
            record[0x12B]                         = 0;
            SELF(Actor)->header.mode              = 1;
            ACTOR_CLEAR_STEP();
            SELF(Actor)->unk_03 = 0;
            SELF(Actor)->timer  = 0;
            SELF(Actor)->unk_0A = 0;
            Script_Request(SELF(Actor)->direction);
            return;
        }
        Area_RunWalk();
    }
    SELF(Actor)->timer = (SELF(Actor)->timer - 1);
    Actor_MovementUpdate();
    Script_AnimStepLoop();
}
