#include "area189_13.h"

MATCH void func_801F3480(void) {
    Area_SelectSceneRecord(680);
    g_Task->active_flags = 0;
    Actor_SelectScript(0);
    g_Task->draw_layer = 6;
    g_Task->unk_48     = 0;
    g_Task->header.step++;
}
