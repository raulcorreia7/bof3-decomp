#include "boss052_16.h"

MATCH void func_800C1DF8(void) {
    u8 kind;

    ((Actor*)g_Task)->param.unk_0B = 0;
    kind                           = g_BattleEnemyBattlers[0].kind;
    ((Actor*)g_Task)->timer        = MEM_PTR(u8, 0x800E40CEu)[kind * 0x88u];
    Actor_SelectScript(4);
    Actor_StepAnimLoop();
    Area_AddActor();
    ((Actor*)g_Task)->header.step++;
}
