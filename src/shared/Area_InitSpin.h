/* Starts one spin-effect record. */
MATCH void Area_InitSpin(void* spin) {
    WorldSpin* work;
    Actor*     scratch;
    MATRIX     matrix;
    s16        rot[3];

    work           = (WorldSpin*)spin;
    scratch        = g_Task;
    work->origin.x = scratch->pos.x.fixed;
    work->origin.y = scratch->pos.y.fixed;
    work->origin.z = scratch->pos.z.fixed;

    rot[0] = RANDOM_MASK(0xFFF);
    rot[1] = AREA_SPIN_PITCH;
    rot[2] = RANDOM_MASK(0xFFF);

    work->vertex_a.vx = rcos(AREA_SPIN_RADIUS);
    work->vertex_a.vy = rsin(AREA_SPIN_RADIUS);
    work->vertex_a.vz = 0;
    work->vertex_b.vx = rcos(-AREA_SPIN_RADIUS);
    work->vertex_b.vy = rsin(-AREA_SPIN_RADIUS);
    work->vertex_b.vz = 0;

    Matrix_SetIdentity(&matrix);
    RotMatrixX(rot[0], &matrix);
    RotMatrixY(-rot[1], &matrix);
    RotMatrixZ(rot[2], &matrix);

    ApplyMatrixSV(&matrix, &work->vertex_a, &work->vertex_a);
    ApplyMatrixSV(&matrix, &work->vertex_b, &work->vertex_b);

    work->scale      = RANDOM_MASK(AREA_SPIN_SCALE_MASK) + AREA_SPIN_SCALE_BASE;
    work->angle_lo   = 0;
    work->angle_hi   = 0;
    work->spin_angle = 0;
    work->fade       = AREA_SPIN_FADE;
}
