#include "game_00.h"

MATCH s32 func_801C69C8(s32 record_index) {
    s32 index;
    u8* slot;
    s32 mode;
    s32 result;
    /* Retail reserves 0x20 variable bytes and never reads them; the unused
     * array reproduces that frame. */
    u8  unk_10[0x20];

    index           = record_index & BYTE_MASK;
    slot            = D_80143F2C + index * 8;
    mode            = D_801CD944[index].key;
    result          = 0;
    g_Task->z.fixed = Area_SampleHeight(*(s32*)slot, *(s32*)(slot + 4)) << 16;
    if ((func_801C7518(*(s32*)slot, *(s32*)(slot + 4), mode) & BYTE_MASK) != 0) {
        result = func_801BDE14(*(s32*)slot, *(s32*)(slot + 4), mode) == -1;
    }
    return result;
}
