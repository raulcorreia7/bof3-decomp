#include "battle_03.h"

MATCH void func_801E3980(void) {
    u8 type;

    Battle_RequestEnemyScript(2);
    type           = *(u8*)(((u32)g_BattleCurrentEnemy + 0xE0u));
    g_Task->unk_09 = *(u8*)(MEM_PTR(u8, 0x800E40CEu) + type * 0x88u);
    g_Task->header.mode += 1;
    g_Task->header.step = 0;
}
