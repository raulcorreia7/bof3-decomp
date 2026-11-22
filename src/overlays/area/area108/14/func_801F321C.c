#include "area108_14.h"

MATCH void func_801F321C(void) {
    s32               args[3];
    s32               count;
    s32               n;
    u16*              p;
    AreaVertex*       dst;
    AreaTransform*    state;
    const AreaVertex* in;

    dst   = (AreaVertex*)AREA108_VERTEX_DST;
    state = AREA108_STATE_BASE;
    count = 0;
    in    = (const AreaVertex*)D_80147B40;
    do {
        *dst          = *in;
        state->base_x = ((dst->points[0].x + dst->points[1].x + dst->points[2].x + dst->points[3].x) >> 2);
        state->base_y = ((dst->points[0].y + dst->points[1].y + dst->points[2].y + dst->points[3].y) >> 2);
        state->base_z = ((dst->points[0].z + dst->points[1].z + dst->points[2].z + dst->points[3].z) >> 2);
        args[0]       = (s16)state->base_x;
        args[1]       = (s16)state->base_y;
        args[2]       = (s16)state->base_z;
        VectorNormalS((VECTOR*)args, &state->normal.vec);
        state->rotation.vx    = 0;
        state->rotation.vy    = 0;
        state->rotation.vz    = 0;
        state->normal.word[0] = ((s32)(state->normal.word[0] << 16) >> 23);
        state->normal.word[1] = ((state->normal.word[1] << 16) >> 23);
        state->normal.word[2] = ((state->normal.word[2] << 16) >> 23);
        p                     = (u16*)&dst->points[0].x;
        n                     = 0;
        do {
            *p = *p - state->base_x;
            p++;
            *p = *p - state->base_y;
            p++;
            *p = *p - state->base_z;
            p++;
            n++;
        } while ((n & BYTE_MASK) < 4u);
        state++;
        dst++;
        in++;
        count += 1;
    } while (((count & BYTE_MASK)) < 55u);
}
