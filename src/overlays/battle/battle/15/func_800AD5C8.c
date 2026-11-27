#include "battle_15.h"

MATCH void func_800AD5C8(void) {
    PartyMember*  work;
    u8            count;
    u8            i;
    volatile u16* base;

    i = 0;
    if (g_Battle.gene_count != 0) {
        work  = SELF(PartyMember);
        count = work->param.unk_0B;
        base  = (u16*)(&D_80148628);
        do {
            if (g_Battle.genes[i] == count) {
                work->screen_x.value = base[0] + (i * 0x18 + 0x41);
                work->screen_y.value = base[1] + 0x12;
                return;
            }
            i++;
        } while (i < g_Battle.gene_count);
    }
    SELF(PartyMember)->header.step--;
}
