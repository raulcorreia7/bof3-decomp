#include "area168_13.h"

MATCH void func_801F4634(void) {
    u8* state;

    if (g_AreaSceneMode & g_Task->param.unk_0B) {
        state = &g_GameStateIndex;
        if (*state != 2) {
            func_801A4BC0(g_Task->pos.x.part.integer, g_Task->pos.y.part.integer, 0xA1);
            func_801A4BC0(g_Task->pos.x.part.integer, g_Task->pos.y.part.integer + 1, 0xA1);
            if (*state == 0) {
                SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0));
            }
            g_Task->header.step++;
        }
    }
    Area_Update();
}
