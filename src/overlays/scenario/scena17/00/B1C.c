#define FAKE_DECL_AREA_SCROLL_TARGET_VOLATILE
#include "scena17_00.h"
#include "area/map.h"
#include "shared/etc.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F771C(void) {
    /* Retail takes the handler index from the entry $v0; the uninitialised local reads it. */
    u32 index;

    /* FAKE: without the block the scheduler hoists the index shift above the
       ra store (84.46%); the lock restores the retail order (99.85%). */
    FAKE_ORDER_LOCK(D_801F973C[index]());
}

/* func_801F7750 */
MATCH void Scene_EnterSaveArea(void) {
    GFX_PaletteReset();
    g_GfxPalettePending = 1;
    g_AreaDrawFlags     = 0x1F;
    Game_RequestAreaChange(AREA_ID_END_GAME_SAVE, TO_COORD(182), TO_COORD(18) + COORD_HALF, FACING_LEFT);
    g_ScriptVarsReq.word = 0;
    D_80146872           = 1;
}

MATCH void func_801F77B4(void) {
    RECT rect;

    if (g_GameAreaId == AREA_ID_END_GAME_SAVE) {
        Game_SetScriptActive();
        Party_BattlersHide();
        g_AreaCameraAngle.vx = -0x2E4;
        g_AreaCameraAngle.vz = 0x12C;
        Area_ScrollAdvance(0x300);
        Camera_Update();
        func_801A0514();
        Area_SceneDraw();
        setRECT(&rect, 0, g_GfxBufferIndex * SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);
        SetDrawMove((DR_MOVE*)g_GfxPrimCursor, &rect, 0x2C0, 0);
        GFX_AddPrim(GFX_LAYER_SCENE_BACK, sizeof(DR_MOVE));
    }
    g_AreaDrawFlags = 0;
    SND_SetBankLayout(2);
    g_ScenarioState.mode_02 = 2;
    g_ScenarioState.unk_03  = 1;
}

MATCH void func_801F789C(void) {
    SYS_DISPATCH_BYTE(D_801F9748, D_80146873);
}

MATCH void func_801F78D8(void) {
}

MATCH void func_801F78E0(void) {
    SYS_DISPATCH_BYTE(D_801F9758, (s8)g_ScenarioState.state_04);
    func_801F8EF0();
}

MATCH void func_801F7924(void) {
    s8* step;

    if (g_SysThreads[2].state == 0) {
        g_AreaScrollTargetX = TO_COORD(176);
        g_AreaScrollTargetY = TO_COORD(19) + COORD_HALF;
        Area_InitMapRenderer();
        g_AreaSceneMode = 4;
        SND_BGMRequest(0x96);
        UI_ModeSet(UI_MODE_FADE_IN);
        func_801F88CC(0, 0x80);
        step = &g_ScenarioState.state_04;
        *step += 1;
    }
}

MATCH void func_801F79AC(void) {
    if ((g_SysThreads[2].state == 0) && (EMI_IsReady() != 0)) {
        g_ScenarioState.step = 0x5A;
        g_ScenarioState.state_04 += 1;
    }
    func_801F88CC(0, 0x80);
}

MATCH void func_801F7A08(void) {
    u8* timer;

    timer = &g_ScenarioState.step;
    *timer -= 1;
    if (*timer == 0) {
        SND_BGMPlay(0x96, 0x64, 0x8);
        *timer = 30;
        g_ScenarioState.state_04 += 1;
    }
    func_801F88CC(0, 0x80);
}

MATCH void func_801F7A84(void) {
    u8* timer;
    u8  count;

    timer  = &g_ScenarioState.step;
    count  = *timer - 1;
    *timer = count;
    if (count == 0) {
        g_AreaScrollTargetX      = TO_COORD(148);
        g_AreaCameraSpeed        = 0x20;
        *timer                   = 128;
        g_AreaCameraAngle.vx     = -0x16A;
        g_AreaCameraAngle.vz     = 512;
        g_AreaDrawFlags          = AREA_DRAW_ALL_FLAGS;
        g_ScenarioState.state_04 = g_ScenarioState.state_04 + 1;
    }
    func_801F88CC(0, 0x80);
}

MATCH void func_801F7B20(void) {
    u8* timer;

    timer = &g_ScenarioState.step;
    *timer -= 1;
    func_801F88CC(1, *timer);
    if (*timer == 0) {
        g_ScenarioState.state_04 += 1;
    }
}

MATCH void func_801F7B88(void) {
    s8* step;

    if (!g_AreaCameraMoving) {
        step                = &g_ScenarioState.state_04;
        g_AreaScrollTargetX = TO_COORD(140);
        *step += 1;
    }
}

MATCH void func_801F7BC0(void) {
    s8* step;

    g_AreaCameraAngle.vx -= 5;
    if (g_AreaCameraMoving == 0) {
        step                = &g_ScenarioState.state_04;
        g_AreaScrollTargetX = TO_COORD(84);
        g_ScriptVars[3]     = 0xA;
        *step += 1;
    }
}

MATCH void func_801F7C14(void) {
    s8* step;

    if (g_AreaCameraMoving == 0 && g_ScriptVars[3] == 0x14) {
        step                = &g_ScenarioState.state_04;
        g_AreaCameraSpeed   = 0x10;
        g_AreaScrollTargetX = TO_COORD(60);
        *step += 1;
    }
}

MATCH void func_801F7C6C(void) {
    s8* step;

    if (g_AreaCameraMoving == 0) {
        Area_ScrollAdvance(Area_HeightSample(g_AreaScrollTargetX, g_AreaScrollTargetY));
        step                = &g_ScenarioState.state_04;
        g_AreaScrollTargetX = TO_COORD(46);
        *step += 1;
    } else if (g_FrameCount & 0x1) {
        g_AreaCameraHeight -= 1;
    }
}

/* The script counter is read and written through one materialized address (a0), so the increment
 * store lands in the jump's delay slot; a direct g_ScenarioState.state_04 += 1 reloads the address per access. */
MATCH void func_801F7D08(void) {
    s32 height;
    s8* step;

    if (g_AreaCameraMoving == 0) {
        Area_ScrollAdvance(Area_HeightSample(g_AreaScrollTargetX, g_AreaScrollTargetY));
        g_AreaScrollTargetX     = TO_COORD(38);
        g_AreaCameraHeightDelta = ((Area_HeightSample(g_AreaScrollTargetX, g_AreaScrollTargetY) - g_AreaCameraHeight) / 128);
        step                    = &g_ScenarioState.state_04;
        g_AreaSceneMode         = 1;
        *step                   = *step + 1;
        return;
    }
    height             = g_AreaCameraHeight;
    g_AreaCameraHeight = height + 2;
    if (!(g_FrameCount & 0x3)) {
        g_AreaCameraHeight = height + 3;
    }
}

MATCH void func_801F7DF4(void) {
    s8* state;

    if (g_AreaCameraMoving == 0) {
        Area_ScrollAdvance(Area_HeightSample(g_AreaScrollTargetX, g_AreaScrollTargetY));
        state                   = &g_ScenarioState.state_04;
        g_AreaCameraSpeed       = 0x10;
        g_AreaScrollTargetX     = TO_COORD(25);
        g_AreaCameraHeightDelta = 0;
        (*state)++;
    } else {
        g_AreaCameraAngle.vx--;
        g_AreaCameraOffsetZ -= 6;
    }
}

MATCH void func_801F7E9C(void) {
    s8* step;

    if (g_AreaCameraMoving == 0) {
        step            = &g_ScenarioState.state_04;
        g_AreaSceneMode = 2;
        *step           = *step + 1;
    } else {
        g_AreaCameraHeight += 2;
        if ((u32)g_AreaCameraHeight >= 0x541) {
            g_AreaCameraHeight = 0x540;
        }
    }
}

MATCH void func_801F7F04(void) {
    s8* step;

    if (g_ScriptVars[3] == 0x64) {
        step            = &g_ScenarioState.state_04;
        g_AreaSceneMode = 3;
        *step += 1;
    }
}

MATCH void func_801F7F3C(void) {
    s32 height;

    height             = g_AreaCameraHeight + 0x10;
    g_AreaCameraHeight = height;
    if (height >= 3265U) {
        g_ScenarioState.step = 0xF;
        g_ScenarioState.state_04 += 1;
    }
    g_AreaCameraRefreshCount = 2;
}

MATCH void func_801F7F94(void) {
    u8* timer;
    u8  count;

    timer  = &g_ScenarioState.step;
    count  = *timer - 1;
    *timer = count;
    if (count == 0) {
        UI_ModeSet(UI_MODE_LONG_FADE_OUT);
        g_ScenarioState.state_04 = g_ScenarioState.state_04 + 1;
    }
}

MATCH void func_801F7FF0(void) {
    u8* bgm;
    s8* stage;
    u32 row;

    if (g_SysThreads[2].state == 0) {
        bgm = &g_SndBGMId;
        row = *bgm * 4;
        SND_SeqStop(g_SelectionSepSlots[row], g_SelectionSequences[row]);
        stage                    = &D_80146873;
        *bgm                     = 0xFF;
        g_AreaDrawFlags          = 0;
        g_AreaSceneMode          = 6;
        g_ScenarioState.state_04 = 0;
        *stage                   = *stage + 1;
    }
}

MATCH void func_801F8088(void) {
    SYS_DISPATCH_BYTE(D_801F9798, (s8)g_ScenarioState.state_04);
    func_801F8EF0();
}

/* func_801F80CC */
MATCH void Scene_StartEndingXA(void) {
    s8* step;

    SND_XAStartStream(8, 1);
    step               = &g_ScenarioState.state_04;
    g_EndingRollLine   = 0;
    g_EndingRollScroll = 0;
    *step += 1;
}

/* func_801F8110 */
MATCH void Scene_WaitEndingXA(void) {
    u8  ready;
    s8* step;

    ready = Scene_UpdateEndingRoll();
    if ((u8)SND_XAIsIdle() && ready) {
        UI_ModeSet(UI_MODE_LONG_FADE_OUT);
        step  = &g_ScenarioState.state_04;
        *step = *step + 1;
    }
}

MATCH void func_801F8170(void) {
    s8* stage;

    if (g_SysThreads[2].state == 0) {
        stage                    = &D_80146873;
        g_ScenarioState.state_04 = 0;
        *stage                   = *stage + 1;
    } else {
        Scene_UpdateEndingRoll();
    }
}

MATCH void func_801F81BC(void) {
    SYS_DISPATCH_BYTE(D_801F97A4, g_ScenarioState.state_04);
}

MATCH void func_801F81F8(void) {
    /* FAKE: the two words size the frame like retail. */
    s32 unused[2];
    s8* step;

    g_AreaScrollTargetX = TO_COORD(37) + COORD_HALF;
    g_AreaScrollTargetY = TO_COORD(27);
    Area_InitMapRenderer();
    UI_ModeSet(UI_MODE_FADE_IN);
    SYS_ThreadWait(1);
    g_AreaDrawFlags = 0x1F;
    SND_BGMPlay(0xA0, 0x64, 0x8);
    step = &g_ScenarioState.state_04;
    *step += 1;
}

MATCH void func_801F8274(void) {
    if (g_SysThreads[2].state == 0) {
        g_ScenarioState.step = 0;
        g_ScenarioState.state_04 += 1;
    }
    func_801F8B10(0, 0xFF);
}

MATCH void func_801F82C0(void) {
    u8* timer;
    u8  value;

    timer  = &g_ScenarioState.step;
    value  = *timer + 1;
    *timer = value;
    if (value == 50) {
        *timer = 150;
        g_ScenarioState.state_04 += 1;
        func_801F8B10(0x1F4, 0xFF);
    } else {
        func_801F8B10(value * 10, 0xFF);
    }
}

MATCH void func_801F833C(void) {
    u8* timer;

    timer = &g_ScenarioState.step;
    *timer -= 1;
    if (*timer == 0) {
        g_ScriptVars[3] = 0x6E;
        g_ScenarioState.state_04 += 1;
        *timer = 70;
    }
    func_801F8B10(0x1F4, 0xFF);
}

MATCH void func_801F83A8(void) {
    u8* timer;
    u8  count;

    timer  = &g_ScenarioState.step;
    count  = *timer - 1;
    *timer = count;
    if (count == 0) {
        g_ScenarioState.state_04 = g_ScenarioState.state_04 + 1;
    }
    func_801F8B10(0x1F4, 0xFF);
}

MATCH void func_801F8404(void) {
    u8* timer;
    u8  value;

    timer  = &g_ScenarioState.step;
    value  = *timer + 2;
    *timer = value;
    if (value >= 0x46) {
        *timer = 0;
        g_ScenarioState.state_04 += 1;
        func_801F8B10(0x4B0, 0xFF);
    } else {
        func_801F8B10(value * 10 + 0x1F4, 0xFF);
    }
}

MATCH void func_801F8480(void) {
    u8* timer;
    u32 value;

    timer  = &g_ScenarioState.step;
    value  = *timer + 2;
    *timer = value;
    if ((u8)value >= 127) {
        *timer = 0;
        g_ScenarioState.state_04 += 1;
        func_801F8B10(0x4B0, 0x80);
    } else {
        func_801F8B10(0x4B0, (u8)~value);
    }
}

MATCH void func_801F84F4(void) {
    u8* timer;
    u8  value;

    timer  = &g_ScenarioState.step;
    value  = *timer + 1;
    *timer = value;
    if (value >= 128) {
        g_ScriptVars[3] = 0x3C;
        *timer          = 30;
        D_801F9DD8      = 0;
        g_ScenarioState.state_04 += 1;
        EMI_ArchiveLoad(EMI_SLOT_ENDKANJI);
        func_801F8FAC(0xE0, 0xBE, 0x80, 1);
    } else {
        func_801F8FAC(0xE0, 0xBE, value, 1);
    }
    func_801F8B10(0x4B0, 0x80);
}

MATCH void func_801F8594(void) {
    u8* timer;
    u8* count;

    if (g_PadStates[0].pressed & PADRdown) {
        D_801F9DD8 = 1;
    }
    if (EMI_IsReady() != 0) {
        timer = &g_ScenarioState.step;
        *timer -= 1;
        if (*timer == 0) {
            count = &g_ScriptVars[3];
            *count -= 1;
            if (*count == 0) {
                g_ScenarioState.state_04 += 1;
            } else {
                *timer = 30;
            }
        }
    }
    func_801F8B10(0x4B0, 0x80);
    func_801F8FAC(0xE0, 0xBE, 0x80, 1);
}

MATCH void func_801F8664(void) {
    s8* state;

    if ((g_PadStates[0].pressed & PADRdown) || D_801F9DD8 != 0) {
        SND_StartDecrescendo(g_BGMTracks[g_SndBGMId].sep_slot, g_BGMTracks[g_SndBGMId].sequence, 100, 16);
        UI_ModeSet(UI_MODE_LONG_FADE_OUT);
        state = &g_ScenarioState.state_04;
        (*state)++;
    }
    func_801F8B10(0x4B0, 0x80);
    func_801F8FAC(0xE0, 0xBE, 0x80, 1);
}

MATCH void func_801F8710(void) {
    s8* state;
    u8* bgm;

    if (g_SysThreads[2].state == 0) {
        bgm = &g_SndBGMId;
        SND_SeqStop(g_BGMTracks[*bgm].sep_slot, g_BGMTracks[*bgm].sequence);
        *bgm = GAME_NONE;
        SND_SetBankLayout(0);
        g_AreaDrawFlags = 0;
        MESSAGE_START_WAIT(MSG_SCENA17_001);
        state = &g_ScenarioState.state_04;
        (*state)++;
    }
    func_801F8B10(0x4B0, 0x80);
    func_801F8FAC(0xE0, 0xBE, 0x80, 1);
}

MATCH void func_801F87D0(void) {
    if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
        if (g_ScenarioState.step == 0) {
            g_ScenarioState.state_04 += 1;
            return;
        }
        SND_Exit();
        SYS_ThreadReplace(SYS_StartFrontend);
    }
}

MATCH void func_801F8844(void) {
    D_80146873               = 0;
    g_ScenarioState.state_04 = 0;
    SYS_ThreadReplace(Scene_RunSaveMenu);
}

#include "overlays/scenario/shared/Scene_DispatchActor.h"

MATCH s32 func_801F88BC(void) {
    return 0;
}

MATCH s32 func_801F88C4(void) {
    return 0;
}

/* func_801F88CC */
MATCH void func_801F88CC(s32 semi, s32 color) {
    SPRT* sprite;
    TILE* tile;
    s32   tpage;
    s32   shade;

    if ((u8)semi != 0) {
        tpage = getTPage(TPAGE_DEPTH_15BIT, TPAGE_ABR_SUB, 704, 0);
        GFX_ADD_LAYER_DRAW_MODE(GFX_LAYER_EFFECT_FRONT, tpage);
        tile = (TILE*)g_GfxPrimCursor;
        setlen(tile, 3);
        setcode(tile, 0x60);
        PSX_SET_SEMI_TRANSPARENT(tile);
        shade = color * 2;
        setRGB0(tile, shade, shade, shade);
        tile->w = SCREEN_WIDTH;
        setXY0(tile, 0, 0);
        tile->h = SCREEN_HEIGHT;
        GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(TILE));
    }
    tpage = getTPage(TPAGE_DEPTH_15BIT, TPAGE_ABR_ADD, 704, 0);
    GFX_ADD_LAYER_DRAW_MODE(GFX_LAYER_EFFECT_FRONT, tpage);
    sprite = (SPRT*)g_GfxPrimCursor;
    setSprt(sprite);
    SetSemiTrans(sprite, (u8)semi);
    sprite->w = 0x100;
    setXY0(sprite, 0, 0);
    sprite->h = 0xF0;
    setUV0(sprite, 0, 0);
    setRGB0(sprite, color, color, color);
    GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(SPRT));
    tpage = getTPage(TPAGE_DEPTH_15BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y);
    GFX_ADD_LAYER_DRAW_MODE(GFX_LAYER_EFFECT_FRONT, tpage);
    sprite = (SPRT*)g_GfxPrimCursor;
    setSprt(sprite);
    SetSemiTrans(sprite, (u8)semi);
    setXY0(sprite, 0x100, 0);
    setWH(sprite, 0x40, 0xF0);
    setUV0(sprite, 0, 0);
    setRGB0(sprite, color, color, color);
    GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(SPRT));
}

#ifdef NON_MATCHING
NON_MATCHING void func_801F8B10(s32 scale, s32 shade) {
    SVECTOR  rot;
    SVECTOR  axis;
    MATRIX   mtx;
    long     flag;
    long     p;
    long     sxy;
    POLY_G3* tri;
    POLY_F4* quad;
    u16      radius;
    s32      i;
    s32      a;
    s32      b;
    u8       col;
    s32      mode;

    radius = scale;
    col    = shade;
    PushMatrix();
    setVector(&axis, 0, 0, 0);
    rot.vx = (g_AreaScrollTargetX >> 9) - 0x4000;
    rot.vy = (g_AreaScrollTargetCoordY.fixed >> 9) - 0x4000;
    rot.vz = -Area_HeightSample(g_AreaScrollTargetX, g_AreaScrollTargetY) / 2;
    RotTransMatrix(&rot, mtx, &flag);
    RotMatrix(&axis, &mtx);
    MulMatrix2(&g_CameraMatrix, &mtx);
    SetRotMatrix(&mtx);
    SetTransMatrix(&mtx);
    mode = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 0, 0);
    GFX_ADD_DITHERED_DRAW_MODE(GFX_LAYER_EFFECT_FRONT, mode);
    for (i = 0; i < 32;) {
        a                         = i << 7;
        g_ScratchPadVectors[0].vx = 0;
        g_ScratchPadVectors[0].vy = 0;
        g_ScratchPadVectors[0].vz = 0;
        setVector(&g_ScratchPadVectors[1], (s16)FIXED_MUL(radius, rcos(a)), (s16)FIXED_MUL(radius, rsin(a)), 0);
        i++;
        b = i << 7;
        setVector(&g_ScratchPadVectors[2], (s16)FIXED_MUL(radius, rcos(b)), (s16)FIXED_MUL(radius, rsin(b)), 0);
        tri = (POLY_G3*)g_GfxPrimCursor;
        setPolyG3(tri);
        PSX_SET_SEMI_TRANSPARENT(tri);
        RotTransPers3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&tri->x0, (long*)&tri->x1, (long*)&tri->x2, &p, &sxy);
        setRGB0(tri, 0, 0, 0);
        setRGB1(tri, col, col, col);
        setRGB2(tri, col, col, col);
        GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(POLY_G3));
        setVector(&g_ScratchPadVectors[0], 0, 0, 0);
        setVector(&g_ScratchPadVectors[1], (s16)((u32)(rcos(a) * 25) >> 6), (s16)((u32)(rsin(a) * 25) >> 6), 0);
        setVector(&g_ScratchPadVectors[2], (s16)((u32)(rcos(b) * 25) >> 6), (s16)((u32)(rsin(b) * 25) >> 6), 0);
        quad = (POLY_F4*)g_GfxPrimCursor;
        setPolyF4(quad);
        PSX_SET_SEMI_TRANSPARENT(quad);
        RotTransPers3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&quad->x0, (long*)&quad->x2, (long*)&quad->x3, &p, &sxy);
        quad->x0 = tri->x1;
        quad->x1 = tri->x2;
        quad->y0 = tri->y1;
        quad->y1 = tri->y2;
        setRGB0(quad, col, col, col);
        GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(POLY_F4));
    }
    PopMatrix();
}
#else
INCLUDE_ASM(func_801F8B10);
#endif

MATCH void func_801F8EF0(void) {
    TILE* prim;
    s16   width;
    s16   height;

    width  = 320;
    height = 30;
    prim   = (TILE*)g_GfxPrimCursor;
    setTile(prim);
    setRGB0(prim, 0, 0, 0);
    setXY0(prim, 0, 0);
    setWH(prim, width, height);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(TILE));

    prim = (TILE*)g_GfxPrimCursor;
    setTile(prim);
    setRGB0(prim, 0, 0, 0);
    setXY0(prim, 0, 0xD2);
    setWH(prim, width, height);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(TILE));
}

MATCH void func_801F8FAC(s32 x, s32 y, s32 color, u8 semi_trans) {
    s32   tpage;
    SPRT* sprite;

    if (g_AreaDrawFlags == 0) {
        return;
    }
    tpage = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 832, 256);
    GFX_ADD_LAYER_DRAW_MODE(GFX_LAYER_EFFECT_FRONT, tpage);
    sprite = (SPRT*)g_GfxPrimCursor;
    setSprt(sprite);
    SetSemiTrans(sprite, semi_trans);
    setWH(sprite, 64, 32);
    setXY0(sprite, x, y);
    setUV0(sprite, 0, 0);
    sprite->clut = getClut(0, 493);
    setRGB0(sprite, color, color, color);
    GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(SPRT));
}

#ifdef NON_MATCHING
NON_MATCHING void func_801F90BC(s16 x, s16 y, u32 clut, u32 uv) {
    SPRT_16* prim;

    prim = (SPRT_16*)g_GfxPrimCursor;
    SetSprt16(prim);
    PSX_SET_NEUTRAL_RGB(prim);
    setXY0(prim, x, y);
    prim->clut = (clut & 0x3F) | 0x7B80;
    setUV0(prim, (uv & 0xF) << 4, uv & 0xF0);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(SPRT_16));
}
#else
INCLUDE_ASM(func_801F90BC);
#endif

MATCH void func_801F9160(s16 x, s16 y) {
    SPRT* prim;

    prim = (SPRT*)g_GfxPrimCursor;
    SetSprt(prim);
    PSX_SET_NEUTRAL_RGB(prim);
    prim->clut = getClut(80, 494);
    prim->v0   = 0x40;
    setXY0(prim, x, y);
    prim->u0 = 0;
    setWH(prim, 0x58, 0x12);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(SPRT));
}

/* func_801F91F0 */
MATCH void Scene_DrawEndingRollLine(s16 x, s16 y, u8* text) {
    u8  color;
    u8  glyph;
    s32 tpage;
    s32 idx;
    s32 t;

    color = 0;
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 960, 256);
    GFX_ADD_DRAW_MODE(tpage);
    while (*text != 0) {
        switch (*text) {
            case '!':
                text++;
                color = *text - '0';
                break;
            case '#':
                text++;
                idx   = *text + 4;
                glyph = idx;
                func_801F90BC(x, y, color, glyph);
                x += g_EndingGlyphWidth[glyph];
                break;
            case ' ':
                x += 12;
                break;
            case '@':
                func_801F9160(x, y);
                x += 0x58;
                break;
            default:
                t = *text - 0x41;
                if ((u8)t < 26) {
                    idx = t;
                } else {
                    idx = *text - 0x47;
                }
                glyph = idx;
                func_801F90BC(x, y, color, glyph);
                x += g_EndingGlyphWidth[glyph];
                break;
        }
        text++;
    }
}

/* func_801F938C */
MATCH bool Scene_UpdateEndingRoll(void) {
    s32 i;
    u8* text;

    for (i = 0; i < 16; i++) {
        text = g_EndingRollText[g_EndingRollLine + i];
        if (text != (u8*)-1 && text != NULL) {
            Scene_DrawEndingRollLine(16, i * 22 - g_EndingRollScroll, text);
        }
    }
    if (g_EndingRollText[g_EndingRollLine] != (u8*)-1) {
        g_EndingRollScroll += 1;
        if (g_EndingRollScroll == 22) {
            g_EndingRollScroll = 0;
            g_EndingRollLine += 1;
        }
        return 0;
    }
    return 1;
}

/* func_801F9490 */
MATCH void Scene_RunSaveMenu(void) {
    g_GameEntrySubstate = 0;
    SYS_ClearCurrentThread();
    UI_PanelResetTasks();
    while (1) {
        SYS_DISPATCH_BYTE(D_801F9DBC, g_GameEntrySubstate);
        SYS_ThreadWait(1);
    }
}

/* func_801F9504 */
MATCH void Scene_EnterSaveMenu(void) {
    s32 i;

    SYS_SetFlag(g_SceneEventFlags, 146);
    for (i = 9; i < 23; i++) {
        /* FAKE: retail passes the index as a word; the header's u8 parameter forces an andi. */
        ((void (*)(void*, s32))SYS_ClearFlag)(g_Scenario2Flags + 0x68, i);
    }
    Char_RebuildPartyStats();
    g_GameAreaId = AREA_ID_DRAGNIER_SURFACE;
    Game_ClearScriptActive();
    g_Game.members[0].pos.x.fixed = TO_COORD(15);
    g_Game.members[0].facing      = 3;
    g_SndBGMId                    = 0x6F;
    g_ScenarioState.scenario_id   = 15;
    D_8014865C                    = -2;
    g_Game.members[0].pos.y.fixed = TO_COORD_HALF(33);
    D_80146873                    = 0;
    g_ScenarioState.state_04      = 0;
    g_ScenarioState.step          = 0;
    g_MenuStep.step               = 0;
    D_80148698                    = 1;
    D_80148699                    = 0;
    D_80143BB4                    = 1;
    EMI_ArchiveLoad(EMI_SLOT_SHOP);
    while (EMI_IsReady() == 0) {
        SYS_ThreadWait(1);
    }
    GFX_PaletteCopy(1);
    GFX_PaletteCopy(2);
    g_GfxPalettePending = 1;
    FAKE_VOLATILE(u16, g_GameEntrySubstate) += 1;
}

/* func_801F9654 */
MATCH void Scene_UpdateSaveMenu(void) {
    UI_PanelUpdateTasks();
    Shop_DispatchStep();
}

/* func_801F967C */
MATCH void Scene_ExitToTitle(void) {
    g_ScriptVars[0] = 0;
    g_ScriptVars[1] = 0;
    g_ScriptVars[2] = 0;
    g_ScriptVars[3] = 0;
    SND_Exit();
    SYS_ThreadReplace(SYS_StartFrontend);
}

MATCH s32 func_801F96CC(void) {
    return 0;
}

#include "overlays/scenario/shared/Scene_SetPartyRyuYoungTeepoRei.h"

MATCH void func_801F9720(void) {
}
