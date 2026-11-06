#include "area030_04.h"

/* Builds the texture-page word for the selected AREA030 graphic and
 * appends its draw-mode primitive to the current ordering-table stream. */
MATCH void func_801E0C80(s32 graphic, s32 layer) {
    s32 tpage;

    tpage = getTPage(D_801E2384[(graphic & 0xFF) << 2], D_801E2388[(graphic & 0xFF) << 2],
                     D_801E238C[(graphic & 0xFF) << 2], D_801E2390[(graphic & 0xFF) << 2]);

    GFX_SET_DRAW_MODE(tpage);
    GFX_AddPrim((u8)layer, 0x0C);
}
