#include "boss012_16.h"

/* hint: shadow quad (GFX_SET_DRAW_MODE, POLY_FT4, PartyBattler view, depth = unk_20 - 0x3C) matches to the y2 store; retail stores x3 before the u/v bytes and loads the y3 cells ahead of them, the candidate stores x3 after the u/v bytes (reloads g_Task). */
INCLUDE_ASM(func_800C1CD8);
