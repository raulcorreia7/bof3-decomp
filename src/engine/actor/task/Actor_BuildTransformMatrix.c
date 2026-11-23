#include "engine/slus/slus.h"

/* builds the projection matrix from the work object: RotTrans maps the vertex (+0x34/+0x38 scaled by 1/512
 * and biased by -0x4000, and the negated half of +0x3E) into the matrix translation, then RotMatrix composes its
 * angle_x/y/z.
 */
/* func_8015B410 */
MATCH void Actor_BuildTransformMatrix(void* matrix) {
    SVECTOR vertex;
    SVECTOR rotation;
    long    flag;
    Actor*  work;

    work = TASK(Actor);
    setVector(&vertex, (s16)(work->pos.x.fixed >> 9) - 0x4000, (s16)(work->pos.y.fixed >> 9) - 0x4000, (s16)(-COORD_INT(work->pos.z) / 2));
    setVector(&rotation, (s16)work->angle_x, (s16)work->angle_y, (s16)work->angle_z);
    RotTrans(&vertex, (VECTOR*)((MATRIX*)matrix)->t, &flag);
    RotMatrix(&rotation, matrix);
}
