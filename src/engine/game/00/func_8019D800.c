#include "game_00.h"

MATCH void func_8019D800(void) {
    s16*          src;
    volatile u16* dst;
    volatile u16* work;
    s32           count;
    u16           tmp;
    u16           t0;
    u16           t1;
    u16           t2;
    u16           a;
    u16           b;

    dst   = MEM_PTR(u16, 0x800E4800u);
    count = 0;
    work  = MEM_PTR(u16, 0x800E4804u);
    src   = (s16*)g_Task->source_50;
    for (;; work += 0x1C) {
        a                      = work[4];
        b                      = work[2];
        work[4]                = (u16)(a + 2);
        dst[0]                 = (u16)(dst[0] + b);
        t0                     = work[-1];
        tmp                    = work[3];
        t1                     = work[0];
        t2                     = work[4];
        work[-1]               = (u16)(t0 + tmp);
        *(u16*)(void*)&work[0] = (u16)(t1 + t2);
        func_8019D8C0((void*)dst, src);
        dst += 0x1C;
        src += 0x14;
        count += 1;
        if (((u32)(count & BYTE_MASK)) >= 0x18) {
            break;
        }
    }
}
