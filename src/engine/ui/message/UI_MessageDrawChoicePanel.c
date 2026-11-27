#include "engine/slus/slus.h"

/* draws the panel box at the record's 12.4 position words and size words (>> 4), then the D_801490C6 + 1
 * glyph writes of UI_MessageDrawTextRows and the g_UIMessageChoice glyph of UI_MessageDrawChoiceCursor; state 2 of the g_UIMessageChoiceSteps step table.
 */
/* func_8015999C */
MATCH void UI_MessageDrawChoicePanel(void) {
    Slus_DrawPanelBox();
    UI_MessageDrawTextRows();
    UI_MessageDrawChoiceCursor();
}
