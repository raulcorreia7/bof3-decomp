#include "area067_14.h"

MATCH void func_801F3048(void) {
    AreaRippleQuad* quad;
    u8              timer;

    quad = (AreaRippleQuad*)&SELF(Actor)->vx;
    func_801F3AD8(quad);
    quad->radius -= 8;
    ACTOR_COUNT_DOWN(SELF(Actor), timer, timer);
    if (timer == 0) {
        g_ScriptVars[0]    = 0x31;
        quad->radius       = 2;
        quad->height       = 0;
        SELF(Actor)->timer = 15;
        SELF(Actor)->header.mode++;
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 3));
    }
}
