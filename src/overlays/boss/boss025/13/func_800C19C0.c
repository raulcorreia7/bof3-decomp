#include "boss025_13.h"

MATCH void func_800C19C0(void) {
    Actor_RequestScript(0xFU);
    ((PartyBattler*)g_SpadWork)->unk_2A = 0;
    func_8014DAEC();
    func_801E54EC();
    ((PartyBattler*)g_SpadWork)->flags_00 &= 0xBF;
    ((PartyBattler*)g_SpadWork)->step_01 = 3;
    ((PartyBattler*)g_SpadWork)->unk_02  = 0;
    ((PartyBattler*)g_SpadWork)->unk_03  = 0;
    if (g_BattleEncounter == 0x19) {
        g_MenuPanelMode = 2;
        Message_StartAreaMessage(0x20);
    }
}
