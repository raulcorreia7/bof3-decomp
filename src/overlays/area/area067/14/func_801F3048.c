#include "area067_14.h"

MATCH void func_801F3048(void) {
    AreaRippleQuad* quad;
    u8              timer;

    quad = (AreaRippleQuad*)&g_Task->vx;
    func_801F3AD8(quad);
    quad->radius -= 8;
    ACTOR_COUNT_DOWN(timer, timer);
    if (timer == 0) {
        g_ScriptVars[0] = 0x31;
        quad->radius    = 2;
        quad->height    = 0;
        g_Task->timer   = 15;
        g_Task->header.mode++;
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 3));
    }
}
