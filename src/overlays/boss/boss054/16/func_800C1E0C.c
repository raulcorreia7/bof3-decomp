#include "boss054_16.h"

#define g_Task ((PartyMember*)g_Task)

MATCH void func_800C1E0C(void) {
    Area_SelectSceneRecord(467);
    if (g_Battle.target_selector < 3) {
        g_Task->pos.x = g_Game.members[g_Battle.target_selector].pos.x;
        g_Task->pos.y = g_Game.members[g_Battle.target_selector].pos.y;
    } else {
        g_Task->pos.x = ENEMY_COMBATANT(g_Battle.target_selector).pos.x;
        g_Task->pos.y = ENEMY_COMBATANT(g_Battle.target_selector).pos.y;
    }
    g_Task->unk_20 = -16;
    COORD_INT(g_Task->pos.z) += 0x800;
    g_Task->unk_14 = 0;
    g_Task->unk_5D = 0;
    g_Task->unk_5E = 0;
    g_Task->unk_5F = 0;
    g_Task->unk_5C = 0;
    g_Task->unk_24 = 0;
    g_Task->unk_48 = 0;
    g_Task->unk_2A = 0;
    g_Task->unk_29 = 2;
    Script_Select(3);
    g_Task->header.step++;
}
