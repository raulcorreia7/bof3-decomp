#include "area100_13.h"

MATCH void func_801F3B9C(void) {
    SYS_SetFlag(g_SceneEventFlags, 0x40);
    Area_SetCellPalette(0x4A, 0x2F);
    Scene_StartEvent(0x1C, 0);
}
