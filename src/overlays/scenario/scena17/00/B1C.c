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
    ORDER_LOCK(D_801F973C[index]());
}

MATCH void func_801F7750(void) {
    GFX_ResetPalette();
    g_GfxPalettePending = 1;
    g_AreaDrawFlags     = 0x1F;
    Game_RequestAreaChange(AREA_ID_END_GAME_SAVE, TO_COORD(182), TO_COORD(18) + COORD_HALF, FACING_LEFT);
    g_ScriptVarsReq.word = 0;
    D_80146872           = 1;
}

INCLUDE_ASM(func_801F77B4);

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
        g_AreaScrollTargetX = 0xB00000;
        g_AreaScrollTargetY = 0x138000;
        func_80153DE8();
        g_AreaSceneMode = 4;
        SND_RequestBgm(0x96);
        UI_SetMode(1);
        func_801F88CC(0, 0x80);
        step = &D_80146874;
        *step += 1;
    }
}

MATCH void func_801F79AC(void) {
    if ((g_UiWindowEffectBusy == 0) && (EMI_LoaderIsReady() != 0)) {
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
        SND_PlayBgm(0x96, 0x64, 0x8);
        *timer = 0x1E;
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
        g_AreaScrollTargetX  = 0x940000;
        g_AreaCameraStep     = 0x20;
        *timer               = 0x80;
        g_AreaCameraAngle.vx = -0x16A;
        g_AreaCameraAngle.vz = 0x200;
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
        g_AreaScrollTargetX = 0x8C0000;
        *step += 1;
    }
}

MATCH void func_801F7BC0(void) {
    u8* step;

    g_AreaCameraAngle.vx -= 5;
    if (g_AreaCameraMoving == 0) {
        step                = &D_80146874;
        g_AreaScrollTargetX = 0x540000;
        D_80146867          = 0xA;
        *step += 1;
    }
}

MATCH void func_801F7C14(void) {
    u8* step;

    if (g_AreaCameraMoving == 0 && D_80146867 == 0x14) {
        step                = &D_80146874;
        g_AreaCameraStep    = 0x10;
        g_AreaScrollTargetX = 0x3C0000;
        *step += 1;
    }
}

MATCH void func_801F7C6C(void) {
    u8* step;

    if (g_AreaCameraMoving == 0) {
        Area_AdvanceScroll(Area_SampleHeight(g_AreaScrollTargetX, g_AreaScrollTargetY));
        step                = &D_80146874;
        g_AreaScrollTargetX = 0x2E0000;
        *step += 1;
    } else if (g_FrameCount & 1) {
        g_AreaCameraHeight -= 1;
    }
}

/* The script counter is read and written through one materialized address (a0), so the increment
 * store lands in the jump's delay slot; a direct D_80146874 += 1 reloads the address per access. */
MATCH void func_801F7D08(void) {
    s32 temp_a0;
    u8* var_a0;

    if (g_AreaCameraMoving == 0) {
        Area_AdvanceScroll(Area_SampleHeight(g_AreaScrollTargetX, g_AreaScrollTargetY));
        g_AreaScrollTargetX = 0x260000;
        g_AreaCameraHeightStep =
            ((Area_SampleHeight(g_AreaScrollTargetX, g_AreaScrollTargetY) - g_AreaCameraHeight) / 128);
        var_a0          = &D_80146874;
        g_AreaSceneMode = 1;
        *var_a0         = *var_a0 + 1;
        return;
    }
    temp_a0            = g_AreaCameraHeight;
    g_AreaCameraHeight = temp_a0 + 2;
    if (!(g_FrameCount & 3)) {
        g_AreaCameraHeight = temp_a0 + 3;
    }
}

MATCH void func_801F7DF4(void) {
    u8* state;

    if (g_AreaCameraMoving == 0) {
        Area_AdvanceScroll(Area_SampleHeight(g_AreaScrollTargetX, g_AreaScrollTargetY));
        state                  = &D_80146874;
        g_AreaCameraStep       = 0x10;
        g_AreaScrollTargetX    = 0x190000;
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
    if (height >= 0xCC1U) {
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
        UI_SetMode(13);
        D_80146874 = D_80146874 + 1;
    }
}

MATCH void func_801F7FF0(void) {
    u8* bgm;
    s8* stage;
    u32 row;

    if (g_UiWindowEffectBusy == 0) {
        bgm = &g_SndBgmId;
        row = *bgm * 4;
        SND_StopSequence(g_SelectionCues[row], D_80181EBB[row]);
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

MATCH void func_801F80CC(void) {
    u8* step;

    SND_StartXAStream(8, 1);
    step       = &D_80146874;
    D_801F9DD0 = 0;
    D_801F9DD4 = 0;
    *step += 1;
}

MATCH void func_801F8110(void) {
    u8  ready;
    u8* step;

    ready = func_801F938C();
    if ((u8)SND_IsXAIdle() && ready) {
        UI_SetMode(0xD);
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

    g_AreaScrollTargetX = 0x258000;
    g_AreaScrollTargetY = 0x1B0000;
    func_80153DE8();
    UI_SetMode(1);
    CallbackWait(1);
    g_AreaDrawFlags = 0x1F;
    SND_PlayBgm(0xA0, 0x64, 0x8);
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
    if (value == 0x32) {
        *timer = 0x96;
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
        *timer = 0x46;
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

/* blocker: sum register; first diff: +0x18 addiu v0,v0,2 (candidate) against addiu a1,v0,2 (retail). */
INCLUDE_ASM(func_801F8480);

/* nonmatching: timer D_80146875 counts up; at 0x80 it sets D_80146867 = 0x3C, the timer to 0x1E, D_801F9DD8 = 0, steps
   D_80146874, starts EMI_LoaderStreamInitSlot(0x260), then calls func_801F8FAC(0xE0, 0xBE, shade, 1) and
   func_801F8B10(0x4B0, 0x80). Candidate is 8 bytes short (first differing instruction: bnez at +0x28 targets +0x78
   against +0x70): retail sets a0, a1 and a2 inside the branch and ends it with j, and sets only a1 on the other path.
*/
MATCH void func_801F84F4(void) {
    u8* timer;
    u8  value;

    timer  = &D_80146875;
    value  = *timer + 1;
    *timer = value;
    if (value >= 0x80) {
        D_80146867 = 0x3C;
        *timer     = 0x1E;
        D_801F9DD8 = 0;
        D_80146874 += 1;
        EMI_LoaderStreamInitSlot(0x260);
        func_801F8FAC(0xE0, 0xBE, 0x80, 1);
    } else {
        func_801F8FAC(0xE0, 0xBE, value, 1);
    }
    func_801F8B10(0x4B0, 0x80);
}

/* blocker: argument duplication across paths; first diff: +0x2C beqz v0 target against jal. */
INCLUDE_ASM(func_801F8594);

MATCH void func_801F8664(void) {
    u8* state;

    if ((g_InputPressed & PADRdown) || D_801F9DD8 != 0) {
        SND_StartDecrescendo(g_SelectionCues[g_SndBgmId * 4], D_80181EBB[g_SndBgmId * 4], 100, 16);
        UI_SetMode(0xD);
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
        bgm = &g_SndBgmId;
        SND_StopSequence(g_SelectionCues[*bgm * 4], D_80181EBB[*bgm * 4]);
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
    CallbackReplace(func_801F9490);
}

MATCH void func_801F887C(void* entity) {
    SceneFunc handler;
    u8        index;

    index   = ((Actor*)entity)->callback_index;
    handler = D_801F97D8[index];
    handler(entity, g_SceneFlags);
}

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
    width  = 0x140;
    height = 0x1E;
    prim   = (TILE*)g_GfxPrimCursor;
    setlen(prim, len);
    setcode(prim, code);
    setRGB0(prim, 0, 0, 0);
    setXY0(prim, 0, 0);
    setWH(prim, width, height);
    GFX_AddPrim(1, 0x10);

    prim = (TILE*)g_GfxPrimCursor;
    setlen(prim, len);
    setcode(prim, code);
    setRGB0(prim, 0, 0, 0);
    setXY0(prim, 0, 0xD2);
    setWH(prim, width, height);
    GFX_AddPrim(1, 0x10);
}

INCLUDE_ASM(func_801F8FAC);

/* blocker: argument locals' register order; first diff: +0x14 move s2,a2 (candidate) against move s2,a3 (retail). */
INCLUDE_ASM(func_801F90BC);

MATCH void func_801F9160(s16 x, s16 y) {
    SPRT* prim;

    prim = (SPRT*)g_GfxPrimCursor;
    SetSprt(prim);
    setRGB0(prim, 0x80, 0x80, 0x80);
    prim->clut = 0x7B85;
    prim->v0   = 0x40;
    setXY0(prim, x, y);
    prim->u0 = 0;
    setWH(prim, 0x58, 0x12);
    GFX_AddPrim(1, 0x14);
}

INCLUDE_ASM(func_801F91F0);

INCLUDE_ASM(func_801F938C);

MATCH void func_801F9490(void) {
    g_GameEntrySubstate = 0;
    func_8014BA04();
    Menu_ResetPanelTasks();
    while (1) {
        SYS_DISPATCH_BYTE(D_801F9DBC, g_GameEntrySubstate);
        CallbackWait(1);
    }
}

INCLUDE_ASM(func_801F9504);

MATCH void func_801F9654(void) {
    Menu_RunPanelTasks();
    Shop_DispatchStep();
}

MATCH void func_801F967C(void) {
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
