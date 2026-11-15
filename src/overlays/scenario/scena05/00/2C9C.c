#include "scena05_00.h"
#include "area/map.h"
#include "overlays/area/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F989C(void) {
}

INCLUDE_ASM(func_801F98A4);

#ifdef NON_MATCHING
NON_MATCHING void func_801FB66C(void) {
    u8*  mode;
    u16* timer;

    switch (g_SceneState.step_05) {
        case 0:
            if ((g_UiWindowChannel & 2) == 0) {
                break;
            }
            if (g_ScriptVars[0] == 1) {
                g_ScriptVars[0] = 0;
                Message_StartAreaMessage(0x22);
                g_GameStateIndex     = GAME_REQUEST_MESSAGE;
                g_SceneState.step_05 = 1;
            } else {
                g_ScriptVars[0] = 0;
                Message_StartAreaMessage(0x20);
                g_GameStateIndex     = GAME_REQUEST_MESSAGE;
                g_SceneState.step_05 = 2;
            }
            break;
        case 1:
            mode = &g_GameStateIndex;
            if (*mode == 2) {
                break;
            }
            Message_StartAreaMessage(0x20);
            *mode                = 2;
            g_SceneState.step_05 = 2;
            break;
        case 2:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            if (g_ScriptVars[0] == 3) {
                g_SceneState.step_05 = 6;
            } else {
                g_SceneState.step_05 = 5;
            }
            break;
        case 5:
            Game_ClearScriptActive();
            g_ScriptVars[0] = 0;
            Scene_ClearScriptState(&g_SceneState.step_05);
            break;
        case 6:
            g_ScriptVars[0]      = 5;
            g_SceneState.step_05 = 7;
            break;
        case 7:
            if (g_ScriptVars[0] != 6) {
                break;
            }
            g_ScriptVars[0]      = 0;
            g_SceneState.step_05 = 8;
            SYS_SetFlag(g_SceneFlags, 0x28);
            switch (g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK) {
                case 1:
                    Game_RequestAreaChange(0x51, TO_COORD(53), TO_COORD(7), 0x81);
                    break;
                case 2:
                    Game_RequestAreaChange(0x51, TO_COORD(53), TO_COORD(7), 0x80);
                    break;
            }
            break;
        case 8:
            SND_StopSequence(0, 0);
            SND_PlayCue(0x208);
            g_SndVoiceTargetVolume[16] = 0x7F;
            g_SndVoiceVolume[16]       = 0;
            g_SceneState.step_05       = 9;
            break;
        case 9:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            g_SceneState.step_05 = 10;
            break;
        case 10:
            if (g_ScriptVars[0] != 5) {
                break;
            }
            g_SceneState.step_05 = 11;
            D_80146876           = 0;
            break;
        case 11:
            timer = &D_80146876;
            (*timer)++;
            if (*timer >= 200) {
                SND_PlayCue(0x209);
                *timer               = 0;
                g_SceneState.step_05 = 12;
            }
            func_8015D104(0x10, 4);
            SND_StartVolumeSweep(0x10);
            if ((s8)g_SndVoiceTargetVolume[16] < 9) {
                SND_PlayCue(0x209);
                *timer               = 0;
                g_SceneState.step_05 = 12;
            }
            break;
        case 12:
            if (g_ScriptVars[0] != 6) {
                break;
            }
            SND_PlayBGM(0x4E, 0x64, 8);
            g_SceneState.step_05 = 15;
            break;
        case 15:
            if (g_ScriptVars[0] != 0xF) {
                break;
            }
            g_SceneState.step_05 = 16;
            SYS_SetFlag(g_SceneFlags, 0x29);
            switch (g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK) {
                case 1:
                    Game_RequestAreaChange(0x51, TO_COORD(53), TO_COORD(7), 0x83);
                    g_GamePrevSelection = 0xFF;
                    break;
                case 2:
                    Game_RequestAreaChange(0x51, TO_COORD(53), TO_COORD(7), 0x82);
                    g_GamePrevSelection = 0xFF;
                    break;
            }
            break;
        case 16:
            SND_PlayCue(0x208);
            g_SceneState.step_05 = 21;
            break;
        case 21:
            if (g_ScriptVars[0] != 0x11) {
                break;
            }
            g_SceneState.step_05 = 22;
            SYS_SetFlag(g_SceneFlags, 0x2A);
            Game_RequestAreaChange(0x51, TO_COORD(90), TO_COORD(6), 0x84);
            g_GamePrevSelection = 0xFF;
            break;
        case 22:
            if (g_ScriptVars[0] != 0x10) {
                break;
            }
            g_SceneState.step_05 = 24;
            D_80146866           = 2;
            switch (g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK) {
                case 1:
                    Game_RequestAreaChange(0x51, TO_COORD(197), TO_COORD(14), 0x86);
                    g_GamePrevSelection = 0xFF;
                    break;
                case 2:
                    Game_RequestAreaChange(0x51, TO_COORD(197), TO_COORD(14), 0x85);
                    g_GamePrevSelection = 0xFF;
                    break;
            }
            break;
        case 24:
            if (g_ScriptVars[0] != 6) {
                break;
            }
            SND_PlayCue(0x209);
            Battle_StartScripted(0x15);
            g_SceneState.step_05 = 25;
            break;
        case 25:
            if (g_ScriptVars[0] != 0xA) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 0x3C);
            g_SceneState.step_05 = 26;
            switch (g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK) {
                case 1:
                    func_801BE1B0(8);
                    break;
                case 2:
                    func_801BE1B0(7);
                    break;
            }
            break;
        case 26:
            if (g_ScriptVars[0] != 0xE) {
                break;
            }
            g_SceneState.step_05 = 27;
            switch (g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK) {
                case 1:
                    Game_RequestAreaChange(0x51, TO_COORD(52), TO_COORD(9), AREA_ENTRY_MAP_LOADING | 0x08 | FACING_UP_RIGHT);
                    g_GamePrevSelection = 0x4E;
                    break;
                case 2:
                    Game_RequestAreaChange(0x51, TO_COORD(52), TO_COORD(9), AREA_ENTRY_MAP_LOADING | 0x08 | FACING_UP);
                    g_GamePrevSelection = 0x4E;
                    break;
            }
            break;
        case 27:
            if (g_ScriptVars[0] != 0x15) {
                break;
            }
            g_SceneState.step_05 = 28;
            Game_RequestAreaChange(0x4E, TO_COORD(40), TO_COORD(173), 0x88);
            g_GamePrevSelection = 0x4F;
            break;
        case 28:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            Area_StartScrollRoute(0);
            g_SceneState.step_05 = 29;
            SYS_SetFlag(g_SceneFlags, 0x2C);
            break;
        case 29:
            if (g_ScriptVars[0] != 0xA) {
                break;
            }
            g_SceneState.step_05 = 30;
            SYS_SetFlag(g_SceneFlags, 0x2B);
            switch (g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK) {
                case 1:
                    Game_RequestAreaChange(0x51, TO_COORD(52), TO_COORD(7), AREA_ENTRY_MAP_LOADING | 0x08 | FACING_DOWN_RIGHT);
                    break;
                case 2:
                    Game_RequestAreaChange(0x51, TO_COORD(52), TO_COORD(7), AREA_ENTRY_MAP_LOADING | 0x08 | FACING_RIGHT);
                    break;
            }
            break;
        case 30:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            Game_ClearScriptActive();
            Scene_ClearScriptState(&g_SceneState.step_05);
            break;
    }
}
#else
INCLUDE_ASM(func_801FB66C);
#endif

#ifdef NON_MATCHING
NON_MATCHING void func_801FBDBC(void) {
    switch (g_SceneState.step_05) {
        case 0:
            if ((g_UiWindowChannel & 2) == 0) {
                break;
            }
            if (g_ScriptVars[0] == 1) {
                g_SceneState.step_05 = 1;
            } else {
                Game_ClearScriptActive();
                g_ScriptVars[0] = 0;
                Scene_ClearScriptState(&g_SceneState.step_05);
            }
            break;
        case 1:
            g_ScriptVars[0]      = 2;
            g_SceneState.step_05 = 2;
            break;
        case 2:
            if (g_ScriptVars[0] != 3) {
                break;
            }
            g_ScriptVars[0]      = 0;
            g_SceneState.step_05 = 3;
            SYS_SetFlag(g_SceneFlags, 0x2D);
            Game_RequestAreaChange(0x50, TO_COORD(32), TO_COORD(10), AREA_ENTRY_MAP_LOADING | 0x08 | FACING_DOWN_LEFT);
            g_GamePrevSelection = 0x4F;
            break;
        case 3:
            if (g_ScriptVars[0] != 7) {
                break;
            }
            g_SceneState.step_05 = 4;
            SYS_SetFlag(g_SceneFlags, 0x2E);
            g_GameFlags |= GAME_FLAG_SCROLL_LOCK;
            SND_PlayCue(0x208);
            switch (g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK) {
                case 1:
                    Game_RequestAreaChange(0x50, TO_COORD(129), TO_COORD(7), 0x85);
                    g_GamePrevSelection = 0xFF;
                    break;
                case 2:
                    Game_RequestAreaChange(0x50, TO_COORD(129), TO_COORD(7), 0x84);
                    g_GamePrevSelection = 0xFF;
                    break;
            }
            break;
        case 4:
            if (g_ScriptVars[0] != 2) {
                break;
            }
            UI_SetMode(0xD);
            g_SceneState.step_05 = 5;
            break;
        case 5:
            if (g_UiWindowEffectBusy != 0) {
                break;
            }
            g_AreaDrawFlags      = 0;
            g_SceneState.step_05 = 6;
            break;
        case 6:
            switch (g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK) {
                case 1:
                    func_801C1E3C(0);
                    break;
                case 2:
                    func_801C1E3C(1);
                    func_801C1E3C(3);
                    break;
            }
            D_80146866           = 1;
            g_SceneState.step_05 = 7;
            Game_RequestAreaChange(0x50, TO_COORD(198), TO_COORD(15) + COORD_HALF, 0x82);
            g_GamePrevSelection = 0xFF;
            break;
        case 7:
            g_AreaDrawFlags      = 0x1F;
            g_SceneState.step_05 = 8;
            break;
        case 8:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            Area_StartScrollRoute(0);
            g_SceneState.step_05 = 9;
            break;
        case 9:
            if (g_ScriptVars[0] != 7) {
                break;
            }
            SND_PlayCue(0x209);
            SND_PlayBGM(0x66, 0x64, 8);
            g_SceneState.step_05 = 10;
            break;
        case 10:
            if (g_ScriptVars[0] != 0xB) {
                break;
            }
            func_801BFE34(g_Game.members[0].pos.x.fixed, g_Game.members[0].pos.y.fixed, 0x16);
            Battle_StartScripted(0x16);
            g_SceneState.step_05 = 11;
            break;
        case 11:
            if (g_ScriptVars[0] != 0xC) {
                break;
            }
            func_801BE1B0(3);
            SND_PlayBGM(0x6A, 0x64, 0x10);
            g_SceneState.step_05 = 12;
            break;
        case 12:
            if (g_ScriptVars[0] != 0x14) {
                break;
            }
            g_SceneState.step_05 = 13;
            SYS_SetFlag(g_SceneFlags, 0x2F);
            UI_SetMode(0xD);
            break;
        case 13:
            if (g_UiWindowEffectBusy != 0) {
                break;
            }
            g_AreaDrawFlags      = 0;
            g_SceneState.step_05 = 14;
            break;
        case 14:
            switch (g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK) {
                case 1:
                    g_SceneState.step_05 = 15;
                    Scene_RunScenario(1);
                    Scene_RunScenario(2);
                    Game_RequestAreaChange(0x50, TO_COORD(129), TO_COORD(11), 0x81);
                    break;
                case 2:
                    g_SceneState.step_05 = 15;
                    Scene_RunScenario(1);
                    Scene_RunScenario(3);
                    Game_RequestAreaChange(0x50, TO_COORD(129), TO_COORD(11), 0x80);
                    break;
            }
            break;
        case 15:
            g_AreaDrawFlags      = 0x1F;
            g_SceneState.step_05 = 16;
            break;
        case 16:
            if (g_ScriptVars[0] != 8) {
                break;
            }
            func_801C16B8();
            g_GameFlags ^= GAME_FLAG_SCROLL_LOCK;
            SYS_SetFlag(g_SceneFlags, 0x3D);
            Game_ClearScriptActive();
            Scene_ClearScriptState(&g_SceneState.step_05);
            break;
    }
}
#else
INCLUDE_ASM(func_801FBDBC);
#endif

MATCH void func_801FC2F0(void) {
    u8* state;

    state = &D_80146875;
    switch (*state) {
        case 0:
            Message_StartAreaMessage(132);
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

#ifdef NON_MATCHING
NON_MATCHING void func_801FC380(void) {
    switch (g_SceneState.step_05) {
        case 0:
            func_801FC8A0(0x91);
            g_SceneState.step_05 = 1;
            break;
        case 1:
            g_SceneState.step_05 = 2;
            switch (g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK) {
                case 1:
                    Game_RequestAreaChange(AREA_ID_CONTEST_OUTER, TO_COORD(37), TO_COORD(174), AREA_ENTRY_MAP_LOADING | 0x08 | FACING_UP_RIGHT);
                    break;
                case 2:
                    Game_RequestAreaChange(AREA_ID_CONTEST_OUTER, TO_COORD(37), TO_COORD(174), AREA_ENTRY_MAP_LOADING | 0x08 | FACING_UP);
                    break;
            }
            break;
        case 2:
            if (g_ScriptVars[0] == 0x1) {
                g_SceneState.step_05 = 3;
                SYS_SetFlag(g_SceneFlags, 0x30);
                g_GameFlags |= GAME_FLAG_SCROLL_LOCK;
                switch (g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK) {
                    case 1:
                        Game_RequestAreaChange(AREA_ID_CONTEST_OUTER, TO_COORD(39), TO_COORD(173), AREA_ENTRY_MAP_LOADING | 0x08 | FACING_DOWN_RIGHT);
                        break;
                    case 2:
                        Game_RequestAreaChange(AREA_ID_CONTEST_OUTER, TO_COORD(39), TO_COORD(173), AREA_ENTRY_MAP_LOADING | 0x08 | FACING_RIGHT);
                        break;
                }
            }
            break;
        case 3:
            if (g_ScriptVars[0] == 0xA) {
                g_SceneState.step_05 = 4;
                SYS_SetFlag(g_SceneFlags, 0x31);
                g_GameFlags ^= GAME_FLAG_SCROLL_LOCK;
                switch (g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK) {
                    case 1:
                        Game_RequestAreaChange(AREA_ID_CONTEST_OUTER, TO_COORD(34), TO_COORD(114), AREA_ENTRY_MAP_LOADING | 0x08 | FACING_DOWN_LEFT);
                        break;
                    case 2:
                        Game_RequestAreaChange(AREA_ID_CONTEST_OUTER, TO_COORD(34), TO_COORD(114), AREA_ENTRY_MAP_LOADING | 0x08 | FACING_DOWN);
                        break;
                }
            }
            break;
        case 4:
            if (g_ScriptVars[0] == 0x4) {
                g_SceneState.step_05 = 5;
                g_Characters[CHAR_INDEX_NINA].unk_07 |= 1;
                g_Characters[CHAR_INDEX_MOMO].unk_07 |= 1;
                g_Characters[CHAR_INDEX_PECO].unk_07 |= 1;
                switch (g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK) {
                    case 1:
                        Scene_RunScenario(3);
                        break;
                    case 2:
                        Scene_RunScenario(2);
                        break;
                }
            }
            break;
        case 5:
            if (g_GameStateIndex == 0) {
                g_ScriptVars[0]      = 0x5;
                g_SceneState.step_05 = 6;
            }
            break;
        case 6:
            if (g_ScriptVars[0] == 0x5) {
                SYS_SetFlag(g_SceneFlags, 0x32);
                Game_ClearScriptActive();
                Scene_ClearScriptState(&g_SceneState.step_05);
            }
            break;
    }
}
#else
INCLUDE_ASM(func_801FC380);
#endif

MATCH void func_801FC6A8(void) {
    u8* state;
    u8  next;

    state = &g_SceneState.step_05;
    switch (*state) {
        case 0:
            if (!(g_UiWindowChannel & FRONTEND_FLAG_CONFIRM)) {
                break;
            }
            next            = 1;
            g_ScriptVars[0] = next;
            SYS_SetFlag(g_SceneFlags, 0x3A);
            func_801BE1B0(3);
            Area_StartScrollRoute(0);
            *state = next;
            break;
        case 1:
            if (g_ScriptVars[0] != 0x1C) {
                break;
            }
            SYS_ClearFlag(g_SceneFlags, 0x3A);
            Game_ClearScriptActive();
            *state                = 0;
            g_SceneState.state_04 = 0;
            break;
    }
}

MATCH void func_801FC778(void) {
    u8* state;

    state = &D_80146875;
    switch (*state) {
        case 0:
            Message_StartAreaMessage(76);
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

MATCH void func_801FC808(void) {
    u8 i;

    for (i = 0; i < PARTY_SLOT_COUNT; i++) {
        if (g_PartyFieldOrder[i] == CHAR_ID_MOMO) {
            g_ScriptVars[1] = 1;
        }
    }
    for (i = 0; i < PARTY_SLOT_COUNT; i++) {
        if (g_PartyFieldOrder[i] == CHAR_ID_PECO) {
            g_ScriptVars[1] = 2;
        }
    }
}

/* Give the lead party member a field actor of type 6: claim a free slot and seed its row from the member. */
MATCH void func_801FC8A0(s32 variant){ACTOR_SEED_PARTY_SLOT(0, D_801FD5C0, 6, variant + 112)}
#include "overlays/scenario/Scene_DispatchActor.h"

MATCH void func_801FCA98(void) {
}

MATCH void func_801FCAA0(void) {
    if (SYS_TestFlag(g_SceneFlags, 2) == 0) {
        SYS_SetFlag(g_SceneFlags, 2U);
        Game_SetScriptActive();
        *g_ScriptVars = 0;
        D_80146865    = 0;
        D_80146866    = 0;
        D_80146867    = 0;
        D_80146875    = 0;
        D_80146874    = 0x15;
    }
}

MATCH void func_801FCB1C(void) {
    SYS_SetFlag(g_SceneFlags, 11);
    Game_SetScriptActive();
    g_ScriptVars[0] = 0;
    D_80146865      = 0;
    D_80146866      = 0;
    D_80146867      = 0;
    D_80146875      = 0;
    D_80146874      = 8;
}

MATCH void func_801FCB80(void) {
    Game_SetScriptActive();
    g_ScriptVars[0]       = 0;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.step_05  = 0;
    g_SceneState.state_04 = 12;
}

MATCH void func_801FCBD4(void) {
    SCENE_ENTER_STATE_13();
}

MATCH void func_801FCC28(void) {
    Game_SetScriptActive();
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.step_05  = 0;
    g_SceneState.state_04 = 16;
}

MATCH void func_801FCC74(void) {
    Game_SetScriptActive();
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.step_05  = 0;
    g_SceneState.state_04 = 17;
}

MATCH void func_801FCCC0(void) {
    Game_SetScriptActive();
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.step_05  = 0;
    g_SceneState.state_04 = 18;
}

MATCH void func_801FCD0C(void) {
    SCENE_ENTER_STATE_13();
}

MATCH s32 func_801FCD60(void) {
    return 0;
}

/* Start the scene script at the given state with its variables and first step cleared. */
#define SCENE_ENTER_STATE(state)  \
    Game_SetScriptActive();       \
    g_ScriptVars[0]       = 0;    \
    g_ScriptVars[1]       = 0;    \
    g_ScriptVars[2]       = 0;    \
    g_ScriptVars[3]       = 0;    \
    g_SceneState.step_05  = 0;    \
    g_SceneState.state_04 = state

MATCH s32 func_801FCD68(s32 x, s32 y) {
    if (g_GameAreaId == AREA_ID_PLANT) {
        if (SYS_TestFlag(g_SceneFlags, 9) && SYS_TestFlag(g_SceneFlags, 11) == 0 && (x == TO_COORD(77) || x == TO_COORD_HALF(77)) && (u32)(y - TO_COORD(33)) <= TO_COORD_HALF(4)) {
            SCENE_ENTER_STATE(7);
            return 1;
        }
    }
    if (g_GameAreaId == AREA_ID_DUMP) {
        if (SYS_TestFlag(g_SceneFlags, 5) == 0) {
            if ((u32)(x - TO_COORD(147)) <= TO_COORD_HALF(1) && (y == TO_COORD(6) || y == TO_COORD_HALF(6))) {
                SCENE_ENTER_STATE(4);
                return 1;
            }
        } else if (SYS_TestFlag(g_SceneFlags, 9) == 0 && (u32)(x - TO_COORD(132)) <= TO_COORD_HALF(2) && (y == TO_COORD(12) || y == TO_COORD_HALF(12) || y == TO_COORD(24) || y == TO_COORD_HALF(24))) {
            Game_SetScriptActive();
            g_SceneState.step_05  = 20;
            g_ScriptVars[0]       = 0;
            g_ScriptVars[1]       = 0;
            g_ScriptVars[2]       = 0;
            g_ScriptVars[3]       = 0;
            g_SceneState.state_04 = 4;
            return 1;
        }
    }
    if (g_GameAreaId == AREA_ID_MAEKYSS_GORGE && (y == TO_COORD(52) || y == TO_COORD_HALF(52)) && (u32)(x - TO_COORD(29)) <= TO_COORD_HALF(1)) {
        SCENE_ENTER_STATE(11);
        return 1;
    }
    if (g_GameAreaId == AREA_ID_CAFE) {
        if (SYS_TestFlag(g_SceneFlags, 0) == 0 && (y == TO_COORD(36) || y == TO_COORD_HALF(36)) && (u32)(x - TO_COORD(25)) <= TO_COORD_HALF(6)) {
            SCENE_ENTER_STATE(1);
            return 1;
        }
    }
    if (g_GameAreaId == AREA_ID_CONTEST_OUTER && SYS_TestFlag(g_SceneFlags, 61)) {
        if (SYS_TestFlag(g_SceneFlags, 50) == 0) {
            if (x == TO_COORD_HALF(40) || x == TO_COORD(41)) {
                if ((u32)(y - TO_COORD(126)) <= TO_COORD_HALF(3)) {
                    SCENE_ENTER_STATE(19);
                    return 1;
                }
            } else if (x == TO_COORD(31) || x == TO_COORD_HALF(31)) {
                if ((u32)(y - TO_COORD(113)) <= TO_COORD_HALF(1)) {
                    SCENE_ENTER_STATE(20);
                    return 1;
                }
            }
        } else if ((x == TO_COORD(31) || x == TO_COORD_HALF(31)) && (u32)(y - TO_COORD(113)) <= TO_COORD_HALF(1)) {
            SCENE_ENTER_STATE(22);
            return 1;
        }
    }
    return 0;
}

MATCH s8 func_801FD110(s32 x, s32 y) {
    SCENE_PROBE_POSITION(D_801FD668, 2, D_801FD674);
}

MATCH s32 func_801FD178(void) {
    SCENA05_START_SCENE(0x26, 1);
}

MATCH s32 func_801FD208(void) {
    SCENA05_START_SCENE(0x25, 0x19);
}

/* func_801FD298 */
MATCH void Scene_JoinMomoNinaPeco(void) {
    g_Characters[g_CharSlot[6]].unk_07 |= 1;
    Party_BuildBattlers(PARTY_ORDER_FIELD);
    Party_JoinMember(CHAR_ID_MOMO);
    Party_JoinMember(CHAR_ID_NINA_YOUNG);
    Party_JoinMember(CHAR_ID_PECO);
}

/* func_801FD30C */
MATCH void Party_JoinNinaYoung(void) {
    Party_JoinMember(CHAR_ID_NINA_YOUNG);
}

/* func_801FD32C */
MATCH void Party_JoinMomo(void) {
    Party_JoinMember(CHAR_ID_MOMO);
}

/* func_801FD34C */
MATCH void Party_JoinPeco(void) {
    Party_JoinMember(CHAR_ID_PECO);
}

/* func_801FD36C */
MATCH void Party_JoinRyuYoung(void) {
    Party_JoinMember(CHAR_ID_RYU_YOUNG);
}

MATCH void func_801FD38C(void) {
    EMI_LoadPartyArchives(CHAR_ID_RYU_YOUNG, CHAR_ID_NINA_YOUNG, CHAR_ID_MOMO, 0U);
    Party_BuildBattlers(PARTY_ORDER_FIELD);
    Party_JoinMember(CHAR_ID_MOMO);
}

/* func_801FD3C8 */
MATCH void Scene_JoinNinaYoung(void) {
    EMI_LoadPartyArchives(CHAR_ID_RYU_YOUNG, CHAR_ID_NINA_YOUNG, CHAR_ID_MOMO, 0U);
    Party_BuildBattlers(PARTY_ORDER_FIELD);
    Party_JoinMember(CHAR_ID_NINA_YOUNG);
}

MATCH void func_801FD404(void) {
    EMI_LoadPartyArchives(CHAR_ID_RYU_YOUNG, CHAR_ID_NINA_YOUNG, CHAR_ID_PECO, 0U);
    Party_BuildBattlers(PARTY_ORDER_FIELD);
    Party_JoinMember(CHAR_ID_PECO);
}

/* func_801FD440 */
MATCH void Party_JoinGarr(void) {
    Party_JoinMember(CHAR_ID_GARR);
}

#include "overlays/scenario/Scene_JoinNina.h"

MATCH void Scene_JoinNina2(void) {
    SCENE_JOIN_NINA();
}

/* func_801FD4D8 */
MATCH void Scene_RemoveMomoNina(void) {
    Party_RemoveMember(CHAR_ID_MOMO);
    Party_RemoveMember(CHAR_ID_NINA_YOUNG);
    Party_LoadPalettes();
}

#include "overlays/scenario/Scene_RemoveNina.h"

#include "overlays/scenario/Scene_RemoveMomo.h"

#include "overlays/scenario/Scene_RemovePeco.h"

/* func_801FD580 */
MATCH void Scene_RemoveRyuYoung(void) {
    Party_RemoveMember(CHAR_ID_RYU_YOUNG);
    Party_LoadPalettes();
}
