#include "battle_15.h"

MATCH void func_800B0118(void) {
    BattleWork* work;
    u8          table_index;

    work         = (BattleWork*)g_Task;
    table_index  = D_800B6D00[g_DragonForm];
    work->unk_0C = D_800B6C90[table_index].values[work->unk_08 & 3][0];
    work->unk_10 = D_800B6C90[table_index].values[work->unk_08 & 3][1];
}
