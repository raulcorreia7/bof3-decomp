#include "scena02_00.h"
#include "area/map.h"
#include "overlays/area/shared/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FBF24(void) {
    u8* state;

    state = &g_ScriptVars[2];
    if (*state == 3) {
        Game_SetScriptActive();
        return;
    }
    Game_ClearScriptActive();
    g_ScriptVars[3]      = 0;
    g_ScenarioState.step = 8;
    *state += 1;
}

MATCH void func_801FBF94(u8 actor_id) {
    SCENA02_TRIGGER_NEAR_Y(actor_id, TO_COORD(1) + COORD_HALF, TO_COORD(5));
}

MATCH void func_801FC044(u8 actor_id) {
    SCENA02_TRIGGER_BEHIND_X(actor_id, TO_COORD(4), TO_COORD(1) + COORD_HALF);
}

MATCH void func_801FC0F4(u8 actor_id) {
    if (g_GameCellType == 0) {
        if (g_Actors[actor_id].pos.x.fixed + TO_COORD(1) + COORD_HALF >= g_Game.members[0].pos.x.fixed && g_Game.members[0].pos.x.fixed >= g_Actors[actor_id].pos.x.fixed - TO_COORD(1) - COORD_HALF &&
            g_Game.members[0].pos.y.fixed >= g_Actors[actor_id].pos.y.fixed + TO_COORD(1) && g_Actors[actor_id].pos.y.fixed + TO_COORD(4) >= g_Game.members[0].pos.y.fixed) {
            func_801FCB54();
        }
    }
}

MATCH void func_801FC1A4(u8 actor_id) {
    if (g_GameCellType == 0) {
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
    if (g_GameCellType == 0) {
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
        if (((u16)(g_Game.members[0].pos.x.part.integer - 0x44) < 2) && (g_Game.members[0].pos.y.part.integer == 0x3F) && (g_Game.members[0].unk_4B == 0x42) && (g_Game.members[0].facing == 1)) {
            SCENA02_START_SCRIPT_1A();
        }
        if (g_Game.members[0].pos.x.part.integer == 0x46) {
            if ((g_Game.members[0].pos.y.part.integer == 0x3E) && (g_Game.members[0].unk_4B == 0x45) && (g_Game.members[0].facing == 7)) {
                SCENA02_START_SCRIPT_1A();
            }
        }
        if ((g_Game.members[0].pos.x.part.integer == 0x44) && (g_Game.members[0].pos.y.part.integer == 0x3E) && (g_Game.members[0].unk_4B == 0x43) && (g_Game.members[0].facing == 3)) {
            SCENA02_START_SCRIPT_1A();
        }
    }
}

MATCH void func_801FC9CC(void) {
    if (g_PartyFieldOrder[0] == 0 || g_PartyFieldOrder[0] == 3) {
        if ((u32)((u16)g_Game.members[0].pos.x.part.integer - 0x44) < 2 && g_Game.members[0].pos.y.part.integer == 0x3F && g_Game.members[0].unk_4B == 0x42 && g_Game.members[0].facing == 1) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x0B));
            g_ScenarioState.step     = 0x1E;
            g_ScenarioState.state_04 = 0x1A;
        }
        if (g_Game.members[0].pos.x.part.integer == 0x46) {
            if (g_Game.members[0].pos.y.part.integer == 0x3E && g_Game.members[0].unk_4B == 0x45 && g_Game.members[0].facing == 7) {
                SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x0B));
                g_ScenarioState.step     = 0x1E;
                g_ScenarioState.state_04 = 0x1A;
            }
        }
        if (g_Game.members[0].pos.x.part.integer == 0x44 && g_Game.members[0].pos.y.part.integer == 0x3E && g_Game.members[0].unk_4B == 0x43 && g_Game.members[0].facing == 3) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x0B));
            g_ScenarioState.step     = 0x1E;
            g_ScenarioState.state_04 = 0x1A;
        }
    }
}

MATCH void func_801FCB54(void) {
    g_ScriptVars[0]          = 31;
    g_ScriptVars[1]          = 0;
    g_ScriptVars[2]          = 0;
    g_ScriptVars[3]          = 0;
    g_ScenarioState.step     = 0;
    g_ScenarioState.state_04 = 7;
}

MATCH void func_801FCB94(void) {
    g_ScriptVars[0]      = 0;
    g_ScriptVars[1]      = 0;
    g_ScriptVars[2]      = 0;
    g_ScriptVars[3]      = 0;
    g_ScenarioState.step = 0;
    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 2));
}

MATCH void func_801FCBDC(s32 delta) {
    u8* state;
    s32 amount;
    s32 amount_2;
    u8  frame;
    u8  frame_2;

    state = &g_ScriptVars[1];
    switch (*state) {
        case 0:
            amount                   = delta & BYTE_MASK;
            g_AreaCameraRefreshCount = 2;
            frame                    = g_ScriptVars[3] + 1;
            g_ScriptVars[3]          = frame;
            g_AreaCameraOffsetY      = g_AreaCameraOffsetY + amount;
            g_AreaCameraOffsetY      = g_AreaCameraOffsetX + amount;
            if (frame == 2) {
                g_AreaCameraOffsetY      = 0;
                g_AreaCameraOffsetX      = 0;
                g_AreaCameraRefreshCount = 2;
                *state                   = 1;
                g_ScriptVars[3]          = 0;
                return;
            }
            return;
        case 1:
            amount_2                 = delta & BYTE_MASK;
            g_AreaCameraRefreshCount = 2;
            frame_2                  = g_ScriptVars[3] + 1;
            g_ScriptVars[3]          = frame_2;
            g_AreaCameraOffsetY      = g_AreaCameraOffsetY - amount_2;
            g_AreaCameraOffsetY      = g_AreaCameraOffsetX + amount_2;
            if (frame_2 == 2) {
                g_AreaCameraOffsetY      = 0;
                g_AreaCameraOffsetX      = 0;
                g_AreaCameraRefreshCount = 2;
                g_ScriptVars[3]          = 0;
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
    g_ScenarioState.step     = 7;
    g_ScriptVars[1]          = 0;
    g_ScriptVars[2]          = 0;
    g_ScenarioState.state_04 = 11;
}

MATCH void func_801FD114(void) {
    Game_SetScriptActive();
    g_ScenarioState.step     = 2;
    g_ScriptVars[1]          = 0;
    g_ScriptVars[2]          = 0;
    g_ScenarioState.state_04 = 11;
}

MATCH void func_801FD15C(void) {
}

MATCH void func_801FD164(void) {
    if (SYS_TestFlag(g_SceneFlags, 5) == 0) {
        g_GameFlags ^= 0x36;
        Game_SetScriptActive();
        g_ScenarioState.step     = 5;
        g_ScriptVars[1]          = 0;
        g_ScriptVars[2]          = 0;
        g_ScenarioState.state_04 = 4;
    }
}

MATCH void func_801FD1DC(void) {
    if (SYS_TestFlag(g_SceneFlags, 5) == 0) {
        g_GameFlags ^= 0x36;
        Game_SetScriptActive();
        g_ScenarioState.step     = 7;
        g_ScriptVars[1]          = 0;
        g_ScriptVars[2]          = 0;
        g_ScenarioState.state_04 = 4;
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
    g_ScriptVars[0]          = 1;
    g_ScriptVars[1]          = 0;
    g_ScriptVars[2]          = 0;
    g_ScenarioState.step     = 0;
    g_ScenarioState.state_04 = 7;
}

MATCH void func_801FD330(void) {
    Game_SetScriptActive();
    g_ScriptVars[1]          = 0;
    g_ScriptVars[2]          = 0;
    g_ScenarioState.step     = 0;
    g_ScenarioState.state_04 = 11;
}

MATCH void func_801FD374(void) {
    Game_SetScriptActive();
    g_ScenarioState.step     = 5;
    g_ScriptVars[1]          = 0;
    g_ScriptVars[2]          = 0;
    g_ScenarioState.state_04 = 11;
}

MATCH void func_801FD3BC(void) {
    Game_SetScriptActive();
    g_ScriptVars[0]          = 20;
    g_ScenarioState.step     = 20;
    g_ScriptVars[1]          = 0;
    g_ScriptVars[2]          = 0;
    g_ScenarioState.state_04 = 2;
}

MATCH void func_801FD40C(void) {
    Game_SetScriptActive();
    g_ScriptVars[1]          = 0;
    g_ScriptVars[2]          = 0;
    g_ScenarioState.step     = 0;
    g_ScenarioState.state_04 = 15;
}

MATCH void func_801FD450(void) {
    Game_SetScriptActive();
    g_ScenarioState.step     = 0xF;
    g_ScenarioState.state_04 = 0x10;
    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
}

MATCH void func_801FD490(void) {
    Game_SetScriptActive();
    SCRIPT_VARS_CLEAR_ALL();
    g_ScenarioState.step     = 0;
    g_ScenarioState.state_04 = 18;
}

MATCH void func_801FD4E4(void) {
}

MATCH void func_801FD4EC(void) {
    Game_SetScriptActive();
    g_ScenarioState.step = 0x1e;
    SCRIPT_VARS_CLEAR_EXCEPT_CHOICE();
    g_ScenarioState.state_04 = 2;
}

MATCH void func_801FD53C(void) {
    Game_SetScriptActive();
    g_ScenarioState.step     = 0xA;
    g_ScenarioState.state_04 = 0x1B;
}

MATCH void func_801FD574(void) {
    Game_SetScriptActive();
    g_ScenarioState.step     = 0;
    g_ScenarioState.state_04 = 0x17;
}

MATCH void func_801FD5A8(void) {
    Game_SetScriptActive();
    SCRIPT_VARS_CLEAR_ALL();
    g_ScenarioState.step     = 0;
    g_ScenarioState.state_04 = 25;
}

MATCH void func_801FD5FC(void) {
    Game_SetScriptActive();
    g_ScenarioState.step = 10;
    SCRIPT_VARS_CLEAR_ALL();
    g_ScenarioState.state_04 = 25;
    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
}

MATCH void func_801FD65C(void) {
    SYS_SetFlag(g_SceneFlags, 0x31U);
}

MATCH void func_801FD684(void) {
    Game_SetScriptActive();
    g_ScenarioState.step     = 0x19;
    g_ScenarioState.state_04 = 0x1A;
}

MATCH void func_801FD6BC(void) {
    Game_SetScriptActive();
    g_ScenarioState.step     = 5;
    g_ScenarioState.state_04 = 0x1B;
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
            Char_AbilityAdd(*ability, 0, 1, 0);
            *ability = 0;
        }
        ability++;
    }
}

/* Starts the scene script for the trigger cell at (x, y) in the current area; returns 1 when one starts. */
MATCH s32 func_801FD780(s32 x, s32 y) {
    if (g_GameAreaId == AREA_ID_CEDAR_WOODS_BUNYAN && SYS_TestFlag(g_SceneFlags, 0x1F) && !SYS_TestFlag(g_SceneFlags, 0x20) && (u32)(x - TO_COORD_HALF(85)) <= TO_COORD(1) &&
        (u32)(y - TO_COORD(28)) <= TO_COORD_HALF(1)) {
        Game_SetScriptActive();
        g_ScenarioState.step     = 5;
        g_ScriptVars[0]          = 0;
        g_ScriptVars[1]          = 0;
        g_ScriptVars[2]          = 0;
        g_ScriptVars[3]          = 0;
        g_ScenarioState.state_04 = 0x15;
        g_AreaDrawFlags          = 0;
        func_8019FA28(3, TO_COORD(51), TO_COORD(20), 0x81);
        return 1;
    }
    if (g_GameAreaId == AREA_ID_MCNEIL_MANOR_AREA) {
        if (!SYS_TestFlag(g_SceneFlags, 0x19) && y > TO_COORD(81) && (u32)(x - TO_COORD(54)) <= TO_COORD_HALF(1)) {
            Game_SetScriptActive();
            g_ScenarioState.step     = 0;
            g_ScenarioState.state_04 = 5;
            return 1;
        }
    }
    if (g_GameAreaId == AREA_ID_MCNEIL_MANOR_COURTYARD) {
        if (SYS_TestFlag(g_SceneFlags, 0x32)) {
            if (!SYS_TestFlag(g_SceneFlags, 7)) {
                if (y == TO_COORD(8) && (u32)(x - TO_COORD(52)) <= TO_COORD_HALF(1)) {
                    g_ScriptVars[2]          = 0;
                    g_ScenarioState.step     = 0;
                    g_ScenarioState.state_04 = 8;
                    func_8019FA28(0x1A, TO_COORD(7), TO_COORD(13), 0x80);
                }
            } else if (SYS_TestFlag(g_SceneFlags, 0x34) && !SYS_TestFlag(g_SceneFlags, 0x35) && y == TO_COORD(8) && (u32)(x - TO_COORD(52)) <= TO_COORD_HALF(1)) {
                g_ScenarioState.step     = 5;
                g_ScriptVars[2]          = 0;
                g_ScenarioState.state_04 = 8;
                func_8019FA28(0x1A, TO_COORD(7), TO_COORD(13), 0x81);
                g_GamePrevSelection = 0x1F;
            }
        }
        if (g_GameCellType == 1 && SYS_TestFlag(g_SceneFlags, 0x34) && !SYS_TestFlag(g_SceneFlags, 0x35) && x >= TO_COORD(5)) {
            if (x <= TO_COORD(9) && y > TO_COORD(15)) {
                Game_SetScriptActive();
                g_ScenarioState.step     = 6;
                g_ScenarioState.state_04 = 8;
                return 1;
            }
        }
        if (SYS_TestFlag(g_SceneFlags, 7) && !SYS_TestFlag(g_SceneFlags, 0x34) && (y == TO_COORD(50) || y == TO_COORD_HALF(50)) && (u32)(x - TO_COORD(29)) <= TO_COORD(3)) {
            Game_SetScriptActive();
            g_ScriptVars[0]          = 0xA0;
            g_ScenarioState.step     = 0;
            g_ScenarioState.state_04 = 9;
            return 1;
        }
        if ((x == TO_COORD(53) || x == TO_COORD_HALF(53)) && (u32)(y - TO_COORD(76)) <= TO_COORD_HALF(1)) {
            Game_SetScriptActive();
            g_ScenarioState.step     = 0;
            g_ScenarioState.state_04 = 6;
            return 1;
        }
        if ((y == TO_COORD(76) || y == TO_COORD_HALF(76)) && (u32)(x - TO_COORD(37)) <= TO_COORD_HALF(2)) {
            Game_SetScriptActive();
            g_ScenarioState.step     = 0xF;
            g_ScriptVars[0]          = 0;
            g_ScriptVars[1]          = 0;
            g_ScriptVars[2]          = 0;
            g_ScriptVars[3]          = 0;
            g_ScenarioState.state_04 = 0x19;
            return 1;
        }
        if (!SYS_TestFlag(g_SceneFlags, 0x2F) && (u32)(x - TO_COORD(48)) <= TO_COORD(2) && (y == TO_COORD(42) || y == TO_COORD_HALF(41))) {
            Game_SetScriptActive();
            g_ScenarioState.step     = 5;
            g_ScenarioState.state_04 = 0x1A;
            return 1;
        }
        if (!SYS_TestFlag(g_SceneFlags, 0x30)) {
            if ((u32)(x - TO_COORD(49)) <= TO_COORD(1) && (y == TO_COORD(37) || y == TO_COORD_HALF(36))) {
                Game_SetScriptActive();
                g_ScenarioState.step     = 0xF;
                g_ScenarioState.state_04 = 0x1A;
                return 1;
            }
            if ((x == TO_COORD(59) || x == TO_COORD_HALF(59)) && (u32)(y - TO_COORD(38)) <= TO_COORD_HALF(3)) {
                Game_SetScriptActive();
                g_ScenarioState.step     = 0x14;
                g_ScenarioState.state_04 = 0x1A;
                return 1;
            }
        }
        if (!SYS_TestFlag(g_SceneFlags, 0x24)) {
            if (!SYS_TestFlag(g_SceneFlags, 0x25)) {
                if ((x == TO_COORD_HALF(41) || x == TO_COORD_HALF(42)) && (u32)(y - TO_COORD(80)) <= TO_COORD(4)) {
                    u8* phase = &g_ScriptVars[1];

                    switch (*phase) {
                        case 0:
                            Game_SetScriptActive();
                            g_ScriptVars[0]          = 0;
                            *phase                   = 0;
                            g_ScriptVars[2]          = 0;
                            g_ScriptVars[3]          = 0;
                            g_ScenarioState.step     = 0;
                            g_ScenarioState.state_04 = 0x18;
                            return 1;
                        case 1:
                            Game_SetScriptActive();
                            g_ScriptVars[0]          = 1;
                            *phase                   = 0;
                            g_ScenarioState.step     = 0x14;
                            g_ScriptVars[2]          = 0;
                            g_ScriptVars[3]          = 0;
                            g_ScenarioState.state_04 = 0x18;
                            func_801BE1B0(0xD);
                            return 1;
                    }
                }
            } else if ((x == TO_COORD_HALF(41) || x == TO_COORD_HALF(42)) && (u32)(y - TO_COORD(80)) <= TO_COORD(4)) {
                u8* phase = &g_ScriptVars[1];

                switch (*phase) {
                    case 0:
                        Game_SetScriptActive();
                        g_ScriptVars[0]          = 0;
                        *phase                   = 0;
                        g_ScenarioState.step     = 0xA;
                        g_ScriptVars[2]          = 0;
                        g_ScriptVars[3]          = 0;
                        g_ScenarioState.state_04 = 0x18;
                        func_801BE1B0(0xD);
                        return 1;
                    case 1:
                        Game_SetScriptActive();
                        g_ScriptVars[0]          = 1;
                        *phase                   = 0;
                        g_ScenarioState.step     = 0x14;
                        g_ScriptVars[2]          = 0;
                        g_ScriptVars[3]          = 0;
                        g_ScenarioState.state_04 = 0x18;
                        func_801BE1B0(0xD);
                        return 1;
                }
            }
        }
    }
    if (g_GameAreaId == AREA_ID_MCNEIL_MANOR) {
        if ((x == TO_COORD_HALF(39) || x == TO_COORD_HALF(40)) && (u32)(y - TO_COORD(37)) <= TO_COORD_HALF(2)) {
            Game_SetScriptActive();
            g_ScenarioState.step     = 0;
            g_ScenarioState.state_04 = 0x1B;
            return 1;
        }
        if (g_Game.party_size == 2 && !SYS_TestFlag(g_SceneFlags, 0xF) && (u32)(x - TO_COORD(27)) <= TO_COORD_HALF(1) && y == TO_COORD_HALF(28)) {
            g_ScenarioState.step     = 0;
            g_ScenarioState.state_04 = 0xA;
            return 1;
        }
        if (!SYS_TestFlag(g_SceneFlags, 0x10) && (u32)(x - TO_COORD_HALF(23)) <= TO_COORD(1) && (u32)(y - TO_COORD(37)) <= TO_COORD_HALF(2)) {
            Game_SetScriptActive();
            g_ScenarioState.step     = 5;
            g_ScriptVars[0]          = 0;
            g_ScenarioState.state_04 = 0xA;
            return 1;
        }
        if (!SYS_TestFlag(g_SceneFlags, 0x11) && (u32)(x - TO_COORD(9)) <= TO_COORD_HALF(2) && (u32)(y - TO_COORD(64)) <= TO_COORD_HALF(1)) {
            Game_SetScriptActive();
            g_ScriptVars[0]          = 0x14;
            g_ScenarioState.step     = 0;
            g_ScenarioState.state_04 = 0xC;
            return 1;
        }
        if (!SYS_TestFlag(g_SceneFlags, 0x13) && x == TO_COORD_HALF(13) && (u32)((y >> 16) - 3) < 2) {
            g_ScriptVars[0]          = 0x25;
            g_ScenarioState.step     = 0;
            g_ScenarioState.state_04 = 0xD;
            Game_SetScriptActive();
            return 1;
        }
        if (!SYS_TestFlag(g_SceneFlags, 0x14) && (u32)(x - TO_COORD(57)) <= TO_COORD_HALF(2) && (u32)(y - TO_COORD(72)) <= TO_COORD(1)) {
            Game_SetScriptActive();
            g_ScriptVars[0]          = 0x31;
            g_ScenarioState.step     = 0;
            g_ScenarioState.state_04 = 0xE;
            return 1;
        }
        if (!SYS_TestFlag(g_SceneFlags, 0x18) && (u32)(y - TO_COORD(52)) <= TO_COORD_HALF(1) && x == TO_COORD_HALF(32)) {
            g_ScenarioState.step     = 0xA;
            g_ScriptVars[0]          = 0;
            g_ScenarioState.state_04 = 0xF;
            return 1;
        }
    }
    if (g_GameAreaId == AREA_ID_MCNEIL_MANOR_ROOF) {
        if (!SYS_TestFlag(g_SceneFlags, 0x19) && (x == TO_COORD(35) || x == TO_COORD_HALF(35)) && (u32)(y - TO_COORD(95)) <= TO_COORD(1)) {
            Game_SetScriptActive();
            g_ScenarioState.step     = 0;
            g_ScenarioState.state_04 = 0x11;
            return 1;
        }
    }
    return 0;
}

/* func_801FE178 */
MATCH void Party_JoinRei(void) {
    Party_MemberJoin(CHAR_ID_REI);
}

#include "overlays/scenario/shared/Scene_RemoveRei.h"

/* Scene_RemoveReiTeepo */
/* func_801FE1C0 */
MATCH void Scene_RemoveReiTeepo(void) {
    g_Characters[g_CharSlot[CHAR_ID_REI]].party_flags &= ~PARTY_FLAG_JOINED;
    g_Characters[g_CharSlot[CHAR_ID_TEEPO]].party_flags &= ~PARTY_FLAG_JOINED;
    Party_MemberRemove(CHAR_ID_REI);
    Party_MemberRemove(CHAR_ID_TEEPO);
    Party_LoadPalettes();
}
