#include "area067_14.h"

MATCH void func_801F2F5C(void) {
    u16* rect;
    s16* row;
    u8   timer;

    /* The quad a mode draws lives in the task's velocity words. */
    rect          = (u16*)&g_Task->vx;
    timer         = g_Task->timer + 1;
    g_Task->timer = timer;
    rect[3] += 0x40;
    rect[4] += 2;
    if (timer == 0xF) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 2));
    }
    func_801F358C(rect);
    /* area.h declares the family's three-argument form; this image's step takes none. */
    ((void (*)(void))func_801F39D8)();
    func_801F3AD8(rect);
    if ((g_FrameCount & 1) != 0) {
        row = func_801F3A9C();
        if (row != NULL) {
            func_801F3D54(row);
        }
    }
    if ((s16)rect[4] >= 0x101) {
        g_Task->timer = 7;
        g_Task->header.mode++;
    }
}
