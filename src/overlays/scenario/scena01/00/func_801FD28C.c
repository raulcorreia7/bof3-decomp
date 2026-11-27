#include "scena01_00.h"
#include "area/map.h"
#include "overlays/area/shared/Area_DrawDimQuad.h"
#include "overlays/area/shared/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* Give the lead party member a field actor of type 6: claim a free slot and seed its row from the member. */
MATCH void func_801FD28C(s32 variant){ACTOR_SEED_PARTY_SLOT(0, D_801FE280, 6, variant + 112)}

MATCH void func_801FD444(void* record) {
    D_801FE308[((Actor*)record)->callback_index](record, &D_80144E90);
}

MATCH void func_801FD484(void) {
}

MATCH void func_801FD48C(void) {
    if (SYS_TestFlag(g_SceneFlags, 20) == 0) {
        *g_ScriptVars = 0;
        Game_SetScriptActive();
        g_ScenarioState.step     = 0;
        g_ScenarioState.state_04 = 0x12;
        SYS_SetFlag(g_SceneFlags, 20U);
    }
}

MATCH void func_801FD4F0(void) {
    Game_SetScriptActive();
    g_ScriptVars[1]          = 0;
    g_ScriptVars[2]          = 0;
    g_ScenarioState.step     = 0;
    g_ScenarioState.state_04 = 23;
}

MATCH void func_801FD534(void) {
    Game_SetScriptActive();
    g_ScenarioState.step     = 5;
    g_ScriptVars[1]          = 0;
    g_ScriptVars[2]          = 0;
    g_ScenarioState.state_04 = 23;
}

MATCH void func_801FD57C(void) {
    Game_SetScriptActive();
    g_ScenarioState.step     = 2;
    g_ScriptVars[1]          = 0;
    g_ScriptVars[2]          = 0;
    g_ScenarioState.state_04 = 23;
}

MATCH void func_801FD5C4(void) {
    Game_SetScriptActive();
    g_ScenarioState.step     = 2;
    g_ScriptVars[1]          = 0;
    g_ScriptVars[2]          = 0;
    g_ScenarioState.state_04 = 17;
}

MATCH void func_801FD60C(Actor* actor) {
    Game_SetScriptActive();
    g_ScriptVars[0]        = 10;
    g_ScriptVars[1]        = 0;
    g_ScriptVars[2]        = 0;
    actor->header.mode     = 4;
    actor->unk_7E          = 0;
    actor->unk_7B          = 0;
    actor->unk_77          = 10;
    SELF(Actor)->direction = g_Game.members[0].facing ^ 4;
    Script_DispatchSelector(SELF(Actor)->direction);
    SELF(Actor)->option_flags |= ACTOR_OPT_ROUTE_LOCKED;
    g_ScenarioState.step     = 10;
    g_ScenarioState.state_04 = 13;
}

MATCH void func_801FD6CC(Actor* actor) {
    Game_SetScriptActive();
    actor->header.mode     = 4;
    actor->unk_7B          = 0;
    actor->unk_77          = 0xA;
    SELF(Actor)->direction = g_Game.members[0].facing ^ 0x4;
    Script_DispatchSelector(SELF(Actor)->direction);
    SELF(Actor)->option_flags |= ACTOR_OPT_ROUTE_LOCKED;
    SCRIPT_VARS_CLEAR_ALL();
    g_ScenarioState.step     = 13;
    g_ScenarioState.state_04 = 13;
}

MATCH void func_801FD788(Actor* actor) {
    Game_SetScriptActive();
    actor->header.mode     = 4;
    actor->unk_7E          = 0;
    actor->unk_7B          = 0;
    actor->unk_77          = 11;
    SELF(Actor)->direction = g_Game.members[0].facing ^ 4;
    Script_DispatchSelector(SELF(Actor)->direction);
    SELF(Actor)->option_flags |= ACTOR_OPT_ROUTE_LOCKED;
    g_ScenarioState.step = 16;
    SCRIPT_VARS_CLEAR_ALL();
    g_ScenarioState.state_04 = 13;
}

MATCH void func_801FD84C(Actor* actor) {
    Game_SetScriptActive();
    actor->header.mode     = 4;
    actor->unk_7E          = 0;
    actor->unk_7B          = 0;
    actor->unk_77          = 0xB;
    SELF(Actor)->direction = g_Game.members[0].facing ^ 0x4;
    Script_DispatchSelector(SELF(Actor)->direction);
    SELF(Actor)->option_flags |= ACTOR_OPT_ROUTE_LOCKED;
    g_ScenarioState.step     = 16;
    g_ScriptVars[3]          = 0;
    g_ScenarioState.state_04 = 13;
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
    g_ScenarioState.step = 40;
    SCRIPT_VARS_CLEAR_ALL();
    g_ScenarioState.state_04 = 9;
}

MATCH void func_801FD9A0(void) {
    Game_SetScriptActive();
    g_ScriptVars[1]          = 0;
    g_ScriptVars[2]          = 0;
    g_ScenarioState.step     = 0;
    g_ScenarioState.state_04 = 17;
}

MATCH void func_801FD9E4(void) {
    Game_SetScriptActive();
    g_ScenarioState.step     = 5;
    g_ScriptVars[1]          = 0;
    g_ScriptVars[2]          = 0;
    g_ScenarioState.state_04 = 17;
}

MATCH void func_801FDA2C(void) {
    Game_SetScriptActive();
    g_ScenarioState.step     = 0xF;
    g_ScenarioState.state_04 = 0xB;
}

MATCH s32 func_801FDA64(void) {
    return 0;
}

/* func_801FDA6C */
MATCH s32 Scenario_TryStartPositionEvent(s32 x, s32 y) {
    if (g_GameAreaId == AREA_ID_CEDAR_WOODS_HOUSE_BEFORE_NUE) {
        if (SYS_TestFlag(g_SceneFlags, 28) == 0 && x == TO_COORD_HALF(105) && (u32)((y >> 16) - 6) < 2U) {
            Game_SetScriptActive();
            g_ScenarioState.step     = 0;
            g_ScenarioState.state_04 = 20;
            return 1;
        }
    }
    if (g_GameAreaId == AREA_ID_MCNEIL_BEFORE_NUE) {
        if (SYS_TestFlag(g_SceneFlags, 27) == 0) {
            if ((x == TO_COORD(1) || x == COORD_HALF) && (u32)(y - TO_COORD(19)) <= TO_COORD_HALF(2)) {
                Game_SetScriptActive();
                g_ScenarioState.step     = 10;
                g_ScenarioState.state_04 = 11;
                return 1;
            } else if ((u32)(x - TO_COORD(21)) <= TO_COORD_HALF(1)) {
                if (y == TO_COORD(1) || y == COORD_HALF) {
                    Game_SetScriptActive();
                    g_ScenarioState.step     = 10;
                    g_ScenarioState.state_04 = 11;
                    return 1;
                }
            }
            if ((u32)(y - TO_COORD(24)) <= TO_COORD_HALF(1)) {
                if (x == TO_COORD(39) || x == TO_COORD_HALF(39)) {
                    Game_SetScriptActive();
                    g_ScenarioState.step     = 10;
                    g_ScenarioState.state_04 = 11;
                    return 1;
                }
            }
        }
    }
    if (g_GameAreaId == AREA_ID_CEDAR_WOODS_BUNYAN_BEFORE_NUE) {
        if (SYS_TestFlag(g_SceneFlags, 6) == 0) {
            if (x == TO_COORD_HALF(84) && (u32)((y >> 16) - 28) < 2U) {
                Game_SetScriptActive();
                SND_SEPlay(0x202);
                g_ScenarioState.state_04 = 21;
                return 1;
            }
        } else if (SYS_TestFlag(g_SceneFlags, 5) == 0 && (u32)(x - TO_COORD_HALF(85)) <= TO_COORD(1) && (u32)(y - TO_COORD(28)) <= TO_COORD_HALF(1)) {
            Game_SetScriptActive();
            g_GameFlags = (g_GameFlags ^ 6) & 0xFF7F;
            func_8019FA28(8, TO_COORD(52), TO_COORD_HALF(23), 0x83);
            return 1;
        }
    }
    if (g_GameAreaId == AREA_ID_YRAAL_ROAD_BEFORE_NUE) {
        if (SYS_TestFlag(g_SceneFlags, 27) != 0 && SYS_TestFlag(g_SceneFlags, 2) == 0 && (u32)(x - TO_COORD(26)) <= TO_COORD_HALF(2) && (u32)(y - TO_COORD(26)) <= TO_COORD_HALF(3)) {
            Game_SetScriptActive();
            g_ScriptVars[0]          = 30;
            g_ScenarioState.step     = 0;
            g_ScenarioState.state_04 = 3;
            return 1;
        }
        if (SYS_TestFlag(g_SceneFlags, 2) != 0 && SYS_TestFlag(g_SceneFlags, 3) == 0 && x == TO_COORD(22) && (u32)(y - TO_COORD(12)) <= TO_COORD_HALF(1)) {
            Game_SetScriptActive();
            g_ScenarioState.step     = 10;
            g_ScriptVars[0]          = 0;
            g_ScenarioState.state_04 = 3;
            return 1;
        }
    }
    if (g_GameAreaId == AREA_ID_MOUNT_GLAUS) {
        if (SYS_TestFlag(g_SceneFlags, 10) == 0 && (u32)(y - TO_COORD_HALF(12)) <= TO_COORD(1) && (u32)(x - TO_COORD(72)) <= TO_COORD_HALF(1)) {
            Game_SetScriptActive();
            g_ScriptVars[0] = 0;
            g_ScriptVars[2] = 7;
            func_8019FA28(23, TO_COORD(24), TO_COORD(24), 0x82);
            return 1;
        }
    }
    if (g_GameAreaId == AREA_ID_NUE_CAVE) {
        if (SYS_TestFlag(g_SceneFlags, 12) != 0) {
            if (SYS_TestFlag(g_SceneFlags, 13) == 0) {
                if ((u32)(y - TO_COORD_HALF(31)) <= COORD_HALF && (u32)(x - TO_COORD(81)) <= TO_COORD(1)) {
                    g_ScriptVars[0]      = 0;
                    g_ScenarioState.step = 8;
                    func_8019FA28(22, TO_COORD_HALF(5), TO_COORD(20), 0x80);
                    return 1;
                }
            } else if (SYS_TestFlag(g_SceneFlags, 15) == 0) {
                if ((x == TO_COORD_HALF(2) || x == TO_COORD(48)) && (u32)(y - TO_COORD(7)) <= TO_COORD_HALF(1)) {
                    Game_SetScriptActive();
                    g_ScriptVars[0]      = 0;
                    g_ScenarioState.step = 11;
                    func_8019FA28(22, TO_COORD(69), TO_COORD_HALF(11), 0x81);
                    return 1;
                }
            } else {
                if (SYS_TestFlag(g_SceneFlags, 18) == 0 && SYS_TestFlag(g_SceneFlags, 16) == 0 && x == TO_COORD(61) && (u32)(y - TO_COORD(10)) <= TO_COORD_HALF(1)) {
                    Game_SetScriptActive();
                    g_ScenarioState.step = 18;
                    return 1;
                }
            }
        }
    }
    if (g_GameAreaId == AREA_ID_BEFORE_MOUNT_GLAUS_BEFORE_NUE) {
        if ((x == TO_COORD(1) || x == TO_COORD_HALF(1)) && (u32)(y - TO_COORD(17)) <= TO_COORD_HALF(1)) {
            SYS_SetFlag(g_SceneFlags, 24);
        }
    }
    return 0;
}

MATCH s8 func_801FE03C(s32 x, s32 y) {
    SCENE_PROBE_POSITION(D_801FE350, 2, D_801FE35C);
}

MATCH s32 func_801FE0A4(void) {
    if (SYS_TestFlag(g_SceneFlags, 3) == 0 || SYS_TestFlag(g_SceneFlags, 4)) {
        return -1;
    }

    Game_SetScriptActive();
    g_ScenarioState.step     = 0;
    g_ScenarioState.state_04 = 5;
    return 1;
}

/* func_801FE10C */
MATCH void Scene_InitOpeningParty(void) {
    g_Characters[g_CharSlot[10]].party_flags &= ~PARTY_FLAG_JOINED;
    EMI_PartyLoadArchives(CHAR_ID_RYU_PAJAMAS, CHAR_ID_TEEPO, CHAR_ID_REI, 0);
    g_Game.party_size                        = 0;
    g_Characters[g_CharSlot[9]].character_id = CHAR_ID_RYU_PAJAMAS;
    Party_MemberJoin(CHAR_ID_RYU_PAJAMAS);
}

/* func_801FE1B0 */
MATCH void Scene_SetPartyRyuTeepoRei(void) {
    g_Characters[g_CharSlot[0]].character_id = CHAR_ID_RYU_YOUNG;
    EMI_PartyLoadArchives(CHAR_ID_RYU_YOUNG, CHAR_ID_TEEPO, CHAR_ID_REI, 0);
    g_Game.party_size = 0;
    Party_MemberJoin(CHAR_ID_RYU_YOUNG);
    Party_MemberJoin(CHAR_ID_TEEPO);
    Party_MemberJoin(CHAR_ID_REI);
}

/* func_801FE224 */
MATCH void Party_JoinRei(void) {
    Party_MemberJoin(CHAR_ID_REI);
}

#include "overlays/scenario/shared/Scene_RemoveRei.h"
