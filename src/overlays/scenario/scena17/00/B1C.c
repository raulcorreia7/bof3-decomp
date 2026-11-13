#define AREA_SCROLL_TARGET_VOLATILE
#include "scena17_00.h"
#include "area/map.h"

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
    GFX_ResetPalette();
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
        Party_HideBattlers();
        g_AreaCameraAngle.vx = -0x2E4;
        g_AreaCameraAngle.vz = 0x12C;
        Area_AdvanceScroll(0x300);
        Area_UpdateCamera();
        func_801A0514();
        Area_DrawScene();
        rect.x = 0;
        rect.y = g_FrameBufferIndex * SCREEN_HEIGHT;
        rect.w = SCREEN_WIDTH;
        rect.h = SCREEN_HEIGHT;
        SetDrawMove((DR_MOVE*)g_GfxPrimCursor, &rect, 0x2C0, 0);
        GFX_AddPrim(5, sizeof(DR_MOVE));
    }
    g_AreaDrawFlags = 0;
    SND_SetBankLayout(2);
    g_SceneState.mode_02 = 2;
    g_SceneState.unk_03  = 1;
}

MATCH void func_801F789C(void) {
    SYS_DISPATCH_BYTE(D_801F9748, D_80146873);
}

MATCH void func_801F78D8(void) {
}

MATCH void func_801F78E0(void) {
    SYS_DISPATCH_BYTE(D_801F9758, (s8)D_80146874);
    func_801F8EF0();
}

MATCH void func_801F7924(void) {
    u8* step;

    if (g_UiWindowEffectBusy == 0) {
        g_AreaScrollTargetX = TO_COORD(176);
        g_AreaScrollTargetY = TO_COORD(19) + COORD_HALF;
        func_80153DE8();
        g_AreaSceneMode = 4;
        SND_RequestBGM(0x96);
        UI_SetMode(UI_MODE_FADE_IN);
        func_801F88CC(0, 0x80);
        step = &D_80146874;
        *step += 1;
    }
}

MATCH void func_801F79AC(void) {
    if ((g_UiWindowEffectBusy == 0) && (EMI_IsReady() != 0)) {
        D_80146875 = 0x5A;
        D_80146874 += 1;
    }
    func_801F88CC(0, 0x80);
}

MATCH void func_801F7A08(void) {
    u8* timer;

    timer = &D_80146875;
    *timer -= 1;
    if (*timer == 0) {
        SND_PlayBGM(0x96, 0x64, 0x8);
        *timer = 30;
        D_80146874 += 1;
    }
    func_801F88CC(0, 0x80);
}

MATCH void func_801F7A84(void) {
    u8* timer;
    u8  count;

    timer  = &D_80146875;
    count  = *timer - 1;
    *timer = count;
    if (count == 0) {
        g_AreaScrollTargetX  = TO_COORD(148);
        g_AreaCameraStep     = 0x20;
        *timer               = 128;
        g_AreaCameraAngle.vx = -0x16A;
        g_AreaCameraAngle.vz = 512;
        g_AreaDrawFlags      = AREA_DRAW_ALL_FLAGS;
        D_80146874           = D_80146874 + 1;
    }
    func_801F88CC(0, 0x80);
}

MATCH void func_801F7B20(void) {
    u8* timer;

    timer = &D_80146875;
    *timer -= 1;
    func_801F88CC(1, *timer);
    if (*timer == 0) {
        D_80146874 += 1;
    }
}

MATCH void func_801F7B88(void) {
    u8* step;

    if (!g_AreaCameraMoving) {
        step                = &D_80146874;
        g_AreaScrollTargetX = TO_COORD(140);
        *step += 1;
    }
}

MATCH void func_801F7BC0(void) {
    u8* step;

    g_AreaCameraAngle.vx -= 5;
    if (g_AreaCameraMoving == 0) {
        step                = &D_80146874;
        g_AreaScrollTargetX = TO_COORD(84);
        D_80146867          = 0xA;
        *step += 1;
    }
}

MATCH void func_801F7C14(void) {
    u8* step;

    if (g_AreaCameraMoving == 0 && D_80146867 == 0x14) {
        step                = &D_80146874;
        g_AreaCameraStep    = 0x10;
        g_AreaScrollTargetX = TO_COORD(60);
        *step += 1;
    }
}

MATCH void func_801F7C6C(void) {
    u8* step;

    if (g_AreaCameraMoving == 0) {
        Area_AdvanceScroll(Area_SampleHeight(g_AreaScrollTargetX, g_AreaScrollTargetY));
        step                = &D_80146874;
        g_AreaScrollTargetX = TO_COORD(46);
        *step += 1;
    } else if (g_FrameCount & 0x1) {
        g_AreaCameraHeight -= 1;
    }
}

/* The script counter is read and written through one materialized address (a0), so the increment
 * store lands in the jump's delay slot; a direct D_80146874 += 1 reloads the address per access. */
MATCH void func_801F7D08(void) {
    s32 height;
    u8* step;

    if (g_AreaCameraMoving == 0) {
        Area_AdvanceScroll(Area_SampleHeight(g_AreaScrollTargetX, g_AreaScrollTargetY));
        g_AreaScrollTargetX    = TO_COORD(38);
        g_AreaCameraHeightStep = ((Area_SampleHeight(g_AreaScrollTargetX, g_AreaScrollTargetY) - g_AreaCameraHeight) / 128);
        step                   = &D_80146874;
        g_AreaSceneMode        = 1;
        *step                  = *step + 1;
        return;
    }
    height             = g_AreaCameraHeight;
    g_AreaCameraHeight = height + 2;
    if (!(g_FrameCount & 0x3)) {
        g_AreaCameraHeight = height + 3;
    }
}

MATCH void func_801F7DF4(void) {
    u8* state;

    if (g_AreaCameraMoving == 0) {
        Area_AdvanceScroll(Area_SampleHeight(g_AreaScrollTargetX, g_AreaScrollTargetY));
        state                  = &D_80146874;
        g_AreaCameraStep       = 0x10;
        g_AreaScrollTargetX    = TO_COORD(25);
        g_AreaCameraHeightStep = 0;
        (*state)++;
    } else {
        g_AreaCameraAngle.vx--;
        g_AreaCameraOffsetZ -= 6;
    }
}

MATCH void func_801F7E9C(void) {
    u8* step;

    if (g_AreaCameraMoving == 0) {
        step            = &D_80146874;
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
    u8* step;

    if (D_80146867 == 0x64) {
        step            = &D_80146874;
        g_AreaSceneMode = 3;
        *step += 1;
    }
}

MATCH void func_801F7F3C(void) {
    s32 height;

    height             = g_AreaCameraHeight + 0x10;
    g_AreaCameraHeight = height;
    if (height >= 3265U) {
        D_80146875 = 0xF;
        D_80146874 += 1;
    }
    g_AreaCameraRefreshCount = 2;
}

MATCH void func_801F7F94(void) {
    u8* timer;
    u8  count;

    timer  = &D_80146875;
    count  = *timer - 1;
    *timer = count;
    if (count == 0) {
        UI_SetMode(UI_MODE_LONG_FADE_OUT);
        D_80146874 = D_80146874 + 1;
    }
}

MATCH void func_801F7FF0(void) {
    u8* bgm;
    s8* stage;
    u32 row;

    if (g_UiWindowEffectBusy == 0) {
        bgm = &g_SndBGMId;
        row = *bgm * 4;
        SND_StopSequence(g_SelectionCues[row], g_SelectionSequences[row]);
        stage           = &D_80146873;
        *bgm            = 0xFF;
        g_AreaDrawFlags = 0;
        g_AreaSceneMode = 6;
        D_80146874      = 0;
        *stage          = *stage + 1;
    }
}

MATCH void func_801F8088(void) {
    SYS_DISPATCH_BYTE(D_801F9798, (s8)D_80146874);
    func_801F8EF0();
}

/* func_801F80CC */
MATCH void Scene_StartEndingXa(void) {
    u8* step;

    SND_StartXAStream(8, 1);
    step       = &D_80146874;
    D_801F9DD0 = 0;
    D_801F9DD4 = 0;
    *step += 1;
}

/* func_801F8110 */
MATCH void Scene_WaitEndingXa(void) {
    u8  ready;
    u8* step;

    ready = func_801F938C();
    if ((u8)SND_IsXAIdle() && ready) {
        UI_SetMode(UI_MODE_LONG_FADE_OUT);
        step  = &D_80146874;
        *step = *step + 1;
    }
}

MATCH void func_801F8170(void) {
    s8* stage;

    if (g_UiWindowEffectBusy == 0) {
        stage      = &D_80146873;
        D_80146874 = 0;
        *stage     = *stage + 1;
    } else {
        func_801F938C();
    }
}

MATCH void func_801F81BC(void) {
    SYS_DISPATCH_BYTE(D_801F97A4, g_SceneState.state_04);
}

MATCH void func_801F81F8(void) {
    /* FAKE: the two words size the frame like retail. */
    s32 unused[2];
    u8* step;

    g_AreaScrollTargetX = TO_COORD(37) + COORD_HALF;
    g_AreaScrollTargetY = TO_COORD(27);
    func_80153DE8();
    UI_SetMode(UI_MODE_FADE_IN);
    CallbackWait(1);
    g_AreaDrawFlags = 0x1F;
    SND_PlayBGM(0xA0, 0x64, 0x8);
    step = &D_80146874;
    *step += 1;
}

MATCH void func_801F8274(void) {
    if (g_UiWindowEffectBusy == 0) {
        D_80146875 = 0;
        D_80146874 += 1;
    }
    func_801F8B10(0, 0xFF);
}

MATCH void func_801F82C0(void) {
    u8* timer;
    u8  value;

    timer  = &D_80146875;
    value  = *timer + 1;
    *timer = value;
    if (value == 50) {
        *timer = 150;
        D_80146874 += 1;
        func_801F8B10(0x1F4, 0xFF);
    } else {
        func_801F8B10(value * 10, 0xFF);
    }
}

MATCH void func_801F833C(void) {
    u8* timer;

    timer = &D_80146875;
    *timer -= 1;
    if (*timer == 0) {
        D_80146867 = 0x6E;
        D_80146874 += 1;
        *timer = 70;
    }
    func_801F8B10(0x1F4, 0xFF);
}

MATCH void func_801F83A8(void) {
    u8* timer;
    u8  count;

    timer  = &D_80146875;
    count  = *timer - 1;
    *timer = count;
    if (count == 0) {
        D_80146874 = D_80146874 + 1;
    }
    func_801F8B10(0x1F4, 0xFF);
}

MATCH void func_801F8404(void) {
    u8* timer;
    u8  value;

    timer  = &D_80146875;
    value  = *timer + 2;
    *timer = value;
    if (value >= 0x46) {
        *timer = 0;
        D_80146874 += 1;
        func_801F8B10(0x4B0, 0xFF);
    } else {
        func_801F8B10(value * 10 + 0x1F4, 0xFF);
    }
}

MATCH void func_801F8480(void) {
    u8* timer;
    u32 value;

    timer  = &D_80146875;
    value  = *timer + 2;
    *timer = value;
    if ((u8)value >= 127) {
        *timer = 0;
        D_80146874 += 1;
        func_801F8B10(0x4B0, 0x80);
    } else {
        func_801F8B10(0x4B0, (u8)~value);
    }
}

MATCH void func_801F84F4(void) {
    u8* timer;
    u8  value;

    timer  = &D_80146875;
    value  = *timer + 1;
    *timer = value;
    if (value >= 128) {
        D_80146867 = 0x3C;
        *timer     = 30;
        D_801F9DD8 = 0;
        D_80146874 += 1;
        EMI_LoadArchive(0x260);
        func_801F8FAC(0xE0, 0xBE, 0x80, 1);
    } else {
        func_801F8FAC(0xE0, 0xBE, value, 1);
    }
    func_801F8B10(0x4B0, 0x80);
}

INCLUDE_ASM(func_801F8594);

MATCH void func_801F8664(void) {
    u8* state;

    if ((g_InputPressed & PADRdown) || D_801F9DD8 != 0) {
        SND_StartDecrescendo(g_SelectionCues[g_SndBGMId * 4], g_SelectionSequences[g_SndBGMId * 4], 100, 16);
        UI_SetMode(UI_MODE_LONG_FADE_OUT);
        state = &D_80146874;
        (*state)++;
    }
    func_801F8B10(0x4B0, 0x80);
    func_801F8FAC(0xE0, 0xBE, 0x80, 1);
}

MATCH void func_801F8710(void) {
    u8* state;
    u8* bgm;

    if (g_UiWindowEffectBusy == 0) {
        bgm = &g_SndBGMId;
        SND_StopSequence(g_SelectionCues[*bgm * 4], g_SelectionSequences[*bgm * 4]);
        *bgm = GAME_NONE;
        SND_SetBankLayout(0);
        g_AreaDrawFlags = 0;
        Message_StartAreaMessage(1);
        g_GameStateIndex = GAME_REQUEST_MESSAGE;
        state            = &D_80146874;
        (*state)++;
    }
    func_801F8B10(0x4B0, 0x80);
    func_801F8FAC(0xE0, 0xBE, 0x80, 1);
}

MATCH void func_801F87D0(void) {
    if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
        if (D_80146875 == 0) {
            D_80146874 += 1;
            return;
        }
        SND_Exit();
        CallbackReplace(SYS_StartFrontend);
    }
}

MATCH void func_801F8844(void) {
    D_80146873            = 0;
    g_SceneState.state_04 = 0;
    CallbackReplace(Scene_RunSaveMenu);
}

#include "overlays/scenario/Scene_DispatchActor.h"

MATCH s32 func_801F88BC(void) {
    return 0;
}

MATCH s32 func_801F88C4(void) {
    return 0;
}

INCLUDE_ASM(func_801F88CC);

INCLUDE_ASM(func_801F8B10);

MATCH void func_801F8EF0(void) {
    TILE* prim;
    u8    len;
    u8    code;
    s16   width;
    s16   height;

    len    = 3;
    code   = 0x60;
    width  = 320;
    height = 30;
    prim   = (TILE*)g_GfxPrimCursor;
    setlen(prim, len);
    setcode(prim, code);
    setRGB0(prim, 0, 0, 0);
    setXY0(prim, 0, 0);
    setWH(prim, width, height);
    GFX_AddPrim(1, sizeof(TILE));

    prim = (TILE*)g_GfxPrimCursor;
    setlen(prim, len);
    setcode(prim, code);
    setRGB0(prim, 0, 0, 0);
    setXY0(prim, 0, 0xD2);
    setWH(prim, width, height);
    GFX_AddPrim(1, sizeof(TILE));
}

MATCH void func_801F8FAC(s32 x, s32 y, s32 color, u8 semi_trans) {
    s32   tpage;
    SPRT* sprite;

    if (g_AreaDrawFlags == 0) {
        return;
    }
    tpage = getTPage(1, 1, 832, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, tpage, 0);
    GFX_AddPrim(2, sizeof(DR_MODE));
    sprite = (SPRT*)g_GfxPrimCursor;
    setSprt(sprite);
    SetSemiTrans(sprite, semi_trans);
    setWH(sprite, 64, 32);
    setXY0(sprite, x, y);
    setUV0(sprite, 0, 0);
    sprite->clut = getClut(0, 493);
    setRGB0(sprite, color, color, color);
    GFX_AddPrim(2, sizeof(SPRT));
}

INCLUDE_ASM(func_801F90BC);

MATCH void func_801F9160(s16 x, s16 y) {
    SPRT* prim;

    prim = (SPRT*)g_GfxPrimCursor;
    SetSprt(prim);
    setRGB0(prim, 128, 128, 128);
    prim->clut = 0x7B85;
    prim->v0   = 0x40;
    setXY0(prim, x, y);
    prim->u0 = 0;
    setWH(prim, 0x58, 0x12);
    GFX_AddPrim(1, sizeof(SPRT));
}

INCLUDE_ASM(func_801F91F0);

INCLUDE_ASM(func_801F938C);

/* func_801F9490 */
MATCH void Scene_RunSaveMenu(void) {
    g_GameEntrySubstate = 0;
    func_8014BA04();
    Menu_ResetPanelTasks();
    while (1) {
        SYS_DISPATCH_BYTE(D_801F9DBC, g_GameEntrySubstate);
        CallbackWait(1);
    }
}

INCLUDE_ASM(func_801F9504);

/* func_801F9654 */
MATCH void Scene_UpdateSaveMenu(void) {
    Menu_UpdatePanelTasks();
    Shop_DispatchStep();
}

/* func_801F967C */
MATCH void Scene_ExitToTitle(void) {
    g_ScriptVars[0] = 0;
    D_80146865      = 0;
    D_80146866      = 0;
    D_80146867      = 0;
    SND_Exit();
    CallbackReplace(SYS_StartFrontend);
}

MATCH s32 func_801F96CC(void) {
    return 0;
}

#include "overlays/scenario/Scene_SetPartyRyuYoungTeepoRei.h"

MATCH void func_801F9720(void) {
}
