#include "area130_13.h"

MATCH void func_801F322C(void) {
    Actor* work;
    Actor* next;

    work           = g_Task;
    work->unk_32   = g_Actors[2].unk_32;
    work->timer    = 20;
    next           = g_Task;
    next->vx       = 0;
    next->vy       = 0;
    next->screen_x = g_Actors[2].screen_x;
    next->screen_y = g_Actors[2].screen_y;
    next->header.mode++;
}
