#include "area030_04.h"

/* Draws the AREA030 panel header row through the shared helper at
 * `0x801D9534`. */
/* func_801D3908 */
MATCH void Fishing_DrawPanelHeader(void) {
    Fishing_DrawWindowFrame(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, 0);
}
