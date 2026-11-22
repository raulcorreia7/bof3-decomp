#include "area170_13.h"

MATCH void func_801F3838(u16 line_index) {
    GFX_ADD_LAYER_DRAW_MODE(GFX_LAYER_EFFECT_FRONT, GetTPage(TPAGE_DEPTH_4BIT, line_index & BYTE_MASK, 896, 256));
}
