#include "boss055_16.h"

MATCH void func_800C1A8C(void) {
    u8 type;

    func_800C2340(4, 2, 2);
    type                      = g_BattleCurrentEnemy->type;
    TASK(PartyMember)->unk_09 = MEM_PTR(u8, 0x800E40CEu)[type * 0x88u];
    TASK(PartyMember)->header.step += 1;
}
