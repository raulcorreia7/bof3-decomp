#include "area197_13.h"

MATCH void func_801F2DA4(void) {
    MATRIX matrix;
    u8     first;
    u8     second;

    if (g_Task->header.step == 0) {
        g_AreaSceneMode = 1;
        Area_SetCellPalette(2, 119);
        g_Task->header.step++;
    }
    Area_SetCameraMatrix(&matrix);
    first  = func_801F2FC4();
    second = func_801F3368();
    if (first != 0 || second != 0) {
        return;
    }
    g_Task->header.mode++;
}
