#include "start_08.h"

/* func_801E3E34 */
MATCH void Menu_SetGlyphPage(u16 line_index) {
    GFX_AddDrawMode(GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 960, line_index));
}
