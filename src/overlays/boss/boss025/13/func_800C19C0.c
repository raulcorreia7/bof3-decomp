#include "boss025_13.h"

MATCH void func_800C19C0(void) {
    Actor_RequestScript(0xFU);
    g_Task->unk_2A = 0;
    Actor_StepAnimOnce();
    Battle_DefeatEnemy();
    g_Task->header.flags &= ~ACTOR_FLAG_HIDDEN;
    g_Task->header.mode = 3;
    g_Task->header.step = 0;
    g_Task->unk_03      = 0;
    if (g_Battle.encounter == 0x19) {
        g_MenuPanelMode = 2;
        Message_StartAreaMessage(32);
    }
}
