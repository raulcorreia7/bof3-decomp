#include "area108_14.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3588(u8* dst, u8* src, u16* state) {
    MATRIX  rot;
    VECTOR  vtx;
    SVECTOR in;
    long    flag;
    s16*    corners;
    s16*    out;
    s32     index;

    corners   = (s16*)dst;
    out       = (s16*)src;
    state[8]  = RANDOM_MASK(0xFC0);
    state[9]  = RANDOM_MASK(0xFC0);
    state[10] = RANDOM_MASK(0xFC0);
    RotMatrix((SVECTOR*)(state + 8), &rot);
    rot.t[0] = 0;
    rot.t[1] = 0;
    rot.t[2] = 0;
    SetTransMatrix(&rot);
    SetRotMatrix(&rot);

    corners += 1;
    out += 1;
    index = 0;
    do {
        in.vx = *corners++;
        in.vy = *corners++;
        in.vz = *corners++;
        RotTrans(&in, &vtx, &flag);
        *out = state[0] + vtx.vx;
        out++;
        *out = state[1] + vtx.vy;
        out++;
        *out = state[2] + vtx.vz;
        out++;
        index += 1;
    } while ((index & BYTE_MASK) < 4U);
}
#else
INCLUDE_ASM(func_801F3588);
#endif
