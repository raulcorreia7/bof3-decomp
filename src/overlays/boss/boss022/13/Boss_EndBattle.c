#include "boss022_13.h"

MATCH void Boss_EndBattle(void) {
    Battle_ShowActorEntry(0);
    SELF_SET(func_800AC754(0));
    Area_SceneSelectRecord(0xAA);
    SELF(Actor)->mirror = 0;
    SELF(Actor)->unk_48 = 0;
    Script_Select(6);
}
