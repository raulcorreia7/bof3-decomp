#include "area108_14.h"

MATCH void func_801F3F34(void) {
    Actor* actor;

    g_Task->unk_09++;
    actor = g_Task;
    if (actor->unk_09 == 1) {
        Area_SetCellPalette((s16)(COORD_INT(actor->pos.x) + 1), COORD_INT(actor->pos.y));
    }
    actor = g_Task;
    if (actor->unk_09 == 5) {
        Area_SetCellPalette(COORD_INT(actor->pos.x), COORD_INT(actor->pos.y));
    }
    if (g_Task->unk_09 == 0xF) {
        SYS_ClearFlag(g_SaveData.scene_event_flags, 0x1C);
        Actor_Clear();
    }
}
