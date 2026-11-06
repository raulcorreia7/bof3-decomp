#include "game_00.h"

MATCH s32 func_801C6DCC(void) {
    s16             outer;
    s16             inner;
    u8              flag;
    EncounterEnemy* record;
    u8*             field;

    record     = D_801463DC;
    outer      = 0;
    field      = (u8*)D_801463DC + 0xA;
    D_801CD8C4 = 0;
    do {
        flag = 0;
        if (record->active != 0) {
            inner = 0;
            for (;;) {
                if (inner >= (Party_CountOrder(PARTY_ORDER_BATTLE) & BYTE_MASK)) {
                    break;
                }
                if ((func_801C7824(D_80143F2E[inner].unk_00, D_80143F2E[inner].unk_04, *(s16*)(field - 4),
                                   *(s16*)field) &
                     0xFF) != 0) {
                    flag = 1;
                    D_801CD8C4 += 1;
                    break;
                }
                inner += 1;
            }
            record->active = flag;
        }
        field += 0xC;
        outer += 1;
        record++;
    } while (outer < 8);
    return D_801CD8C4 != 0;
}
