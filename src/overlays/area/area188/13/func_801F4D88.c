#include "area188_13.h"

MATCH void func_801F4D88(void) {
    if (g_GameLastCellType == 1) {
        if (g_GameCellType == 4) {
            g_PartyActors[0].unk_77 = 0xC;
        }
    }
    if (g_GameLastCellType == 4) {
        if (g_GameCellType == 1) {
            g_PartyActors[0].unk_77 = 0xE;
        }
    }
}
