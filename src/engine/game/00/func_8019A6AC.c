#include "game_00.h"

MATCH void func_8019A6AC(void) {
    Actor* work;

    g_Task->timer--;
    if (g_Task->timer == 0) {
        g_Task->header.mode++;
        return;
    }
    g_Task->tint.bytes.rgb.red -= 6;
    g_Task->tint.bytes.rgb.green -= 6;
    g_Task->tint.bytes.rgb.blue -= 6;
    Actor_StepAnimLoop();
    work = g_Task;
    if (work->unk_05 == 6) {
        if ((work->timer & 0x1) != 0) {
            work->screen_y++;
        }
        Area_AddActor();
    } else {
        if ((work->timer & 0x1) != 0) {
            work->vy--;
        }
        Area_AddGridActor();
    }
}
