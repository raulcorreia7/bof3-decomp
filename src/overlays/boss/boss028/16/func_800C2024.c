#include "boss028_16.h"

MATCH void func_800C2024(void) {
    s32 y;

    TASK(PartyMember)->unk_24 = 0;
    TASK(PartyMember)->unk_2A = 0;
    TASK(PartyMember)->unk_48 = 0;
    TASK(PartyMember)->unk_29 = 5;
    Area_SceneSelectRecord(0x15C);
    Script_Select(6U);
    TASK(PartyMember)->pos.x.fixed      = g_BattleEffectBattler->pos.x.fixed;
    y                                   = g_BattleEffectBattler->pos.y.fixed;
    TASK(PartyMember)->pos.y.fixed      = y;
    COORD_INT(TASK(PartyMember)->pos.z) = Area_HeightSample(TASK(PartyMember)->pos.x.fixed, y);
    TASK(PartyMember)->header.step += 1;
}
