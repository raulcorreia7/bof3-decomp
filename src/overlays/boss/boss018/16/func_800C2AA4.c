#include "boss018_16.h"

MATCH void func_800C2AA4(void) {
    if (!(g_BattleEnemyBattlers[1].status & STATUS_KO)) {
        if (g_BattleEnemyBattlers[1].status & STATUS_LOW_HP) {
            SYS_SetFlag(g_SceneFlags, 52);
            SELF_SET(&g_BattleEnemyBattlers[1]);
            Script_Request(3);
            func_800C29AC(1, 1);
        } else {
            SYS_ClearFlag(g_SceneFlags, 52);
            SELF_SET(&g_BattleEnemyBattlers[1]);
            Script_Request(2);
            func_800C29AC(1, 0);
        }
    }
    if (!(g_BattleEnemyBattlers[2].status & STATUS_KO)) {
        if (g_BattleEnemyBattlers[2].status & STATUS_LOW_HP) {
            SYS_SetFlag(g_SceneFlags, 51);
            SELF_SET(&g_BattleEnemyBattlers[2]);
            Script_Request(3);
            func_800C29AC(0, 1);
        } else {
            SYS_ClearFlag(g_SceneFlags, 51);
            SELF_SET(&g_BattleEnemyBattlers[2]);
            Script_Request(2);
            func_800C29AC(0, 0);
        }
    }
    D_801EB66E                           = Area_HeightSample(D_801EB664, D_801EB668);
    g_Game.members[0].pos.z.part.integer = Area_HeightSample(g_Game.members[0].pos.x.fixed, g_Game.members[0].pos.y.fixed);
    if (g_Game.members[0].u.turn.action_flags.value & 2) {
        D_801EBF5C = g_Game.members[0].pos.z.fixed;
    }
}
