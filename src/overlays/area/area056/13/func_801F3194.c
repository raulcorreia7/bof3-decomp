#include "area056_13.h"

MATCH void func_801F3194(void) {
    MESSAGE_REQUEST_CLEAR();
    if (g_UIMessageChoice == 1) {
        *D_80145E91 = 2;
        *D_80145E92 = 7;
        *D_80145E93 = 0;
        Area_CellSetPalette(g_Game.members[0].pos.x.part.integer, g_Game.members[0].pos.y.part.integer);
    }
}
