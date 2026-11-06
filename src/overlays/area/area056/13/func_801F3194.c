#include "area056_13.h"

MATCH void func_801F3194(void) {
    MESSAGE_REQUEST_CLEAR();
    if (g_MessageChoice == 1) {
        *D_80145E91 = 2;
        *D_80145E92 = 7;
        *D_80145E93 = 0;
        Area_SetCellPalette(D_80145EC6, D_80145ECA);
    }
}
