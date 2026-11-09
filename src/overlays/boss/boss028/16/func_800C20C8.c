#include "boss028_16.h"
#include "area/spad.h"

MATCH void func_800C20C8(void) {
    if (!ACTOR_IN_USE(*g_BattleEffectBattler)) {
        g_Task->header.step++;
    }
    Actor_StepAnimLoop();
}
