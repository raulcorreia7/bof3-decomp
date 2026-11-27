#include "engine/slus/slus.h"

/* draws the panel box at the record's 12.4 position words and size words (>> 4), then the D_801490C5 glyph
 * writes of UI_MessageDrawPresetRows and the g_UIMessageChoice scaled glyph of UI_MessageDrawPresetCursor; state 2 of the g_UIMessagePresetSteps step table.
 */
/* func_80159B38 */
MATCH void UI_MessageDrawPresetPanel(void) {
    Slus_DrawPanelBox();
    UI_MessageDrawPresetRows();
    UI_MessageDrawPresetCursor();
}
