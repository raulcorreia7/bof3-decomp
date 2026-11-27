#include "area103_13.h"

/* Draws the ribbon trail of one spin row: thirty-two quads from the projected centre point, each
 * edge turned from the segment direction by the accumulated length. */
MATCH void func_801F2FB8(AreaSpinEffect* effect) {
    VECTOR   point;
    VECTOR   from;
    VECTOR   edge;
    DVECTOR  screen;
    DVECTOR  screen2;
    POLY_G4* prim;
    s16      angle;
    s16      scale;
    s16      shade;
    s32      length;
    u8       i;
    /* FAKE: retail reserves 8 frame bytes past the screen points that no statement uses; best pure C 28 rows. */
    FAKE_STACK_PADS(u8, 8);

    angle    = effect->angle;
    scale    = effect->scale;
    shade    = effect->unk_14;
    point.vx = effect->pos.x + ((scale * rcos(angle)) >> 4);
    point.vy = effect->pos.y + ((scale * rsin(angle)) >> 4);
    point.vz = effect->pos.z;
    Camera_ProjectPoint((s32*)&point, &screen);
    screen2 = screen;
    length  = 0;
    for (i = 0; i < 0x20; i++) {
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        prim->x0 = screen.vx;
        prim->y0 = screen.vy;
        prim->x1 = screen2.vx;
        prim->y1 = screen2.vy;
        if (shade < 0) {
            shade = 0;
        } else if (shade >= 0x100) {
            shade = 0xFF;
        }
        angle -= 0x20;
        setRGB0(prim, shade, shade, shade);
        setRGB1(prim, shade, shade, shade);
        point.vz += 0x70000;
        from = point;
        scale += 0x18;
        point.vx = effect->pos.x + ((scale * rcos(angle)) >> 4);
        point.vy = effect->pos.y + ((scale * rsin(angle)) >> 4);
        point.vz = effect->pos.z;
        from.vx  = point.vx - from.vx;
        from.vy  = point.vy - from.vy;
        from.vz  = 0;
        length += SquareRoot0(VectorNormal(&from, &from));
        from.vz = from.vx;
        from.vx = -from.vy;
        from.vy = from.vz;
        from.vz = 0;
        edge.vx = point.vx + (((length * rsin(0x40)) / rcos(0x80) * from.vx) >> 12);
        edge.vy = point.vy + (((length * rsin(0x40)) / rcos(0x80) * from.vy) >> 12);
        edge.vz = point.vz;
        Camera_ProjectPoint((s32*)&edge, &screen);
        edge.vx = point.vx - (((length * rsin(0x40)) / rcos(0x80) * from.vx) >> 12);
        edge.vy = point.vy - (((length * rsin(0x40)) / rcos(0x80) * from.vy) >> 12);
        edge.vz = point.vz;
        Camera_ProjectPoint((s32*)&edge, &screen2);
        prim->x2 = screen.vx;
        prim->y2 = screen.vy;
        prim->x3 = screen2.vx;
        prim->y3 = screen2.vy;
        shade -= 4;
        if (shade < 0) {
            shade = 0;
        } else if (shade >= 0x100) {
            shade = 0xFF;
        }
        setRGB2(prim, shade, shade, shade);
        setRGB3(prim, shade, shade, shade);
        GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_G4));
    }
}
