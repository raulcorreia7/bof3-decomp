#include "game_00.h"

MATCH void func_8019D8C0(SpinQuad* quad, s16* out) {
    MATRIX rot;
    VECTOR vtx;
    long   flag;
    s16*   dst;
    s32    index;

    dst = out;
    PushMatrix();
    dst += 1;
    quad->rotation.vx = (rand() & 0xFC0);
    quad->rotation.vy = (rand() & 0xFC0);
    quad->rotation.vz = (rand() & 0xFC0);
    RotMatrix(&quad->rotation, &rot);
    rot.t[0] = 0;
    rot.t[1] = 0;
    rot.t[2] = 0;
    SetTransMatrix(&rot);
    SetRotMatrix(&rot);
    index = 0;
    do {
        RotTrans(&quad->corners[index & 0xFF], &vtx, &flag);
        index += 1;
        *dst = quad->pos.x + vtx.vx;
        dst += 1;
        *dst = quad->pos.y + vtx.vy;
        dst += 1;
        *dst = quad->pos.z + vtx.vz;
        dst += 1;
    } while (((index & 0xFF)) < 4U);
    PopMatrix();
}
