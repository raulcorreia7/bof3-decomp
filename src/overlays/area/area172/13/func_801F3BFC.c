#include "area172_13.h"

MATCH void func_801F3BFC(const void* spin) {
    AreaSpin* work;
    POLY_G3*  primitive;
    s32       point[3];
    s16       fade;
    s16       tmp;
    s16       shade;

    work      = (AreaSpin*)spin;
    primitive = (POLY_G3*)g_GfxPrimCursor;

    SetPolyG3(primitive);
    PSX_SET_SEMI_TRANSPARENT(primitive);
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

    setRGB0(primitive, shade, shade, shade);
    primitive->r1 = 0;
    primitive->g1 = 0;
    primitive->b1 = 0;
    primitive->r2 = 0;
    primitive->g2 = 0;
    primitive->b2 = 0;

    GFX_AddPrim(1u, 0x1Cu);
}
