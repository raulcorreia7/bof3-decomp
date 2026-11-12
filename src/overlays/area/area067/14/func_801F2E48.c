#include "area067_14.h"

MATCH void func_801F2E48(void) {
    Point2D* vy = (Point2D*)&g_Task->vy;

    g_Task->timer = 90;
    /* FAKE: retail clears vy as two halfword stores. */
    vy->x         = 0;
    vy->y         = 0;
    g_Task->header.mode++;
    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 1));
}
