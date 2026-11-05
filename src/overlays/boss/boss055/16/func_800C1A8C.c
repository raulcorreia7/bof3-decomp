#include "boss055_16.h"

MATCH void func_800C1A8C(void) {
    u8 kind;

    func_800C2340(4, 2, 2);
    kind          = g_BattleCurrentEnemy->kind;
    g_SpadWork[9] = MEM_PTR(u8, 0x800E40CEu)[(u32)kind * 0x88u];
    g_SpadWork[2] += 1;
}
