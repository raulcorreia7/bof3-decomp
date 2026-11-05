#define AREA_SCROLL_TARGET_VOLATILE
#include "scena17_00.h"

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
    func_8019FA28(0xC7, 0xB60000, 0x128000, 7);
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

INCLUDE_ASM(func_801F7924);

MATCH void func_801F79AC(void) {
    if ((g_UiWindowEffectBusy == 0) && (EMI_LoaderIsReady() != 0)) {
        D_80146875 = 0x5A;
        D_80146874 += 1;
    }
    func_801F88CC(0, 0x80);
}

INCLUDE_ASM(func_801F7A08);

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

INCLUDE_ASM(func_801F7B20);

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

INCLUDE_ASM(func_801F7C6C);

/* needs: type. While the camera is idle: Area_AdvanceScroll(Area_SampleHeight(x, y)), g_AreaScrollTargetX = 0x260000, g_AreaCameraHeightStep = (Area_SampleHeight(x, y) - g_AreaCameraHeight) / 128, g_AreaSceneMode = 1, D_80146874++ (through a pointer local); otherwise g_AreaCameraHeight += 2, or 3 every fourth frame. Exact except retail reloads g_AreaScrollTargetX after the 0x260000 store (lui a0 / lw a0 where the candidate folds lui a0,0x26; first differing instruction +0x30), which needs `g_AreaScrollTargetX` volatile in slus/data.h with the exe kept exact. */
INCLUDE_ASM(func_801F7D08);

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
    if ((u32)height >= 0xCC1U) {
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

    SND_StartXaStream(8, 1);
    step       = &D_80146874;
    D_801F9DD0 = 0;
    D_801F9DD4 = 0;
    *step += 1;
}

MATCH void func_801F8110(void) {
    u8  ready;
    u8* step;

    ready = func_801F938C();
    if ((u8)SND_IsXaIdle() && ready) {
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

INCLUDE_ASM(func_801F81F8);

MATCH void func_801F8274(void) {
    if (g_UiWindowEffectBusy == 0) {
        D_80146875 = 0;
        D_80146874 += 1;
    }
    func_801F8B10(0, 0xFF);
}

INCLUDE_ASM(func_801F82C0);

INCLUDE_ASM(func_801F833C);

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

INCLUDE_ASM(func_801F8404);

INCLUDE_ASM(func_801F8480);

/* nonmatching: timer D_80146875 counts up; at 0x80 it sets D_80146867 = 0x3C, the timer to 0x1E, D_801F9DD8 = 0, steps D_80146874, starts EMI_LoaderStreamInitSlot(0x260), then calls func_801F8FAC(0xE0, 0xBE, shade, 1) and func_801F8B10(0x4B0, 0x80). Candidate is 8 bytes short (first differing instruction: bnez at +0x28 targets +0x78 against +0x70): retail sets a0, a1 and a2 inside the branch and ends it with j, and sets only a1 on the other path. */
INCLUDE_ASM(func_801F84F4);

/* Counts D_80146875 down and, at zero, D_80146867; both zero steps D_80146874, else D_80146875 = 0x1E, then func_801F8B10 and func_801F8FAC. The pointer-local draft is 4 to 8 bytes short whichever branch order: retail ends the step branch with `j` and the 0x4B0 argument load in its delay slot, and falls into a second copy of that load from the else branch (first differing instruction +0x30: beqz targets +0x78 against +0x70). */
INCLUDE_ASM(func_801F8594);

MATCH void func_801F8664(void) {
    u8* state;

    if ((g_InputPressed & 0x40) || D_801F9DD8 != 0) {
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
        g_GameStateIndex = 2;
        state            = &D_80146874;
        (*state)++;
    }
    func_801F8B10(0x4B0, 0x80);
    func_801F8FAC(0xE0, 0xBE, 0x80, 1);
}

MATCH void func_801F87D0(void) {
    if (g_GameStateIndex != 2) {
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

INCLUDE_ASM(func_801F8EF0);

INCLUDE_ASM(func_801F8FAC);

INCLUDE_ASM(func_801F90BC);

INCLUDE_ASM(func_801F9160);

INCLUDE_ASM(func_801F91F0);

INCLUDE_ASM(func_801F938C);

INCLUDE_ASM(func_801F9490);

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

#include "overlays/scenario/Scene_SetPartyRyuTeepoRei.h"

MATCH void func_801F9720(void) {
}
