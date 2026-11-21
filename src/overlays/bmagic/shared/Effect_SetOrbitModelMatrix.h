/* Sets the model matrix from the orbit effect angle and position; verify every image after a change. */
MATCH void Effect_SetOrbitModelMatrix(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;
    s32     off;

    PushMatrix();
    rot.vx = 0;
    rot.vy = 0;
    off    = g_BMagicOrbit->angle + 0x800;
    rot.vz = ((g_BMagicOrbit->unk_03 << 7) - off) & ANGLE_MASK;
    setVector(&pos, (g_BMagicOrbit->pos.x.fixed >> 9) - AREA_CELL_ORIGIN, (g_BMagicOrbit->pos.y.fixed >> 9) - AREA_CELL_ORIGIN, -COORD_INT(g_BMagicOrbit->pos.z) / 2);
    RotTransMatrix(&pos, matrix, &flags);
    Camera_SetModelMatrix(&rot, &matrix);
}
