#include "boss031_13.h"

MATCH void Boss_EndBattle(void) {
    volatile u8* entry;

    func_800AC844(0);
    entry          = func_800AC754(0);
    g_CurrentActor = entry;
    TASK_SET(entry);
    Actor_SelectScript(1);
    TASK_BYTES[0x2A] = 1;
}
