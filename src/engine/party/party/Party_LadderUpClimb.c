#include "engine/game/00/game_00.h"

/* func_801B7B54 */
/* Raises the actor up the ladder to the dismount height. */
MATCH void Party_LadderUpClimb(void) {
    u16 next;

    next = COORD_INT(SELF(Actor)->pos.z);
    next += 0x10;
    FIELD(u16, g_Self, 0x3Eu) = next;
    if ((s16)next >= Area_HeightRead(D_80146264, D_80146268) - g_AreaClimbHeightOffsets[g_Game.current->chr.character_id]) {
        Area_ClimbDismountBegin();
        SELF(Actor)->unk_04++;
    } else {
        Script_AnimStepLoop();
    }
}
