#include "scena15_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FDB84(void) {
    if (D_801FE74C == 0) {
        g_ScriptVars[1] = 1;
        D_801FE74C      = (RANDOM_MOD(38) + 42) / 2;
    } else {
        D_801FE74C--;
    }
}

MATCH void func_801FDC10(s32 shift) {
    s32 offset;

    if (D_801FE750 != 0) {
        offset                   = D_801FE6E8[g_FrameCount & 0x3];
        g_AreaCameraRefreshCount = 2;
        g_AreaCameraOffsetY += offset << shift;
    }
}

MATCH s32 func_801FDC6C(s32 x, s32 y, s32 unk_06, s32 unk_07, u8 link) {
    u8 slot;

    slot = Actor_FindFreeSpawned();
    if (slot != GAME_NONE) {
        g_SpawnedActors[slot].header.flags = 1;
        g_SpawnedActors[slot].pos.x.fixed  = x;
        g_SpawnedActors[slot].type         = 0x9E;
        g_SpawnedActors[slot].pos.y.fixed  = y;
        g_SpawnedActors[slot].pos.z.fixed  = (Area_HeightSample(g_SpawnedActors[slot].pos.x.fixed, y) << 16) + TO_COORD(512);
        g_SpawnedActors[slot].unk_06       = unk_06;
        g_SpawnedActors[slot].unk_07       = unk_07;
        g_SpawnedActors[slot].link         = link;
        return 1;
    }
    return 0;
}

#include "overlays/scenario/shared/Scene_DispatchActor.h"

/* func_801FDDC0 */
MATCH void Scene_ShowEntityMessage(void* entity) {
    u8 message;

    message = D_801FE71C[((Actor*)entity)->callback_index];
    if (g_GameAreaId == AREA_ID_DESERT_CAMP_SECOND) {
        UI_MessageStartArea(func_801F326C(message));
    } else {
        UI_MessageStartArea(func_801F37AC(message));
    }
    g_GameStateIndex = GAME_REQUEST_MESSAGE;
}

MATCH void func_801FDE2C(void) {
    Game_SetScriptActive();
    g_ScenarioState.state_04 = 3;
    g_ScenarioState.step_05  = 0x32;
}

MATCH void func_801FDE64(void* entity) {
    Actor* actor;

    actor = entity;
    Game_SetScriptActive();
    SYS_SetFlag(g_SceneFlags, 13);
    Scene_SetupParty(11);
    actor->unk_7E = actor->unk_7E + 1;
}

MATCH void func_801FDEB4(void* entity) {
    Actor* actor;

    actor = entity;
    Game_SetScriptActive();
    SYS_SetFlag(g_SceneFlags, 14);
    Scene_SetupParty(12);
    actor->unk_7E = actor->unk_7E + 1;
}

MATCH void func_801FDF04(void* entity) {
    Actor* actor;

    actor = entity;
    Game_SetScriptActive();
    SYS_SetFlag(g_SceneFlags, 12);
    actor->unk_7E = actor->unk_7E + 1;
}

MATCH void func_801FDF4C(void* entity) {
    Actor* actor;

    actor = entity;
    Game_SetScriptActive();
    SYS_SetFlag(g_SceneFlags, 16);
    Scene_SetupParty(14);
    actor->unk_7E = actor->unk_7E + 1;
}

MATCH void func_801FDF9C(void* entity) {
    Actor* actor;

    actor = entity;
    Game_SetScriptActive();
    SYS_SetFlag(g_SceneFlags, 15);
    Scene_SetupParty(13);
    actor->unk_7E = actor->unk_7E + 1;
}

MATCH void func_801FDFEC(void* entity) {
    Actor* actor;

    actor = entity;
    Game_SetScriptActive();
    actor->unk_7E = actor->unk_7E + 1;
}

MATCH s32 func_801FE024(s32 x, s32 y) {
    if (g_GameAreaId == AREA_ID_MYRIA_STATION_AFTER_SAMPLES) {
        if (g_GameCellType == 1) {
            if (SYS_TestFlag(g_SceneFlags, 1) == 0 && y > TO_COORD(71)) {
                Game_SetScriptActive();
                g_ScenarioState.state_04 = 3;
                g_ScenarioState.step_05  = 15;
            }
        }
        if (g_GameCellType == 2) {
            if (SYS_TestFlag(g_SceneEventFlags, 0x81) == 0 && (x >> 16) >= 45 && (u32)((y >> 16) - 120) < 8) {
                Game_SetScriptActive();
                g_ScenarioState.state_04 = 3;
                g_ScenarioState.step_05  = 0;
            }
        }
    }
    if (g_GameAreaId == AREA_ID_MYRIA_STATION_MYRIA_ROOM && g_GameCellType == 0 && x == TO_COORD(65) + COORD_HALF && (u32)((y >> 16) - 34) < 3) {
        Game_SetScriptActive();
        g_ScenarioState.state_04 = 4;
        g_ScenarioState.step_05  = 0;
        return 1;
    }
    return 0;
}

MATCH s32 func_801FE18C(s32 x, s32 y) {
    if (g_GameAreaId == 0xAE) {
        if (SYS_TestFlag(g_SceneFlags, 2) == 0) {
            if (x > 4456447 && (u32)((y >> 16) - 3) < 2) {
                Game_SetScriptActive();
                g_ScenarioState.state_04 = 3;
                g_ScenarioState.step_05  = 0x14;
            }
            return 0;
        }
        if (SYS_TestFlag(g_SceneFlags, 4) == 0) {
            if (x <= 5439488 && (u32)((y >> 16) - 0x2E) < 3) {
                Game_SetScriptActive();
                g_ScenarioState.state_04 = 3;
                g_ScenarioState.step_05  = 0x1E;
            }
            return 0;
        }
        if (SYS_TestFlag(g_SceneFlags, 5) == 0) {
            if (y <= 3801088 && (u32)((x >> 16) - 0x23) < 4) {
                Game_SetScriptActive();
                g_ScenarioState.state_04 = 3;
                g_ScenarioState.step_05  = 0x28;
            }
            return 0;
        }
        if (x == 3211264 && (u32)((y >> 16) - 0x27) < 2) {
            if (SYS_TestFlag(g_SceneFlags, 12) && SYS_TestFlag(g_SceneFlags, 14) && SYS_TestFlag(g_SceneFlags, 13) && SYS_TestFlag(g_SceneFlags, 15) && SYS_TestFlag(g_SceneFlags, 16)) {
                Game_SetScriptActive();
                g_ScenarioState.state_04 = 5;
                g_ScenarioState.step_05  = 5;
            } else {
                Game_SetScriptActive();
                g_ScenarioState.state_04 = 5;
                g_ScenarioState.step_05  = 0;
            }
        }
    }
    return 0;
}

MATCH void func_801FE3C8(void) {
    u8 ids[PARTY_SLOT_COUNT];
    u8 slot;

    for (slot = 0; slot < g_PartySize; slot++) {
        ids[slot] = g_Game.members[slot].chr.character_id;
    }
    for (slot = 0; slot < PARTY_SLOT_COUNT; slot++) {
        Party_MemberRemove(ids[slot]);
    }
    EMI_PartyLoadArchives(CHAR_ID_RYU_ADULT, CHAR_ID_REI, CHAR_ID_GARR, 0);
    g_PartySize = 0;
    Party_MemberJoin(CHAR_ID_RYU_ADULT);
    Party_LoadPalettes();
}

MATCH void func_801FE49C(void) {
    Party_MemberJoin(CHAR_ID_REI);
    Party_MemberJoin(CHAR_ID_GARR);
    Party_LoadPalettes();
}

MATCH void Scene_SetPartyRyuAdultNinaAdultGarr(void) {
    SCENE_SET_PARTY(CHAR_ID_RYU_ADULT, CHAR_ID_NINA_ADULT, CHAR_ID_GARR);
}

#include "overlays/scenario/shared/Scene_SetPartyRyuAdultNinaAdultRei.h"

MATCH void func_801FE574(void) {
}
