#include "scena01_00.h"
#include "area/map.h"
#include "overlays/area/shared/Area_DrawDimQuad.h"
#include "overlays/area/shared/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F71C0(void) {
    POLY_G4* prim;

    AREA_DRAW_DIM_QUAD(3, 0);
}

MATCH void func_801F729C(void) {
    POLY_G4* prim;

    GFX_ADD_DITHERED_DRAW_MODE(GFX_LAYER_EFFECT_FRONT, GetTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_SUB, 0x140, 0) & 0xFFFF);
    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    SetSemiTrans(prim, 1);
    setXY4(prim, 0, 0, SCREEN_WIDTH, 0, 0, 100, SCREEN_WIDTH, 100);
    prim->r1 = 0xC8;
    prim->r0 = 0xC8;
    prim->g1 = 0xC8;
    prim->g0 = 0xC8;
    prim->b1 = 0xC8;
    prim->b0 = 0xC8;
    prim->r3 = 0;
    prim->r2 = 0;
    prim->g3 = 0;
    prim->g2 = 0;
    prim->b3 = 0;
    prim->b2 = 0;
    GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(POLY_G4));
    GFX_ADD_LAYER_DRAW_MODE(GFX_LAYER_EFFECT_FRONT, GetTPage(TPAGE_DEPTH_15BIT, TPAGE_ABR_QUARTER, 0x140, 0x140) & 0xFFFF);
}

MATCH void func_801F73B8(void) {
    SYS_DISPATCH_TASK(D_801FE26C, 1, g_Task);
}

MATCH void func_801F73FC(void) {
    Actor* work;
    s32    height;

    work              = TASK(Actor);
    work->pos.x.fixed = TO_COORD(96);
    work->pos.y.fixed = TO_COORD(17);
    height            = Area_HeightSample(work->pos.x.fixed, work->pos.y.fixed);

    work              = TASK(Actor);
    work->pos.z.fixed = height << 16;
    work->screen_x    = 0x180;
    work->screen_y    = 0x500;
    work->timer       = 0;
    Area_ClearWorkColumn();

    TASK(Actor)->header.mode += 1;
    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 2));
}

MATCH void func_801F7480(void) {
    func_801F7678(TASK(Actor)->timer);
    if ((g_FrameCount & 0x1) == 0) {
        Area_AddSpark();
    }
    Area_StepSparks();
    TASK(Actor)->timer = TASK(Actor)->timer + 4;
    if (TASK(Actor)->timer == 0) {
        TASK(Actor)->timer       = 32;
        TASK(Actor)->header.mode = TASK(Actor)->header.mode + 1;
    }
}

MATCH void func_801F752C(void) {
    func_801F7678(0xFF);
    if ((g_FrameCount & 0x1) == 0) {
        Area_AddSpark();
    }
    Area_StepSparks();
    if (--TASK(Actor)->timer == 0) {
        TASK(Actor)->timer = 252;
        TASK(Actor)->header.mode += 1;
    }
}

MATCH void func_801F75C8(void) {
    func_801F7678(TASK(Actor)->timer);
    Area_StepSparks();
    TASK(Actor)->timer = TASK(Actor)->timer - 4;
    if (TASK(Actor)->timer == 0) {
        TASK(Actor)->header.mode = TASK(Actor)->header.mode + 1;
    }
}

MATCH void func_801F7644(void) {
    if (!(Area_StepSparks() & BYTE_MASK)) {
        Actor_Clear();
    }
}

/* func_801F7678 */
MATCH void func_801F7678(s32 shade_arg) {
    DVECTOR  last_inner;
    DVECTOR  last_outer;
    DVECTOR  inner;
    DVECTOR  outer;
    s32      point[3];
    MATRIX   matrix;
    u8       camera[48];
    POLY_G4* prim;
    s32      angle;
    u32      shade;
    u32      color;
    u32      level;
    u8       i;

    Camera_SetMatrix(&matrix);
    angle    = 0;
    point[0] = TASK(Actor)->pos.x.fixed + ((FIELD(s16, g_Task, 0x2E) * rcos(0)) >> 4);
    point[1] = TASK(Actor)->pos.y.fixed + ((FIELD(s16, g_Task, 0x2E) * rsin(0)) >> 4);
    point[2] = TASK(Actor)->pos.z.fixed;
    Camera_ProjectPoint(point, &inner);
    point[2] = TASK(Actor)->pos.z.fixed + (FIELD(s16, g_Task, 0x30) << 16);
    Camera_ProjectPoint(point, &outer);
    shade = ((g_FrameCount & 1) << 2) | 0x40;
    for (i = 0; i < AREA_RING_POINTS; i++) {
        last_inner = inner;
        last_outer = outer;
        angle += AREA_RING_ANGLE_STEP;
        point[0] = TASK(Actor)->pos.x.fixed + ((FIELD(s16, g_Task, 0x2E) * rcos((u16)angle)) >> 4);
        point[1] = TASK(Actor)->pos.y.fixed + ((FIELD(s16, g_Task, 0x2E) * rsin((u16)angle)) >> 4);
        point[2] = TASK(Actor)->pos.z.fixed;
        Camera_ProjectPoint(point, &inner);
        point[2] = TASK(Actor)->pos.z.fixed + (FIELD(s16, g_Task, 0x30) << 16);
        Camera_ProjectPoint(point, &outer);

        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y), 0);
        Area_CellAddPrim(point[0], point[1], 0, sizeof(DR_MODE));
        prim = GFX_BeginPolyG4(1);
        setXY4(prim, last_inner.vx, last_inner.vy, last_outer.vx, last_outer.vy, inner.vx, inner.vy, outer.vx, outer.vy);
        level = shade_arg & BYTE_MASK;
        color = level * (shade & BYTE_MASK) >> 8;
        setRGB0(prim, color, color, color);
        setRGB1(prim, color, color, color);
        if ((u8)(i - 4) >= 8) {
            shade += 8;
        } else {
            shade -= 8;
        }
        level = shade_arg & BYTE_MASK;
        color = level * (shade & BYTE_MASK) >> 8;
        setRGB2(prim, color, color, color);
        setRGB3(prim, color, color, color);
        Area_CellAddPrim(point[0], point[1], 0, sizeof(POLY_G4));
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y), 0);
        Area_CellAddPrim(point[0], point[1], 0, sizeof(DR_MODE));
    }
}

#include "shared/Area_DrawSparkCell.h"

#include "shared/Area_ClearWorkColumn.h"

#include "shared/Area_AddSpark.h"

#include "shared/Area_StepSparks.h"

MATCH void func_801F7D04(void) {
    s16 screen_x;
    u16 next_x;
    s32 red;
    s32 blue;

    switch (g_AreaSceneMode) {
        case 0:
            break;
        case 1:
            TASK(Actor)->screen_x = 0;
            func_801F7DCC(64, 90, 255);
            break;
        case 2:
            screen_x = TASK(Actor)->screen_x;
            if (screen_x < 191) {
                next_x                = screen_x + 1;
                TASK(Actor)->screen_x = next_x;
            }
            red  = (s16)TASK(Actor)->screen_x;
            blue = 255 - red * 2;
            red += 64;
            if (blue < 0) {
                blue = 0;
            }
            func_801F7DCC(red, 90, blue);
            func_801F7EDC();
            break;
    }
}

MATCH void func_801F7DCC(s32 red, s32 green, s32 blue) {
    POLY_G4* prim;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(GFX_LAYER_BACKDROP, tpage);
    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    setXY4(prim, 0, 0, SCREEN_WIDTH - 1, 0, 0, SCREEN_HEIGHT - 1, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);
    setRGB0(prim, prim->r1 = red, prim->g1 = green, prim->b1 = blue);
    setRGB2(prim, prim->r3 = 0, prim->g3 = 0, prim->b3 = 0);
    GFX_AddPrim(GFX_LAYER_BACKDROP, sizeof(POLY_G4));
}

MATCH void func_801F7EDC(void) {
    POLY_F4* prim;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_SET_DRAW_MODE(tpage);
    GFX_AddPrim(GFX_LAYER_EFFECT, sizeof(DR_MODE));
    prim = (POLY_F4*)g_GfxPrimCursor;
    SetPolyF4(prim);
    SetSemiTrans(prim, 1);
    setXYWH(prim, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    setRGB0(prim, (s16)TASK(Actor)->screen_x / 8, 0, 0);
    GFX_AddPrim(GFX_LAYER_EFFECT, sizeof(POLY_F4));
}

MATCH void func_801F7FC4(void) {
    SYS_DISPATCH_BYTE(D_801FE29C, D_80146872);
}

/* func_801F8000 */
MATCH void Scene_EnterCedarWoods(void) {
    Scene_RunScenario(0);
    Game_RequestAreaChange(AREA_ID_CEDAR_WOODS_BEFORE_NUE, TO_COORD(87), TO_COORD(4), FACING_LEFT);
    *D_80144E90          = 0;
    g_ScriptVarsReq.word = 0;
    D_80146872           = 1;
}
