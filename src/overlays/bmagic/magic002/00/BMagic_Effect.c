#include "magic002_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/BMagic_DispatchMode.h"

MATCH void func_801EEC78(void) {
    u32 index;

    index                                            = Battle_AllocEffect(3, 1) & BYTE_MASK;
    g_BattleEffects[index].header.mode               = 0;
    g_BattleEffects[index].unk_0C                    = g_Game.members[0].screen_x.signed_value << 16;
    g_BattleEffects[index].unk_10                    = g_Game.members[0].screen_y.signed_value << 16;
    D_801EC344[index].value                          = 0;
    g_BattleEffects[index].unk_18                    = 40;
    g_BattleEffects[index].arg.unk_09                = 0;
    g_BattleEffects[index].unk_1C                    = ((g_Battle.selected_actor->screen_x.signed_value - g_Game.members[0].screen_x.signed_value) << 16) / 10;
    D_801EC350[index].value                          = ((g_Battle.selected_actor->screen_y.signed_value - g_Game.members[0].screen_y.signed_value) << 16) / 10;
    g_BattleEffects[index].target_index.target_index = 0x100;
    D_801EC388[index].value                          = 0x100;
    D_801EC2E0->target.effect                        = &g_BattleEffects[index];
    SELF(PartyMember)->header.mode += 1;
}

MATCH void func_801EEDE4(void) {
    if (D_801EC2E0->target.party->unk_09 >= 0x28) {
        SELF(PartyMember)->header.mode++;
    }
}

#include "shared/Effect_StartPlaying.h"

MATCH void func_801EEE64(void) {
    BMagic_DispatchTaskPair(func_801EEEBC, func_801EEF84);
}

MATCH void func_801EEEBC(void) {
    PartyMember* work;
    PartyMember* draw;

    work = SELF(PartyMember);
    work->unk_14 += 0x100;
    work->unk_18 += 4;
    work->unk_0C += work->unk_1C;
    work->unk_09++;
    work->unk_10 += work->unk_20;
    draw = SELF(PartyMember);
    func_801EF1FC(draw->unk_0C >> 16, draw->unk_10 >> 16, (draw->unk_18 << 15) >> 16, draw->unk_14, draw->unk_60, draw->unk_58);
    if (SELF(PartyMember)->unk_09 >= 0xB) {
        SELF(PartyMember)->header.mode++;
    }
}

MATCH void func_801EEF84(void) {
    PartyMember* work;
    PartyMember* draw;

    work = SELF(PartyMember);
    work->unk_60 += 4;
    work->unk_09++;
    work->unk_58 -= 8;
    work->unk_14 += 0x20;
    draw = SELF(PartyMember);
    func_801EF1FC(draw->unk_0C >> 16, draw->unk_10 >> 16, (draw->unk_18 << 15) >> 16, draw->unk_14, draw->unk_60, draw->unk_58);
    if (SELF(PartyMember)->unk_09 >= 0x29) {
        Effect_Reset();
    }
}

MATCH void func_801EF030(s32 x, s32 y, u16 radius, s32 phase) {
    SVECTOR  points[6];
    POLY_F3* prim;
    s32      angle;
    u16      tpage;
    u8       i;

    for (i = 0; i < 6; i++) {
        angle        = (i << 12) / 6 + (u16)phase;
        points[i].vx = x + ((rsin(angle) * radius) >> 12);
        points[i].vy = y + ((rcos(angle) * radius) >> 12);
    }
    tpage = GetTPage(0x3C0, 0x100, 0, 0);
    GFX_ADD_DRAW_MODE(tpage);
    for (i = 0; i < 2; i++) {
        prim = (POLY_F3*)g_GfxPrimCursor;
        SetPolyF3(prim);
        setXY3(prim, points[i].vx, points[i].vy, points[i + 2].vx, points[i + 2].vy, points[i + 4].vx, points[i + 4].vy);
        setRGB0(prim, 0xFF, 0xFF, 0);
        SetSemiTrans(prim, 1);
        GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_F3));
    }
}

/* Draws the magic002 effect's shaded sphere: rings of ten points from the south pole to the equator, each ring quad also drawn mirrored below the centre. */
#ifdef NON_MATCHING
NON_MATCHING void func_801EF1FC(s16 x0, s16 y0, s16 x1, s16 y1, s16 x2, s16 y2) {
    POLY_G4* prim;
    s16      prev_x[12];
    s16      prev_z[12];
    s16      ring_x[12];
    s16      ring_z[12];
    u8       prev_light[16];
    u8       ring_light[16];
    u8       prev_mirror[16];
    u8       ring_mirror[16];
    VECTOR   centre;
    VECTOR   vec;
    SVECTOR  normal;
    SVECTOR  light = D_801EEC10;
    s16      quad_x[4];
    s16      quad_y[4];
    s32      avg_x;
    s32      avg_z;
    s32      mid_height;
    s32      ring_radius;
    s32      dot;
    s16      angle;
    s16      prev_height;
    s16      ring_height;
    s16      i;
    s16      j;
    s8       point;
    u16      tpage;

    tpage = GetTPage(0x3C0, 0x100, 0, 0);
    GFX_ADD_DRAW_MODE(tpage);

    ring_height = -x1;
    for (i = 0; i < 10; i++) {
        ring_x[i] = 0;
        ring_z[i] = 0;
        vec.vx    = ring_x[i];
        vec.vy    = ring_height;
        vec.vz    = ring_z[i];
        VectorNormalS(&vec, &normal);
        dot            = normal.vx * light.vx + normal.vy * light.vy + normal.vz * light.vz;
        ring_light[i]  = (u8)((u32)SquareRoot0(dot) >> 4);
        normal.vy      = -normal.vy;
        dot            = normal.vx * light.vx + normal.vy * light.vy + normal.vz * light.vz;
        ring_mirror[i] = (u8)((u32)SquareRoot0(dot) >> 4);
    }

    prev_height = ring_height;
    for (i = 1; i < 5; i++) {
        for (j = 0; j < 10; j++) {
            prev_x[j]      = ring_x[j];
            prev_z[j]      = ring_z[j];
            prev_light[j]  = ring_light[j];
            prev_mirror[j] = ring_mirror[j];
        }
        ring_x[0]   = FIXED_MUL(-x1, rsin(i << 8));
        ring_z[0]   = 0;
        ring_height = FIXED_MUL(-x1, rcos(i << 8));
        ring_radius = ring_x[0];
        vec.vx      = ring_x[0];
        vec.vy      = ring_height;
        vec.vz      = ring_z[0];
        VectorNormalS(&vec, &normal);
        dot            = normal.vx * light.vx + normal.vy * light.vy + normal.vz * light.vz;
        ring_light[0]  = (u8)((u32)SquareRoot0(dot) >> 4);
        normal.vy      = -normal.vy;
        dot            = normal.vx * light.vx + normal.vy * light.vy + normal.vz * light.vz;
        ring_mirror[0] = (u8)((u32)SquareRoot0(dot) >> 4);

        angle = (u8)y1;
        for (point = 1; angle < 0x800; point++, angle += 0x100) {
            ring_x[point] = FIXED_MUL(ring_radius, rcos(angle));
            ring_z[point] = FIXED_MUL(ring_radius, rsin(angle));
            vec.vx        = ring_x[point];
            vec.vy        = ring_height;
            vec.vz        = ring_z[point];
            VectorNormalS(&vec, &normal);
            dot                = normal.vx * light.vx + normal.vy * light.vy + normal.vz * light.vz;
            ring_light[point]  = (u8)((u32)SquareRoot0(dot) >> 4);
            normal.vy          = -normal.vy;
            dot                = normal.vx * light.vx + normal.vy * light.vy + normal.vz * light.vz;
            ring_mirror[point] = (u8)((u32)SquareRoot0(dot) >> 4);
        }

        ring_x[point] = -ring_radius;
        ring_z[point] = 0;
        vec.vx        = ring_x[point];
        vec.vy        = ring_height;
        vec.vz        = ring_z[point];
        VectorNormalS(&vec, &normal);
        dot                = normal.vx * light.vx + normal.vy * light.vy + normal.vz * light.vz;
        ring_light[point]  = (u8)((u32)SquareRoot0(dot) >> 4);
        normal.vy          = -normal.vy;
        dot                = normal.vx * light.vx + normal.vy * light.vy + normal.vz * light.vz;
        ring_mirror[point] = (u8)((u32)SquareRoot0(dot) >> 4);
        point++;

        for (j = 0; j < point - 1; j++) {
            avg_x      = (prev_x[j] + prev_x[j + 1] + ring_x[j] + ring_x[j + 1]) / 4;
            avg_z      = (prev_z[j] + prev_z[j + 1] + ring_z[j] + ring_z[j + 1]) / 4;
            mid_height = (prev_height + ring_height) / 2;
            centre.vx  = (avg_x * x2) >> 8;
            centre.vy  = (mid_height * x2) >> 8;
            centre.vz  = (avg_z * x2) >> 8;

            quad_x[0] = ((prev_x[j] - avg_x) * y2) >> 8;
            quad_x[1] = ((prev_x[j + 1] - avg_x) * y2) >> 8;
            quad_x[2] = ((ring_x[j] - avg_x) * y2) >> 8;
            quad_x[3] = ((ring_x[j + 1] - avg_x) * y2) >> 8;
            quad_y[0] = ((prev_height - mid_height) * y2) >> 8;
            quad_y[1] = quad_y[0];
            quad_y[2] = ((ring_height - mid_height) * y2) >> 8;
            quad_y[3] = quad_y[2];

            prim = (POLY_G4*)g_GfxPrimCursor;
            SetPolyG4(prim);
            setXY4(prim, x0 + centre.vx + quad_x[0], y0 + centre.vy + quad_y[0], x0 + centre.vx + quad_x[1], y0 + centre.vy + quad_y[1], x0 + centre.vx + quad_x[2], y0 + centre.vy + quad_y[2],
                   x0 + centre.vx + quad_x[3], y0 + centre.vy + quad_y[3]);
            setRGB0(prim, prev_light[j], prev_light[j], 0);
            setRGB1(prim, prev_light[j], prev_light[j], 0);
            setRGB2(prim, ring_light[j + 1], ring_light[j + 1], 0);
            setRGB3(prim, ring_light[j + 1], ring_light[j + 1], 0);
            SetSemiTrans(prim, 1);
            GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_G4));

            prim = (POLY_G4*)g_GfxPrimCursor;
            SetPolyG4(prim);
            setXY4(prim, x0 + centre.vx + quad_x[0], y0 - centre.vy - quad_y[0], x0 + centre.vx + quad_x[1], y0 - centre.vy - quad_y[1], x0 + centre.vx + quad_x[2], y0 - centre.vy - quad_y[2],
                   x0 + centre.vx + quad_x[3], y0 - centre.vy - quad_y[3]);
            setRGB0(prim, prev_mirror[j], prev_mirror[j], 0);
            setRGB1(prim, prev_mirror[j], prev_mirror[j], 0);
            setRGB2(prim, ring_mirror[j + 1], ring_mirror[j + 1], 0);
            setRGB3(prim, ring_mirror[j + 1], ring_mirror[j + 1], 0);
            SetSemiTrans(prim, 1);
            GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_G4));
        }
        prev_height = ring_height;
    }
}
#else
INCLUDE_ASM(func_801EF1FC);
#endif
