#include "engine/slus/slus.h"

#include <inline_c.h>

/* draws one textured quadrangle per five-word part in the list at
 * parts: four vertices built from signed byte offsets around the projected
 * origin, and a primitive code chosen from the part texture word.
 */
MATCH void Area_DrawQuad(ScenePart* parts, s32 origin_x, s32 origin_y) {
    SVECTOR    verts[4];
    ScenePart* rec;
    POLY_FT4*  prim;
    s32        i;
    s32        n;

    if ((Area_TestCondition(parts->head.id) << 24) == 0) {
        return;
    }
    origin_x = (origin_x - 0x80) << 7;
    origin_y = (origin_y - 0x80) << 7;
    n        = 1;
    if (parts->head.count != 1) {
        do {
            rec         = &parts[n];
            verts[0].vx = origin_x + rec[0].vertex.x * 2;
            verts[0].vy = origin_y + rec[0].vertex.y * 2;
            verts[0].vz = rec[0].raw;
            gte_ldv0(&verts[0]);
            gte_rtps();
            prim = (POLY_FT4*)g_GfxPrimCursor;
            gte_stsxy((s16*)((u8*)prim + 8));
            if (((u16)(prim->x0 + 0x3B) < 0x1B7) && ((u16)(prim->y0 + 0x95) < 0x1C1)) {
                SetPolyFT4(prim);
                SetShadeTex(prim, 0);
                for (i = 1; i < 4; i++) {
                    verts[i].vx = origin_x + rec[i].vertex.x * 2;
                    verts[i].vy = origin_y + rec[i].vertex.y * 2;
                    verts[i].vz = rec[i].raw;
                }
                gte_ldv3c(&verts[1]);
                func_80155560(rec[4].raw, prim, 1);
                gte_rtpt();
                GFX_AddPrim((rec[4].raw & 0x40000000) ? 7 : 4, 0x28);
                gte_stsxy3((s16*)((u8*)prim + 0x10), (s16*)((u8*)prim + 0x18), (s16*)((u8*)prim + 0x20));
            }
            n += 5;
        } while (n != parts->head.count);
    }
}
