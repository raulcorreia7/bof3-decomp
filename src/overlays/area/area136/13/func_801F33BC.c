#include "area136_13.h"

MATCH void func_801F33BC(void) {
    if (g_GameLastCellType == 1 && g_GameCellType == 4) {
        g_PartyActors[0].unk_77 = 2;
    }
    if (g_GameLastCellType == 4 && g_GameCellType == 1) {
        g_PartyActors[0].unk_77 = 4;
    }
}
