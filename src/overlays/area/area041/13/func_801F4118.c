#include "area041_13.h"

MATCH void func_801F4118(void) {
    PartyMember* cur;

    cur = g_Game.current;
    g_Task->pos.x.fixed += g_Task->vx;
    g_PaletteFades[cur->unk_13D].offset.red += 2;
    g_PaletteFades[g_Game.current->unk_13D].offset.green += 2;
    g_PaletteFades[g_Game.current->unk_13D].offset.blue += 2;
}
