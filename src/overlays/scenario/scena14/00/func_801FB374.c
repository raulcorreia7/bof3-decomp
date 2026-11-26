#include "scena14_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FB374(void) {
}

#include "overlays/scenario/shared/Scene_DispatchActor.h"

/* Starts the area message `message`: the area overlay's own lookup (func_801F326C
 * for the second desert camp, func_801F37AC otherwise) maps it to a message index. */
#define SCENA14_START_AREA_MESSAGE(message)                 \
    if (LOHU(g_GameAreaId) == AREA_ID_DESERT_CAMP_SECOND) { \
        UI_MessageStartArea(func_801F326C(message));        \
    } else {                                                \
        UI_MessageStartArea(func_801F37AC(message));        \
    }                                                       \
    g_GameStateIndex = GAME_REQUEST_MESSAGE

MATCH void func_801FB3BC(void) {
    SCENA14_START_AREA_MESSAGE(MSG_SCENA14_008);
}

MATCH void func_801FB414(void) {
    SCENA14_START_AREA_MESSAGE(MSG_SCENA14_004);
}

MATCH void func_801FB46C(void) {
    SCENA14_START_AREA_MESSAGE(MSG_SCENA14_002);
}

MATCH void func_801FB4C4(void) {
    SCENA14_START_AREA_MESSAGE(MSG_SCENA14_005);
}

MATCH void func_801FB51C(void) {
    SCENA14_START_AREA_MESSAGE(MSG_SCENA14_006);
}

MATCH void func_801FB574(void) {
    Game_SetScriptActive();
    g_ScenarioState.state_04 = 5;
    g_ScenarioState.step     = 5;
}

MATCH void func_801FB5A8(void* entity) {
    Actor* actor;

    actor = entity;
    Game_SetScriptActive();
    g_ScenarioState.state_04 = 5;
    g_ScenarioState.step     = 30;
    actor->unk_7E            = actor->unk_7E + 1;
}

MATCH void func_801FB5F8(void* entity) {
    Actor* actor;

    actor = entity;
    Game_SetScriptActive();
    g_ScenarioState.state_04 = 7;
    g_ScenarioState.step     = 30;
    actor->unk_7E            = actor->unk_7E + 1;
}

MATCH s32 func_801FB648(s32 x, s32 y) {
    s32 map_x;
    s32 map_y;
    u8  cell_count;
    u8  origin_hit;
    s32 cell_code;

    if (LOHU(g_GameAreaId) == 0x94 && g_GameCellType == 4 && !SYS_TestFlag(g_SceneFlags, 0x10) && x == 0x738000 && (u32)((y >> 16) - 0x36) < 2) {
        Game_SetScriptActive();
        g_ScenarioState.state_04 = 4;
        g_ScenarioState.step     = 0;
        return 1;
    }

    if (LOHU(g_GameAreaId) == 0xBF && SYS_TestFlag(g_SceneFlags, 5)) {
        map_x      = x >> 16;
        map_y      = y >> 16;
        cell_count = origin_hit = (u8)Area_CellGetCode(map_x, map_y) == 0xA6;
        cell_code               = 0xA6;
        if ((u16)x != 0 && (u8)Area_CellGetCode((s16)(map_x + 1), map_y) == cell_code) {
            cell_count++;
        }
        if ((u16)y != 0 && (u8)Area_CellGetCode(x >> 16, (s16)((y >> 16) + 1)) == 0xA6) {
            cell_count++;
        }
        if ((u16)x != 0 && (u16)y != 0 && (u8)Area_CellGetCode((s16)((x >> 16) + 1), (s16)((y >> 16) + 1)) == 0xA6) {
            cell_count++;
        }
        if (cell_count != 0) {
            Game_SetScriptActive();
            g_ScenarioState.state_04 = 2;
            g_ScenarioState.step     = 20;
            return 1;
        }
    }
    return 0;
}

MATCH s32 func_801FB84C(s32 x, s32 y) {
    if (LOHU(g_GameAreaId) == AREA_ID_RYU_DREAM_FIRST) {
        if (g_GameCellType == 0) {
            if (!SYS_TestFlag(g_SceneFlags, 21)) {
                if (x < TO_COORD_HALF(79) && (u32)((y >> 16) - 7) < 8) {
                    Game_SetScriptActive();
                    g_ScenarioState.state_04 = 7;
                    g_ScenarioState.step     = 0;
                }
            } else if (!SYS_TestFlag(g_SceneFlags, 22)) {
                if (x < TO_COORD_HALF(73) && (u32)((y >> 16) - 9) < 4) {
                    Game_SetScriptActive();
                    g_ScenarioState.state_04 = 7;
                    g_ScenarioState.step     = 1;
                }
            } else if (!SYS_TestFlag(g_SceneFlags, 23)) {
                if (x < TO_COORD_HALF(64) && (u32)((y >> 16) - 9) < 4) {
                    Game_SetScriptActive();
                    g_ScenarioState.state_04 = 7;
                    g_ScenarioState.step     = 2;
                }
            }
        }
        if (g_GameCellType == 1 && SYS_TestFlag(g_SceneEventFlags, 0x7A)) {
            if (!SYS_TestFlag(g_SceneFlags, 25)) {
                if (x < TO_COORD_HALF(57) && (u32)((y >> 16) - 0x31) < 4) {
                    Game_SetScriptActive();
                    g_ScenarioState.state_04 = 7;
                    g_ScenarioState.step     = 3;
                }
            } else if (!SYS_TestFlag(g_SceneFlags, 26)) {
                if (x < TO_COORD_HALF(45) && (u32)((y >> 16) - 0x31) < 4) {
                    Game_SetScriptActive();
                    g_ScenarioState.state_04 = 7;
                    g_ScenarioState.step     = 4;
                }
            }
        }
    }
    if (LOHU(g_GameAreaId) == AREA_ID_RYU_DREAM_LAST) {
        if (g_GameCellType == 1) {
            if (!SYS_TestFlag(g_SceneFlags, 28) && y < TO_COORD_HALF(29) && (u32)((x >> 16) - 0x13) < 4) {
                Game_SetScriptActive();
                g_ScenarioState.state_04 = 7;
                g_ScenarioState.step     = 5;
            }
        }
        if (g_GameCellType == 3 && !SYS_TestFlag(g_SceneFlags, 31) && x < TO_COORD_HALF(44) && (u32)((y >> 16) - 0x26) < 4) {
            Game_SetScriptActive();
            SND_SeqStop(0, 0);
            SND_BGMRequest(0x9F);
            g_ScenarioState.state_04 = 7;
            g_ScenarioState.step     = 10;
        }
    }
    if (LOHU(g_GameAreaId) == AREA_ID_CAER_XHAN_LIFT_AREA && g_GameCellType == 0 && !SYS_TestFlag(g_SceneFlags, 17) && (y >> 16) == 0x1C && (u32)((x >> 16) - 0x12) < 3) {
        Game_SetScriptActive();
        g_ScenarioState.state_04 = 4;
        g_ScenarioState.step     = 10;
        return 1;
    }
    if (LOHU(g_GameAreaId) == AREA_ID_EDEN_TEEPO_FIGHT && g_GameCellType == 0) {
        if (!SYS_TestFlag(g_SceneFlags, 19) && x < TO_COORD_HALF(11) && (u32)((y >> 16) - 0x3F) < 2) {
            Game_SetScriptActive();
            g_ScenarioState.state_04 = 6;
            g_ScenarioState.step     = 10;
        }
    }
    if (LOHU(g_GameAreaId) == AREA_ID_DESERT_CAMP_FIRST && g_GameCellType == 0) {
        if ((u32)((x >> 16) - 0x1D) < 5 && (u32)((y >> 16) - 0x14) < 2 && SYS_TestFlag(g_SceneFlags, 8) && !SYS_TestFlag(g_SceneFlags, 9)) {
            Game_SetScriptActive();
            g_ScenarioState.state_04 = 2;
            g_ScenarioState.step     = 0x1D;
            return 1;
        }
    }
    return 0;
}

MATCH void Scene_JoinPartyRyuAdultReiNinaAdult(void) {
    EMI_PartyLoadArchives(CHAR_ID_RYU_ADULT, CHAR_ID_NINA_ADULT, CHAR_ID_REI, 0);
    g_Game.party_size = 0;
    Party_MemberJoin(CHAR_ID_RYU_ADULT);
    Party_MemberJoin(CHAR_ID_REI);
    Party_MemberJoin(CHAR_ID_NINA_ADULT);
}

MATCH void Scene_SetPartyRyuAdultReiPeco(void) {
    SCENE_SET_PARTY_NO_RESTAGE(CHAR_ID_RYU_ADULT, CHAR_ID_REI, CHAR_ID_PECO);
}

MATCH void Scene_SetPartyRyuAdultMomoPeco(void) {
    SCENE_SET_PARTY_NO_RESTAGE(CHAR_ID_RYU_ADULT, CHAR_ID_MOMO, CHAR_ID_PECO);
}

MATCH void func_801FBE10(void) {
    u8 ids[3];
    u8 slot;

    for (slot = 0; slot < 3; slot++) {
        if (g_Game.members[slot].chr.character_id != CHAR_ID_RYU_ADULT && g_Game.members[slot].chr.character_id != CHAR_ID_REI) {
            D_80144908[0] = g_Game.members[slot].chr.character_id;
        }
        ids[slot] = g_Game.members[slot].chr.character_id;
    }
    for (slot = 0; slot < 3; slot++) {
        Party_MemberRemove(ids[slot]);
    }
    EMI_PartyLoadArchives(CHAR_ID_WHELP, CHAR_ID_BLANK, CHAR_ID_BLANK, 0);
    g_Game.party_size = 0;
    Party_MemberJoin(CHAR_ID_WHELP);
    Party_LoadPalettes();
}

MATCH void func_801FBF18(void) {
    g_Characters[g_CharSlot[10]].party_flags &= 0xFE;
    EMI_PartyLoadArchives(CHAR_ID_RYU_ADULT, CHAR_ID_REI, CHAR_ID_NINA_ADULT, 0);
    g_Game.party_size = 0;
    Party_MemberJoin(CHAR_ID_RYU_ADULT);
    Party_MemberJoin(CHAR_ID_REI);
    Party_MemberJoin(CHAR_ID_NINA_ADULT);
    Party_LoadPalettes();
}

MATCH void func_801FBFA8(void) {
    EMI_PartyLoadArchives(CHAR_ID_RYU_YOUNG, CHAR_ID_NINA_YOUNG, CHAR_ID_MOMO, 0);
    g_Game.party_size = 0;
    Party_MemberJoin(CHAR_ID_RYU_YOUNG);
    Party_MemberJoin(CHAR_ID_NINA_YOUNG);
    Party_MemberJoin(CHAR_ID_MOMO);
    Party_LoadPalettes();
    g_PartyBattleOrder[0] = 7;
    D_80144F5E[0]         = 8;
    D_80144F5F            = 5;
}

MATCH void Scene_SetPartyRyuAdultGarrPeco(void) {
    SCENE_SET_PARTY(CHAR_ID_RYU_ADULT, CHAR_ID_GARR, CHAR_ID_PECO);
}

#include "overlays/scenario/shared/Scene_SetPartyRyuAdultGarrNinaAdult.h"

MATCH void func_801FC0C8(void) {
    EMI_PartyLoadArchives(CHAR_ID_RYU_ADULT, CHAR_ID_REI, *D_80144908, 0U);
    g_Game.party_size = 0;
    Party_MemberJoin(CHAR_ID_RYU_ADULT);
    Party_MemberJoin(CHAR_ID_REI);
    Party_MemberJoin(*D_80144908);
    Party_LoadPalettes();
}

MATCH void func_801FC130(void) {
    u8 slot;
    /* FAKE: the retail frame holds 8 bytes no statement explains. */
    FAKE_STACK_PADS(u8, 8);

    for (slot = 0; slot < 3; slot++) {
        D_80144908[slot] = g_Game.members[slot].chr.character_id;
    }
    for (slot = 0; slot < 3; slot++) {
        Party_MemberRemove(D_80144908[slot]);
    }
    EMI_PartyLoadArchives(CHAR_ID_RYU_ADULT, CHAR_ID_NINA_ADULT, CHAR_ID_REI, 0);
    g_Game.party_size = 0;
    Party_MemberJoin(CHAR_ID_RYU_ADULT);
    Party_LoadPalettes();
}

MATCH void func_801FC1E8(void) {
    EMI_PartyLoadArchives(CHAR_ID_RYU_ADULT, CHAR_ID_GARR, CHAR_ID_PECO, 0);
    g_Game.party_size = 0;
    Party_MemberJoin(CHAR_ID_RYU_ADULT);
    Party_LoadPalettes();
}

#include "overlays/scenario/shared/Scene_SetPartyRyuAdultNinaAdultRei.h"

MATCH void func_801FC280(void) {
    u8 slot;
    u8 character;

    for (slot = 0; slot < 3; slot++) {
        character = D_80144908[slot];
        if (character != CHAR_ID_RYU_ADULT && character != CHAR_ID_REI) {
            break;
        }
    }
    EMI_PartyLoadArchives(CHAR_ID_RYU_ADULT, CHAR_ID_REI, character, 0);
    g_Game.party_size = 0;
    Party_MemberJoin(CHAR_ID_RYU_ADULT);
    Party_MemberJoin(CHAR_ID_REI);
    Party_MemberJoin(character);
    Party_LoadPalettes();
}

MATCH void func_801FC328(void) {
    u8 ids[PARTY_SLOT_COUNT];
    u8 slot;
    u8 count;

    slot  = 0;
    count = 0;
    for (; slot < PARTY_SLOT_COUNT; slot++) {
        if (g_Game.members[slot].header.flags & PARTY_MEMBER_FLAG_OCCUPIED) {
            count++;
        }
        ids[slot] = g_Game.members[slot].chr.character_id;
    }
    g_Game.party_size = count;
    for (slot = 0; slot < PARTY_SLOT_COUNT; slot++) {
        if (ids[slot] != CHAR_ID_RYU_ADULT) {
            Party_MemberRemove(ids[slot]);
        }
    }
}
