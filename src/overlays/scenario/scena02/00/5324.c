#include "scena02_00.h"
#include "area/map.h"
#include "area/spad.h"
#include "overlays/area/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FBF24(void) {
    u8* state;

    state = &D_80146866;
    if (*state == 3) {
        Game_SetScriptActive();
        return;
    }
    Game_ClearScriptActive();
    D_80146867 = 0;
    D_80146875 = 8;
    *state += 1;
}

MATCH void func_801FBF94(u8 actor_id) {
    SCENA02_TRIGGER_NEAR_Y(actor_id, TO_COORD(1) + COORD_HALF, TO_COORD(5));
}

MATCH void func_801FC044(u8 actor_id) {
    SCENA02_TRIGGER_BEHIND_X(actor_id, TO_COORD(4), TO_COORD(1) + COORD_HALF);
}

MATCH void func_801FC0F4(u8 actor_id) {
    if (D_80143F03 == 0) {
        if (g_Actors[actor_id].pos.x.fixed + TO_COORD(1) + COORD_HALF >= g_Game.members[0].pos.x.fixed && g_Game.members[0].pos.x.fixed >= g_Actors[actor_id].pos.x.fixed - TO_COORD(1) - COORD_HALF &&
            g_Game.members[0].pos.y.fixed >= g_Actors[actor_id].pos.y.fixed + TO_COORD(1) && g_Actors[actor_id].pos.y.fixed + TO_COORD(4) >= g_Game.members[0].pos.y.fixed) {
            func_801FCB54();
        }
    }
}

MATCH void func_801FC1A4(u8 actor_id) {
    if (D_80143F03 == 0) {
        if (g_Actors[actor_id].pos.y.fixed + TO_COORD(1) >= g_Game.members[0].pos.y.fixed && g_Game.members[0].pos.y.fixed >= g_Actors[actor_id].pos.y.fixed - TO_COORD(4) &&
            g_Game.members[0].pos.x.fixed >= g_Actors[actor_id].pos.x.fixed - TO_COORD(1) - COORD_HALF && g_Actors[actor_id].pos.x.fixed + TO_COORD(1) + COORD_HALF >= g_Game.members[0].pos.x.fixed) {
            func_801FCB54();
        }
    }
}

MATCH void func_801FC25C(u8 actor_id) {
    SCENA02_TRIGGER_NEAR_Y(actor_id, TO_COORD(2), TO_COORD(6));
}

MATCH void func_801FC308(u8 actor_id) {
    if (D_80143F03 == 0) {
        if (g_Game.members[0].pos.y.fixed <= g_Actors[actor_id].pos.y.fixed && g_Game.members[0].pos.y.fixed >= g_Actors[actor_id].pos.y.fixed - TO_COORD(5) &&
            g_Game.members[0].pos.x.fixed >= g_Actors[actor_id].pos.x.fixed - TO_COORD(1) && g_Actors[actor_id].pos.x.fixed + TO_COORD(1) >= g_Game.members[0].pos.x.fixed) {
            func_801FCB54();
        }
    }
}

MATCH void func_801FC3B4(s32 actor_id) {
    SCENA02_TRIGGER_BEHIND_X(actor_id & BYTE_MASK, TO_COORD(4) + COORD_HALF, TO_COORD(1) + COORD_HALF);
}

MATCH void func_801FC46C(u8 actor_id) {
    SCENA02_TRIGGER_NEAR_Y(actor_id, TO_COORD(1), TO_COORD(4));
}

MATCH void func_801FC518(s32 actor_id) {
    SCENA02_TRIGGER_BAND_Y(actor_id & BYTE_MASK, TO_COORD(2) + COORD_HALF, TO_COORD(2), TO_COORD(4));
}

MATCH void func_801FC5D0(s32 actor_id) {
    SCENA02_TRIGGER_BAND_Y(actor_id & BYTE_MASK, TO_COORD(1) + COORD_HALF, TO_COORD(1), TO_COORD(3));
}

MATCH void func_801FC688(u8 actor_id) {
    SCENA02_TRIGGER_NEAR_X(actor_id, TO_COORD(1), TO_COORD(5));
}

MATCH void func_801FC734(u8 actor_id) {
    SCENA02_TRIGGER_NEAR_X(actor_id, TO_COORD(1) + COORD_HALF, TO_COORD(4));
}

MATCH void func_801FC7E4(void) {
    if ((g_PartyFieldOrder[0] == 0) || (g_PartyFieldOrder[0] == 3)) {
        if (((u16)(D_80145EC6 - 0x44) < 2) && (D_80145ECA == 0x3F) && (D_80145EDB == 0x42) && (D_80145E98 == 1)) {
            SCENA02_START_SCRIPT_1A();
        }
        if (D_80145EC6 == 0x46) {
            if ((D_80145ECA == 0x3E) && (D_80145EDB == 0x45) && (D_80145E98 == 7)) {
                SCENA02_START_SCRIPT_1A();
            }
        }
        if ((D_80145EC6 == 0x44) && (D_80145ECA == 0x3E) && (D_80145EDB == 0x43) && (D_80145E98 == 3)) {
            SCENA02_START_SCRIPT_1A();
        }
    }
}

MATCH void func_801FC9CC(void) {
    if (g_PartyFieldOrder[0] == 0 || g_PartyFieldOrder[0] == 3) {
        if ((u32)((u16)D_80145EC6 - 0x44) < 2 && D_80145ECA == 0x3F && D_80145EDB == 0x42 && D_80145E98 == 1) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x0B));
            D_80146875 = 0x1E;
            D_80146874 = 0x1A;
        }
        if (D_80145EC6 == 0x46) {
            if (D_80145ECA == 0x3E && D_80145EDB == 0x45 && D_80145E98 == 7) {
                SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x0B));
                D_80146875 = 0x1E;
                D_80146874 = 0x1A;
            }
        }
        if (D_80145EC6 == 0x44 && D_80145ECA == 0x3E && D_80145EDB == 0x43 && D_80145E98 == 3) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x0B));
            D_80146875 = 0x1E;
            D_80146874 = 0x1A;
        }
    }
}

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
    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 2));
}

MATCH void func_801FCBDC(s32 delta) {
    u8* state;
    s32 amount;
    s32 amount_2;
    u8  frame;
    u8  frame_2;

    state = &D_80146865;
    switch (*state) {
        case 0:
            amount                   = delta & BYTE_MASK;
            g_AreaCameraRefreshCount = 2;
            frame                    = D_80146867 + 1;
            D_80146867               = frame;
            g_AreaCameraOffsetY      = g_AreaCameraOffsetY + amount;
            g_AreaCameraOffsetY      = g_AreaCameraOffsetX + amount;
            if (frame == 2) {
                g_AreaCameraOffsetY      = 0;
                g_AreaCameraOffsetX      = 0;
                g_AreaCameraRefreshCount = 2;
                *state                   = 1;
                D_80146867               = 0;
                return;
            }
            return;
        case 1:
            amount_2                 = delta & BYTE_MASK;
            g_AreaCameraRefreshCount = 2;
            frame_2                  = D_80146867 + 1;
            D_80146867               = frame_2;
            g_AreaCameraOffsetY      = g_AreaCameraOffsetY - amount_2;
            g_AreaCameraOffsetY      = g_AreaCameraOffsetX + amount_2;
            if (frame_2 == 2) {
                g_AreaCameraOffsetY      = 0;
                g_AreaCameraOffsetX      = 0;
                g_AreaCameraRefreshCount = 2;
                D_80146867               = 0;
                *state                   = 0;
            }
            break;
    }
}

/* Give the lead party member a field actor of type 6: claim a free slot and seed its row from the member. */
MATCH void func_801FCD14(s32 variant){ACTOR_SEED_PARTY_SLOT(0, D_801FE26C, 6, variant + 112)}

/* Give the lead party member a field actor of type 25: claim a free slot and seed its row from the member. */
MATCH void func_801FCECC(s32 variant){ACTOR_SEED_PARTY_SLOT(0, D_801FE26C, 25, variant + 104)}

MATCH void func_801FD084(void* record) {
    D_801FE304[((Actor*)record)->callback_index](record, &g_Scenario2Flags);
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

MATCH void func_801FD164(void) {
    if (SYS_TestFlag(g_SceneFlags, 5) == 0) {
        g_GameFlags ^= 0x36;
        Game_SetScriptActive();
        D_80146875 = 5;
        D_80146865 = 0;
        D_80146866 = 0;
        D_80146874 = 4;
    }
}

MATCH void func_801FD1DC(void) {
    if (SYS_TestFlag(g_SceneFlags, 5) == 0) {
        g_GameFlags ^= 0x36;
        Game_SetScriptActive();
        D_80146875 = 7;
        D_80146865 = 0;
        D_80146866 = 0;
        D_80146874 = 4;
    }
}

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
    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
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
    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
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

    ability = g_Characters[character].abilities.skill;
    for (i = 0; i < 10; i++) {
        if (*ability != 0) {
            Char_AddAbility(*ability, 0, 1, 0);
            *ability = 0;
        }
        ability++;
    }
}

INCLUDE_ASM(func_801FD780);

/* func_801FE178 */
MATCH void Party_JoinRei(void) {
    Party_JoinMember(CHAR_ID_REI);
}

#include "overlays/scenario/Scene_RemoveRei.h"

INCLUDE_ASM(func_801FE1C0);
