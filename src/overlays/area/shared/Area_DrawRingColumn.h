/* The scratchpad row read as the column's depth window: the word at 0x24 is how far below the column's z the strip's lower end reaches. */
typedef struct AreaRingDepthView {
    u8  pad_00[0x24];
    s32 depth; /* 0x24 */
} AreaRingDepthView;

ASSERT_OFFSET(AreaRingDepthView, depth, 0x24);

ASSERT_SIZE(AreaRingDepthView, 0x28);

/* Draws a column of light strips: textured, semi-transparent quads between successive points of a ring of radius 32 around the actor, rising along z until they pass the work window's ceiling; shade is the strip's grey level. A statement macro: an inline function loads shade as a variable and moves the bytes. func_801F3268 (area132) and func_801F4B6C (area134); every change must verify both. */
#define AREA_DRAW_RING_COLUMN(shade)                                        \
    VECTOR    org;                                                          \
    s32       pt[4];                                                        \
    DVECTOR   a;                                                            \
    DVECTOR   b;                                                            \
    u8        camera[48];                                                   \
    POLY_FT4* prim;                                                         \
    u16       angle;                                                        \
                                                                            \
    Camera_SetMatrix(camera);                                               \
    angle = (u16)SELF(Actor)->gravity;                                      \
    org   = *(VECTOR*)&SELF(Actor)->vx;                                     \
    pt[0] = org.vx + (rcos(angle) << 5);                                    \
    pt[1] = org.vy + (rsin(angle) << 5);                                    \
    pt[2] = org.vz - SELF(AreaRingDepthView)->depth;                        \
    if (pt[2] < SELF(Actor)->vz) {                                          \
        pt[2] = SELF(Actor)->vz;                                            \
    }                                                                       \
    Camera_ProjectPoint(pt, &a);                                            \
    pt[2] = org.vz;                                                         \
    if (SELF(Actor)->unk_1C < pt[2]) {                                      \
        pt[2] = SELF(Actor)->unk_1C;                                        \
    }                                                                       \
    Camera_ProjectPoint(pt, &b);                                            \
    while (org.vz < SELF(Actor)->unk_1C + TO_COORD(256)) {                  \
        prim = (POLY_FT4*)g_GfxPrimCursor;                                  \
        SetPolyFT4(prim);                                                   \
        SetSemiTrans(prim, 0);                                              \
        prim->x0 = a.vx;                                                    \
        prim->y0 = a.vy;                                                    \
        prim->x1 = b.vx;                                                    \
        prim->y1 = b.vy;                                                    \
        angle += ONE / 16;                                                  \
        org.vz += TO_COORD(16);                                             \
        pt[0] = org.vx + (rcos(angle) << 5);                                \
        pt[1] = org.vy + (rsin(angle) << 5);                                \
        pt[2] = org.vz - SELF(AreaRingDepthView)->depth;                    \
        if (pt[2] < SELF(Actor)->vz) {                                      \
            pt[2] = SELF(Actor)->vz;                                        \
        }                                                                   \
        Camera_ProjectPoint(pt, &a);                                        \
        pt[2] = org.vz;                                                     \
        if (SELF(Actor)->unk_1C < pt[2]) {                                  \
            pt[2] = SELF(Actor)->unk_1C;                                    \
        }                                                                   \
        Camera_ProjectPoint(pt, &b);                                        \
        prim->x2 = a.vx;                                                    \
        prim->y2 = a.vy;                                                    \
        prim->x3 = b.vx;                                                    \
        prim->y3 = b.vy;                                                    \
        prim->u0 = 0x1F;                                                    \
        prim->v0 = 0xFF;                                                    \
        prim->u1 = 0x1F;                                                    \
        prim->v1 = 0xE0;                                                    \
        prim->u2 = 0;                                                       \
        prim->v2 = 0xFF;                                                    \
        prim->u3 = 0;                                                       \
        prim->v3 = 0xE0;                                                    \
        setRGB0(prim, shade, shade, shade);                                 \
        prim->tpage = GetTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 448, 256); \
        prim->clut  = GetClut(0, 485);                                      \
        Area_CellAddPrim(pt[0], pt[1], 2, sizeof(POLY_FT4));                \
    }
