#include "engine/slus/slus.h"

/* draws the panel box at the record's 12.4 position words and size words (>> 4), then the D_801490C5 glyph
 * writes of Message_DrawPresetRows and the g_MessageChoice scaled glyph of Message_DrawPresetCursor; state 2 of the g_MessagePresetSteps step table.
 */
/* func_80159B38 */
MATCH void Message_DrawPresetPanel(void) {
    Slus_DrawPanelBox();
    Message_DrawPresetRows();
    Message_DrawPresetCursor();
}
