#include "game_00.h"

MATCH void func_801B7B54(void) {
    u16 next;

    next = COORD_INT(TASK(Actor)->pos.z);
    next += 0x10;
    FIELD(u16, g_Task, 0x3Eu) = next;
    if ((s16)next >= Area_HeightRead(D_80146264, D_80146268) - g_AreaClimbHeightOffsets[g_Game.current->chr.character_id]) {
        Area_ClimbDismountBegin();
        TASK(Actor)->unk_04++;
    } else {
        Script_AnimStepLoop();
    }
}
