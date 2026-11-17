#include "engine/slus/slus.h"

/* draws the panel box at the record's 12.4 position words and size words (>> 4), then the D_801490C5 glyph
 * writes of Menu_DrawMessagePresetRows and the g_MessageChoice scaled glyph of Menu_DrawMessagePresetCursor; state 2 of the g_MessagePresetSteps step table.
 */
/* func_80159B38 */
MATCH void Menu_DrawMessagePreset(void) {
    Slus_DrawPanelBox();
    Menu_DrawMessagePresetRows();
    Menu_DrawMessagePresetCursor();
}
