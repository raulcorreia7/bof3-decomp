/* Draws one spin-effect triangle: a gradient POLY_G3 from the record origin and its two rotated vertex offsets, shaded by the record fade. `order` is the primitive list the triangle joins. */
static inline void Area_DrawSpinTriangleOn(const void* spin, u32 order) {
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
    Area_ProjectPoint(&work->origin.x, POLY_XY(primitive, 0));

    point[0] =
        ((rcos(work->spin_angle) * work->vertex_a.vx - rsin(work->spin_angle) * work->vertex_a.vy) >> 8) * work->scale;
    point[1] =
        ((rsin(work->spin_angle) * work->vertex_a.vx + rcos(work->spin_angle) * work->vertex_a.vy) >> 8) * work->scale;
    point[2] = (work->vertex_a.vz << 12) * work->scale;
    point[0] += work->origin.x;
    point[1] += work->origin.y;
    point[2] += work->origin.z;
    Area_ProjectPoint(point, POLY_XY(primitive, 1));

    point[0] =
        ((rcos(work->spin_angle) * work->vertex_b.vx - rsin(work->spin_angle) * work->vertex_b.vy) >> 8) * work->scale;
    point[1] =
        ((rsin(work->spin_angle) * work->vertex_b.vx + rcos(work->spin_angle) * work->vertex_b.vy) >> 8) * work->scale;
    point[2] = (work->vertex_b.vz << 12) * work->scale;
    point[0] += work->origin.x;
    point[1] += work->origin.y;
    point[2] += work->origin.z;
    Area_ProjectPoint(point, POLY_XY(primitive, 2));

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
    setRGB1(primitive, 0, 0, 0);
    setRGB2(primitive, 0, 0, 0);

    GFX_AddPrim(order, sizeof(POLY_G3));
}
