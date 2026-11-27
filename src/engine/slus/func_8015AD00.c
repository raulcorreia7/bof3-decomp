#include "engine/slus/slus.h"
#include <inline_c.h>

/* One 0x28-byte textured-quad record of the table at work->unk_50: clut index,
 * four vertices, the face normal and four packed uv pairs. */
typedef struct PanelPiece {
    s16 clut;           /* 0x00 */
    u16 vertices[4][3]; /* 0x02 */
    s16 normal[3];      /* 0x1A */
    u16 uv[4];          /* 0x20 */
} PanelPiece;

/* One 0x28-byte primitive this function builds at the primitive cursor: a
 * POLY_FT4, with a halves view over the uv pairs retail stores whole. */
typedef union PanelQuadPrim {
    POLY_FT4 ft4;

    struct {
        u8  pad_00[0x0C];
        u16 uv0; /* 0x0C */
        u8  pad_0E[0x06];
        u16 uv1; /* 0x14 */
        u8  pad_16[0x06];
        u16 uv2; /* 0x1C */
        u8  pad_1E[0x06];
        u16 uv3; /* 0x24 */
        u8  pad_26[0x02];
    } halves;
} PanelQuadPrim;

/* projects the panel's textured-quad table through the GTE into
 * the primitive list, fills one sort-list row per quad and returns the quad
 * count.
 */
MATCH s8 func_8015AD00(PanelSortItem* sort_list) {
    CVECTOR color;
    FAKE_STACK_PADS(VECTOR, 1); /* FAKE: retail keeps a dead 16-byte VECTOR slot at sp+0x18. */
    VECTOR         normal;
    VECTOR         vec;
    MATRIX         light;
    MATRIX         m;
    s32            z;
    u8             abr;
    u16            count;
    u16            tpage;
    u8*            prim;
    u8*            p;
    PanelPiece*    piece;
    PanelQuadPrim* quad;
    u16            otz;
    s32            i;

    vec = D_80149BF0;
    PushMatrix();
    count = SELF(Actor)->range_54.table[0];
    Actor_BuildTransformMatrix(&m);
    SetRotMatrix(&m);
    SetTransMatrix(&m);
    if (SELF(Actor)->unk_48 == 0) {
        normal.vx = normal.vy = normal.vz = SELF(Actor)->scale.x;
        ScaleMatrix(&m, &normal);
    }
    light = m;
    func_8015B2AC(D_801481B8.m[0], &SELF(Actor)->angle_x);
    Camera_ApplyMatrix(&light);
    SetLightMatrix(&D_801481B8);

    abr = SELF(Actor)->range_54.table[3];
    if ((abr & 0x40) == 0) {
        abr = 2;
    }
    piece = (PanelPiece*)SELF(Actor)->script;
    tpage = GetTPage(TPAGE_DEPTH_4BIT, abr & 0x3, 704, 256);
    prim  = g_GfxPrimCursor;
    p     = prim;
    if ((u8*)(g_GfxBufferIndex * 0x9000 + PRIM_ARENA_BASE) < (prim + count * 0x28)) {
        return 0;
    }
    i = 0;
    if (count != 0) {
        do {
            quad = (PanelQuadPrim*)p;
            SetPolyFT4(&quad->ft4);

            setVector(&g_ScratchPadVectors[0], piece->vertices[0][0], piece->vertices[0][1], piece->vertices[0][2]);
            setVector(&g_ScratchPadVectors[1], piece->vertices[1][0], piece->vertices[1][1], piece->vertices[1][2]);
            setVector(&g_ScratchPadVectors[2], piece->vertices[2][0], piece->vertices[2][1], piece->vertices[2][2]);
            setVector(&g_ScratchPadVectors[3], piece->vertices[3][0], piece->vertices[3][1], piece->vertices[3][2]);
            setVector(&normal, piece->normal[0], piece->normal[1], piece->normal[2]);
            quad->halves.uv0 = piece->uv[0];
            quad->halves.uv1 = piece->uv[1];
            quad->halves.uv2 = piece->uv[2];
            quad->halves.uv3 = piece->uv[3];

            gte_ldv0(&g_ScratchPadVectors[0]);
            gte_rtps();
            gte_stsxy(&quad->ft4.x0);
            gte_stszotz(&z);
            otz                 = z;
            sort_list->z        = otz;
            sort_list->tagged_z = otz;

            gte_ldv0(&g_ScratchPadVectors[1]);
            gte_rtps();
            gte_stsxy(&quad->ft4.x1);
            gte_stszotz(&z);
            if (sort_list->z < z) {
                sort_list->z = z;
            }

            gte_ldv0(&g_ScratchPadVectors[2]);
            gte_rtps();
            gte_stsxy(&quad->ft4.x2);
            gte_stszotz(&z);
            if (sort_list->z < z) {
                sort_list->z = z;
            }

            gte_ldv0(&g_ScratchPadVectors[3]);
            gte_rtps();
            gte_stsxy(&quad->ft4.x3);
            gte_stszotz(&z);
            if (sort_list->z < z) {
                sort_list->z = z;
            }

            sort_list->work      = SELF(u8);
            sort_list->primitive = p;
            setRGB0(&quad->ft4, SELF(Actor)->tint.bytes.rgb.r, SELF(Actor)->tint.bytes.rgb.g, SELF(Actor)->tint.bytes.rgb.b);
            if ((SELF(Actor)->range_54.table[3] & 0x80) != 0) {
                VectorNormalS(&normal, g_ScratchPadVectors);
                color.r  = SELF(Actor)->tint.bytes.rgb.r;
                color.g  = SELF(Actor)->tint.bytes.rgb.g;
                color.b  = SELF(Actor)->tint.bytes.rgb.b;
                color.cd = quad->ft4.code;
                NormalColorCol(g_ScratchPadVectors, &color, (CVECTOR*)&quad->ft4.r0);
            }

            quad->ft4.tpage = tpage;
            quad->ft4.clut  = GetClut(piece->clut * 16, STAGE_PALETTE_Y + 3);
            SetSemiTrans(p, (abr >> 6) & 0x1);

            i++;
            sort_list++;
            p += 0x28;
            piece++;
        } while ((u16)i < count);
    }
    g_GfxPrimCursor = prim + count * 0x28;
    PopMatrix();
    return count;
}
