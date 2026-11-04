#include "engine/slus/slus.h"

/* draws one Gouraud-shaded quadrangle per eight-record part in the
 * list at parts: four vertices built from signed byte offsets around the
 * projected origin, four packed RGBA colours, and a draw mode selected from
 * the first colour's tpage bits.
 */
MATCH void Area_DrawGouraudQuads(ScenePart* parts, s32 shift_x, s32 shift_y) {
    SVECTOR    verts[4];
    SVECTOR*   v;
    long       flag;
    long       p;
    ScenePart* rec;
    POLY_G4*   prim;
    s32        n;
    s32        i;
    s32        mode;

    if ((Area_TestCondition(parts->head.id) << 24) == 0) {
        return;
    }
    shift_x = (shift_x - 0x80) << 7;
    shift_y = (shift_y - 0x80) << 7;
    n       = 1;
    if (parts->head.count != 1) {
        v   = verts;
        rec = &parts[1];
        do {
            mode = getTPage(1, rec[4].color.tpage, 320, 256);
            SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, mode, NULL);
            GFX_AddPrim(g_AreaDrawMode, 0xC);
            prim = (POLY_G4*)g_GfxPrimCursor;
            SetPolyG4(prim);
            for (i = 0; i < 4; i++, rec++, n++) {
                v[i].vx = shift_x + parts[n].vertex.x * 2;
                v[i].vy = shift_y + parts[n].vertex.y * 2;
                v[i].vz = parts[n].raw;
            }
            RotTransPers4(&verts[1], &verts[2], &verts[3], &verts[0], (long*)&prim->x1, (long*)&prim->x2,
                          (long*)&prim->x3, (long*)&prim->x0, &p, &flag);
            SetSemiTrans(prim, (s32)(rec[0].raw >> 31));
            setRGB0(prim, (u8)(rec[0].raw >> 16), (u8)(rec[0].raw >> 8), (u8)rec[0].raw);
            rec++;
            setRGB1(prim, (u8)(rec[0].raw >> 16), (u8)(rec[0].raw >> 8), (u8)rec[0].raw);
            rec++;
            setRGB2(prim, (u8)(rec[0].raw >> 16), (u8)(rec[0].raw >> 8), (u8)rec[0].raw);
            rec++;
            setRGB3(prim, (u8)(rec[0].raw >> 16), (u8)(rec[0].raw >> 8), (u8)rec[0].raw);
            rec++;
            n += 4;
            GFX_AddPrim(g_AreaDrawMode, 0x24);
        } while (n != parts->head.count);
    }
    mode = getTPage(1, 0, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, mode, NULL);
    GFX_AddPrim(g_AreaDrawMode, 0xC);
}
