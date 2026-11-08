#include "game_00.h"

MATCH void func_801B90A0(void) {
    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 7));
    func_801A0048(COORD_INT(g_Task->pos.x), COORD_INT(g_Task->pos.y));
    g_Task->vz = 0;
    Actor_RequestScript(g_Task->direction_08);
    g_Task->unk_03 = 1;
}
