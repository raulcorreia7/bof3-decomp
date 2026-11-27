#include "boss055_16.h"

MATCH u8 func_800C1DD0(void) {
    if (!EMI_IsReady()) {
        return 4;
    }
    if (g_BattleCurrentEnemy->turn.command.type == BATTLE_COMMAND_ABILITY) {
        if (BATTLE_IS_SCRIPTED()) {
            if (func_801DDF50((g_BattleCurrentEnemy->unk_F0 + 0x20) & BYTE_MASK, D_801463CD) != 0) {
                g_Battle.unk_DE = 0;
            } else {
                SELF(PartyMember)->unk_09 = 0x1E;
            }
        }
    } else {
        SELF(PartyMember)->unk_09 = 0;
    }
    if (!(D_801CA71C[g_Battle.action_id].mask & 0x800)) {
        SELF(PartyMember)->unk_09 = ENCOUNTER_ENEMIES[g_BattleCurrentEnemy->type].unk_84[3];
        switch (g_Battle.action_id) {
            case ABILITY_SANCTUARY:
                func_800C2340(5, 4, 7);
                Battle_RequestEnemyScript(10);
                break;
            case ABILITY_HOLOCAUST:
                func_800C2340(6, 4, 6);
                Battle_RequestEnemyScript(10);
                break;
            case ABILITY_VENOM:
                func_800C2340(3, 4, 5);
                Battle_RequestEnemyScript(6);
                break;
            default:
                func_800C2340(3, 4, 3);
                Battle_RequestEnemyScript(10);
                break;
        }
        SELF(PartyMember)->header.step++;
    } else {
        SELF(PartyMember)->header.mode++;
    }
    func_801E3160();
}
