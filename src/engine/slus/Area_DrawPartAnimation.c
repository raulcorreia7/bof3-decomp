#include "engine/slus/slus.h"

/* draws the part list of one scene record: per run it builds an FT4 primitive from four packed cells (byte offsets
 * around the origin), projects the quad, picks one of the run's animation frames from g_FrameCount modulo the run
 * length and queues it.
 */
MATCH void Area_DrawPartAnimation(ScenePart* parts, s32 origin_x, s32 origin_y) {
    SVECTOR    verts[4];
    ScenePart* run;
    POLY_FT4*  prim;
    long       depth;
    long       flag;
    s32        i;
    s32        n;
    u32        skip;

    if ((Area_TestCondition(parts->head.id) << 24) == 0) {
        return;
    }
    origin_x = (origin_x - 0x80) << 7;
    origin_y = (origin_y - 0x80) << 7;
    n        = 1;
    if (parts->head.count != 1) {
        do {
            prim = (POLY_FT4*)g_GfxPrimCursor;
            SetPolyFT4(prim);
            SetShadeTex(prim, 0);
            for (i = 0; i < 4; i++) {
                verts[i].vx = origin_x + parts[n].vertex.x * 2;
                verts[i].vy = origin_y + parts[n].vertex.y * 2;
                verts[i].vz = parts[n].raw;
                n++;
            }
            RotTransPers4(&verts[1], &verts[2], &verts[3], &verts[0], (long*)&prim->x1, (long*)&prim->x2,
                          (long*)&prim->x3, (long*)&prim->x0, &depth, &flag);
            i    = 0;
            skip = (u32)g_FrameCount % parts[n].pick.table;
            run  = &parts[n];
        scan:
            if ((s32)skip >= *(i + run->pick.limit)) {
                i++;
                goto scan;
            }
            skip = (u32)(run->pick.extra + 5) >> 2;
            func_80155560((run + skip)[i].raw, prim, 1);
            n += skip + run->pick.extra;
            GFX_AddPrim(g_AreaDrawMode, sizeof(POLY_FT4));
        } while (n != parts->head.count);
    }
}
