#include "area108_14.h"

MATCH void func_801F3F34(void) {
    Actor* actor;

    g_Task->unk_09++;
    actor = g_Task;
    if (actor->unk_09 == 1) {
        Area_SetCellPalette((s16)(COORD_INT(actor->x) + 1), COORD_INT(actor->y));
    }
    actor = g_Task;
    if (actor->unk_09 == 5) {
        Area_SetCellPalette(COORD_INT(actor->x), COORD_INT(actor->y));
    }
    if (g_Task->unk_09 == 0xF) {
        SYS_ClearFlag(g_SceneEventFlags, 0x1C);
        func_80196070();
    }
}
