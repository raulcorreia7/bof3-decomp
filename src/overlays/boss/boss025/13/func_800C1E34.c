#include "boss025_13.h"

MATCH void func_800C1E34(void) {
    if ((D_801462EC & 0x2800) != 0x800) {
        if (g_BattleCurrentEnemy->flags_100 & 2) {
            func_801E2314(8);
        } else {
            func_801E2314(0);
        }
    } else {
        Actor_RequestScript(0xC);
    }
    func_801E30F8();
    g_SpadWork[1]++;
}
