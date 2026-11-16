#include "scena01_00.h"
#include "area/map.h"
#include "overlays/area/Area_DrawDimQuad.h"
#include "overlays/area/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F71C0(void) {
    POLY_G4* prim;

    AREA_DRAW_DIM_QUAD(3, 0);
}

MATCH void func_801F729C(void) {
    POLY_G4* prim;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, GetTPage(1, 2, 0x140, 0) & 0xFFFF, 0);
    GFX_AddPrim(2, sizeof(DR_MODE));
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
    GFX_AddPrim(2, sizeof(POLY_G4));
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, GetTPage(2, 3, 0x140, 0x140) & 0xFFFF, 0);
    GFX_AddPrim(2, sizeof(DR_MODE));
}

MATCH void func_801F73B8(void) {
    SYS_DISPATCH_TASK(D_801FE26C, 1, g_Task);
}

MATCH void func_801F73FC(void) {
    Actor* work;
    s32    height;

    work              = g_Task;
    work->pos.x.fixed = TO_COORD(96);
    work->pos.y.fixed = TO_COORD(17);
    height            = Area_SampleHeight(work->pos.x.fixed, work->pos.y.fixed);

    work              = g_Task;
    work->pos.z.fixed = height << 16;
    work->screen_x    = 0x180;
    work->screen_y    = 0x500;
    work->timer       = 0;
    Area_ClearWorkColumn();

    g_Task->header.mode += 1;
    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 2));
}

MATCH void func_801F7480(void) {
    func_801F7678(g_Task->timer);
    if ((g_FrameCount & 0x1) == 0) {
        Area_AddSpark();
    }
    Area_StepSparks();
    g_Task->timer = (g_Task)->timer + 4;
    if (g_Task->timer == 0) {
        g_Task->timer       = 32;
        g_Task->header.mode = (g_Task)->header.mode + 1;
    }
}

MATCH void func_801F752C(void) {
    func_801F7678(0xFF);
    if ((g_FrameCount & 0x1) == 0) {
        Area_AddSpark();
    }
    Area_StepSparks();
    if (--g_Task->timer == 0) {
        g_Task->timer = 252;
        g_Task->header.mode += 1;
    }
}

MATCH void func_801F75C8(void) {
    func_801F7678(g_Task->timer);
    Area_StepSparks();
    g_Task->timer = (g_Task)->timer - 4;
    if (g_Task->timer == 0) {
        g_Task->header.mode = (g_Task)->header.mode + 1;
    }
}

MATCH void func_801F7644(void) {
    if (!(Area_StepSparks() & BYTE_MASK)) {
        Actor_Clear();
    }
}

/* func_801F7678 */
#ifdef NON_MATCHING
NON_MATCHING void func_801F7678(s32 shade_arg) {
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
    u8       i;

    Area_SetCameraMatrix(&matrix);
    angle    = 0;
    point[0] = g_Task->pos.x.fixed + ((FIELD(s16, g_Task, 0x2E) * rcos(0)) >> 4);
    point[1] = g_Task->pos.y.fixed + ((FIELD(s16, g_Task, 0x2E) * rsin(0)) >> 4);
    point[2] = g_Task->pos.z.fixed;
    Area_ProjectPoint(point, &inner);
    point[2] = g_Task->pos.z.fixed + (FIELD(s16, g_Task, 0x30) << 16);
    Area_ProjectPoint(point, &outer);
    shade = ((g_FrameCount & 1) << 2) | 0x40;
    for (i = 0; i < AREA_RING_POINTS; i++) {
        last_inner = inner;
        last_outer = outer;
        angle += AREA_RING_ANGLE_STEP;
        point[0] = g_Task->pos.x.fixed + ((FIELD(s16, g_Task, 0x2E) * rcos((u16)angle)) >> 4);
        point[1] = g_Task->pos.y.fixed + ((FIELD(s16, g_Task, 0x2E) * rsin((u16)angle)) >> 4);
        point[2] = g_Task->pos.z.fixed;
        Area_ProjectPoint(point, &inner);
        point[2] = g_Task->pos.z.fixed + (FIELD(s16, g_Task, 0x30) << 16);
        Area_ProjectPoint(point, &outer);

        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, GetTPage(0, 1, 960, 0), 0);
        Area_AddCellPrim(point[0], point[1], 0, sizeof(DR_MODE));
        prim = GFX_BeginPolyG4(1);
        setXY4(prim, last_inner.vx, last_inner.vy, last_outer.vx, last_outer.vy, inner.vx, inner.vy, outer.vx, outer.vy);
        color = ((u32)shade_arg & BYTE_MASK) * (shade & BYTE_MASK) >> 8;
        setRGB0(prim, color, color, color);
        setRGB1(prim, color, color, color);
        if ((u8)(i - 4) >= 8) {
            shade += 8;
        } else {
            shade -= 8;
        }
        color = ((u32)shade_arg & BYTE_MASK) * shade >> 8;
        setRGB2(prim, color, color, color);
        setRGB3(prim, color, color, color);
        Area_AddCellPrim(point[0], point[1], 0, sizeof(POLY_G4));
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, GetTPage(0, 1, 960, 0), 0);
        Area_AddCellPrim(point[0], point[1], 0, sizeof(DR_MODE));
    }
}
#else
INCLUDE_ASM(func_801F7678);
#endif

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
            g_Task->screen_x = 0;
            func_801F7DCC(64, 90, 255);
            break;
        case 2:
            screen_x = g_Task->screen_x;
            if (screen_x < 191) {
                next_x           = screen_x + 1;
                g_Task->screen_x = next_x;
            }
            red  = (s16)g_Task->screen_x;
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

    tpage = getTPage(1, 0, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(7, tpage);
    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    setXY4(prim, 0, 0, SCREEN_WIDTH - 1, 0, 0, SCREEN_HEIGHT - 1, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1);
    prim->r0 = prim->r1 = red;
    prim->g0 = prim->g1 = green;
    prim->b0 = prim->b1 = blue;
    prim->r2 = prim->r3 = 0;
    prim->g2 = prim->g3 = 0;
    prim->b2 = prim->b3 = 0;
    GFX_AddPrim(7, sizeof(POLY_G4));
}

MATCH void func_801F7EDC(void) {
    POLY_F4* prim;
    s32      tpage;

    tpage = getTPage(1, 1, 320, 256);
    GFX_SET_DRAW_MODE(tpage);
    GFX_AddPrim(3, sizeof(DR_MODE));
    prim = (POLY_F4*)g_GfxPrimCursor;
    SetPolyF4(prim);
    SetSemiTrans(prim, 1);
    setXYWH(prim, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    setRGB0(prim, (s16)g_Task->screen_x / 8, 0, 0);
    GFX_AddPrim(3, sizeof(POLY_F4));
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
