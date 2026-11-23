#include "engine/slus/slus.h"

/* composes the caller's matrix with the shared matrix g_CameraMatrix in
 * place and loads the result as the GTE rotation and translation matrix.
 */
/* func_8015B4B0 */
MATCH void Camera_ApplyMatrix(void* matrix) {
    MulMatrix2(&g_AreaCamera.matrix, matrix);
    SetRotMatrix(matrix);
    SetTransMatrix(matrix);
}
