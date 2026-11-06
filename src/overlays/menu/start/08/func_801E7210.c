#include "start_08.h"

MATCH void func_801E7210(u32 panel_index) {
    u8* src;
    u8* dst;
    u8  a;
    u8  b;
    u8  c;

    panel_index &= BYTE_MASK;
    src    = &s_PanelIconSelectors[panel_index * 3];
    dst    = &D_8014866C[panel_index * 5];
    a      = src[0];
    b      = src[1];
    c      = src[2];
    dst[0] = s_PanelIconValues[func_801E715C(a, b, c) & BYTE_MASK];
    dst[1] = s_PanelIconValues[func_801E715C(a, b, c) & BYTE_MASK];
    dst[2] = s_PanelIconValues[func_801E715C(a, b, c) & BYTE_MASK];
    dst[3] = s_PanelIconValues[func_801E715C(a, b, c) & BYTE_MASK];
    dst[4] = s_PanelIconValues[func_801E715C(a, b, c) & BYTE_MASK];
    dst[0] = 0;
    dst[1] = 0;
    dst[2] = 0;
    dst[3] = 0;
    dst[4] = 0;
}
