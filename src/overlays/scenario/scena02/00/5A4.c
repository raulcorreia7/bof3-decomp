#include "scena02_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F71A4(void) {
    /* Retail takes the handler index from the entry $v0; the uninitialised local reads it. */
    u32 index;

    /* FAKE: without the block the scheduler hoists the index shift above the
       ra store (84.46%); the lock restores the retail order (99.85%). */
    ORDER_LOCK(D_801FE288[index]());
}

MATCH void func_801F71D8(void) {
    *D_80144E98      = 0;
    g_ScriptVarsWord = 0;
    D_80146872       = 1;
}

INCLUDE_ASM(func_801F71FC);

MATCH void func_801F7A60(void) {
    SYS_DISPATCH_BYTE(D_801FE294, g_SceneState.state_04);
}

MATCH void func_801F7A9C(void) {
    if ((SYS_TestFlag(g_SceneFlags, 0x3F) == 0) && (g_GameAreaId == 0x1A)) {
        if (SYS_TestFlag(g_SceneFlags, 0x28) != 0) {
            func_801FC044(0);
        }
        if (SYS_TestFlag(g_SceneFlags, 0x29) != 0) {
            func_801FBF94(0);
        }
        if ((SYS_TestFlag(g_SceneFlags, 7) == 0) || (SYS_TestFlag(g_SceneFlags, 0x34) != 0)) {
            if (SYS_TestFlag(g_SceneFlags, 0x2B) != 0) {
                func_801FC0F4(5);
            }
            if (SYS_TestFlag(g_SceneFlags, 0x2C) != 0) {
                func_801FC1A4(5);
            }
        }
        func_801FC25C(1);
        func_801FC308(2);
        func_801FC518(3);
        func_801FC5D0(4);
        if ((SYS_TestFlag(g_SceneFlags, 7) == 0) || (SYS_TestFlag(g_SceneFlags, 0x34) != 0)) {
            func_801FC3B4(6);
            func_801FC46C(7);
            func_801FC688(8);
        }
        if (SYS_TestFlag(g_SceneFlags, 0x2E) == 0) {
            func_801FC734(9);
            func_801FC7E4();
            return;
        }
        func_801FC9CC();
    }
}

MATCH void func_801F7C30(void) {
}

INCLUDE_ASM(func_801F7C38);

MATCH void func_801F8068(void) {
}

INCLUDE_ASM(func_801F8070);

MATCH void func_801F8264(void) {
    u8* state;

    state = &D_80146875;
    switch (*state) {
        case 0:
            Message_StartAreaMessage(0x3E);
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

INCLUDE_ASM(func_801F82F4);

INCLUDE_ASM(func_801F8538);

INCLUDE_ASM(func_801F8740);

INCLUDE_ASM(func_801F8C78);

INCLUDE_ASM(func_801F9134);

INCLUDE_ASM(func_801F936C);

INCLUDE_ASM(func_801F9678);

INCLUDE_ASM(func_801F9800);

INCLUDE_ASM(func_801F9BD0);

INCLUDE_ASM(func_801F9EA4);

INCLUDE_ASM(func_801FA1F0);

INCLUDE_ASM(func_801FA548);

INCLUDE_ASM(func_801FAA68);

INCLUDE_ASM(func_801FAC54);

MATCH void func_801FB0E8(void) {
}

INCLUDE_ASM(func_801FB0F0);

MATCH void func_801FB2F8(void) {
}

INCLUDE_ASM(func_801FB300);

INCLUDE_ASM(func_801FB36C);

INCLUDE_ASM(func_801FB6C4);

INCLUDE_ASM(func_801FB868);

INCLUDE_ASM(func_801FBC6C);

INCLUDE_ASM(func_801FBF24);

MATCH void func_801FBF94(u8 actor_id) {
    SCENA02_TRIGGER_NEAR_Y(actor_id, 0x18000, 0x50000);
}

MATCH void func_801FC044(u8 actor_id) {
    SCENA02_TRIGGER_BEHIND_X(actor_id, 0x40000, 0x18000);
}

MATCH void func_801FC0F4(u8 actor_id) {
    if (D_80143F03 == 0) {
        if (g_Actors[actor_id].x.fixed + 0x18000 >= D_80145EC4 && D_80145EC4 >= g_Actors[actor_id].x.fixed - 0x18000 &&
            D_80145EC8 >= g_Actors[actor_id].y.fixed + 0x10000 && g_Actors[actor_id].y.fixed + 0x40000 >= D_80145EC8) {
            func_801FCB54();
        }
    }
}

MATCH void func_801FC1A4(u8 actor_id) {
    if (D_80143F03 == 0) {
        if (g_Actors[actor_id].y.fixed + 0x10000 >= D_80145EC8 && D_80145EC8 >= g_Actors[actor_id].y.fixed - 0x40000 &&
            D_80145EC4 >= g_Actors[actor_id].x.fixed - 0x18000 && g_Actors[actor_id].x.fixed + 0x18000 >= D_80145EC4) {
            func_801FCB54();
        }
    }
}

MATCH void func_801FC25C(u8 actor_id) {
    SCENA02_TRIGGER_NEAR_Y(actor_id, 0x20000, 0x60000);
}

MATCH void func_801FC308(u8 actor_id) {
    if (D_80143F03 == 0) {
        if (D_80145EC8 <= g_Actors[actor_id].y.fixed && D_80145EC8 >= g_Actors[actor_id].y.fixed - 0x50000 &&
            D_80145EC4 >= g_Actors[actor_id].x.fixed - 0x10000 && g_Actors[actor_id].x.fixed + 0x10000 >= D_80145EC4) {
            func_801FCB54();
        }
    }
}

MATCH void func_801FC3B4(s32 actor_id) {
    SCENA02_TRIGGER_BEHIND_X(actor_id & 0xFF, 0x48000, 0x18000);
}

MATCH void func_801FC46C(u8 actor_id) {
    SCENA02_TRIGGER_NEAR_Y(actor_id, 0x10000, 0x40000);
}

MATCH void func_801FC518(s32 actor_id) {
    SCENA02_TRIGGER_BAND_Y(actor_id & 0xFF, 0x28000, 0x20000, 0x40000);
}

MATCH void func_801FC5D0(s32 actor_id) {
    SCENA02_TRIGGER_BAND_Y(actor_id & 0xFF, 0x18000, 0x10000, 0x30000);
}

MATCH void func_801FC688(u8 actor_id) {
    SCENA02_TRIGGER_NEAR_X(actor_id, 0x10000, 0x50000);
}

MATCH void func_801FC734(u8 actor_id) {
    SCENA02_TRIGGER_NEAR_X(actor_id, 0x18000, 0x40000);
}

INCLUDE_ASM(func_801FC7E4);

INCLUDE_ASM(func_801FC9CC);

MATCH void func_801FCB54(void) {
    g_ScriptVars[0] = 31;
    D_80146865      = 0;
    D_80146866      = 0;
    D_80146867      = 0;
    D_80146875      = 0;
    D_80146874      = 7;
}

MATCH void func_801FCB94(void) {
    g_ScriptVars[0] = 0;
    D_80146865      = 0;
    D_80146866      = 0;
    D_80146867      = 0;
    D_80146875      = 0;
    SND_PlayCue(514);
}

INCLUDE_ASM(func_801FCBDC);

INCLUDE_ASM(func_801FCD14);

INCLUDE_ASM(func_801FCECC);

MATCH void func_801FD084(void* record) {
    D_801FE304[((Actor*)record)->callback_index](record, &D_80144E98);
}

MATCH void func_801FD0C4(void) {
}

MATCH void func_801FD0CC(void) {
    Game_SetScriptActive();
    g_SceneState.step_05  = 7;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_SceneState.state_04 = 11;
}

MATCH void func_801FD114(void) {
    Game_SetScriptActive();
    g_SceneState.step_05  = 2;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_SceneState.state_04 = 11;
}

MATCH void func_801FD15C(void) {
}

INCLUDE_ASM(func_801FD164);

INCLUDE_ASM(func_801FD1DC);

MATCH void func_801FD254(void) {
    g_ScriptVars[1] = 1;
}

MATCH void func_801FD268(void) {
    g_ScriptVars[2] = 1;
}

MATCH void func_801FD27C(void) {
    g_ScriptVars[1] = 1;
}

MATCH void func_801FD290(void) {
    SYS_SetFlag(g_SceneFlags, 0xDU);
}

MATCH void func_801FD2B8(void) {
    SYS_SetFlag(g_SceneFlags, 0xEU);
}

MATCH void func_801FD2E0(void) {
    Game_SetScriptActive();
    g_ScriptVars[0]       = 1;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_SceneState.step_05  = 0;
    g_SceneState.state_04 = 7;
}

MATCH void func_801FD330(void) {
    Game_SetScriptActive();
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_SceneState.step_05  = 0;
    g_SceneState.state_04 = 11;
}

MATCH void func_801FD374(void) {
    Game_SetScriptActive();
    g_SceneState.step_05  = 5;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_SceneState.state_04 = 11;
}

MATCH void func_801FD3BC(void) {
    Game_SetScriptActive();
    g_ScriptVars[0]       = 20;
    g_SceneState.step_05  = 20;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_SceneState.state_04 = 2;
}

MATCH void func_801FD40C(void) {
    Game_SetScriptActive();
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_SceneState.step_05  = 0;
    g_SceneState.state_04 = 15;
}

MATCH void func_801FD450(void) {
    Game_SetScriptActive();
    g_SceneState.step_05  = 0xF;
    g_SceneState.state_04 = 0x10;
    SND_PlayCue(EMI_CUE_ID(1, 6));
}

MATCH void func_801FD490(void) {
    Game_SetScriptActive();
    g_ScriptVars[0]       = 0;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.step_05  = 0;
    g_SceneState.state_04 = 18;
}

MATCH void func_801FD4E4(void) {
}

MATCH void func_801FD4EC(void) {
    Game_SetScriptActive();
    g_SceneState.step_05  = 0x1e;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.state_04 = 2;
}

MATCH void func_801FD53C(void) {
    Game_SetScriptActive();
    g_SceneState.step_05  = 0xA;
    g_SceneState.state_04 = 0x1B;
}

MATCH void func_801FD574(void) {
    Game_SetScriptActive();
    g_SceneState.step_05  = 0;
    g_SceneState.state_04 = 0x17;
}

MATCH void func_801FD5A8(void) {
    Game_SetScriptActive();
    g_ScriptVars[0]       = 0;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.step_05  = 0;
    g_SceneState.state_04 = 25;
}

MATCH void func_801FD5FC(void) {
    Game_SetScriptActive();
    g_SceneState.step_05  = 10;
    g_ScriptVars[0]       = 0;
    g_ScriptVars[1]       = 0;
    g_ScriptVars[2]       = 0;
    g_ScriptVars[3]       = 0;
    g_SceneState.state_04 = 25;
    SND_PlayCue(0x106);
}

MATCH void func_801FD65C(void) {
    SYS_SetFlag(g_SceneFlags, 0x31U);
}

MATCH void func_801FD684(void) {
    Game_SetScriptActive();
    g_SceneState.step_05  = 0x19;
    g_SceneState.state_04 = 0x1A;
}

MATCH void func_801FD6BC(void) {
    Game_SetScriptActive();
    g_SceneState.step_05  = 5;
    g_SceneState.state_04 = 0x1B;
}

MATCH s32 func_801FD6F4(void) {
    return 0;
}

MATCH void func_801FD6FC(u8 character) {
    u8* ability;
    u8  i;

    ability = g_Characters[character].skill_abilities;
    for (i = 0; i < 10; i++) {
        if (*ability != 0) {
            Char_AddAbility(*ability, 0, 1, 0);
            *ability = 0;
        }
        ability++;
    }
}

INCLUDE_ASM(func_801FD780);

MATCH void func_801FE178(void) {
    Party_JoinMember(4);
}

#include "overlays/scenario/Scene_RemoveRei.h"

INCLUDE_ASM(func_801FE1C0);
