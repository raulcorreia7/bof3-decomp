#include "boss054_16.h"

MATCH void func_800C1E0C(void) {
    Area_SceneSelectRecord(467);
    if (g_Battle.target_selector < 3) {
        TASK(PartyMember)->pos.x = g_Game.members[g_Battle.target_selector].pos.x;
        TASK(PartyMember)->pos.y = g_Game.members[g_Battle.target_selector].pos.y;
    } else {
        TASK(PartyMember)->pos.x = ENEMY_COMBATANT(g_Battle.target_selector).pos.x;
        TASK(PartyMember)->pos.y = ENEMY_COMBATANT(g_Battle.target_selector).pos.y;
    }
    TASK(PartyMember)->unk_20 = -16;
    COORD_INT(TASK(PartyMember)->pos.z) += 0x800;
    TASK(PartyMember)->unk_14 = 0;
    TASK(PartyMember)->unk_5D = 0;
    TASK(PartyMember)->unk_5E = 0;
    TASK(PartyMember)->unk_5F = 0;
    TASK(PartyMember)->unk_5C = 0;
    TASK(PartyMember)->unk_24 = 0;
    TASK(PartyMember)->unk_48 = 0;
    TASK(PartyMember)->unk_2A = 0;
    TASK(PartyMember)->unk_29 = 2;
    Script_Select(3);
    TASK(PartyMember)->header.step++;
}
