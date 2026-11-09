#include "engine/slus/slus.h"

/* builds the projection matrix from the work object. */
MATCH void func_8015B410(void* matrix) {
    SVECTOR vertex;
    SVECTOR rotation;
    long    flag;
    Actor*  work;

    work        = g_Task;
    vertex.vx   = (s16)(work->pos.x.fixed >> 9) - 0x4000;
    vertex.vy   = (s16)(work->pos.y.fixed >> 9) - 0x4000;
    vertex.vz   = (s16)(-COORD_INT(work->pos.z) / 2);
    rotation.vx = (s16)work->unk_64;
    rotation.vy = (s16)work->unk_68;
    rotation.vz = (s16)work->unk_6C;
    RotTrans(&vertex, (VECTOR*)((MATRIX*)matrix)->t, &flag);
    RotMatrix(&rotation, matrix);
}
