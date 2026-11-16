#include "area077_14.h"

MATCH void func_801F564C(void) {
    ((Actor*)g_Task)->timer = 0;
    if (SYS_TestFlag(g_SceneEventFlags, 7)) {
        ((Actor*)g_Task)->header.step = 3;
    } else {
        Area_CopyPaletteRow(3, 0, 3, 3);
        ((Actor*)g_Task)->header.step++;
    }
}
