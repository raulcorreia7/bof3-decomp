#include "area172_13.h"

MATCH void func_801F2ED8(void) {
    Actor* saved;
    u8     i;

    saved = g_Task;
    for (i = 0; i < 6; i++) {
        g_Task         = &g_Actors[i];
        g_Task->unk_29 = 2;
        func_8014D290();
    }
    for (i = 0; i < g_PartySize; i++) {
        if (g_BattlePartyBattlers[i].chr.character_id == 7) {
            TASK_SET(&g_BattlePartyBattlers[i]);
            g_Task->unk_29 = 2;
            func_8014D290();
        }
    }
    g_Task = saved;
}
