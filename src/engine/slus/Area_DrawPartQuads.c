#include "engine/slus/slus.h"

#include <inline_c.h>

/* projects the anchor vertex of each five-record part in the list at
 * parts and, when it lands on screen, builds a textured quadrangle from the
 * part's four vertex offsets and packed colour word, appending it to the
 * ordering-table bucket its flag bits select.
 */
MATCH void Area_DrawPartQuads(ScenePart* parts, s32 shift_x, s32 shift_y) {
    SVECTOR    verts[4];
    ScenePart* p;
    POLY_FT4*  prim;
    s32        i;
    s32        n;
    u32        mask;
    u8         ot;

    if ((Area_TestCondition(parts->head.id) << 24) == 0) {
        return;
    }
    shift_x = (shift_x - 0x80) << 7;
    shift_y = (shift_y - 0x80) << 7;
    for (n = 1; n != parts->head.count; n += 5) {
        verts[0].vx = shift_x + parts[n].vertex.x * 2;
        verts[0].vy = shift_y + parts[n].vertex.y * 2;
        verts[0].vz = parts[n].raw;
        gte_ldv0(&verts[0]);
        gte_rtps();
        p    = &parts[n];
        prim = (POLY_FT4*)g_GfxPrimCursor;
        gte_stsxy2(&prim->x0);
        if ((u16)(prim->x0 + 0x63) < 0x207U && (u16)(prim->y0 + 0x95) < 0x1C1U) {
            SetPolyFT4(prim);
            SetShadeTex(prim, 0);
            for (i = 1; i < 4; i++) {
                verts[i].vx = shift_x + p[i].vertex.x * 2;
                verts[i].vy = shift_y + p[i].vertex.y * 2;
                verts[i].vz = p[i].raw;
            }
            gte_ldv3c(&verts[1]);
            func_80155560(parts[n + 4].raw, prim, 1);
            gte_rtpt();
            if (parts[n + 4].raw & 0x4000) {
                /* Per-arm: keeps the constant's load inside the loop. */
                mask = 0x40000000;
                ot   = 4;
                if (parts[n + 4].raw & mask) {
                    ot = 7;
                }
            } else {
                mask = 0x40000000;
                ot   = 6;
                if (!(parts[n + 4].raw & mask)) {
                    ot = g_AreaDrawMode;
                }
            }
            GFX_AddPrim(ot, sizeof(POLY_FT4));
            gte_stsxy3(&prim->x1, &prim->x2, &prim->x3);
        }
    }
}
