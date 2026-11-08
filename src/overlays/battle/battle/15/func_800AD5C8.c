#include "battle_15.h"

MATCH void func_800AD5C8(void) {
    PartyMember*  work;
    u8            count;
    u8            i;
    volatile u16* base;

    i = 0;
    if (g_Battle.gene_count != 0) {
        work  = (PartyMember*)g_Task;
        count = work->param.unk_0B;
        base  = (u16*)(&D_80148628);
        do {
            if (g_Battle.genes[i] == count) {
                work->unk_2E.half = base[0] + (i * 0x18 + 0x41);
                work->unk_30.half = base[1] + 0x12;
                return;
            }
            i++;
        } while (i < g_Battle.gene_count);
    }
    BATTLE_WORK->header.step--;
}
