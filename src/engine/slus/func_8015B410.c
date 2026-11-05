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
    vertex.vx   = (work->x.fixed >> 9) - 0x4000;
    vertex.vy   = (work->y.fixed >> 9) - 0x4000;
    vertex.vz   = (-work->z.part.integer / 2);
    rotation.vx = work->unk_64;
    rotation.vy = work->unk_68;
    rotation.vz = work->unk_6C;
    RotTrans(&vertex, (VECTOR*)((MATRIX*)matrix)->t, &flag);
    RotMatrix(&rotation, matrix);
}
