#include "area077_14.h"

MATCH void func_801F4550(s32 arg0, s16 x) {
    MATRIX matrix;

    GFX_AddDitheredDrawMode(1, GetTPage(0, 1, 0x380, 0x100));
    Area_SetCameraMatrix(&matrix);
    func_801F462C(arg0, x >> 2, 0x20, 0);
    func_801F462C(arg0, (x * 2) >> 2, 0x20, 0);
    func_801F462C(arg0, (x * 3) >> 2, 0x20, 0);
    func_801F462C(arg0, x, 0x20, 0);
}
