#include "boss025_13.h"

MATCH void func_800C19C0(void) {
    Actor_RequestScript(0xFU);
    g_Task->unk_2A = 0;
    func_8014DAEC();
    Battle_CollectEnemySpoils();
    g_Task->flags &= ~ACTOR_FLAG_HIDDEN;
    g_Task->mode   = 3;
    g_Task->step   = 0;
    g_Task->unk_03 = 0;
    if (g_BattleEncounter == 0x19) {
        g_MenuPanelMode = 2;
        Message_StartAreaMessage(0x20);
    }
}
