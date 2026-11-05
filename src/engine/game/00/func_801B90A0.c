#include "game_00.h"

MATCH void func_801B90A0(void) {
    SND_PlayCue(EMI_CUE_ID(1, 7));
    func_801A0048(g_Task->x.part.integer, g_Task->y.part.integer);
    g_Task->vz = 0;
    Actor_RequestScript(g_Task->direction_08);
    g_Task->unk_03 = 1;
}
