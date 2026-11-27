#include "boss028_16.h"

MATCH void func_800C20C8(void) {
    if (!ACTOR_IN_USE(*g_BattleEffectBattler)) {
        SELF(Actor)->header.step++;
    }
    Script_AnimStepLoop();
}
