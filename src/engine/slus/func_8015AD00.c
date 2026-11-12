#include "engine/slus/slus.h"
#include <inline_c.h>

/* One 0x28-byte textured-quad record of the table at work->unk_50: clut index,
 * four vertices, the face normal and four packed uv pairs. */
typedef struct PanelPiece {
    s16 clut;    /* 0x00 */
    u16 v[4][3]; /* 0x02 */
    s16 n[3];    /* 0x1A */
    u16 uv[4];   /* 0x20 */
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
    u16            vv;
    s32            i;

    vec = D_80149BF0;
    PushMatrix();
    count = g_Task->range_54.table[0];
    func_8015B410(&m);
    SetRotMatrix(&m);
    SetTransMatrix(&m);
    if (g_Task->unk_48 == 0) {
        normal.vx = normal.vy = normal.vz = g_Task->scale.x;
        ScaleMatrix(&m, &normal);
    }
    light = m;
    func_8015B2AC(D_801481B8.m[0], &g_Task->unk_64);
    func_8015B4B0(&light);
    SetLightMatrix(&D_801481B8);

    abr = g_Task->range_54.table[3];
    if ((abr & 0x40) == 0) {
        abr = 2;
    }
    piece = (PanelPiece*)g_Task->script;
    tpage = GetTPage(0, abr & 0x3, 704, 256);
    prim  = g_GfxPrimCursor;
    p     = prim;
    if ((u8*)(g_FrameBufferIndex * 0x9000 + PRIM_ARENA_BASE) < (prim + count * 0x28)) {
        return 0;
    }
    i = 0;
    if (count != 0) {
        do {
            quad = (PanelQuadPrim*)p;
            SetPolyFT4(&quad->ft4);

            vv = piece->v[0][0];
            FAKE_BARRIER(); /* FAKE: pin the vertex load into its retail store slot. */
            D_1F800014[0].vx = vv;
            FAKE_BARRIER(); /* FAKE: pin the vertex load into its retail store slot. */
            vv = piece->v[0][1];
            FAKE_BARRIER(); /* FAKE: pin the vertex load into its retail store slot. */
            SP_REF(u16, 0x16u) = vv;
            FAKE_BARRIER(); /* FAKE: pin the vertex load into its retail store slot. */
            vv = piece->v[0][2];
            FAKE_BARRIER(); /* FAKE: pin the vertex load into its retail store slot. */
            SP_REF(u16, 0x18u) = vv;
            FAKE_BARRIER(); /* FAKE: pin the vertex load into its retail store slot. */
            vv = piece->v[1][0];
            FAKE_BARRIER(); /* FAKE: pin the vertex load into its retail store slot. */
            D_1F800014[1].vx = vv;
            FAKE_BARRIER(); /* FAKE: pin the vertex load into its retail store slot. */
            vv = piece->v[1][1];
            FAKE_BARRIER(); /* FAKE: pin the vertex load into its retail store slot. */
            SP_REF(u16, 0x1Eu) = vv;
            FAKE_BARRIER(); /* FAKE: pin the vertex load into its retail store slot. */
            vv = piece->v[1][2];
            FAKE_BARRIER(); /* FAKE: pin the vertex load into its retail store slot. */
            SP_REF(u16, 0x20u) = vv;
            FAKE_BARRIER(); /* FAKE: pin the vertex load into its retail store slot. */
            vv = piece->v[2][0];
            FAKE_BARRIER(); /* FAKE: pin the vertex load into its retail store slot. */
            D_1F800014[2].vx = vv;
            FAKE_BARRIER(); /* FAKE: pin the vertex load into its retail store slot. */
            vv = piece->v[2][1];
            FAKE_BARRIER(); /* FAKE: pin the vertex load into its retail store slot. */
            SP_REF(u16, 0x26u) = vv;
            FAKE_BARRIER(); /* FAKE: pin the vertex load into its retail store slot. */
            vv = piece->v[2][2];
            FAKE_BARRIER(); /* FAKE: pin the vertex load into its retail store slot. */
            SP_REF(u16, 0x28u) = vv;
            FAKE_BARRIER(); /* FAKE: pin the vertex load into its retail store slot. */
            vv = piece->v[3][0];
            FAKE_BARRIER(); /* FAKE: pin the vertex load into its retail store slot. */
            D_1F800014[3].vx = vv;
            FAKE_BARRIER(); /* FAKE: pin the vertex load into its retail store slot. */
            vv = piece->v[3][1];
            FAKE_BARRIER(); /* FAKE: pin the vertex load into its retail store slot. */
            SP_REF(u16, 0x2Eu) = vv;
            FAKE_BARRIER(); /* FAKE: pin the vertex load into its retail store slot. */
            vv = piece->v[3][2];
            FAKE_BARRIER(); /* FAKE: pin the vertex load into its retail store slot. */
            SP_REF(u16, 0x30u) = vv;
            FAKE_BARRIER(); /* FAKE: pin the vertex load into its retail store slot. */
            normal.vx        = piece->n[0];
            normal.vy        = piece->n[1];
            normal.vz        = piece->n[2];
            quad->halves.uv0 = piece->uv[0];
            quad->halves.uv1 = piece->uv[1];
            quad->halves.uv2 = piece->uv[2];
            quad->halves.uv3 = piece->uv[3];

            gte_ldv0(&D_1F800014[0]);
            gte_rtps();
            gte_stsxy(&quad->ft4.x0);
            gte_stszotz(&z);
            otz           = z;
            sort_list->z  = otz;
            sort_list->z0 = otz;

            gte_ldv0(&D_1F800014[1]);
            gte_rtps();
            gte_stsxy(&quad->ft4.x1);
            gte_stszotz(&z);
            if (sort_list->z < z) {
                sort_list->z = z;
            }

            gte_ldv0(&D_1F800014[2]);
            gte_rtps();
            gte_stsxy(&quad->ft4.x2);
            gte_stszotz(&z);
            if (sort_list->z < z) {
                sort_list->z = z;
            }

            gte_ldv0(&D_1F800014[3]);
            gte_rtps();
            gte_stsxy(&quad->ft4.x3);
            gte_stszotz(&z);
            if (sort_list->z < z) {
                sort_list->z = z;
            }

            sort_list->work      = (u8*)g_Task;
            sort_list->primitive = p;
            quad->ft4.r0         = g_Task->tint.bytes.unk_5D;
            quad->ft4.g0         = g_Task->tint.bytes.unk_5E;
            quad->ft4.b0         = g_Task->tint.bytes.unk_5F;
            if ((g_Task->range_54.table[3] & 0x80) != 0) {
                VectorNormalS(&normal, D_1F800014);
                color.r  = g_Task->tint.bytes.unk_5D;
                color.g  = g_Task->tint.bytes.unk_5E;
                color.b  = g_Task->tint.bytes.unk_5F;
                color.cd = quad->ft4.code;
                NormalColorCol(D_1F800014, &color, (CVECTOR*)&quad->ft4.r0);
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
