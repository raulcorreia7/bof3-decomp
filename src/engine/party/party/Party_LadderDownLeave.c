#include "engine/game/00/game_00.h"

/* func_801B7E74 */
/* Climbs the actor down out of the area and requests the area change. */
MATCH void Party_LadderDownLeave(void) {
    u16 next;

    next = COORD_INT(TASK(Actor)->pos.z);
    next -= 0x10;
    FIELD(u16, g_Task, 0x3Eu) = next;
    if ((s16)next < Area_HeightRead(D_80146264, D_80146268) - 0x200)
        g_GameStateIndex = GAME_REQUEST_AREA_CHANGE;
    Script_AnimStepLoop();
}
