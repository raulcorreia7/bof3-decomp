#include "battle_03.h"

MATCH void func_801E3980(void) {
    u8 kind;

    func_801E2314(2);
    kind                        = *(u8*)(((u32)g_BattleCurrentEnemy + 0xE0u));
    g_Task->word_08.byte.unk_09 = *(u8*)(MEM_PTR(u8, 0x800E40CEu) + (u32)kind * 0x88u);
    g_Task->mode += 1;
    g_Task->step = 0;
}
