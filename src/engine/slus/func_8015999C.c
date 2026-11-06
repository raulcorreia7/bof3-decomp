#include "engine/slus/slus.h"

/* draws the panel box at the record's 12.4 position words and size words (>> 4), then the D_801490C6 + 1
 * glyph writes of func_8015A170 and the g_MessageChoice glyph of func_8015A264; state 2 of the D_80149B50 step table.
 */
MATCH void func_8015999C(void) {
    Slus_DrawPanelBox();
    func_8015A170();
    func_8015A264();
}
