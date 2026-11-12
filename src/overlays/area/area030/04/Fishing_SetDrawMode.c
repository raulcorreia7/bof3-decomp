#include "area030_04.h"

/* Builds the texture-page word for the selected AREA030 graphic and
 * appends its draw-mode primitive to the current ordering-table stream. */
/* func_801E0C80 */
MATCH void Fishing_SetDrawMode(s32 graphic, s32 layer) {
    s32 tpage;

    tpage = getTPage(D_801E2384[(graphic & BYTE_MASK) << 2], D_801E2388[(graphic & BYTE_MASK) << 2], D_801E238C[(graphic & BYTE_MASK) << 2], D_801E2390[(graphic & BYTE_MASK) << 2]);

    GFX_SET_DRAW_MODE(tpage);
    GFX_AddPrim((u8)layer, sizeof(DR_MODE));
}
