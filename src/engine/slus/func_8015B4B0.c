#include "engine/slus/slus.h"

/* composes the caller's matrix with the shared matrix g_CameraMatrix in place and loads the result as the GTE rotation and translation matrix. */
MATCH void func_8015B4B0(void* matrix) {
    MulMatrix2(&g_CameraMatrix, matrix);
    SetRotMatrix(matrix);
    SetTransMatrix(matrix);
}
