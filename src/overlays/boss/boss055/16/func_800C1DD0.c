#include "boss055_16.h"

MATCH u8 func_800C1DD0(void) {
    if (!EMI_IsReady()) {
        return 4;
    }
    if (g_BattleCurrentEnemy->turn.command.type == BATTLE_COMMAND_ABILITY) {
        if (BATTLE_IS_SCRIPTED()) {
            if (func_801DDF50((g_BattleCurrentEnemy->unk_F0 + 0x20) & BYTE_MASK, D_801463CD) != 0) {
                D_801463BE = 0;
            } else {
                g_Task->unk_09 = 0x1E;
            }
        }
    } else {
        g_Task->unk_09 = 0;
    }
    if (!(D_801CA71C[g_Battle.action_id].mask & 0x800)) {
        g_Task->unk_09 = ENCOUNTER_ENEMIES[g_BattleCurrentEnemy->kind].unk_84[3];
        switch (g_Battle.action_id) {
            case 0x3A:
                func_800C2340(5, 4, 7);
                func_801E2314(10);
                break;
            case 0x81:
                func_800C2340(6, 4, 6);
                func_801E2314(10);
                break;
            case 0x82:
                func_800C2340(3, 4, 5);
                func_801E2314(6);
                break;
            default:
                func_800C2340(3, 4, 3);
                func_801E2314(10);
                break;
        }
        g_Task->header.step++;
    } else {
        g_Task->header.mode++;
    }
    func_801E3160();
}
