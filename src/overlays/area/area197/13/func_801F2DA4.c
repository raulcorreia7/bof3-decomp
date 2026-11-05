#include "area197_13.h"

MATCH void func_801F2DA4(void) {
    MATRIX matrix;
    u8     first;
    u8     second;

    if (g_SpadWork->state_02 == 0) {
        g_AreaSceneMode = 1;
        Area_SetCellPalette(2, 0x77);
        g_SpadWork->state_02++;
    }
    Area_SetCameraMatrix(&matrix);
    first = func_801F2FC4();
    second = func_801F3368();
    if (first != 0 || second != 0) {
        return;
    }
    g_SpadWork->unk_01++;
}
