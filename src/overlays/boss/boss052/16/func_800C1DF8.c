#include "boss052_16.h"

MATCH void func_800C1DF8(void) {
    u8 type;

    TASK(Actor)->param.unk_0B = 0;
    type                      = g_BattleEnemyBattlers[0].type;
    TASK(Actor)->timer        = ENCOUNTER_ENEMIES[type].unk_84[2];
    Script_Select(4);
    Script_AnimStepLoop();
    Area_AddActor();
    TASK(Actor)->header.step++;
}
