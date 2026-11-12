#include "boss033_16.h"

MATCH void Boss_ChooseBattleEnding(void) {
    if (FIELD(u32, &g_Battle.outcome.result, 0x0) & 0x6) {
        func_800AC934(0U);
        D_80146875          = 8;
        g_AreaScrollTargetX = g_Game.members[0].pos.x.fixed;
        g_AreaScrollTargetY = g_Game.members[0].pos.y.fixed;
        func_801DDED8();
        return;
    }
    func_801DDF00();
}
