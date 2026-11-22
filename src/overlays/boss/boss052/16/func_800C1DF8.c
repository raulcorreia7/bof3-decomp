#include "boss052_16.h"
#include "area/spad.h"

MATCH void func_800C1DF8(void) {
    u8 type;

    g_Task->param.unk_0B = 0;
    type                 = g_BattleEnemyBattlers[0].type;
    g_Task->timer        = ENCOUNTER_ENEMIES[type].unk_84[2];
    Script_Select(4);
    Script_AnimStepLoop();
    Area_AddActor();
    g_Task->header.step++;
}
