#include "boss055_16.h"

MATCH void func_800C2FA4(void) {
    if (g_BattleEffectBattler->header.mode == 2) {
        Effect_Reset();
    } else {
        func_801E30F8();
        Area_AddActor();
        Boss_CopyEffectTransform();
    }
}
