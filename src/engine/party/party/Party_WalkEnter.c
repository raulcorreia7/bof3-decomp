#include "engine/game/00/game_00.h"

/* func_801B85C0 */
/* Walks the actor in to its spot, then returns it to mode 1. */
MATCH void Party_WalkEnter(void) {
    u8  delay;
    u8* record;

    if (TASK(Actor)->timer == 0) {
        delay               = TASK(Actor)->unk_0A - 1;
        TASK(Actor)->unk_0A = delay;
        if ((delay & BYTE_MASK) == 0) {
            if (TASK(Actor)->unk_05 == 0) {
                g_AreaWalkFlags &= ~AREA_WALK_ENTRY_ACTIVE;
            }
            g_Game.current->u.field.counter.value = 3;
            record                                = (u8*)g_Game.current;
            TASK(Actor)->vx                       = 0;
            TASK(Actor)->vy                       = 0;
            record[0x12B]                         = 0;
            TASK(Actor)->header.mode              = 1;
            ACTOR_CLEAR_STEP();
            TASK(Actor)->unk_03 = 0;
            TASK(Actor)->timer  = 0;
            TASK(Actor)->unk_0A = 0;
            Script_Request(TASK(Actor)->direction);
            return;
        }
        Area_RunWalk();
    }
    TASK(Actor)->timer = (TASK(Actor)->timer - 1);
    Actor_MovementUpdate();
    Script_AnimStepLoop();
}
