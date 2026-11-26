/* The dark ring of magic053 and magic226: radius from the effect param byte (0x0B), twice that outside, and an
 * inner shade of four times the effect timer (byte 0x0A). */
#include "overlays/bmagic/shared/BMagic_DarkRingQuads.h"

/* func_801EFA30 (magic053), func_801EFA64 (magic226) */
MATCH void BMagic_DrawDarkRing(void) {
    GFX_AddDitheredDrawMode(BMAGIC_LAYER_BEHIND_BATTLERS, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 320, 256));
    g_ScratchPad.cells.halves[0] = SELF(PartyMember)->param.unk_0B;
    g_ScratchPad.cells.halves[1] = SELF(PartyMember)->param.unk_0B * 2;
    g_ScratchPad.cells.halves[5] = SELF(PartyMember)->timer * 4;
    BMAGIC_DRAW_DARK_RING_QUADS(BMAGIC_LAYER_BEHIND_BATTLERS, 5);
}
