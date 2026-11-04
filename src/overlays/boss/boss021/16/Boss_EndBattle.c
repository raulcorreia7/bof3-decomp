#include "boss021_16.h"

MATCH void Boss_EndBattle(void) {
    u8* work;

    func_800AC844(0);
    work       = (u8*)func_800AC754(0);
    g_SpadWork = work;
    work[0x2A] = 0;
    Actor_SelectScript(4);
    func_800AC934(1);
    func_800AC934(2);
}
