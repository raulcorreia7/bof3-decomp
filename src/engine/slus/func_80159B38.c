#include "engine/slus/slus.h"

/* draws the panel box at the record's 12.4 position words and size words (>> 4), then the D_801490C5 glyph
 * writes of func_8015A098 and the g_MessageChoice scaled glyph of func_8015A1D8; state 2 of the D_80149B64 step table.
 */
MATCH void func_80159B38(void) {
    Slus_DrawPanelBox();
    func_8015A098();
    func_8015A1D8();
}
