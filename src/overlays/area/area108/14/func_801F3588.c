#include "area108_14.h"

/* Projects the four corners of one row through a random rotation around the row's state centre. */
MATCH void func_801F3588(u8* dst, u8* src, AreaTransform* state) {
    MATRIX  rot;
    SVECTOR in;
    VECTOR  vtx;
    long    flag;
    s16*    corner;
    s16*    result;
    s32     index;

    state->rotation.vx = RANDOM_MASK(0xFC0);
    state->rotation.vy = RANDOM_MASK(0xFC0);
    state->rotation.vz = RANDOM_MASK(0xFC0);
    RotMatrix(&state->rotation, &rot);
    rot.t[0] = 0;
    rot.t[1] = 0;
    rot.t[2] = 0;
    SetTransMatrix(&rot);
    SetRotMatrix(&rot);

    corner = FIELD_PTR(s16, dst, 2);
    result = FIELD_PTR(s16, src, 2);
    index  = 0;
    do {
        setVector(&in, *corner++, *corner++, *corner++);
        RotTrans(&in, &vtx, &flag);
        *result++ = state->base_x + vtx.vx;
        *result++ = state->base_y + vtx.vy;
        *result++ = state->base_z + vtx.vz;
        index += 1;
    } while ((index & BYTE_MASK) < 4U);
}
