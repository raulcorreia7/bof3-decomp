#include "area151_13.h"

MATCH void func_801F3194(void) {
    Actor* scratch;
    Actor* scratch2;
    u8     timer;

    Actor_CenterOnScreen();

    scratch        = (Actor*)g_Task;
    timer          = scratch->timer;
    scratch->timer = timer - 1;
    scratch2       = (Actor*)g_Task;
    scratch->scale.x += 0x2000;

    if (scratch2->timer == 0) {
        scratch2->unk_48    = 0;
        g_Task->header.mode = 3;
    }

    Area_AddActor();
}
