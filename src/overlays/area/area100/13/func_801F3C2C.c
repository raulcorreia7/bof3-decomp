#include "area100_13.h"

MATCH void func_801F3C2C(void) {
    if (SYS_TestFlag(g_SceneEventFlags, 69) == 0) {
        Area_CellSetCode(73, 30, 0x50);
        Area_CellSetCode(73, 31, 0x50);
        Area_CellSetCode(77, 51, 0x50);
        Area_CellSetCode(77, 52, 0x50);
    }
}
