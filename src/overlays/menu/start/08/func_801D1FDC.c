#include "start_08.h"

MATCH void func_801D1FDC(void) {
    s32 i;
    u8  count;
    u32 idx;
    u8* panel;

    Menu_ResetPanelTasks();
    i = 0;
    for (;;) {
        count = Party_CountOrder(0);
        idx   = i & BYTE_MASK;
        if (idx >= (u32)count) {
            break;
        }
        panel = &D_801483C0 + idx * 0x24;

        panel[0xA] = i;
        i += 1;
        panel[0x1]       = 6;
        panel[0x0]       = 1;
        panel[0x2]       = 0;
        panel[0x3]       = 0;
        ((u16*)panel)[2] = 0x62;
        ((u16*)panel)[3] = idx * 0x36 + 0x3E;
        panel[0xB]       = 0;
        panel[0xC]       = 0;
    }
    panel      = &D_8014842C;
    D_8014842D = 6;
    D_8014842E = 1;
    D_8014842F = 0;
    *panel     = 1;
    panel += 0x24;
    D_80148430 = 0xC8;
    D_80148432 = 0x10;
    D_80148451 = 6;
    D_80148452 = 2;
    D_80148453 = 0;
    *panel     = 1;
    panel += 0x24;
    D_80148476 = 3;
    D_80148454 = 0x10;
    D_80148456 = 0x10;
    D_80148475 = 6;
    D_80148477 = 0;
    *panel     = 1;
    D_80148478 = 0x68;
    D_8014847A = 0x2A;
    D_8014849A = 4;
    D_8014847E = 0;
    D_8014847F = 0;
    D_80148480 = 0;
    D_80148484 = 0;
    D_80148499 = 6;
    D_8014849B = 0;
    panel += 0x24;
    *panel     = 1;
    D_8014849C = 0x73;
    D_8014849E = 0x10;
    D_801484A8 = 0;
}
