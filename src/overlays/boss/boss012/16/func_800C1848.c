#include "boss012_16.h"

MATCH void func_800C1848(void) {
    EnemyBattler* work;
    u8*           spad;

    work = g_BattleCurrentEnemy;
    spad = TASK_BYTES;
    EnemyBattler_SetScript(work, D_800C1E14, func_800C1B18, D_800C1E20);
    GFX_StartPaletteAnimation(spad, D_800C1E64);
    ACTOR_SET_MODE(2);
    Actor_StepAnimLoop();
}
