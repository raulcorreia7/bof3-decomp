#include "battle_15.h"

MATCH void func_800AD4D4(void) {
    volatile PartyMember* work;
    PartyMember*          ptr;
    u32                   first;
    u32                   second;
    u8                    remainder;
    u8                    index;

    work                 = SELF(PartyMember);
    first                = work->param.unk_0B;
    second               = work->param.unk_0B;
    remainder            = (u8)first % 6;
    work->screen_x.value = D_80148628 + (remainder * 0x1E + 0x13);
    work->screen_y.value = (second / 3 * 0x10 & 0x1FE0) + (0x30 + D_8014862A);
    index                = 0;
    if (g_Battle.gene_count != 0) {
        do {
            ptr = SELF(PartyMember);
            if (g_Battle.genes[index] == ptr->param.unk_0B) {
                ptr->header.step += 1;
            }
            index++;
        } while (index < g_Battle.gene_count);
    }
}
