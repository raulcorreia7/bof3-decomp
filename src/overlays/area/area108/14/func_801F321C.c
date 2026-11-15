#include "area108_14.h"

MATCH void func_801F321C(void) {
    s32               args[3];
    s32               count;
    s32               n;
    u16*              p;
    AreaVertex*       dst;
    u16*              state;
    const AreaVertex* in;

    dst   = (AreaVertex*)AREA108_VERTEX_DST;
    state = AREA108_STATE_BASE;
    count = 0;
    in    = (const AreaVertex*)D_80147B40;
    do {
        *dst     = *in;
        state[0] = ((dst->points[0].x + dst->points[1].x + dst->points[2].x + dst->points[3].x) >> 2);
        state[1] = ((dst->points[0].y + dst->points[1].y + dst->points[2].y + dst->points[3].y) >> 2);
        state[2] = ((dst->points[0].z + dst->points[1].z + dst->points[2].z + dst->points[3].z) >> 2);
        args[0]  = (s16)state[0];
        args[1]  = (s16)state[1];
        args[2]  = (s16)state[2];
        VectorNormalS((VECTOR*)args, (SVECTOR*)(state + 4));
        state[8]  = 0;
        state[9]  = 0;
        state[10] = 0;
        state[4]  = ((s32)(state[4] << 16) >> 23);
        state[5]  = ((state[5] << 16) >> 23);
        state[6]  = ((state[6] << 16) >> 23);
        p         = (u16*)&dst->points[0].x;
        n         = 0;
        do {
            *p = *p - state[0];
            p++;
            *p = *p - state[1];
            p++;
            *p = *p - state[2];
            p++;
            n++;
        } while ((n & BYTE_MASK) < 4u);
        state += 12;
        dst++;
        in++;
        count += 1;
    } while (((count & BYTE_MASK)) < 55u);
}
