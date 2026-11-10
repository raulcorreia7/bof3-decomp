#include "area125_13.h"

extern u8 D_801F3834;
extern u8 D_801F36F0[];
extern u8 D_801F36F8[];

MATCH void func_801F2E7C(void) {
    s16 x;
    u8* task;
    s16 val;

    task = (u8*)g_Task;
    x    = *(s16*)(task + 0x2E);
    if (x < 0x1A4) {
        if (x < 0x3C) {
            D_801F3834 = 0;
        } else if (x < 0xB4) {
            D_801F3834 = 1;
        } else if (x < 0x12C) {
            D_801F3834 = 2;
        } else if (x < 0x168) {
            D_801F3834 = 3;
        } else {
            D_801F3834 = 4;
        }
        task = (u8*)g_Task;
        val  = *(s16*)(task + 0x30);
        if (val == 0) {
            func_801F3268(D_801F36F0[D_801F3834]);
            *(s16*)((u8*)g_Task + 0x30) = D_801F36F8[D_801F3834];
        } else {
            *(s16*)(task + 0x30) = val - 1;
        }
        (*(u16*)((u8*)g_Task + 0x2E))++;
    } else {
        task[1]++;
    }
    func_801F33B0();
}
