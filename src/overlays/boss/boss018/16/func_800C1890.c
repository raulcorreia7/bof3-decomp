#include "boss018_16.h"

MATCH void func_800C1890(void) {
    EnemyBattler* work;

    if (SYS_TestFlag(g_SceneFlags, 0x35) != 0) {
        g_BattleCurrentEnemy->hp = D_801FD700;
        g_BattleCurrentEnemy->ap = D_801FD6FE;
    } else {
        SYS_SetFlag(g_SceneFlags, 0x35);
    }
    work         = g_BattleCurrentEnemy;
    work->script = D_800C2C38;
    work->unk_E4 = func_800C197C;
    work->unk_E8 = D_800C2C8C;
    ACTOR_SET_STEP(1);
    Actor_RequestScript(2);
    func_8014D978();
}
