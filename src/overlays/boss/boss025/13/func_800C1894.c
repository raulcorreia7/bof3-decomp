#include "boss025_13.h"

MATCH void func_800C1894(void) {
    EnemyBattler* enemy;
    u16           v;

    enemy         = g_BattleCurrentEnemy;
    enemy->script = D_800C3174;
    enemy->unk_E4 = func_800C1A68;
    enemy->unk_E8 = D_800C318C;

    SELF(PartyMember)->header.mode = 2;
    Script_AnimStepLoop();
    if (g_Battle.encounter == 26) {
        Battle_LoadEnemyBattler(0, func_800AC704(89));
        g_BattleCurrentEnemy->unk_7F = 1;
        g_BattleCurrentEnemy->unk_F0 = 30;

        enemy               = g_BattleCurrentEnemy;
        v                   = g_Characters[CHAR_ID_RYU_ADULT].stats.max_hp;
        enemy->hp           = v;
        enemy->base.max_hp  = v;
        enemy->stats.max_hp = v;

        v                  = g_Characters[CHAR_ID_RYU_ADULT].stats.power;
        enemy->base.power  = v;
        enemy->stats.power = v;

        v                    = g_Characters[CHAR_ID_RYU_ADULT].stats.defense;
        enemy->base.defense  = v;
        enemy->stats.defense = v;
    }
}
