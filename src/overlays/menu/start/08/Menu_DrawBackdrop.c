#include "start_08.h"

void func_801E7514(s32 x, s32 y, s32 icon, s32 palette); /* extern */

/* func_801E7608 */
MATCH void Menu_DrawBackdrop(void) {
    GFX_ADD_LAYER_DRAW_MODE(GFX_LAYER_EFFECT_FRONT, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 704, 256));
    func_801E7514(0x1A, 0x18, 0, 2);
    func_801E7514(0x10A, 0x88, 1, 2);
    GFX_ADD_LAYER_DRAW_MODE(GFX_LAYER_EFFECT_FRONT, getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 576, 256));
    func_801E7514(-6, 0x1C, 2, 2);
    func_801E7514(0xDA, 0x1C, 3, 2);
}
