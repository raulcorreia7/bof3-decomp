#include "area008_13.h"

MATCH void func_801F31D0(void) {
    volatile Actor* previous;
    u8*             table;

    previous                  = g_Task;
    WORLD00_AREA008_STATE_PTR = (volatile Actor*)&g_BattlePartyBattlers[1];
    TASK_SET(&g_BattlePartyBattlers[1]);
    Actor_SelectScript(1);
    table        = (u8*)g_GameState;
    table[0x118] = (u8)(table[0x118] & 0xBF);
    g_Task       = previous;
    Actor_Clear();
}
