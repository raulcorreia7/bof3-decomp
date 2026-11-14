#include "scena16_00.h"
#include "area/map.h"

#define SCN_MODE_HANDLER_FIRST  5
#define SCN_STATE_HANDLER_FIRST 8

typedef void (*SceneEventFunc)(void* record, u32 state);

typedef struct SceneEventDispatch {
    Callback       prefix[13];
    SceneEventFunc handlers[3];
} SceneEventDispatch;

ASSERT_SIZE(SceneEventDispatch, 0x40);
ASSERT_OFFSET(SceneEventDispatch, handlers, 0x34);

typedef union SceneSlots {
    Callback           handlers[16];
    SceneEventDispatch event;
} SceneSlots;

ASSERT_SIZE(SceneSlots, 0x40);

/* 16 handlers at 0x801F8538. func_801F6C90 and func_801F7144 select from
 * entries 5 and 8; func_801F8358 calls entries 13-15 as (record, state). */
static SceneSlots D_801F8538 = {{
    func_801F6C90,
    (Callback)func_801F8358,
    (Callback)func_801F83A0,
    (Callback)func_801F83A8,
    0,
    func_801F6CCC,
    func_801F6D90,
    func_801F7144,
    func_801F7180,
    func_801F7188,
    func_801F7230,
    func_801F7790,
    func_801F7CC4,
    (Callback)func_801F8398,
    Scene_ClearParty,
    func_801F8530,
}};

MATCH void func_801F6C90(void) {
    s8 mode;

    mode = D_80146872;
    D_801F8538.handlers[SCN_MODE_HANDLER_FIRST + mode]();
}

MATCH void func_801F6CCC(void) {
    u16 flags;

    Scene_RunScenario(0u);
    g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
    Game_RequestAreaChange(AREA_ID_DAUNA_MINE_INTRO, TO_COORD(26), TO_COORD(8) + COORD_HALF, FACING_DOWN);
    g_SaveAreaId      = 4u;
    g_SaveEntryX      = 0x1A0000u;
    flags             = g_GameFlags;
    g_SaveEntryY      = 0x88000u;
    g_SaveEntryFacing = FACING_DOWN;
    g_Game.flags      = (flags | GAME_FLAG_MENU_LOCK | 0x200u);
    SND_RequestBGM(6u);

    while (!EMI_IsReady()) {
        SYS_ThreadWait(1u);
    }

    g_ScriptVarsReq.word = 0u;
    D_80146872           = 1;
}

/* Current area id (u16) and the frontend popup word cell, both fixed by the
 * shipped image layout.
 */

MATCH void func_801F6D90(void) {
    u16 area_id;

    area_id = g_GameAreaId;

    switch (area_id) {
        case AREA_ID_DAUNA_MINE_WORKER:
            func_801F6F30();
            LOBU(g_UiPopupRequest) = 1u;
            break;

        case AREA_ID_DAUNA_MINE_INTRO:
            func_801F6EB0();
            LOBU(g_UiPopupRequest) = 1u;
            break;

        case AREA_ID_TITLE_INTRO:
            func_801F6E30();
            LOBU(g_UiPopupRequest) = 0u;
            break;
    }

    D_80146872 = 2;
}

MATCH void func_801F6E30(void) {
    u32 state;

    g_AreaCameraAngle.vx = 256;
    g_AreaCameraAngle.vz = 0;
    g_AreaCameraAngle.vy = 0;
    SCENA16_D_8014932C   = 0x100;
    Party_HideBattlers();

    if (SYS_TestFlag(g_SceneFlags, 1) == 0) {
        state           = g_SceneFlags;
        g_AreaDrawFlags = 0u;
        SYS_SetFlag((void*)state, 1);
        g_SceneState.state_04 = 3;
    }
}

/* Flag byte at 0x80143F03, read through the plain u8 view: the volatile
 * SCENA16_D_80143F03 declaration would add a masking instruction here. */

MATCH void func_801F6EB0(void) {
    if (SYS_TestFlag(g_SceneFlags, 0) == 0) {
        g_AreaDrawFlags = 0u;
        SYS_SetFlag(g_SceneFlags, 0);
        Game_SetScriptActive();
        g_SceneState.state_04 = 2;
    }

    if (D_80143F03 == 2u) {
        g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
        Party_HideBattlers();
    }
}

MATCH void func_801F6F30(void) {
    u8   object_index;
    u16* base;

    if (SYS_TestFlag(g_SceneFlags, 2) == 0) {
        g_ScriptVarsReq.word = 0u;
        Area_AdvanceScroll(768u);
        Area_StartScrollRoute(0u);
        /* The cell is advanced through an unsigned view and read back signed
         * for x: the two views of g_AreaCameraAngle.vx are not interchangeable. */
        base          = (u16*)&g_AreaCameraAngle.vx;
        base[0]       = (base[0] + 0xAAu);
        object_index  = Actor_FindFreeSlot();
        D_1F800000[0] = object_index;

        if (object_index != GAME_NONE) {
            g_SpawnedActors[object_index].header.flags    = 1u;
            g_SpawnedActors[D_1F800000[0]].type           = 0x13u;
            g_SpawnedActors[D_1F800000[0]].camera_angle.x = ((s16)*base - 170);
            g_SpawnedActors[D_1F800000[0]].camera_angle.y = g_AreaCameraAngle.vy;
            g_SpawnedActors[D_1F800000[0]].camera_angle.z = g_AreaCameraAngle.vz;
            g_SpawnedActors[D_1F800000[0]].layer          = 0x40u;
        }

        Party_HideBattlers();
        SCENA16_D_80145EC4 = 0x330000u;
        SCENA16_D_80145EC8 = 0x400000u;
        SYS_SetFlag(g_SceneFlags, 2);
    } else if (SYS_TestFlag(g_SceneFlags, 10) == 0) {
        SYS_SetFlag(g_SceneFlags, 10);
        func_801BE1B0(0u);
        SCENA16_D_80149308 = 0x260000u;
        SCENA16_D_8014930C = 0x1B8000u;
    }
}

MATCH void func_801F7144(void) {
    s8 state;

    state = g_SceneState.state_04;
    D_801F8538.handlers[SCN_STATE_HANDLER_FIRST + state]();
}

MATCH void func_801F7180(void) {
}

MATCH void func_801F7188(void) {
    u8* sel_ptr;
    u32 selection;
    u32 selection_offset;

    if (WINDOW_EFFECT_IDLE()) {
        SCENA16_D_80143C30 = 0u;
        g_AreaDrawFlags    = 0u;
        func_801F845C();
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 19));
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 20));
        sel_ptr   = &g_SndBGMId;
        selection = *sel_ptr;

        if (selection != 0xFFu) {
            selection_offset = selection << 2;
            /* The const byte view: dropping the cast moves this call's loads. */
            SND_StopSequence(((const u8*)(g_SelectionCues))[selection_offset], ((const u8*)(g_SelectionCues))[selection_offset + 1u]);
            *sel_ptr = 0xFFu;
        }

        SsSetMVol(0x7F, 0x7F);
        SYS_ThreadExit();
    }
}

/* Boundary: the reviewed range stops at 0x801F743C, but this routine runs to
 * the shared epilogue at 0x801F777C (0x801F7230..0x801F7790). Its 12-entry
 * switch table at 0x801F6C04 dispatches cases 5-11 into the auto-named
 * func_801F743C block of the `main` segment. */
MATCH void func_801F7230(void) {
    switch (g_SceneState.step_05) {
        case 0: {
            u8* next;
            u8  step;
            u16 flags;

            if (WINDOW_EFFECT_IDLE()) {
                UI_SetMode(UI_MODE_FADE_IN);
                SsSetMVol(0, 0);
                SND_PlayBGM(6u, 0x50, 8);
                next  = &g_SceneState.step_05;
                step  = *next;
                flags = SCENA16_D_80146258;
                step++;
                SCENA16_D_80146258 = flags | 0x80u;
                *next              = step;
            }
            break;
        }

        case 1:
            UI_DrawText(122, 100, 0, 255u, (u8*)(SCENA16_VRAM_BASE + SCENA16_D_80010020));
            if (WINDOW_EFFECT_IDLE()) {
                g_SceneState.timer_06 = 0u;
                g_SceneState.step_05  = (g_SceneState.step_05 + 1u);
            }
            break;

        case 2: {
            u16* timer = &g_SceneState.timer_06;

            *timer = (*timer + 1u);
            SsSetMVol((s16)*timer, (s16)*timer);
            UI_DrawText(122, 100, 0, 255u, (u8*)(SCENA16_VRAM_BASE + SCENA16_D_80010020));
            if (*timer == 127u) {
                UI_SetMode(UI_MODE_FADE_OUT);
                *timer               = 0u;
                g_SceneState.step_05 = (g_SceneState.step_05 + 1u);
            }
            break;
        }

        case 3:
            if (WINDOW_EFFECT_BUSY()) {
                UI_DrawText(122, 100, 0, 255u, (u8*)(SCENA16_VRAM_BASE + SCENA16_D_80010020));
                break;
            }
            g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
            Game_SetScriptActive();
            Party_HideBattlers();
            UI_SetMode(UI_MODE_FADE_IN);
            g_ScriptVars[3]       = 1u;
            g_SceneState.timer_06 = 0u;
            g_SceneState.step_05  = (g_SceneState.step_05 + 1u);
            break;

        case 4: {
            u8* next;

            if (g_ScriptVars[3] == 0x54u) {
                UI_SetMode(UI_MODE_FADE_OUT);
                next  = &g_SceneState.step_05;
                *next = (*next + 1u);
            }
            break;
        }

        case 5: {
            u8* next;

            if (WINDOW_EFFECT_IDLE()) {
                g_AreaDrawFlags = 0u;
                UI_SetMode(UI_MODE_FADE_IN);
                next  = &g_SceneState.step_05;
                *next = (*next + 1u);
            }
            break;
        }

        case 6:
            UI_DrawText(80, 80, 0, 255u, (u8*)(SCENA16_VRAM_BASE + SCENA16_D_80010022));
            if (WINDOW_EFFECT_IDLE()) {
                g_SceneState.timer_06 = 0x7Fu;
                g_SceneState.step_05  = (g_SceneState.step_05 + 1u);
            }
            break;

        case 7: {
            u16* timer = &g_SceneState.timer_06;

            UI_DrawText(80, 80, 0, 255u, (u8*)(SCENA16_VRAM_BASE + SCENA16_D_80010022));
            *timer = (*timer - 1u);
            if (*timer == 0u) {
                UI_SetMode(UI_MODE_FADE_OUT);
                g_SceneState.step_05 = (g_SceneState.step_05 + 1u);
            }
            break;
        }

        case 8: {
            u8* next;

            if (WINDOW_EFFECT_BUSY()) {
                UI_DrawText(80, 80, 0, 255u, (u8*)(SCENA16_VRAM_BASE + SCENA16_D_80010022));
                break;
            }
            Game_RequestAreaChange(AREA_ID_DAUNA_MINE_INTRO, TO_COORD(68), TO_COORD(8), FACING_DOWN);
            next  = &g_SceneState.step_05;
            *next = (*next + 1u);
            break;
        }

        case 9: {
            u8* next;
            u8  step;

            if (D_80143F03 == 2u) {
                next            = &g_SceneState.step_05;
                step            = *next;
                g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
                *next           = (step + 1u);
            }
            break;
        }

        case 10: {
            u8* next;
            u8  object_index;

            if (g_ScriptVars[2] != 0x23u) {
                break;
            }

            object_index  = Actor_FindFreeSlot();
            D_1F800000[0] = object_index;

            if (object_index != GAME_NONE) {
                g_SpawnedActors[object_index].header.flags    = 1u;
                g_SpawnedActors[D_1F800000[0]].type           = 0x13u;
                g_SpawnedActors[D_1F800000[0]].camera_angle.x = (g_AreaCameraAngle.vx + 384);
                g_SpawnedActors[D_1F800000[0]].camera_angle.y = g_AreaCameraAngle.vy;
                g_SpawnedActors[D_1F800000[0]].camera_angle.z = g_AreaCameraAngle.vz;
                g_SpawnedActors[D_1F800000[0]].layer          = 0x60u;
            }

            next  = &g_SceneState.step_05;
            *next = (*next + 1u);
            break;
        }

        case 11:
            if (g_ScriptVars[3] == 0x60u) {
                Game_RequestAreaChange(AREA_ID_TITLE_INTRO, TO_COORD(7), TO_COORD(20), FACING_UP_LEFT);
                SCENA16_D_80143F1D = 0xFFu;
                SND_FadeOutBGM(6u, 0x50, 0x40);
                g_ScriptVars[2]       = 0u;
                g_SceneState.state_04 = 3;
                g_SceneState.step_05  = 0u;
            }
            break;
    }
}

MATCH void func_801F7790(void) {
    u8* state;
    u8  object_index;

    switch (g_SceneState.step_05) {
        case 0:
            if (WINDOW_EFFECT_IDLE()) {
                UI_SetMode(UI_MODE_FADE_IN);
                state  = &g_SceneState.step_05;
                *state = (*state + 1u);
            }
            break;

        case 1:
            UI_DrawText(80, 80, 0, 255u, (u8*)(SCENA16_VRAM_BASE + SCENA16_D_80010004));
            if (WINDOW_EFFECT_IDLE()) {
                g_SceneState.timer_06 = 0x7Fu;
                g_SceneState.step_05  = (g_SceneState.step_05 + 1u);
            }
            break;

        case 2: {
            u16* timer;
            UI_DrawText(80, 80, 0, 255u, (u8*)(SCENA16_VRAM_BASE + SCENA16_D_80010004));
            timer = &g_SceneState.timer_06;
            if (--*timer == 0u) {
                UI_SetMode(UI_MODE_FADE_OUT);
                g_SceneState.step_05 = (g_SceneState.step_05 + 1u);
            }
            break;
        }

        case 3:
            if (WINDOW_EFFECT_BUSY()) {
                UI_DrawText(80, 80, 0, 255u, (u8*)(SCENA16_VRAM_BASE + SCENA16_D_80010004));
                break;
            }

            UI_SetMode(UI_MODE_FADE_IN);
            g_ScriptVars[2] = 0x30u;
            g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
            object_index    = Actor_FindFreeSlot();
            D_1F800000[0]   = object_index;

            if (object_index != GAME_NONE) {
                g_SpawnedActors[object_index].header.flags    = 1u;
                g_SpawnedActors[D_1F800000[0]].type           = 0x13u;
                g_SpawnedActors[D_1F800000[0]].camera_angle.x = (g_AreaCameraAngle.vx + 448);
                g_SpawnedActors[D_1F800000[0]].camera_angle.y = g_AreaCameraAngle.vy;
                g_SpawnedActors[D_1F800000[0]].camera_angle.z = g_AreaCameraAngle.vz;
                g_SpawnedActors[D_1F800000[0]].layer          = 0xFFu;
            }

            state  = &g_SceneState.step_05;
            *state = (*state + 1u);
            break;

        case 4:
            if (WINDOW_EFFECT_IDLE()) {
                g_SceneState.timer_06 = 0u;
                g_SceneState.step_05  = (g_SceneState.step_05 + 1u);
            }
            break;

        case 5: {
            u16* timer;
            UI_DrawText(72, 80, 0, 255u, (u8*)(SCENA16_VRAM_BASE + SCENA16_D_80010006));
            timer = &g_SceneState.timer_06;
            if (++*timer == 32u) {
                func_801F845C();
                *timer               = 0x7Fu;
                g_SceneState.step_05 = (g_SceneState.step_05 + 1u);
                break;
            }
            GFX_CopyPaletteCapped(((u8)*timer));
            break;
        }

        case 6: {
            u16* timer;
            UI_DrawText(72, 80, 0, 255u, (u8*)(SCENA16_VRAM_BASE + SCENA16_D_80010006));
            timer = &g_SceneState.timer_06;
            if (--*timer == 0u) {
                g_SceneState.step_05 = (g_SceneState.step_05 + 1u);
                *timer               = 0x20u;
            }
            break;
        }

        case 7: {
            u16* timer;
            timer = &g_SceneState.timer_06;
            if (--*timer != 0u) {
                UI_DrawText(72, 80, 0, 255u, (u8*)(SCENA16_VRAM_BASE + SCENA16_D_80010006));
                GFX_CopyPaletteCapped((u8)*timer);
                break;
            }
            func_801F845C();
            *timer               = 0x1Eu;
            g_SceneState.step_05 = (g_SceneState.step_05 + 1u);
            break;
        }

        case 8: {
            u16* timer;
            timer = &g_SceneState.timer_06;
            if (--*timer == 0u) {
                g_SceneState.step_05 = (g_SceneState.step_05 + 1u);
            }
            break;
        }

        case 9:
            SND_PlayBGM(2u, 100, 0x20);
            Game_RequestAreaChange(AREA_ID_DAUNA_MINE_WORKER, TO_COORD(52), TO_COORD(67), FACING_RIGHT);
            g_SceneState.state_04 = 4;
            g_SceneState.step_05  = 0u;
            break;
    }

    if (SCENA16_D_80149314 == 0x4400u) {
        s32* pos;
        s32* other;
        s32* plane;
        /* FAKE: the mode constant ties with the pointer at v0/v1. */
        FAKE_REG(u32, mode, "v1");
        mode               = 0x6200u;
        SCENA16_D_80149314 = mode;
        pos                = &SCENA16_D_8014930C;
        other              = &g_AreaFocusY;
        plane              = &SCENA16_D_80143F80;
        SCENA16_D_80149322 = (SCENA16_D_80149322 - 0x1Eu);
        *pos += -0x1E0000;
        *other += -0x1E0000;
        *plane += -0x1E0000;
        Area_RefreshCellGrid();
    }
}

/* local: this consumer reads the cell as u8; the shared declaration is u32. */

MATCH void func_801F7CC4(void) {
    u8* state;
    u8  object_index;

    switch (g_SceneState.step_05) {
        case 0:
            if (WINDOW_EFFECT_BUSY()) {
                return;
            }
            Message_StartAreaMessage(1u);
            {
                /* Case-local pointer: keeps this increment in its own register pair,
                 * so cases 0 and 2 cross-jump into one shared tail. */
                u8* next_state;

                next_state  = &g_SceneState.step_05;
                *next_state = (*next_state + 1u);
            }
            g_GameStateIndex = GAME_REQUEST_MESSAGE;
            break;

        case 1:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                return;
            }
            state  = &g_SceneState.step_05;
            *state = (*state + 1u);
            break;

        case 2:
            if (g_ScriptVars[0] != 3u) {
                return;
            }
            Message_StartAreaMessage(2u);
            {
                /* Same case-local shape as case 0; the shared tail follows. */
                u8* next_state;

                next_state  = &g_SceneState.step_05;
                *next_state = (*next_state + 1u);
            }
            g_GameStateIndex = GAME_REQUEST_MESSAGE;
            break;

        case 3:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE && g_ScriptVars[0] == 4u) {
                g_SceneState.timer_06 = 0x130u;
                g_SceneState.step_05  = (g_SceneState.step_05 + 1u);
            }
            break;

        case 4: {
            u16* progress;
            u16* timer;

            progress  = (u16*)D_1F800000;
            *progress = (0x130u - g_SceneState.timer_06);
            if (*progress < 191u) {
                UI_DrawText(72, 80, 0, 255u, (u8*)(SCENA16_VRAM_BASE + SCENA16_D_80010006));
                if (*progress < 32u) {
                    GFX_CopyPaletteCapped((*progress & BYTE_MASK));
                } else if (*progress == 32u) {
                    func_801F845C();
                } else if (*progress > 159u) {
                    u16 inverted;

                    inverted = (0xBFu - *progress);
                    GFX_CopyPaletteCapped((inverted & BYTE_MASK));
                }
            } else if (*progress == 191u) {
                func_801F845C();
            }

            timer = &g_SceneState.timer_06;
            if (*timer == 0u) {
                g_SceneState.step_05 = (g_SceneState.step_05 + 1u);
                break;
            }

            *timer             = (*timer - 1u);
            SCENA16_D_8014932C = ((((0x130u - *timer)) * 0x57943u) >> 16);
            return;
        }

        case 5:
            if (g_ScriptVars[0] != 5u) {
                return;
            }
            object_index  = Actor_FindFreeSlot();
            D_1F800000[0] = object_index;
            if (object_index != GAME_NONE) {
                g_SpawnedActors[object_index].header.flags    = 1u;
                g_SpawnedActors[D_1F800000[0]].type           = 0x13u;
                g_SpawnedActors[D_1F800000[0]].camera_angle.x = -842;
                g_SpawnedActors[D_1F800000[0]].camera_angle.y = g_AreaCameraAngle.vy;
                g_SpawnedActors[D_1F800000[0]].camera_angle.z = g_AreaCameraAngle.vz;
                g_SpawnedActors[D_1F800000[0]].layer          = 0x60u;
            }
            state  = &g_SceneState.step_05;
            *state = (*state + 1u);
            break;

        case 6:
            if (g_ScriptVars[0] != 8u) {
                break;
            }
            object_index  = Actor_FindFreeSlot();
            D_1F800000[0] = object_index;
            if (object_index != GAME_NONE) {
                g_SpawnedActors[object_index].header.flags    = 1u;
                g_SpawnedActors[D_1F800000[0]].type           = 0x13u;
                g_SpawnedActors[D_1F800000[0]].camera_angle.x = -684;
                g_SpawnedActors[D_1F800000[0]].camera_angle.y = g_AreaCameraAngle.vy;
                g_SpawnedActors[D_1F800000[0]].camera_angle.z = g_AreaCameraAngle.vz;
                g_SpawnedActors[D_1F800000[0]].layer          = 0x20u;
            }
            g_SceneState.timer_06 = 0x200u;
            g_SceneState.step_05  = (g_SceneState.step_05 + 1u);
            break;

        case 7: {
            u16* timer;

            timer = &g_SceneState.timer_06;
            if (*timer == 0u) {
                g_SceneState.step_05 = (g_SceneState.step_05 + 1u);
                break;
            }

            SCENA16_D_8014932C = ((*timer * 0xDu) >> 2);
            (*timer)--;
            return;
        }

        case 8:
            if (g_ScriptVars[0] == 0x0Bu) {
                UI_SetMode(UI_MODE_FADE_OUT);
                g_SceneState.timer_06 = 0u;
                g_SceneState.step_05  = (g_SceneState.step_05 + 1u);
            }
            break;

        case 9:
            if (WINDOW_EFFECT_BUSY()) {
                return;
            }
            g_AreaDrawFlags = 0u;
            UI_SetMode(UI_MODE_FADE_IN);
            SND_FadeOutBGM(2u, 0x6E, 0x20);
            state  = &g_SceneState.step_05;
            *state = (*state + 1u);
            break;

        case 10:
            UI_DrawText(70, 100, 0, 255u, (u8*)(SCENA16_VRAM_BASE + SCENA16_D_80010008));
            if (WINDOW_EFFECT_IDLE()) {
                g_SceneState.timer_06 = 0x7Fu;
                g_SceneState.step_05  = (g_SceneState.step_05 + 1u);
            }
            break;

        case 11: {
            u16* timer;

            UI_DrawText(70, 100, 0, 255u, (u8*)(SCENA16_VRAM_BASE + SCENA16_D_80010008));
            timer  = &g_SceneState.timer_06;
            *timer = (*timer - 1u);
            if (*timer != 0u) {
                return;
            }
            UI_SetMode(UI_MODE_FADE_OUT);
            g_SceneState.step_05 = (g_SceneState.step_05 + 1u);
            break;
        }

        case 12:
            if (WINDOW_EFFECT_IDLE()) {
                g_SceneState.state_04 = 1;
                g_SceneState.step_05  = 0u;
            } else {
                UI_DrawText(70, 100, 0, 255u, (u8*)(SCENA16_VRAM_BASE + SCENA16_D_80010008));
            }
            break;
    }
}

MATCH void func_801F8358(void* record) {
    u8 callback_index;

    callback_index = ((Actor*)record)->callback_index;
    D_801F8538.event.handlers[callback_index](record, g_SceneFlags);
}

MATCH s32 func_801F8398(void) {
    return 0;
}

MATCH s32 func_801F83A0(void) {
    return 0;
}

MATCH s32 func_801F83A8(void) {
    return 0;
}

#include "overlays/scenario/GFX_CopyPaletteCapped.h"

MATCH void func_801F845C(void) {
    s32 i;

    i = 0;
    do {
        g_GraphicsPaletteDst[i] = SCENA16_PALETTE_SRC[i];
        i++;
    } while (i < 16);
    SCENA16_D_80145988 = (SCENA16_D_80145988 + 1u);
}

#include "overlays/scenario/Scene_ClearParty.h"

MATCH void func_801F8530(void) {
}
