#include "area171_13.h"

MATCH u8 func_801F3CF0(s32 x, s32 y) {
    s32 cx;
    s32 cy;

    if (D_80143F03 == 2) {
        if (SYS_TestFlag(g_SceneEventFlags, 115) == 0) {
            D_1F800000.view.raw[0] = 0;
            cx                     = x >> 16;
            cy                     = y >> 16;
            if ((Area_GetCellCode(cx, cy) & BYTE_MASK) == 0x89) {
                D_1F800000.view.raw[0] += 1;
            }
            if ((x & HALF_MASK) != 0) {
                if ((Area_GetCellCode((s16)(cx + 1), cy) & BYTE_MASK) == 0x89) {
                    D_1F800000.view.raw[0] += 1;
                }
            }
            if ((y & HALF_MASK) != 0) {
                if ((Area_GetCellCode(x >> 16, (s16)((y >> 16) + 1)) & BYTE_MASK) == 0x89) {
                    D_1F800000.view.raw[0] += 1;
                }
            }
            if ((x & HALF_MASK) != 0 && (y & HALF_MASK) != 0) {
                if ((Area_GetCellCode((s16)((x >> 16) + 1), (s16)((y >> 16) + 1)) & BYTE_MASK) == 0x89) {
                    D_1F800000.view.raw[0] += 1;
                }
            }
            if (D_1F800000.view.raw[0] != 0) {
                Scene_StartEvent(0x30, 0x14);
            }
        }
    }
    return 0;
}
