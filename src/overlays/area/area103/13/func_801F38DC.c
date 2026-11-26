#include "area103_13.h"
#include "overlays/area/shared/Area_DrawRingColumn.h"

MATCH void func_801F38DC(void) {
    VECTOR    org;
    s32       pt[4];
    DVECTOR   a;
    DVECTOR   b;
    u8        camera[32];
    POLY_FT4* prim;
    u16       angle;

    Camera_SetMatrix(camera);
    angle = (u16)SELF(Actor)->gravity;
    org   = *(VECTOR*)&SELF(Actor)->vx;
    pt[0] = org.vx + (rcos(angle) << 5);
    pt[1] = org.vy + (rsin(angle) << 5);
    pt[2] = org.vz - SELF(AreaRingDepthView)->depth;
    if (pt[2] < SELF(Actor)->vz) {
        pt[2] = SELF(Actor)->vz;
    }
    Camera_ProjectPoint(pt, &a);
    pt[2] = org.vz;
    if (SELF(Actor)->unk_1C < pt[2]) {
        pt[2] = SELF(Actor)->unk_1C;
    }
    Camera_ProjectPoint(pt, &b);
    while (org.vz < SELF(Actor)->unk_1C + TO_COORD(256)) {
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetSemiTrans(prim, 0);
        setXY2(prim, a.vx, a.vy, b.vx, b.vy);
        angle += ONE / 16;
        org.vz += TO_COORD(16);
        pt[0] = org.vx + (rcos(angle) << 5);
        pt[1] = org.vy + (rsin(angle) << 5);
        pt[2] = org.vz - SELF(AreaRingDepthView)->depth;
        if (pt[2] < SELF(Actor)->vz) {
            pt[2] = SELF(Actor)->vz;
        }
        Camera_ProjectPoint(pt, &a);
        pt[2] = org.vz;
        if (SELF(Actor)->unk_1C < pt[2]) {
            pt[2] = SELF(Actor)->unk_1C;
        }
        Camera_ProjectPoint(pt, &b);
        prim->x2 = a.vx;
        prim->y2 = a.vy;
        prim->x3 = b.vx;
        prim->y3 = b.vy;
        setUV4(prim, 0x7F, 0xBF, 0x7F, 0xA0, 0x60, 0xBF, 0x60, 0xA0);
        setRGB0(prim, 128, 128, 128);
        prim->tpage = GetTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256);
        prim->clut  = GetClut(0, 487);
        GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_FT4));
    }
}
