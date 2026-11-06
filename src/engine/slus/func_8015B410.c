#include "engine/slus/slus.h"

/* builds the projection matrix from the work object: RotTrans maps the vertex (+0x34/+0x38 scaled by 1/512
 * and biased by -0x4000, and the negated half of +0x3E) into the matrix translation, then RotMatrix composes the
 * angles at +0x64/+0x68/+0x6C.
 */
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
