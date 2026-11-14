#include "boss055_16.h"

MATCH void func_800C3134(void) {
    Boss055Scripts scripts;

    scripts = D_800C1858;
    if (g_BattleEffectBattler->param.unk_0B != 0) {
        Actor_SelectScript(scripts.byte[D_801463BE]);
        g_Task->header.step++;
    }
    func_801E30F8();
    Area_AddActor();
    Boss_CopyEffectTransform();
}
