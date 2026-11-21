#include "boss051_16.h"

MATCH void func_800C1B14(void) {
    PartyMember* saved;
    PartyMember* battler;
    PartyMember* work;
    u8           type;

    g_Task->header.mode += 1;
    type           = g_BattleEnemyBattlers[0].type;
    g_Task->unk_09 = ENCOUNTER_ENEMIES[type].unk_84[2];
    g_Task->timer  = 45;

    battler = g_BattleEffectBattler;
    saved   = g_Task;
    TASK_SET(battler);
    battler->unk_24 |= 0x80;

    work         = g_Task;
    work->unk_29 = 2;
    work->screen_x.value += 0x30;
    work->screen_y.value -= 0x10;

    Actor_SelectScript(2);
    TASK_SET(saved);
}
