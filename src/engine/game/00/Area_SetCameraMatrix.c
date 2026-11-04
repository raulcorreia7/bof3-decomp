#include "game_00.h"

/* func_801AFE18 */
MATCH void* Area_SetCameraMatrix(void* out_matrix) {
    SVECTOR scale;
    VECTOR  projected;
    MATRIX  matrix;

    RotMatrix(&g_AreaCameraAngle, &matrix);
    scale.vx = (s16)((u32)D_80149310 >> 1);
    scale.vy = (s16)(D_80149314 >> 1);
    /* FAKE: retail reads g_AreaCameraHeight as u32. */
    scale.vz = (s16)((*(u32*)&g_AreaCameraHeight) >> 1);
    ApplyMatrix(&matrix, &scale, &projected);
    matrix.t[0] = projected.vx + g_AreaCameraOffsetX;
    matrix.t[1] = projected.vy + g_AreaCameraOffsetY;
    matrix.t[2] = projected.vz + g_AreaCameraOffsetZ + 0x1194;
    RotMatrix(&g_AreaCameraAngle, &matrix);
    SetRotMatrix(&matrix);
    SetTransMatrix(&matrix);
    return out_matrix;
}
