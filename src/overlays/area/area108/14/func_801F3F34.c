#include "area108_14.h"

MATCH void func_801F3F34(void) {
    Actor* actor;

    g_Task->timer++;
    actor = g_Task;
    if (actor->timer == 1) {
        Area_SetCellPalette((s16)(COORD_INT(actor->pos.x) + 1), COORD_INT(actor->pos.y));
    }
    actor = g_Task;
    if (actor->timer == 5) {
        Area_SetCellPalette(COORD_INT(actor->pos.x), COORD_INT(actor->pos.y));
    }
    if (g_Task->timer == 15) {
        SYS_ClearFlag(g_SceneEventFlags, 28);
        Actor_Clear();
    }
}
