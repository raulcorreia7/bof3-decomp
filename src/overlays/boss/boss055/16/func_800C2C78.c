#include "boss055_16.h"

MATCH void func_800C2C78(void) {
    func_801E30F8();
    if (g_BattleEffectBattler->header.mode == 2) {
        func_801E5988();
    } else {
        Area_AddActor();
        Boss_CopyEffectTransform();
    }
}
