#include "boss055_16.h"

MATCH void func_800C1A8C(void) {
    u8 kind;

    func_800C2340(4, 2, 2);
    kind                                                   = *(u8*)(((u32)g_BattleCurrentEnemy + 0xE0u));
    ((PartyBattler*)g_SpadWork)->word_08.byte.unk_09      = *(u8*)(MEM_PTR(u8, 0x800E40CEu) + (u32)kind * 0x88u);
    ((PartyBattler*)g_SpadWork)->unk_02 += 1;
}
