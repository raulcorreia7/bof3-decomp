#include "area041_13.h"

MATCH void func_801F4118(void) {
    PartyMember* cur;

    cur = g_Game.current;
    g_Task->pos.x.fixed += g_Task->vx;
    g_PaletteFades[cur->palette_fade].offset.r += 2;
    g_PaletteFades[g_Game.current->palette_fade].offset.g += 2;
    g_PaletteFades[g_Game.current->palette_fade].offset.b += 2;
}
