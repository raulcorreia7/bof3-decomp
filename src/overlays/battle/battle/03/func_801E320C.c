#include "battle_03.h"

MATCH void func_801E320C(void) {
    *(u32*)((u32)g_BattleCurrentEnemy + 0xECu) = (g_BattleEnemies - 0x60);
    g_Battle.choose_ending_hook                = Battle_RunDesertDefeat;
    g_Battle.end_hook                          = func_801E57C8;
    Battle_RequestEnemyScript(0);
    SELF(PartyMember)->header.flags |= ACTOR_FLAG_HIDDEN;
    func_801DDAB4(g_BattleCurrentEnemy->status);
    SELF(PartyMember)->header.mode += 1;
}
