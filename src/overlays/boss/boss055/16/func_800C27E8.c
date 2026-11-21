#include "boss055_16.h"

MATCH void func_800C27E8(void) {
    Boss055ScriptIds scripts;

    scripts = D_800C1804;
    if (g_BattleEffectBattler->param.unk_0B != 0) {
        Script_Select(scripts.byte[g_Battle.unk_DE]);
    }
    func_801E30F8();
    Area_AddActor();
    Boss_CopyEffectTransform();
}
