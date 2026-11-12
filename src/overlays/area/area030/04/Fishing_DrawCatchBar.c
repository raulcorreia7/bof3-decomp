#include "area030_04.h"

/* Submits the two AREA030 panel updates at the requested vertical
 * positions after selecting graphics mode 0. */
/* func_801E0ED0 */
MATCH void Fishing_DrawCatchBar(s16 panel_x, s16 panel_y) {
    Fishing_SetDrawMode(0, 1);
    Fishing_DrawSprite(0, 1, (panel_x + 8), panel_y);
    Fishing_DrawSprite(1, 1, (panel_x + 264), panel_y);
}
