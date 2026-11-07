#include "area088_13.h"

MATCH s32 func_801F2CE4(void) {
    u8  tick;
    s32 x;

    tick          = g_Task->timer;
    g_Task->timer = tick + 1;
    if (tick == 0) {
        SND_PlayCue(0x200);
    }
    func_801F2F28((u8*)AREA_WORK);
    func_801F3258((u8*)AREA_WORK);
    x                   = g_Task->pos.x.fixed + TO_COORD(1);
    g_Task->pos.x.fixed = x;
    if (x == TO_COORD(23)) {
        g_Task->timer = 0x20;
        g_Task->header.mode++;
    }
}
