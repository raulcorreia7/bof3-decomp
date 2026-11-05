#include "boss012_16.h"

MATCH void func_800C1848(void) {
    EnemyBattler* work;
    u8*           spad;

    work         = g_BattleCurrentEnemy;
    spad         = TASK_BYTES;
    work->script = D_800C1E14;
    work->unk_E4 = func_800C1B18;
    work->unk_E8 = D_800C1E20;
    GFX_StartPaletteAnimation(spad, D_800C1E64);
    ACTOR_SET_STEP(2);
    func_8014D978();
}
