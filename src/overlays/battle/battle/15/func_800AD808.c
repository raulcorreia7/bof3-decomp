#include "battle_15.h"

MATCH void func_800AD808(void) {
    u8*      work;
    Callback funcs[2] = {func_800AD8D8, func_800AD930};

    work = SPAD_WORK_BYTES;
    funcs[work[0x02]]();
    work = SPAD_WORK_BYTES;
    if (!(work[0x00] & 1)) {
        return;
    }
    if (!(D_80148624 & 1)) {
        work[0x01]          = 2;
        BATTLE_WORK->unk_02 = 0;
        return;
    }
    *(u16*)(work + 0x2E) = D_80148628 + 0x14;
    *(u16*)(work + 0x30) = D_8014862A + 0x12;
    Area_AddActor();
}
