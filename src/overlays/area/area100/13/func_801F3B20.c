#include "area100_13.h"

MATCH void func_801F3B20(void) {
    SYS_SetFlag(g_SceneEventFlags, 69);
    Area_CellSetPalette(74, 30);
    SND_SEPlay(265);
    Area_CellSetCode(73, 30, 161);
    Area_CellSetCode(73, 31, 161);
    Area_CellSetCode(77, 51, 161);
    Area_CellSetCode(77, 52, 161);
}
