#include "boss025_13.h"

MATCH void func_800C19C0(void) {
    Actor_RequestScript(0xFU);
    g_SpadWork->unk_2A = 0;
    func_8014DAEC();
    func_801E54EC();
    g_SpadWork->flags_00 &= 0xBF;
    g_SpadWork->step_01 = 3;
    g_SpadWork->unk_02  = 0;
    g_SpadWork->unk_03  = 0;
    if (g_BattleEncounter == 0x19) {
        g_MenuPanelMode = 2;
        Message_StartAreaMessage(0x20);
    }
}
