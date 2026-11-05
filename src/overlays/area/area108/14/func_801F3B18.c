#include "area108_14.h"

MATCH void func_801F3B18(void) {
    Actor* saved = g_Task;
    u8     i;

    for (i = 0; i < g_PartySize; i++) {
        TASK_SET(&g_BattlePartyBattlers[i]);
        g_Task->unk_29 = 6;
    }
    g_Task = saved;
    Actor_Clear();
}
