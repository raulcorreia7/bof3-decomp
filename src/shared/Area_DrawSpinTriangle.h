/* Draws one spin-effect triangle: a gradient POLY_G3 from the record origin and
 * its two rotated vertex offsets, shaded by the record fade. One definition
 * shared by the area overlays that hold a WorldSpin record, the sibling of
 * Area_InitSpin. Each image sets AREA_SPIN_PRIM_ORDER, the primitive list the
 * triangle joins, in its header. Every change here must verify every member image. */
MATCH void Area_DrawSpinTriangle(const void* spin) {
    WorldSpin* work;
    POLY_G3*   primitive;
    s32        point[3];
    s16        fade;
    s16        tmp;
    s16        shade;
    work      = (WorldSpin*)spin;
    primitive = (POLY_G3*)g_GfxPrimCursor;

    SetPolyG3(primitive);
    SetSemiTrans(primitive, 1);
    Area_ProjectPoint(work, &primitive->x0);

    point[0] =
        ((rcos(work->spin_angle) * work->vertex_a.vx - rsin(work->spin_angle) * work->vertex_a.vy) >> 8) * work->scale;
    point[1] =
        ((rsin(work->spin_angle) * work->vertex_a.vx + rcos(work->spin_angle) * work->vertex_a.vy) >> 8) * work->scale;
    point[2] = (work->vertex_a.vz << 12) * work->scale;
    point[0] += work->origin_x;
    point[1] += work->origin_y;
    point[2] += work->origin_z;
    Area_ProjectPoint(point, &primitive->x1);

    point[0] =
        ((rcos(work->spin_angle) * work->vertex_b.vx - rsin(work->spin_angle) * work->vertex_b.vy) >> 8) * work->scale;
    point[1] =
        ((rsin(work->spin_angle) * work->vertex_b.vx + rcos(work->spin_angle) * work->vertex_b.vy) >> 8) * work->scale;
    point[2] = (work->vertex_b.vz << 12) * work->scale;
    point[0] += work->origin_x;
    point[1] += work->origin_y;
    point[2] += work->origin_z;
    Area_ProjectPoint(point, &primitive->x2);

    fade = work->fade;
    tmp  = fade;
    if (fade < 0) {
        shade = 0;
    } else {
        shade = tmp;
        if (fade >= 256) {
            shade = 0xFF;
        }
    }

    setRGB0(primitive, shade, shade, (u8)shade >> 1);
    primitive->r1 = 0;
    primitive->g1 = 0;
    primitive->b1 = 0;
    primitive->r2 = 0;
    primitive->g2 = 0;
    primitive->b2 = 0;

    GFX_AddPrim(AREA_SPIN_PRIM_ORDER, 0x1Cu);
}
