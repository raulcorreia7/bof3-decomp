#include "boss025_13.h"

MATCH void func_800C1E34(void) {
    if ((D_801462EC & 0x2800) != 0x800) {
        if (g_BattleCurrentEnemy->turn.damage_flags.value & BATTLER_DAMAGE_DEFENDING) {
            Battle_RequestEnemyScript(8);
        } else {
            Battle_RequestEnemyScript(0);
        }
    } else {
        Script_Request(0xC);
    }
    func_801E30F8();
    SELF(PartyMember)->header.mode++;
}
