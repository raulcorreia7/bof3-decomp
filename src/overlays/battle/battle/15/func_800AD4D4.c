#include "battle_15.h"

MATCH void func_800AD4D4(void) {
    volatile PartyMember* work;
    PartyMember*          ptr;
    u32                   first;
    u32                   second;
    u8                    remainder;
    u8                    index;

    work              = (PartyMember*)g_Task;
    first             = work->param.unk_0B;
    second            = work->param.unk_0B;
    remainder         = (u8)first % 6;
    work->unk_2E.half = D_80148628 + (remainder * 0x1E + 0x13);
    work->unk_30.half = (second / 3 * 0x10 & 0x1FE0) + (0x30 + D_8014862A);
    index             = 0;
    if (g_Battle.gene_count != 0) {
        do {
            ptr = (PartyMember*)g_Task;
            if (g_Battle.genes[index] == ptr->param.unk_0B) {
                ptr->header.step += 1;
            }
            index++;
        } while (index < g_Battle.gene_count);
    }
}
