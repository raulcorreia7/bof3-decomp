#include "start_08.h"

/* func_801E3E34 */
MATCH void Menu_SetGlyphPage(u16 line_index) {
    GFX_AddDrawMode(GetTPage(0, 1, 960, line_index));
}
