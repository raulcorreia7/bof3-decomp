#include "boss055_16.h"

MATCH void func_800C2ECC(void) {
    Boss055ScriptIds scripts;

    scripts = D_800C1840;
    Area_SceneSelectRecord(0x318);
    SELF(PartyMember)->unk_48      = 0;
    SELF(PartyMember)->unk_24      = 0;
    SELF(PartyMember)->pos.z.fixed = 0;
    Script_Select(scripts.byte[g_Battle.unk_DE]);
    Battle_IsEnemyBlocked();
    Area_AddActor();
    Boss_CopyEffectTransform();
    SELF(PartyMember)->header.step++;
}
