#include "boss033_16.h"

MATCH void Boss_ChooseBattleEnding(void) {
    if (FIELD(u32, &g_BattleResult, 0) & 6) {
        func_800AC934(0U);
        D_80146875          = 8;
        g_AreaScrollTargetX = D_80145EC4;
        g_AreaScrollTargetY = D_80145EC8;
        func_801DDED8();
        return;
    }
    func_801DDF00();
}
