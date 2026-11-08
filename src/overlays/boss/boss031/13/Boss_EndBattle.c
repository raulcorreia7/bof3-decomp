#include "boss031_13.h"
#include "area/spad.h"

MATCH void Boss_EndBattle(void) {
    volatile u8* entry;

    func_800AC844(0);
    entry          = func_800AC754(0);
    g_CurrentActor = entry;
    TASK_SET(entry);
    Actor_SelectScript(1);
    g_Task->unk_2A = 1;
}
