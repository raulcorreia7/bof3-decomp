#include "engine/game/00/game_00.h"

MATCH void* Camera_SetMatrix(void* out_matrix) {
    SVECTOR scale;
    VECTOR  projected;
    MATRIX  matrix;

    RotMatrix(&g_AreaCamera.angle, &matrix);
    scale.vx = ((u32)g_AreaCamera.x >> 1);
    scale.vy = (g_AreaCamera.y >> 1);
    /* FAKE: retail reads the camera height as u32. */
    scale.vz = ((*(u32*)&g_AreaCamera.height) >> 1);
    ApplyMatrix(&matrix, &scale, &projected);
    matrix.t[0] = projected.vx + g_AreaCameraOffsetX;
    matrix.t[1] = projected.vy + g_AreaCameraOffsetY;
    matrix.t[2] = projected.vz + g_AreaCameraOffsetZ + 0x1194;
    RotMatrix(&g_AreaCamera.angle, &matrix);
    SetRotMatrix(&matrix);
    SetTransMatrix(&matrix);
    return out_matrix;
}
