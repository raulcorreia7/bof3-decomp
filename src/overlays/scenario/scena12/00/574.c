#include "scena12_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/scenario/shared/Scene_DispatchEntity.h"

MATCH void func_801F71B8(void) {
    SYS_DISPATCH_TASK(D_801FD184, 2, g_Task);
}

MATCH void func_801F71FC(void) {
    Actor* actor;

    D_801FD288.half    = (RANDOM_MASK(1)) << 15;
    actor              = TASK(Actor);
    actor->header.step = actor->header.step + 1;
}

#define SCENA12_STEP_COUNTER()                                                                      \
    {                                                                                               \
        s32    bits;                                                                                \
        u16    value;                                                                               \
        u32    high;                                                                                \
        u32    count;                                                                               \
        Actor* actor;                                                                               \
                                                                                                    \
        if (*g_ScriptVars == 1) {                                                                   \
            Actor_Clear();                                                                          \
            return;                                                                                 \
        }                                                                                           \
        high = (u16)D_801FD288.half >> 0xF;                                                         \
        if ((u32)(D_801FD288.half & BYTE_MASK) >= 0xC8U) {                                          \
            actor = g_Task;                                                                         \
            actor->header.step += 1;                                                                \
            return;                                                                                 \
        }                                                                                           \
        count = ((u32)(D_801FD288.half & 0x7F00) >> 8) + 1;                                         \
        value = D_801FD288.half;                                                                    \
        if (((high & BYTE_MASK) == 0 && count >= 30) || ((high & BYTE_MASK) != 0 && count >= 40)) { \
            count = 0;                                                                              \
            value += 1;                                                                             \
            if (SYS_TestFlag(g_SceneFlags, 0x14) != 0) {                                            \
                SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 10));                                           \
            }                                                                                       \
        }                                                                                           \
        bits = high << 15;                                                                          \
        bits |= count << 8;                                                                         \
        D_801FD288.half = (value & BYTE_MASK) | bits;                                               \
    }

MATCH void func_801F7240(void) {
    SCENA12_STEP_COUNTER();
}

/* The statements of func_801F7348 and func_801F7518, byte-identical twins: unless a message is pending, the entry state is 4 or scene flag 0x2E is set, queue script step 5 with g_ScenarioState.step_05 = 0x19, raise the script-active flag and clear the work. */
#define SCENA12_START_SCRIPT()                                                                                        \
    if (g_GameStateIndex != GAME_REQUEST_MESSAGE && g_GameEntryState != 4 && SYS_TestFlag(g_SceneFlags, 0x2E) == 0) { \
        g_ScenarioState.step_05  = 0x19;                                                                              \
        g_ScenarioState.state_04 = 5;                                                                                 \
        g_GameFlags |= GAME_FLAG_SCRIPT_ACTIVE;                                                                       \
        Actor_Clear();                                                                                                \
    }

MATCH void func_801F7348(void) {
    SCENA12_START_SCRIPT();
}

MATCH void func_801F73CC(void) {
    SYS_DISPATCH_TASK(D_801FD190, 2, g_Task);
}

MATCH void func_801F7410(void) {
    SCENA12_STEP_COUNTER();
}

MATCH void func_801F7518(void) {
    SCENA12_START_SCRIPT();
}

MATCH void func_801F759C(void) {
    func_801F75EC();
    if ((g_GameStateIndex != GAME_REQUEST_MESSAGE) && (g_GameEntryState != 4)) {
        Actor_Clear();
    }
}

MATCH void func_801F75EC(void) {
    char* buffer;
    char* fmt;
    u8    value;

    buffer = (char*)g_UiTextFormatBuffer;
    Menu_DrawHeaderBar(138, 30, 45, 20, 1u);
    value = D_801FD288.bytes[0];
    fmt   = D_801F6C04;
    TEXT_Format(buffer, fmt, value);
    UI_TextDrawAscii(0x95, 0x22, 0, buffer);
}

#ifdef NON_MATCHING
NON_MATCHING void Menu_DrawHeaderBar(s32 x, s32 y, s32 width, s32 height, u8 window_style) {
    RECT*     window;
    POLY_FT4* prim;
    u16       left;
    u16       top;
    s32       inner;
    s32       clut_x;
    u8        bottom_v;
    s32       bottom_row;
    s32       bottom_y;
    u16       odd_u;
    s32       width1;
    u16       width1_u;
    s32       half;
    u16       half_u;
    s32       odd;
    s32       mid_x;
    s32       uv_end;

    window          = (RECT*)g_GfxPrimCursor;
    g_GfxPrimCursor = (u8*)(window + 1);
    window->y       = 240;
    window->x       = 0;
    setWH(window, 16, 16);
    left = x;
    top  = y;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y), window);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(DR_MODE));

    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    PSX_SET_SEMI_TRANSPARENT(prim);
    clut_x = (window_style << 5) + 0x10;
    inner  = x + 2;
    setXY0(prim, left, top);
    prim->y1 = top;
    prim->x2 = left;
    prim->x1 = inner;
    prim->x3 = inner;
    setUV0(prim, 0, 0);
    prim->u2 = 0;
    prim->v1 = 0;
    setRGB0(prim, 172, 172, 172);
    bottom_row = height + 1;
    bottom_v   = bottom_row;
    bottom_y   = y + bottom_row;
    prim->y2   = bottom_y;
    prim->y3   = bottom_y;
    prim->u1   = 2;
    prim->v2   = bottom_v;
    prim->u3   = 2;
    prim->v3   = bottom_v;
    prim->y0 += 2;
    prim->y2 -= 3;
    prim->v0 += 2;
    prim->v2 -= 3;
    prim->clut  = GetClut(clut_x, STAGE_PALETTE_Y + 1);
    width1      = width + 1;
    width1_u    = width1;
    prim->tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_FT4));

    half = ((s32)width1_u - 4) >> 1;
    prim = (POLY_FT4*)g_GfxPrimCursor;
    odd  = (width - 3) & 1;
    SetPolyFT4(prim);
    PSX_SET_SEMI_TRANSPARENT(prim);
    half_u = half;
    setXY4(prim, inner, top, half + inner, top, inner, bottom_y, half + inner, bottom_y);
    setUV4(prim, 0u, 0u, (u8)half_u, 0u, 0u, bottom_v, (u8)half_u, bottom_v);
    setRGB0(prim, 172, 172, 172);
    prim->clut  = GetClut(clut_x, STAGE_PALETTE_Y + 1);
    odd_u       = odd;
    prim->tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_FT4));

    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    PSX_SET_SEMI_TRANSPARENT(prim);
    mid_x  = x + half;
    uv_end = half + odd + 2;
    setXY4(prim, mid_x + 2, top, mid_x + uv_end, top, mid_x + 2, bottom_y, mid_x + uv_end, bottom_y);
    setUV4(prim, 0u, 0u, (u8)(half_u + odd_u), 0u, 0u, bottom_v, (u8)(half_u + odd_u), bottom_v);
    setRGB0(prim, 172, 172, 172);
    prim->clut  = GetClut(clut_x, STAGE_PALETTE_Y + 1);
    prim->tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_FT4));

    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    PSX_SET_SEMI_TRANSPARENT(prim);
    prim->y2 = bottom_y;
    prim->v2 = bottom_v;
    prim->x1 = x + width1;
    prim->y1 = top;
    prim->x3 = x + width1;
    setXY0(prim, x + width1 - 2, top);
    prim->x2 = x + width1 - 2;
    setUV0(prim, 0u, 0u);
    prim->u1 = 2u;
    prim->v1 = 0u;
    prim->u2 = 0u;
    prim->u3 = 2u;
    prim->v3 = bottom_v;
    prim->y3 = bottom_y;
    setRGB0(prim, 172, 172, 172);
    prim->y1 += 2;
    prim->y2 -= 1;
    prim->y3 -= 3;
    prim->v2 -= 1;
    prim->v1 += 2;
    prim->v3 -= 3;
    prim->clut  = GetClut(clut_x, STAGE_PALETTE_Y + 1);
    prim->tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_FT4));

    window          = (RECT*)g_GfxPrimCursor;
    g_GfxPrimCursor = (u8*)(window + 1);
    window->x       = 0;
    window->y       = 0;
    setWH(window, 256, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y), window);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(DR_MODE));
    UI_WindowDrawFrame(inner, y + 2, width - 4, height - 4, 0);
}
#else
INCLUDE_ASM(Menu_DrawHeaderBar);
#endif

MATCH void func_801F7BA8(void) {
    SYS_DISPATCH_TASK(D_801FD198, 1, g_Task);
}

MATCH void func_801F7BEC(void) {
    Actor* actor;

    actor              = TASK(Actor);
    actor->screen_x    = 0;
    actor->header.mode = actor->header.mode + 1;
    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 21));
}

/* Places the task on an orbit round the focus point by its angle; at frame 330 it plays a sound and moves on. */
MATCH void func_801F7C24(void) {
    VECTOR from;
    VECTOR to;
    s32    cos;

    setVector(&from, -0x6000, -0x12000, 1 << 24);
    cos                      = rcos(TASK(Actor)->unk_6C);
    to.vx                    = (from.vx * cos - from.vy * rsin(TASK(Actor)->unk_6C)) >> 12;
    cos                      = rsin(TASK(Actor)->unk_6C);
    to.vy                    = (from.vx * cos + from.vy * rcos(TASK(Actor)->unk_6C)) >> 12;
    to.vz                    = from.vz;
    TASK(Actor)->pos.x.fixed = D_80147B24[0] + to.vx;
    TASK(Actor)->pos.y.fixed = D_80147B24[1] + to.vy;
    TASK(Actor)->pos.z.fixed = D_80147B24[2] + to.vz;
    setVector(TASK(Actor), D_80147B24[0] + to.vx - ((s16)TASK(Actor)->screen_x << 15), D_80147B24[1] + to.vy, D_80147B24[2] + to.vz);
    func_801F7E34(&TASK(Actor)->pos.x.fixed, &TASK(Actor)->vx, 0x40);
    TASK(Actor)->screen_x += 1;
    if ((s16)TASK(Actor)->screen_x == 330) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 22));
        TASK(Actor)->header.mode += 1;
    }
}

MATCH void func_801F7E14(void) {
    Actor_Clear();
}

MATCH void func_801F7E34(s32* pos_a, s32* pos_b, u8 shade) {
    LINE_F2* prim;
    DVECTOR  xy;
    MATRIX   matrix;

    GFX_ADD_DITHERED_DRAW_MODE(GFX_LAYER_UI, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y));
    Camera_SetMatrix(&matrix);
    prim = (LINE_F2*)g_GfxPrimCursor;
    SetLineF2(prim);
    SetSemiTrans(prim, 1);
    Camera_ProjectPoint(pos_a, &xy);
    setXY0(prim, (u16)xy.vx, (u16)xy.vy);
    Camera_ProjectPoint(pos_b, &xy);
    prim->x1 = (u16)xy.vx;
    prim->y1 = (u16)xy.vy;
    setRGB0(prim, shade, shade, 0);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(LINE_F2));
}

MATCH void func_801F7F28(void) {
    SYS_DISPATCH_BYTE(D_801FD1B8, D_80146872);
}

MATCH void func_801F7F64(void) {
    D_80146872 = 1;
}
