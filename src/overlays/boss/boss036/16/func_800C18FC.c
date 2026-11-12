#include "boss036_16.h"

MATCH void func_800C18FC(void) {
    u8 kind;

    kind           = g_BattleCurrentEnemy->kind;
    g_Task->unk_09 = MEM_PTR(u8, 0x800E40CEu)[kind * 0x88u];
    func_801E2314(2);
    func_801E30F8();
    g_Task->unk_0C = 0x4000;
    g_Task->unk_18 = g_Task->pos.x.fixed + 0x30000;
    g_Task->header.step++;
}
