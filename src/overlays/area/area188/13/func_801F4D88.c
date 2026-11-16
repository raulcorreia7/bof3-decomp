#include "area188_13.h"

MATCH void func_801F4D88(void) {
    if (g_GameLastCellType == 1) {
        if (g_GameCellType == 4) {
            D_80147ACF = 0xC;
        }
    }
    if (g_GameLastCellType == 4) {
        if (g_GameCellType == 1) {
            D_80147ACF = 0xE;
        }
    }
}
