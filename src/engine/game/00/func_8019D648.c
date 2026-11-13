#include "game_00.h"

MATCH void func_8019D648(void) {
    s32 args[3];
    s32 count;
    /* FAKE: retail keeps the source row in s1. */
    FAKE_REG(s16*, src, "s1");
    u16* base;
    u16* dst;
    /* FAKE: retail keeps the auxiliary base in s0. */
    FAKE_REG(u16*, aux, "s0");
    s32  row;
    u16* cur;
    s16* dst_next;
    s16* out;

    dst  = MEM_PTR(u16, AREA_WORK);
    row  = 0;
    base = (u16*)g_Task->script;
    aux  = MEM_PTR(u16, 0x800E4814u);
    src  = (s16*)(base + 12);
    do {
        *dst    = ((src[-11] + src[-8] + src[-5] + src[-2]) >> 2);
        aux[-9] = ((src[-10] + src[-7] + src[-4] + src[-1]) >> 2);
        cur     = base + 1;
        count   = 0;
        aux[-8] = ((src[-9] + src[-6] + src[-3] + src[0]) >> 2);
        do {
            out     = (s16*)(dst + (count & BYTE_MASK) * 4);
            out[12] = (cur[0] - *dst);
            cur += 1;
            out[13] = (cur[0] - aux[-9]);
            cur += 1;
            out[14] = (cur[0] - aux[-8]);
            count += 1;
            cur += 1;
        } while ((count & BYTE_MASK) < 4u);
        src += 20;
        base += 20;
        args[0]  = (s16)*dst;
        dst_next = (s16*)(dst + 4);
        args[1]  = (s16)aux[-9];
        dst += 28;
        args[2] = (s16)aux[-8];
        /* retail passes the count as a third word, which libgte.h's two-argument prototype lacks */
        ((void (*)(s32*, void*, s32))VectorNormalS)(args, dst_next, count);
        row += 1;
        aux[-2] = 0;
        aux[-1] = 0;
        aux[0]  = 0;
        aux[-6] = ((aux[-6] << 0x10) >> 0x16);
        aux[-5] = ((aux[-5] << 0x10) >> 0x16);
        aux[-4] = ((aux[-4] << 0x10) >> 0x16);
        aux += 28;
    } while ((row & BYTE_MASK) < 24u);
}
