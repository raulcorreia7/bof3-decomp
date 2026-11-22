#include "boss022_13.h"

MATCH void Boss_EndBattle(void) {
    Battle_ShowActorEntry(0);
    TASK_SET(func_800AC754(0));
    Area_SceneSelectRecord(0xAA);
    TASK(Actor)->mirror = 0;
    TASK(Actor)->unk_48 = 0;
    Script_Select(6);
}
