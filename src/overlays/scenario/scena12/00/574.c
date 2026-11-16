#include "scena12_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/scenario/Scene_DispatchEntity.h"

MATCH void func_801F71B8(void) {
    SYS_DISPATCH_TASK(D_801FD184, 2, g_Task);
}

MATCH void func_801F71FC(void) {
    Actor* actor;

    D_801FD288.half    = (RANDOM_MASK(1)) << 15;
    actor              = g_Task;
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
                SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 10));                                         \
            }                                                                                       \
        }                                                                                           \
        bits = high << 15;                                                                          \
        bits |= count << 8;                                                                         \
        D_801FD288.half = (value & BYTE_MASK) | bits;                                               \
    }

MATCH void func_801F7240(void) {
    SCENA12_STEP_COUNTER();
}

/* The statements of func_801F7348 and func_801F7518, byte-identical twins: unless a message is pending, the entry state is 4 or scene flag 0x2E is set, queue script step 5 with D_80146875 = 0x19, raise the script-active flag and clear the work. */
#define SCENA12_START_SCRIPT()                                                                                        \
    if (g_GameStateIndex != GAME_REQUEST_MESSAGE && g_GameEntryState != 4 && SYS_TestFlag(g_SceneFlags, 0x2E) == 0) { \
        D_80146875 = 0x19;                                                                                            \
        D_80146874 = 5;                                                                                               \
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

    buffer = (char*)g_UiFormatBuffer;
    Menu_DrawHeaderBar(138, 30, 45, 20, 1u);
    value = D_801FD288.bytes[0];
    fmt   = D_801F6C04;
    TEXT_Format(buffer, fmt, value);
    UI_DrawAsciiString(0x95, 0x22, 0, buffer);
}

#ifdef NON_MATCHING
NON_MATCHING void Menu_DrawHeaderBar(s32 x_arg, s32 y_arg, s32 width, s32 height, u8 style_arg) {
    RECT*     texture_window;
    POLY_FT4* primitive;
    s32       bottom_y;
    s32       bottom_v;
    s32       clut_x;
    s16       odd_h;
    s32       width_plus_1;
    s32       odd_width;
    s32       graph_type;

    u16 x;
    u16 y;
    u8  window_style;
    s32 r_s1;
    u16 r_s4;
    s32 r_s8;

    window_style      = (u8)style_arg;
    texture_window    = (RECT*)g_GfxPrimCursor;
    g_GfxPrimCursor   = (u8*)(texture_window + 1);
    texture_window->y = 240;
    texture_window->x = 0;
    setWH(texture_window, 16, 16);

    graph_type = GetGraphType();
    x          = (u16)x_arg;
    y          = (u16)y_arg;
    if (graph_type != 1) {
        GetGraphType();
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, FONT_TPAGE_X >> 6, texture_window);
    GFX_AddPrim(1u, sizeof(DR_MODE));

    primitive = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(primitive);
    SetSemiTrans(primitive, 1);
    r_s8   = (s16)(x + 2);
    clut_x = ((s32)window_style << 5) + 0x10;
    setXY0(primitive, (s16)x, (s16)(u16)y);
    primitive->y1 = (s16)(u16)y;
    primitive->x2 = (s16)x;
    primitive->x1 = (s16)r_s8;
    primitive->x3 = (s16)r_s8;
    setUV0(primitive, 0u, 0u);
    primitive->v1 = 0u;
    primitive->u2 = 0u;
    setRGB0(primitive, 172, 172, 172);
    bottom_v      = (u8)(height + 1);
    bottom_y      = (s32)(u16)y + bottom_v;
    primitive->y2 = bottom_y;
    primitive->y3 = bottom_y;
    primitive->u1 = 2u;
    primitive->v2 = bottom_v;
    primitive->u3 = 2u;
    primitive->v3 = bottom_v;
    primitive->y0 += 2;
    primitive->y2 -= 3;
    primitive->v0 += 2;
    primitive->v2 -= 3;
    primitive->clut = GetClut(clut_x, STAGE_PALETTE_Y + 1);
    width_plus_1    = (s32)(width + 1);

    primitive->tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y);
    GFX_AddPrim(1u, sizeof(POLY_FT4));

    /* FAKE: pin signed shift matches original sra computation. */
    r_s1 = (s32)(u16)width_plus_1;
    r_s1 = ((s32)(u16)r_s1 - 4) >> 1;
    r_s4 = r_s1;

    primitive = (POLY_FT4*)g_GfxPrimCursor;
    odd_width = (width - 3) & 1;
    odd_h     = (s16)odd_width;
    SetPolyFT4(primitive);
    SetSemiTrans(primitive, 1);
    setXY4(primitive, (s16)r_s8, (s16)(u16)y, (s16)(r_s1 + r_s8), (s16)(u16)y, (s16)r_s8, bottom_y, (s16)(r_s1 + r_s8), bottom_y);
    setUV4(primitive, 0u, 0u, (u8)r_s4, 0u, 0u, bottom_v, (u8)r_s4, bottom_v);
    setRGB0(primitive, 172, 172, 172);
    primitive->clut = GetClut(clut_x, STAGE_PALETTE_Y + 1);

    primitive->tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y);
    GFX_AddPrim(1u, sizeof(POLY_FT4));

    primitive = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(primitive);
    SetSemiTrans(primitive, 1);
    primitive->y0 = (s16)(u16)y;
    primitive->x0 = (s16)((s32)x + r_s1 + 2);
    primitive->x1 = (s16)(((s32)x + r_s1) + (r_s1 + odd_width + 2));
    primitive->y1 = (s16)(u16)y;
    primitive->x2 = (s16)((s32)x + r_s1 + 2);
    primitive->y2 = bottom_y;
    primitive->x3 = (s16)(((s32)x + r_s1) + (r_s1 + odd_width + 2));
    primitive->y3 = bottom_y;
    setUV4(primitive, 0u, 0u, (u8)(r_s4 + odd_h), 0u, 0u, bottom_v, (u8)(r_s4 + odd_h), bottom_v);
    setRGB0(primitive, 172, 172, 172);
    primitive->clut = GetClut(clut_x, STAGE_PALETTE_Y + 1);

    primitive->tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y);
    GFX_AddPrim(1u, sizeof(POLY_FT4));

    primitive = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(primitive);
    SetSemiTrans(primitive, 1);
    primitive->y2 = bottom_y;
    primitive->v2 = bottom_v;
    primitive->x1 = (s16)((s32)x + width_plus_1);
    primitive->y1 = (s16)(u16)y;
    primitive->x3 = (s16)((s32)x + width_plus_1);
    setXY0(primitive, (s16)((s32)x + width_plus_1 - 2), (s16)(u16)y);
    primitive->x2 = (s16)((s32)x + width_plus_1 - 2);
    primitive->y3 = bottom_y;
    setUV0(primitive, 0u, 0u);
    primitive->u1 = 2u;
    primitive->v1 = 0u;
    primitive->u2 = 0u;
    primitive->u3 = 2u;
    primitive->v3 = bottom_v;
    setRGB0(primitive, 172, 172, 172);
    primitive->y1 += 2;
    primitive->y3 -= 3;
    primitive->y2 -= 1;
    primitive->v1 += 2;
    primitive->v2 -= 1;
    primitive->v3 -= 3;
    primitive->clut = GetClut(clut_x, STAGE_PALETTE_Y + 1);

    primitive->tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y);
    GFX_AddPrim(1u, sizeof(POLY_FT4));

    texture_window    = (RECT*)g_GfxPrimCursor;
    g_GfxPrimCursor   = (u8*)(texture_window + 1);
    texture_window->x = 0;
    texture_window->y = 0;
    setWH(texture_window, 256, 256);

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y), texture_window);
    GFX_AddPrim(1u, sizeof(DR_MODE));
    func_801AEBA0((s16)r_s8, (s16)((s32)(u16)y + 2), (s16)(width - 4), (s16)(height - 4), 0);
}
#else
INCLUDE_ASM(Menu_DrawHeaderBar);
#endif

MATCH void func_801F7BA8(void) {
    SYS_DISPATCH_TASK(D_801FD198, 1, g_Task);
}

MATCH void func_801F7BEC(void) {
    Actor* actor;

    actor              = g_Task;
    actor->screen_x    = 0;
    actor->header.mode = actor->header.mode + 1;
    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 21));
}

#ifdef NON_MATCHING
NON_MATCHING void func_801F7C24(void) {
    VECTOR from;
    VECTOR to;
    s32    cos;

    from.vx             = -0x6000;
    from.vy             = -0x12000;
    from.vz             = 1 << 24;
    cos                 = rcos(g_Task->unk_6C);
    to.vx               = (from.vx * cos - from.vy * rsin(g_Task->unk_6C)) >> 12;
    cos                 = rsin(g_Task->unk_6C);
    to.vy               = (from.vx * cos + from.vy * rcos(g_Task->unk_6C)) >> 12;
    to.vz               = from.vz;
    g_Task->pos.x.fixed = D_80147B24[0] + to.vx;
    g_Task->pos.y.fixed = D_80147B28 + to.vy;
    g_Task->pos.z.fixed = D_80147B2C + to.vz;
    g_Task->vx          = D_80147B24[0] + to.vx - ((s16)g_Task->screen_x << 15);
    g_Task->vy          = D_80147B28 + to.vy;
    g_Task->vz          = D_80147B2C + to.vz;
    func_801F7E34(&g_Task->pos.x.fixed, &g_Task->vx, 0x40);
    g_Task->screen_x += 1;
    if ((s16)g_Task->screen_x == 330) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 22));
        g_Task->header.mode += 1;
    }
}
#else
INCLUDE_ASM(func_801F7C24);
#endif

MATCH void func_801F7E14(void) {
    Actor_Clear();
}

MATCH void func_801F7E34(s32* pos_a, s32* pos_b, u8 shade) {
    LINE_F2* prim;
    DVECTOR  xy;
    MATRIX   matrix;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y), 0);
    GFX_AddPrim(1, sizeof(DR_MODE));
    Area_SetCameraMatrix(&matrix);
    prim = (LINE_F2*)g_GfxPrimCursor;
    SetLineF2(prim);
    SetSemiTrans(prim, 1);
    Area_ProjectPoint(pos_a, &xy);
    setXY0(prim, (u16)xy.vx, (u16)xy.vy);
    Area_ProjectPoint(pos_b, &xy);
    prim->x1 = (u16)xy.vx;
    prim->y1 = (u16)xy.vy;
    setRGB0(prim, shade, shade, 0);
    GFX_AddPrim(1, sizeof(LINE_F2));
}

MATCH void func_801F7F28(void) {
    SYS_DISPATCH_BYTE(D_801FD1B8, D_80146872);
}

MATCH void func_801F7F64(void) {
    D_80146872 = 1;
}

INCLUDE_ASM(func_801F7F78);

MATCH void func_801F886C(void) {
    SYS_DISPATCH_BYTE(D_801FD1C4, g_SceneState.state_04);
}

MATCH void func_801F88A8(void) {
}

MATCH void func_801F88B0(void) {
    u8* state;
    u8* script;

    state = &g_SceneState.step_05;
    switch (*state) {
        case 0xA:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScriptVars[0] = 0x32;
                *state          = 0xB;
            }
            return;
        case 0xB:
            script = &g_ScriptVars[1];
            if (*script == 0xA) {
                *script = 0;
                Game_ClearScriptActive();
                *state                = 0;
                g_SceneState.state_04 = 0;
            }
            return;
    }
}

MATCH void func_801F894C(void) {
    switch (g_SceneState.step_05) {
        case 51:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                g_SceneState.step_05  = 0;
                g_SceneState.state_04 = 0;
            }
            break;

        case 50:
            Message_StartAreaMessage(6);
            g_GameStateIndex     = GAME_REQUEST_MESSAGE;
            g_SceneState.step_05 = 51;
            break;

        case 60:
            Message_StartAreaMessage(7);
            g_GameStateIndex     = GAME_REQUEST_MESSAGE;
            g_SceneState.step_05 = 51;
            break;
    }
}

MATCH void func_801F89FC(void) {
}

INCLUDE_ASM(func_801F8A04);

INCLUDE_ASM(func_801F9680);
