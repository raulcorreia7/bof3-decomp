#include "boss054_16.h"

MATCH void func_800C1E0C(void) {
    Area_SceneSelectRecord(467);
    if (g_Battle.target_selector < 3) {
        SELF(PartyMember)->pos.x = g_Game.members[g_Battle.target_selector].pos.x;
        SELF(PartyMember)->pos.y = g_Game.members[g_Battle.target_selector].pos.y;
    } else {
        SELF(PartyMember)->pos.x = ENEMY_COMBATANT(g_Battle.target_selector).pos.x;
        SELF(PartyMember)->pos.y = ENEMY_COMBATANT(g_Battle.target_selector).pos.y;
    }
    SELF(PartyMember)->unk_20 = -16;
    COORD_INT(SELF(PartyMember)->pos.z) += 0x800;
    SELF(PartyMember)->unk_14 = 0;
    SELF(PartyMember)->unk_5D = 0;
    SELF(PartyMember)->unk_5E = 0;
    SELF(PartyMember)->unk_5F = 0;
    SELF(PartyMember)->unk_5C = 0;
    SELF(PartyMember)->unk_24 = 0;
    SELF(PartyMember)->unk_48 = 0;
    SELF(PartyMember)->unk_2A = 0;
    SELF(PartyMember)->unk_29 = 2;
    Script_Select(3);
    SELF(PartyMember)->header.step++;
}
