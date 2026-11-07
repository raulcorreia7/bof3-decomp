#include "area111_13.h"

MATCH void func_801F2CA8(void) {
    Actor* work = g_Task;

    work->timer    = 0x28;
    work->screen_x = 0;
    work->screen_y = 0x100;
    g_Task->header.mode++;
    SND_PlayCue(0x206);
}
