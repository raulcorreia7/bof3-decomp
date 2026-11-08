/* The dark ring of magic053 and magic226: radius from the effect param byte (0x0B), twice that outside, and an
 * inner shade of four times the effect timer (byte 0x0A). */
#include "overlays/bmagic/BMagic_DarkRingQuads.h"

/* func_801EFA30 (magic053), func_801EFA64 (magic226) */
MATCH void BMagic_DrawDarkRing(void) {
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(0, 2, 320, 256), 0);
    GFX_AddPrim(5, sizeof(DR_MODE));
    D_1F800000.view.effect.params[0] = g_Task->param.unk_0B;
    D_1F800000.view.effect.params[1] = g_Task->param.unk_0B * 2;
    D_1F800000.view.effect.params[5] = g_Task->timer * 4;
    BMAGIC_DRAW_DARK_RING_QUADS(5, 5);
}
