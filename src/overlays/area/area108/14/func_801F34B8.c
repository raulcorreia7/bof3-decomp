#include "area108_14.h"

MATCH void func_801F34B8(void) {
    u8*           dst;
    u16*          state;
    u16*          base;
    u16           phase;
    u16           step;
    u16           speed;
    u16           t0;
    u16           t1;
    u16           t2;
    s32           count;
    u8*           src;
    /* FAKE: volatile fixes the load order; the last store goes through base. */
    volatile u16* work;

    src   = D_80147B40;
    dst   = (u8*)0x800E4FA8;
    state = (u16*)0x800E4A80;
    count = 0;
    work  = (u16*)0x800E4A84;
    for (;; work += 12) {
        phase    = work[4];
        step     = work[2];
        work[4]  = phase + 1;
        state[0] = state[0] + step;
        t0       = work[-1];
        speed    = work[3];
        t1       = work[0];
        t2       = work[4];
        work[-1] = t0 + speed;
        base     = (u16*)work;
        *base    = t1 + t2;
        func_801F3588(dst, src, state);
        dst += 0x28;
        src += 0x28;
        state += 12;
        count += 1;
        if ((count & BYTE_MASK) >= 0x37u) {
            break;
        }
    }
}
