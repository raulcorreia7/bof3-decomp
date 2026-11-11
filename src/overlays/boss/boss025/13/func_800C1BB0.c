#include "boss025_13.h"

extern u8  D_800C3174[];
extern u16 D_800C318C[];
void       func_800C1D2C(u8 index);
extern u16 D_80144E00;
extern u16 D_80144E04;
extern u16 D_80144E06;

MATCH void func_800C1BB0(void) {
    EnemyBattler* enemy;
    u16           v;

    enemy         = g_BattleCurrentEnemy;
    enemy->script = D_800C3174;
    enemy->unk_E4 = (ModeFunc)func_800C1D2C;
    enemy->unk_E8 = D_800C318C;

    g_Task->header.mode = 2;
    Actor_StepAnimLoop();
    g_Task->facing = 1;

    g_BattleCurrentEnemy->unk_7F = 1;

    enemy               = g_BattleCurrentEnemy;
    v                   = D_80144E00;
    enemy->hp           = v;
    enemy->base.max_hp  = v;
    enemy->stats.max_hp = v;

    v                  = D_80144E04;
    enemy->base.power  = v;
    enemy->stats.power = v;

    v                    = D_80144E06;
    enemy->base.defense  = v;
    enemy->stats.defense = v;
}
