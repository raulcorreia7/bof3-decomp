#include "start_08.h"

MATCH void func_801D9664(void) {
    g_MenuPanelTasks[17].handler = 6;
    g_MenuPanelTasks[17].mode    = 0x14;
    D_80148597                   = 2;
    g_MenuPanelTasks[17].active  = 1;
    g_MenuPanelTasks[17].pos.x   = BATTLE_PARTY_STRIDE;
    g_MenuPanelTasks[17].pos.y   = 62;
    g_BattleListCursor           = 0;
    g_MenuPanelTasks[17].unk_0A  = 0;
    g_MenuPanelTasks[17].unk_0C  = 0;
    g_MenuPanelTasks[17].unk_08  = 0;
}
