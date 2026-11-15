#include "boss055_16.h"

MATCH void func_800C2E04(void) {
    if (func_801E3160() & BYTE_MASK) {
        g_BattleEffectBattler->header.mode += 1;
        g_BattleEffectBattler->header.step = 0;
        func_801E5988();
        return;
    }
    Area_AddActor();
    Boss_CopyEffectTransform();
}
