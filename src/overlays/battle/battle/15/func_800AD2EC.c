#include "battle_15.h"

MATCH void func_800AD2EC(void) {
    volatile u8* record;
    u8*          ptr;
    u32          first;
    u32          second;
    u8           remainder;
    u16          label;
    u8           count;

    SELF_BYTES[0x29]          = 1;
    SELF(Actor)->sheet_page   = 0x1E;
    SELF(Actor)->sheet_row    = 0;
    SELF(Actor)->active_flags = 0x80;
    SELF(Actor)->clut_select  = 0x1B;
    SELF_BYTES[0x28]          = 1;
    {
        u8* record;
        u8* other;

        record                 = SELF_BYTES;
        record[0x2B]           = 0;
        other                  = SELF_BYTES;
        *(s16*)(record + 0x2C) = 2;
        other[0x2A]            = 0;
    }
    record                          = SELF_BYTES;
    first                           = record[0xB];
    remainder                       = (u8)first % 6;
    *(volatile s32*)(record + 0x3C) = 0;
    second                          = record[0xB];
    *(u16*)(record + 0x2E)          = g_UiPanelTasks[21].pos.vx + (remainder * 0x1E + 0x13);
    count                           = record[1];
    label                           = g_UiPanelTasks[21].pos.vy;
    record[1]                       = count + 1;
    ptr                             = SELF_BYTES;
    *(u16*)(record + 0x30)          = (second / 3 * 0x10 & 0x1FE0) + (0x30 + label);
    Script_Select(ptr[0x4B]);
    Area_AddActor();
}
