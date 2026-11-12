/* Sets the GTE model matrix from the effect's facing and its position, half its height span deep, viewed through the
 * camera. Every change must verify every member: func_801EF3B0 (magic137), func_801EF688 (magic067). */
MATCH void Effect_SetFacingMatrix(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    rot.vx = 0;
    rot.vy = 0;
    switch (g_Task->facing) {
        case 0:
            rot.vz = 0;
            break;
        case 1:
            rot.vz = ANGLE_90;
            break;
        case 2:
            rot.vz = ANGLE_180;
            break;
        case 3:
            rot.vz = ANGLE_270;
            break;
    }
    pos.vx = (g_Task->pos.x.fixed >> 9) - 0x4000;
    pos.vy = (g_Task->pos.y.fixed >> 9) - 0x4000;
    pos.vz = -COORD_INT(g_Task->pos.z) / 2;
    RotTransMatrix(&pos, matrix, &flags);
    Camera_SetModelMatrix(&rot, &matrix);
}
