#include "boss052_16.h"

MATCH void Boss_EndBattle(void) {
    volatile u8* entry;

    func_800AC844(0);
    entry          = func_800AC754(0);
    g_CurrentActor = entry;
    g_SpadWork     = (u8*)entry;
    Actor_SelectScript(5);
}
