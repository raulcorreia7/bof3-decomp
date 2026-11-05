#include "area108_14.h"

MATCH void func_801F3F34(void) {
    Actor* actor;

    g_SpadWork->unk_09++;
    actor = g_SpadWork;
    if (actor->unk_09 == 1) {
        Area_SetCellPalette((s16)(actor->x.part.integer + 1), actor->y.part.integer);
    }
    actor = g_SpadWork;
    if (actor->unk_09 == 5) {
        Area_SetCellPalette(actor->x.part.integer, actor->y.part.integer);
    }
    if (g_SpadWork->unk_09 == 0xF) {
        SYS_ClearFlag(g_SceneEventFlags, 0x1C);
        func_80196070();
    }
}
