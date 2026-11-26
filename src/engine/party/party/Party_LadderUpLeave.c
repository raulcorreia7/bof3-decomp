#include "engine/game/00/game_00.h"

/* func_801B7988 */
/* Climbs the actor up out of the area and requests the area change. */
MATCH void Party_LadderUpLeave(void) {
    u16 next;

    next = COORD_INT(TASK(Actor)->pos.z);
    next += 0x10;
    COORD_INT(TASK(Actor)->pos.z) = next;
    if ((s16)next > Area_HeightRead(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed) + 0x200)
        g_GameStateIndex = GAME_REQUEST_AREA_CHANGE;
    Script_AnimStepLoop();
}
