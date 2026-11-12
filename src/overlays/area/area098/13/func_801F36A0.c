#include "area098_13.h"

MATCH void func_801F36A0(void) {
    Actor* work;

    if (g_Task->timer == 20) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x05));
    }
    if (g_Task->timer < 21U) {
        g_Task->timer += 1;
    }
    func_801F4490(&g_Task->pos, g_Task->vx, g_Task->vy);
    work = g_Task;
    work->unk_18 += 128;
    work->unk_1C += 140;
    work->vx -= work->unk_18;
    work->vy -= work->unk_1C;
    if (work->vx < 0) {
        work->vx = 0;
    }
    if (g_Task->vy < 0) {
        g_Task->vy = 0;
    }
    if (func_801F42E8() == 0) {
        if ((g_Task->vx == 0) && (g_Task->vy == 0)) {
            Actor_Clear();
        }
    }
}
