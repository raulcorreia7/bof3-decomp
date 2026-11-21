#include "engine/slus/slus.h"

/* draws the panel box at the record's 12.4 position words and size words (>> 4), then the D_801490C6 + 1
 * glyph writes of Message_DrawTextRows and the g_MessageChoice glyph of Message_DrawChoiceCursor; state 2 of the g_MessageChoiceSteps step table.
 */
/* func_8015999C */
MATCH void Message_DrawChoicePanel(void) {
    Slus_DrawPanelBox();
    Message_DrawTextRows();
    Message_DrawChoiceCursor();
}
