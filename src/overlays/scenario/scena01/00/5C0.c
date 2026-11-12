#include "scena01_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801F71C0);

INCLUDE_ASM(func_801F729C);

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
        func_801F7AE4();
    }
    func_801F7C54();
    g_Task->timer = (g_Task)->timer + 4;
    if (g_Task->timer == 0) {
        g_Task->timer       = 32;
        g_Task->header.mode = (g_Task)->header.mode + 1;
    }
}

MATCH void func_801F752C(void) {
    func_801F7678(0xFF);
    if ((g_FrameCount & 0x1) == 0) {
        func_801F7AE4();
    }
    func_801F7C54();
    if (--g_Task->timer == 0) {
        g_Task->timer = 252;
        g_Task->header.mode += 1;
    }
}

MATCH void func_801F75C8(void) {
    func_801F7678(g_Task->timer);
    func_801F7C54();
    g_Task->timer = (g_Task)->timer - 4;
    if (g_Task->timer == 0) {
        g_Task->header.mode = (g_Task)->header.mode + 1;
    }
}

MATCH void func_801F7644(void) {
    if (!(func_801F7C54() & BYTE_MASK)) {
        Actor_Clear();
    }
}

INCLUDE_ASM(func_801F7678);

#include "shared/Area_DrawSparkCell.h"

#include "shared/Area_ClearWorkColumn.h"

INCLUDE_ASM(func_801F7AE4);

INCLUDE_ASM(func_801F7C54);

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

INCLUDE_ASM(func_801F7DCC);

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
    func_801C1DF0(0);
    Game_RequestAreaChange(AREA_ID_CEDAR_WOODS_BEFORE_NUE, TO_COORD(87), TO_COORD(4), FACING_LEFT);
    *D_80144E90          = 0;
    g_ScriptVarsReq.word = 0;
    D_80146872           = 1;
}

INCLUDE_ASM(func_801F8050);

MATCH void func_801F8AA0(void) {
    SYS_DISPATCH_BYTE(D_801FE2A8, g_SceneState.state_04);
}

MATCH void func_801F8ADC(void) {
}

MATCH void func_801F8AE4(void) {
    switch (g_SceneState.step_05) {
        case 0:
            if (g_ScriptVars[0] == 1) {
                g_ScriptVars[1]      = 1;
                g_ScriptVars[2]      = 1;
                g_SceneState.step_05 = 1;
                func_8019FA28(0x9, 0x470000, 0x1D0000, 3);
            }
            break;
        case 1:
            g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
            func_801C601C(0);
            g_SceneState.step_05 = 2;
            break;
        case 2:
            if (g_ScriptVars[0] == 0x1E) {
                SYS_SetFlag(g_SceneFlags, 0);
                g_ScriptVars[0]       = 0;
                g_ScriptVars[1]       = 0;
                g_ScriptVars[2]       = 0;
                g_SceneState.step_05  = 0;
                g_SceneState.state_04 = 0;
                func_8019FA28(0xA, 0x2B0000, 0x200000, 3);
            }
            break;
    }
}

INCLUDE_ASM(func_801F8C0C);

INCLUDE_ASM(func_801F8F34);

MATCH void func_801F986C(void) {
}

INCLUDE_ASM(func_801F9874);

INCLUDE_ASM(func_801F9AA0);

MATCH void func_801FA244(void) {
}

INCLUDE_ASM(func_801FA24C);

INCLUDE_ASM(func_801FA844);

INCLUDE_ASM(func_801FB218);

INCLUDE_ASM(func_801FB5BC);

INCLUDE_ASM(func_801FBB1C);

INCLUDE_ASM(func_801FBF30);

INCLUDE_ASM(func_801FC488);

INCLUDE_ASM(func_801FC6B4);

MATCH void func_801FC890(void) {
}

INCLUDE_ASM(func_801FC898);

MATCH void func_801FCC24(void) {
    switch (g_SceneState.step_05) {
        case 0:
            SND_StopSequence(0, 0);
            SND_PlayBGM(0x1A, BGM_CUE_LEVEL_DEFAULT, BGM_CUE_SHAPE_DEFAULT);
            g_GameFlags |= 0x80;
            func_801BE1B0(0xB);
            g_SceneState.step_05 = 1;
            break;
        case 1:
            if (g_ScriptVars[0] != 2) {
                break;
            }
            Game_ClearScriptActive();
            g_ScriptVars[1]       = 0;
            g_ScriptVars[2]       = 0;
            g_SceneState.step_05  = 0x2D;
            g_SceneState.state_04 = 9;
            break;
    }
}

MATCH void func_801FCCF4(void) {
}

MATCH void func_801FCCFC(void) {
    u8* state;

    state = &D_80146875;
    switch (*state) {
        case 0:
            Message_StartAreaMessage(24);
            g_GameStateIndex = GAME_REQUEST_MESSAGE;
            *state           = 1;
            return;
        case 1:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                D_80146865 = 0;
                D_80146866 = 0;
                *state     = 0;
                D_80146874 = 0;
            }
            return;
    }
}

MATCH void func_801FCD9C(void) {
    u8* state;

    state = &D_80146875;
    switch (*state) {
        case 0:
            Message_StartAreaMessage(52);
            g_GameStateIndex = GAME_REQUEST_MESSAGE;
            *state           = 1;
            return;
        case 1:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                *state     = 0;
                D_80146874 = 0x6;
            }
            return;
    }
}

MATCH void func_801FCE30(void) {
    u8* state;

    state = &D_80146875;
    switch (*state) {
        case 0:
            Message_StartAreaMessage(52);
            g_GameStateIndex = GAME_REQUEST_MESSAGE;
            *state           = 1;
            return;
        case 1:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                *state     = 0;
                D_80146874 = 0;
            }
            return;
    }
}

INCLUDE_ASM(func_801FCEC0);

INCLUDE_ASM(func_801FD28C);

MATCH void func_801FD444(void* record) {
    D_801FE308[((Actor*)record)->callback_index](record, &D_80144E90);
}

MATCH void func_801FD484(void) {
}

MATCH void func_801FD48C(void) {
    if (SYS_TestFlag(g_SceneFlags, 20) == 0) {
        *g_ScriptVars = 0;
        Game_SetScriptActive();
        D_80146875 = 0;
        D_80146874 = 0x12;
        SYS_SetFlag(g_SceneFlags, 20U);
    }
}

MATCH void func_801FD4F0(void) {
    Game_SetScriptActive();
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_SceneState.step_05  = 0;
    g_SceneState.state_04 = 23;
}

MATCH void func_801FD534(void) {
    Game_SetScriptActive();
    g_SceneState.step_05  = 5;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_SceneState.state_04 = 23;
}

MATCH void func_801FD57C(void) {
    Game_SetScriptActive();
    g_SceneState.step_05  = 2;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_SceneState.state_04 = 23;
}

MATCH void func_801FD5C4(void) {
    Game_SetScriptActive();
    g_SceneState.step_05  = 2;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_SceneState.state_04 = 17;
}

MATCH void func_801FD60C(Actor* actor) {
    Game_SetScriptActive();
    g_ScriptVars[0]      = 10;
    g_ScriptVars[1]      = 0;
    g_ScriptVars[2]      = 0;
    actor->header.mode   = 4;
    actor->unk_7E        = 0;
    actor->unk_7B        = 0;
    actor->unk_77        = 10;
    g_Task->direction_08 = g_Game.members[0].facing ^ 4;
    func_8015BAC4(g_Task->direction_08);
    g_Task->option_flags |= ACTOR_OPT_ROUTE_LOCKED;
    g_SceneState.step_05  = 10;
    g_SceneState.state_04 = 13;
}

MATCH void func_801FD6CC(Actor* actor) {
    Game_SetScriptActive();
    actor->header.mode   = 4;
    actor->unk_7B        = 0;
    actor->unk_77        = 0xA;
    g_Task->direction_08 = g_Game.members[0].facing ^ 0x4;
    func_8015BAC4(g_Task->direction_08);
    g_Task->option_flags |= ACTOR_OPT_ROUTE_LOCKED;
    g_ScriptVars[0]       = 0;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.step_05  = 13;
    g_SceneState.state_04 = 13;
}

MATCH void func_801FD788(Actor* actor) {
    Game_SetScriptActive();
    actor->header.mode   = 4;
    actor->unk_7E        = 0;
    actor->unk_7B        = 0;
    actor->unk_77        = 11;
    g_Task->direction_08 = g_Game.members[0].facing ^ 4;
    func_8015BAC4(g_Task->direction_08);
    g_Task->option_flags |= ACTOR_OPT_ROUTE_LOCKED;
    g_SceneState.step_05  = 16;
    g_ScriptVars[0]       = 0;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.state_04 = 13;
}

MATCH void func_801FD84C(Actor* actor) {
    Game_SetScriptActive();
    actor->header.mode   = 4;
    actor->unk_7E        = 0;
    actor->unk_7B        = 0;
    actor->unk_77        = 0xB;
    g_Task->direction_08 = g_Game.members[0].facing ^ 0x4;
    func_8015BAC4(g_Task->direction_08);
    g_Task->option_flags |= ACTOR_OPT_ROUTE_LOCKED;
    g_SceneState.step_05  = 16;
    g_ScriptVars[3]       = 0;
    g_SceneState.state_04 = 13;
}

MATCH void func_801FD8F8(void) {
    g_ScriptVars[0] = 0x64;
}

MATCH void func_801FD90C(void) {
    g_ScriptVars[0] = 0x66;
}

MATCH void func_801FD920(void) {
    g_ScriptVars[0] = 0x67;
}

MATCH void func_801FD934(void) {
    g_ScriptVars[0] = 0x68;
}

MATCH void func_801FD948(void) {
    Game_SetScriptActive();
    g_SceneState.step_05  = 40;
    g_ScriptVars[0]       = 0;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.state_04 = 9;
}

MATCH void func_801FD9A0(void) {
    Game_SetScriptActive();
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_SceneState.step_05  = 0;
    g_SceneState.state_04 = 17;
}

MATCH void func_801FD9E4(void) {
    Game_SetScriptActive();
    g_SceneState.step_05  = 5;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_SceneState.state_04 = 17;
}

MATCH void func_801FDA2C(void) {
    Game_SetScriptActive();
    g_SceneState.step_05  = 0xF;
    g_SceneState.state_04 = 0xB;
}

MATCH s32 func_801FDA64(void) {
    return 0;
}

INCLUDE_ASM(func_801FDA6C);

MATCH s8 func_801FE03C(s32 x, s32 y) {
    SCENE_PROBE_POSITION(D_801FE350, 2, D_801FE35C);
}

MATCH s32 func_801FE0A4(void) {
    if (SYS_TestFlag(g_SceneFlags, 3) == 0 || SYS_TestFlag(g_SceneFlags, 4)) {
        return -1;
    }

    Game_SetScriptActive();
    g_SceneState.step_05  = 0;
    g_SceneState.state_04 = 5;
    return 1;
}

/* func_801FE10C */
MATCH void Scene_InitOpeningParty(void) {
    g_Characters[g_CharSlot[10]].unk_07 &= 0xFE;
    EMI_LoadPartyArchives(CHAR_ID_RYU_PAJAMAS, CHAR_ID_TEEPO, CHAR_ID_REI, 0);
    g_Game.party_size                        = 0;
    g_Characters[g_CharSlot[9]].character_id = CHAR_ID_RYU_PAJAMAS;
    Party_JoinMember(CHAR_ID_RYU_PAJAMAS);
}

/* func_801FE1B0 */
MATCH void Scene_SetPartyRyuTeepoRei(void) {
    g_Characters[g_CharSlot[0]].character_id = CHAR_ID_RYU_YOUNG;
    EMI_LoadPartyArchives(CHAR_ID_RYU_YOUNG, CHAR_ID_TEEPO, CHAR_ID_REI, 0);
    g_Game.party_size = 0;
    Party_JoinMember(CHAR_ID_RYU_YOUNG);
    Party_JoinMember(CHAR_ID_TEEPO);
    Party_JoinMember(CHAR_ID_REI);
}

/* func_801FE224 */
MATCH void Party_JoinRei(void) {
    Party_JoinMember(CHAR_ID_REI);
}

#include "overlays/scenario/Scene_RemoveRei.h"
