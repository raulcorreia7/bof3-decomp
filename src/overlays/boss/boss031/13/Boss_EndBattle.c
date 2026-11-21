#include "boss031_13.h"
#include "area/spad.h"

MATCH void Boss_EndBattle(void) {
    volatile u8* entry;

    Battle_ShowActorEntry(0);
    entry          = func_800AC754(0);
    g_CurrentActor = entry;
    TASK_SET(entry);
    Script_Select(1);
    g_Task->mirror = 1;
}
