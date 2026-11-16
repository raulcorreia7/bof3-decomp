#include "area108_14.h"

/* Projects the four corners of one row through a random rotation around the row's state centre. */
MATCH void func_801F3588(u8* dst, u8* src, u16* state) {
    MATRIX  rot;
    SVECTOR in;
    VECTOR  vtx;
    long    flag;
    s16*    corner;
    s16*    result;
    s32     index;

    state[8]  = RANDOM_MASK(0xFC0);
    state[9]  = RANDOM_MASK(0xFC0);
    state[10] = RANDOM_MASK(0xFC0);
    RotMatrix((SVECTOR*)(state + 8), &rot);
    rot.t[0] = 0;
    rot.t[1] = 0;
    rot.t[2] = 0;
    SetTransMatrix(&rot);
    SetRotMatrix(&rot);

    corner = FIELD_PTR(s16, dst, 2);
    result = FIELD_PTR(s16, src, 2);
    index  = 0;
    do {
        in.vx = *corner++;
        in.vy = *corner++;
        in.vz = *corner++;
        RotTrans(&in, &vtx, &flag);
        *result++ = state[0] + vtx.vx;
        *result++ = state[1] + vtx.vy;
        *result++ = state[2] + vtx.vz;
        index += 1;
    } while ((index & BYTE_MASK) < 4U);
}
