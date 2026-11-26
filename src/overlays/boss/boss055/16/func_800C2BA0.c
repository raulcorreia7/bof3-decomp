#include "boss055_16.h"

MATCH void func_800C2BA0(void) {
    Boss055ScriptIds scripts;

    scripts = D_800C1828;
    Area_SceneSelectRecord(0x30D);
    SELF(PartyMember)->unk_48      = 0;
    SELF(PartyMember)->unk_24      = 0;
    SELF(PartyMember)->pos.z.fixed = 0;
    Script_Select(scripts.byte[g_Battle.unk_DE]);
    Battle_IsEnemyBlockedOnce();
    Area_AddActor();
    Boss_CopyEffectTransform();
    SELF(PartyMember)->header.step++;
}
