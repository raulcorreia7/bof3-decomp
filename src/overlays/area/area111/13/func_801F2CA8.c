#include "area111_13.h"

MATCH void func_801F2CA8(void) {
    Actor* work = g_Task;

    work->timer    = 40;
    work->screen_x = 0;
    work->screen_y = 256;
    g_Task->header.mode++;
    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x06));
}
