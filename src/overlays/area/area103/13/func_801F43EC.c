#include "area103_13.h"

MATCH void func_801F43EC(void) {
    s32 beat;

    if (*g_ScriptVars == 0xF && (g_FrameCount / 5) % 4 == 3) {
        func_801F4E70(4);
        Area_SetCellPalette(67, 26);
        g_Task->header.step++;
        return;
    }
    beat = g_FrameCount / 5;
    if (g_FrameCount == beat * 5) {
        func_801F4E70(beat & 0x3);
    }
    func_801F49A0(2);
}
