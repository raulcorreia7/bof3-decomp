#include "engine/slus/slus.h"

/* draws the panel box at the record's 12.4 position words and size words (>> 4), then the D_801490C6 + 1
 * glyph writes of UI_DrawTextRows and the g_MessageChoice glyph of Menu_DrawMessageChoiceCursor; state 2 of the g_MessageChoiceSteps step table.
 */
/* func_8015999C */
MATCH void Menu_DrawMessageChoice(void) {
    Slus_DrawPanelBox();
    UI_DrawTextRows();
    Menu_DrawMessageChoiceCursor();
}
