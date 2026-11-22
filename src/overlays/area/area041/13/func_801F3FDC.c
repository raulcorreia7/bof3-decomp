#include "area041_13.h"

MATCH void func_801F3FDC(void) {
    PartyMember* cur;

    cur = g_Game.current;
    TASK(Actor)->pos.x.fixed += TASK(Actor)->vx;
    g_PaletteFades[cur->palette_fade].offset.r -= 2;
    g_PaletteFades[g_Game.current->palette_fade].offset.g -= 2;
    g_PaletteFades[g_Game.current->palette_fade].offset.b -= 2;
    TASK(Actor)->unk_0A--;
    if (TASK(Actor)->unk_0A == 0) {
        TASK(Actor)->unk_04 = 0;
    } else {
        g_Game.current->u.field.unk_122 -= 2;
    }
}
