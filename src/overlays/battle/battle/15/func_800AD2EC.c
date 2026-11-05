#include "battle_15.h"

MATCH void func_800AD2EC(void) {
    volatile u8* record;
    u8*          ptr;
    u32          first;
    u32          second;
    u8           remainder;
    u16          label;
    u8           count;

    SPAD_WORK_BYTES[0x29] = 1;
    SPAD_WORK_BYTES[0x25] = 0x1E;
    SPAD_WORK_BYTES[0x26] = 0;
    SPAD_WORK_BYTES[0x24] = 0x80;
    SPAD_WORK_BYTES[0x27] = 0x1B;
    SPAD_WORK_BYTES[0x28] = 1;
    {
        u8* record;
        u8* other;

        record                 = SPAD_WORK_BYTES;
        record[0x2B]           = 0;
        other                  = SPAD_WORK_BYTES;
        *(s16*)(record + 0x2C) = 2;
        other[0x2A]            = 0;
    }
    record                          = SPAD_WORK_BYTES;
    first                           = record[0xB];
    remainder                       = (u8)first % 6;
    *(volatile s32*)(record + 0x3C) = 0;
    second                          = record[0xB];
    *(u16*)(record + 0x2E)          = D_80148628 + (remainder * 0x1E + 0x13);
    count                           = record[1];
    label                           = D_8014862A;
    record[1]                       = count + 1;
    ptr                             = SPAD_WORK_BYTES;
    *(u16*)(record + 0x30)          = (second / 3 * 16 & 0x1FE0) + (0x30 + label);
    Actor_SelectScript(ptr[0x4B]);
    Area_AddActor();
}
