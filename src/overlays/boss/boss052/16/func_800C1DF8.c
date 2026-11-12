#include "boss052_16.h"
#include "area/spad.h"

MATCH void func_800C1DF8(void) {
    u8 kind;

    g_Task->param.unk_0B = 0;
    kind                 = g_BattleEnemyBattlers[0].kind;
    g_Task->timer        = ENCOUNTER_ENEMIES[kind].unk_84[2];
    Actor_SelectScript(4);
    Actor_StepAnimLoop();
    Area_AddActor();
    g_Task->header.step++;
}
