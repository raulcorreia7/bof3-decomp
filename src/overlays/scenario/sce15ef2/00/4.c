#include "sce15ef2_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801D0C04(void) {
    D_801D1B1C[g_Task->header.mode]();
    if (g_Task->header.mode != 0) {
        func_801D1218(&g_Task->pos, (s16)g_Task->vx, 7);
    }
}

MATCH void func_801D0C70(void) {
    u8* work;
    u8* step;

    work                  = (u8*)g_Task;
    work[9]               = 0x10;
    step                  = (u8*)g_Task;
    FIELD(s32, work, 0xC) = 0;
    step[1]++;
}

MATCH void func_801D0CA0(void) {
    Actor* work;
    u8     timer;

    work        = g_Task;
    timer       = work->timer - 1;
    work->vx    = work->vx + 0x10;
    work->timer = timer;
    if (timer == 0) {
        g_Task->timer       = 32;
        g_Task->header.mode = g_Task->header.mode + 1;
    }
}

MATCH void func_801D0D00(void) {
    u8 timer;

    timer         = g_Task->timer - 1;
    g_Task->timer = timer;
    if (timer == 0) {
        g_Task->timer       = 16;
        g_Task->header.mode = g_Task->header.mode + 1;
    }
}

MATCH void func_801D0D5C(void) {
    Actor* work;
    u8     timer;

    work        = g_Task;
    timer       = work->timer - 1;
    work->vx    = work->vx - 0x10;
    work->timer = timer;
    if (timer == 0) {
        Actor_Clear();
    }
}

MATCH void func_801D0DA4(void) {
    SYS_DISPATCH_TASK(D_801D1B2C, 1, g_Task);
}

#include "overlays/scenario/Scene_EndScan.h"

MATCH void func_801D0E30(void) {
    u8 timer;

    timer = g_Task->timer;
    if (timer == 0) {
        Scene_ClaimScanBar();
        g_Task->timer = RANDOM_MASK(0xF) + 24;
    } else {
        g_Task->timer = timer - 1;
    }
    Scene_UpdateScanBars(240);
    if (g_ScriptVars[0] == 14) {
        g_Task->header.mode += 1;
    }
}

MATCH void func_801D0EC4(void) {
    if (!(Scene_UpdateScanBars(240) & BYTE_MASK)) {
        Actor_Clear();
    }
}

MATCH void func_801D0EF8(void) {
    SYS_DISPATCH_TASK(D_801D1B38, 1, g_Task);
    if (g_Task->header.mode != 0) {
        func_801D17A0((s16)g_Task->screen_x, (s16)g_Task->screen_y, 0x80);
    }
}

MATCH void func_801D0F68(void) {
    Actor* work;

    work                = g_Task;
    work->timer         = 10;
    work->screen_x      = 0;
    work->screen_y      = 0;
    g_Task->header.mode = g_Task->header.mode + 1;
}

MATCH void func_801D0F9C(void) {
    Actor* work;
    u8     timer;

    work           = g_Task;
    timer          = work->timer - 1;
    work->timer    = timer;
    work->screen_x = work->screen_x + 0x15;
    work->screen_y = work->screen_y + 9;
    if (timer == 0) {
        g_Task->timer       = 90;
        g_Task->header.mode = g_Task->header.mode + 1;
    }
}

MATCH void func_801D1008(void) {
    if (g_ScriptVars[0] == 9) {
        g_Task->timer       = 30;
        g_Task->header.mode = g_Task->header.mode + 1;
    }
}

MATCH void func_801D1050(void) {
    Actor* work;
    u8     timer;

    work           = g_Task;
    timer          = work->timer - 1;
    work->timer    = timer;
    work->screen_x = work->screen_x - 7;
    work->screen_y = work->screen_y - 3;
    if (timer == 0) {
        Actor_Clear();
    }
}

MATCH void func_801D10A4(void) {
    SYS_DISPATCH_TASK(D_801D1B48, 1, g_Task);
}

MATCH void func_801D10E8(void) {
    u8* work;

    work    = (u8*)g_Task;
    work[9] = 0x10;
    work    = (u8*)g_Task;
    work[1]++;
}

MATCH void func_801D1118(void) {
    Scene_DrawRedGradient(-(g_Task->timer << 4) & BYTE_MASK);
    if (--g_Task->timer == 0) {
        g_Task->timer = 16;
        g_Task->header.mode += 1;
    }
}

MATCH void func_801D11A4(void) {
    u8 timer;

    SCENE_RED_GRADIENT_FADE(timer, 0x10, 4);
}

MATCH void func_801D1218(WorldPos* pos, s16 y, s32 mode) {
    DVECTOR  screen;
    DVECTOR  point;
    DVECTOR  size;
    DVECTOR  scale;
    MATRIX   camera;
    POLY_G3* primitive;
    s32      angle;
    s32      i;

    GFX_AddDitheredDrawMode(7u, GetTPage(0, 1, 0x2C0, 0x100));
    Area_SetCameraMatrix(&camera);
    Area_ProjectPoint((s32*)pos, &screen);
    size.vx = size.vy = y;
    Game_ProjectWorldPoint((s32*)pos, &size, &scale);
    scale.vx += g_FrameCount & 1;
    point.vx = screen.vx + scale.vx;
    point.vy = screen.vy;
    angle    = 0;
    i        = 0;
    do {
        primitive = GFX_BeginPolyG3(0);
        setXY2(primitive, screen.vx, screen.vy, point.vx, point.vy);
        angle += 128;
        point.vx      = screen.vx + (((s16)scale.vx * rcos((u16)angle)) >> 12);
        point.vy      = screen.vy + (((s16)scale.vx * rsin((u16)angle)) >> 12);
        primitive->x2 = point.vx;
        primitive->y2 = point.vy;
        setRGB0(primitive, (mode & 4) << 5, (mode & 2) << 6, (mode & 1) << 7);
        setRGB1(primitive, 0, 0, 0);
        setRGB2(primitive, 0, 0, 0);
        GFX_AddPrim(7u, sizeof(POLY_G3));
        i++;
    } while ((i & BYTE_MASK) < 32U);
}

#include "overlays/scenario/Scene_DrawScanBar.h"

#include "overlays/scenario/Scene_ClearScanBars.h"

#include "overlays/scenario/Scene_ClaimScanBar.h"

INCLUDE_ASM(Scene_UpdateScanBars);

#ifdef NON_MATCHING
NON_MATCHING void func_801D17A0(s32 x, s32 y, s32 mode) {
    POLY_G3* primitive;
    s16      point_x;
    s16      point_y;
    s32      angle;
    s32      frame_offset;
    u8       color;
    u8       i;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, GetTPage(0, 1, 0x380, 0x100), 0);
    GFX_AddPrim(7u, sizeof(DR_MODE));

    frame_offset = (g_FrameCount & 1) << 2;
    angle        = 0x800;
    point_x      = 0xA0 + frame_offset + (((s16)x * rcos((u16)angle)) >> 12);
    point_y      = 0xF0 + frame_offset + (((s16)y * rsin((u16)angle)) >> 12);
    color        = mode >> 2;
    i            = 0;
    do {
        primitive = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(primitive);
        SetSemiTrans(primitive, 1);
        primitive->x0 = 0xA0;
        primitive->y0 = 0xF0;
        primitive->x1 = point_x;
        primitive->y1 = point_y;
        angle += 0x40;
        point_x       = 0xA0 + frame_offset + (((s16)x * rcos((u16)angle)) >> 12);
        point_y       = 0xF0 + frame_offset + (((s16)y * rsin((u16)angle)) >> 12);
        primitive->x2 = point_x;
        primitive->y2 = point_y;
        setRGB0(primitive, mode, color, color);
        setRGB1(primitive, 0, 0, 0);
        setRGB2(primitive, 0, 0, 0);
        GFX_AddPrim(7u, sizeof(POLY_G3));
        i++;
    } while ((i & BYTE_MASK) < 32U);
}
#else
INCLUDE_ASM(func_801D17A0);
#endif

#include "overlays/scenario/Scene_DrawRedGradient.h"
