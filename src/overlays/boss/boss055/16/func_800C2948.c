#include "boss055_16.h"

MATCH void func_800C2948(void) {
    Boss055Scripts scripts;

    scripts = D_800C1810;
    if (g_BattleEffectBattler->param.unk_0B != 0) {
        Actor_SelectScript(scripts.byte[D_801463BE]);
    }
    func_801E30F8();
    Area_AddActor();
    Boss_CopyEffectTransform();
}
