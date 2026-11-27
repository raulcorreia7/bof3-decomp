#include "boss032_16.h"

MATCH void Boss_EndBattle(void) {
    volatile u8* entry;

    Battle_ShowActorEntry(0);
    entry          = func_800AC754(0);
    g_CurrentActor = entry;
    SELF_SET(entry);
    Script_Select(0);
}
