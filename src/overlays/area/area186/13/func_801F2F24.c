#include "area186_13.h"

MATCH void func_801F2F24(void) {
    if (SYS_TestFlag(g_SceneEventFlags, 88)) {
        if (g_GameLastCellType == 1) {
            func_801F2E58(0xA);
        } else if (g_GameLastCellType == 2) {
            func_801F2E58(0);
        }
    }
}
