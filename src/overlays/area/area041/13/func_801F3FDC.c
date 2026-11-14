#include "area041_13.h"

MATCH void func_801F3FDC(void) {
    PartyMember* cur;

    cur = g_Game.current;
    g_Task->pos.x.fixed += g_Task->vx;
    g_PaletteFades[cur->unk_13D].offset.red -= 2;
    g_PaletteFades[g_Game.current->unk_13D].offset.green -= 2;
    g_PaletteFades[g_Game.current->unk_13D].offset.blue -= 2;
    g_Task->unk_0A--;
    if (g_Task->unk_0A == 0) {
        g_Task->unk_04 = 0;
    } else {
        g_Game.current->u.field.unk_122 -= 2;
    }
}
