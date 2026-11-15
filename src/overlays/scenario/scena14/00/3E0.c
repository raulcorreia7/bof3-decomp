#include "scena14_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F6FE0(void) {
    /* Retail takes the handler index from the entry $v0; the uninitialised local reads it. */
    u32 index;

    /* FAKE: without the block the scheduler hoists the index shift above the
       ra store (84.46%); the lock restores the retail order (99.85%). */
    FAKE_ORDER_LOCK(D_801FC418[index]());
}

MATCH void func_801F7014(void) {
    D_80146872 = 1;
}

INCLUDE_ASM(func_801F7028);

/* Averages each working palette colour's red, green and blue channels into a
 * grey level and keeps the mask bit, then marks the palette for upload. */
#ifdef NON_MATCHING
NON_MATCHING void func_801F7960(void) {
    u8   row;
    u16  col;
    u16* p;
    u16  color;
    u32  grey;

    for (row = 0; row < AREA_PALETTE_ROWS; row++) {
        p = (u16*)(AREA_PALETTE_WORK + row * AREA_PALETTE_ROW);
        for (col = 0; col < AREA_PALETTE_COLORS; col++) {
            color = p[col];
            grey  = (color & 0x1F) + ((color >> 5) & 0x1F) + ((color >> 10) & 0x1F);
            grey /= 3;
            p[col] = (color & 0x8000) | (grey << 10) | (grey << 5) | grey;
        }
    }
    g_GfxPalettePending = 1;
}
#else
INCLUDE_ASM(func_801F7960);
#endif

#include "overlays/scenario/Scene_SpawnActor.h"

MATCH bool Scene_SpawnActor(u8 type, s16 angle_x, s16 angle_y, s16 angle_z, u8 layer, s32 scene_step){SCENE_SPAWN_ACTOR(D_801FC4C0)}

MATCH void func_801F7B5C(void) {
    SYS_DISPATCH_BYTE(D_801FC424, g_SceneState.state_04);
}

MATCH void func_801F7B98(void) {
}

INCLUDE_ASM(func_801F7BA0);

INCLUDE_ASM(func_801F7FB8);

MATCH void func_801F8800(u8 amount) {
    s32 step;

    step                     = D_801FC44C[g_FrameCount & 0x3] * amount;
    g_AreaCameraRefreshCount = 2;
    g_AreaCameraOffsetY += step;
}

MATCH void func_801F8850(void) {
    u8* flags;

    flags = &D_80145FF4;
    *flags &= 0xFE;
    D_80146134 &= 0xFE;
    Game_RequestAreaChange(AREA_ID_DESERT_MANMO, TO_COORD(41) + COORD_HALF, TO_COORD(22) + COORD_HALF, AREA_ENTRY_MAP_LOADING);
    Game_SetScriptActive();
    D_80146874 = 2;
    D_80146875 = 0;
    D_80146871 &= 0xFE;
}

INCLUDE_ASM(func_801F88DC);

INCLUDE_ASM(func_801F8CE4);

MATCH void func_801F924C(void) {
    s32* scroll;
    s32* party;
    s32* focus;
    u16  height;

    if (g_AreaCameraX == 0x77FF) {
        g_AreaCameraX = 0x63FF;
        scroll        = &g_AreaScrollTargetX;
        party         = &g_PartyX;
        focus         = &D_80147A8C;
        g_AreaTileOriginX += 20;
        *scroll += TO_COORD(20);
        *party += TO_COORD(20);
        height         = Area_SampleHeight(g_AreaScrollTargetX, g_AreaScrollTargetY);
        g_ScrollHeight = height;
        Area_AdvanceScroll(height);
        Area_RefreshCellGrid();
        *focus += TO_COORD(20);
        D_80147A96 = Area_SampleHeight(*focus, g_AreaFocusY);
    }
}

INCLUDE_ASM(func_801F9320);

INCLUDE_ASM(func_801F9834);

MATCH u16 func_801FA904(u8* tags, u16* messages) {
    u8 i;
    u8 j;

    for (i = 0; i < PARTY_MEMBER_MESSAGE_COUNT; i++) {
        for (j = 0; j < g_PartySize; j++) {
            if (g_Game.members[j].chr.character_id == tags[i]) {
                Message_StartAreaMessage((s16)messages[i]);
                FAKE_ORDER_LOCK(g_GameStateIndex = GAME_REQUEST_MESSAGE); /* FAKE: keeps the state store before the return value's reload. */
                return messages[i];
            }
        }
    }
    return MESSAGE_NONE;
}

INCLUDE_ASM(func_801FA9C8);

MATCH void func_801FB374(void) {
}

#include "overlays/scenario/Scene_DispatchActor.h"

/* Starts the area message `message`: the area overlay's own lookup (func_801F326C
 * for the second desert camp, func_801F37AC otherwise) maps it to a message index. */
#define SCENA14_START_AREA_MESSAGE(message)                 \
    if (LOHU(g_GameAreaId) == AREA_ID_DESERT_CAMP_SECOND) { \
        Message_StartAreaMessage(func_801F326C(message));   \
    } else {                                                \
        Message_StartAreaMessage(func_801F37AC(message));   \
    }                                                       \
    g_GameStateIndex = GAME_REQUEST_MESSAGE

MATCH void func_801FB3BC(void) {
    SCENA14_START_AREA_MESSAGE(8);
}

MATCH void func_801FB414(void) {
    SCENA14_START_AREA_MESSAGE(4);
}

MATCH void func_801FB46C(void) {
    SCENA14_START_AREA_MESSAGE(2);
}

MATCH void func_801FB4C4(void) {
    SCENA14_START_AREA_MESSAGE(5);
}

MATCH void func_801FB51C(void) {
    SCENA14_START_AREA_MESSAGE(6);
}

MATCH void func_801FB574(void) {
    Game_SetScriptActive();
    g_SceneState.state_04 = 5;
    g_SceneState.step_05  = 5;
}

MATCH void func_801FB5A8(void* entity) {
    Actor* actor;

    actor = entity;
    Game_SetScriptActive();
    D_80146874 = 5;
    D_80146875 = 30;
    /* FAKE: preserve the store order. */
    FAKE_BARRIER();
    actor->unk_7E = actor->unk_7E + 1;
}

MATCH void func_801FB5F8(void* entity) {
    Actor* actor;

    actor = entity;
    Game_SetScriptActive();
    D_80146874 = 7;
    D_80146875 = 30;
    /* FAKE: preserve the store order. */
    FAKE_BARRIER();
    actor->unk_7E = actor->unk_7E + 1;
}

#ifdef NON_MATCHING
NON_MATCHING s32 func_801FB648(s32 x, s32 y) {
    s32 map_x;
    s32 map_y;
    u8  cell_count;

    if (g_GameAreaId == 0x94 && D_80143F03 == 4 && !SYS_TestFlag(g_SceneFlags, 0x10) && x == 0x738000) {
        map_y = y >> 16;
        if ((u32)(map_y - 0x36) < 2) {
            Game_SetScriptActive();
            D_80146874 = 4;
            D_80146875 = 0;
            return 1;
        }
    }

    if (g_GameAreaId == 0xBF && SYS_TestFlag(g_SceneFlags, 5)) {
        map_x      = x >> 16;
        map_y      = y >> 16;
        cell_count = Area_GetCellCode(map_x, map_y) == 0xA6;
        if ((u16)x != 0 && Area_GetCellCode((s16)(map_x + 1), map_y) == 0xA6) {
            cell_count++;
        }
        if ((u16)y != 0 && Area_GetCellCode(map_x, (s16)(map_y + 1)) == 0xA6) {
            cell_count++;
        }
        if ((u16)x != 0 && (u16)y != 0 && Area_GetCellCode((s16)(map_x + 1), (s16)(map_y + 1)) == 0xA6) {
            cell_count++;
        }
        if (cell_count != 0) {
            Game_SetScriptActive();
            D_80146874 = 2;
            D_80146875 = 20;
            return 1;
        }
    }
    return 0;
}
#else
INCLUDE_ASM(func_801FB648);
#endif

INCLUDE_ASM(func_801FB84C);

MATCH void Scene_JoinPartyRyuAdultReiNinaAdult(void) {
    EMI_LoadPartyArchives(CHAR_ID_RYU_ADULT, CHAR_ID_NINA_ADULT, CHAR_ID_REI, 0);
    g_Game.party_size = 0;
    Party_JoinMember(CHAR_ID_RYU_ADULT);
    Party_JoinMember(CHAR_ID_REI);
    Party_JoinMember(CHAR_ID_NINA_ADULT);
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
        Party_RemoveMember(ids[slot]);
    }
    EMI_LoadPartyArchives(CHAR_ID_WHELP, CHAR_ID_BLANK, CHAR_ID_BLANK, 0);
    g_Game.party_size = 0;
    Party_JoinMember(CHAR_ID_WHELP);
    Party_LoadPalettes();
}

MATCH void func_801FBF18(void) {
    g_Characters[g_CharSlot[10]].unk_07 &= 0xFE;
    EMI_LoadPartyArchives(CHAR_ID_RYU_ADULT, CHAR_ID_REI, CHAR_ID_NINA_ADULT, 0);
    g_Game.party_size = 0;
    Party_JoinMember(CHAR_ID_RYU_ADULT);
    Party_JoinMember(CHAR_ID_REI);
    Party_JoinMember(CHAR_ID_NINA_ADULT);
    Party_LoadPalettes();
}

MATCH void func_801FBFA8(void) {
    EMI_LoadPartyArchives(CHAR_ID_RYU_YOUNG, CHAR_ID_NINA_YOUNG, CHAR_ID_MOMO, 0);
    g_Game.party_size = 0;
    Party_JoinMember(CHAR_ID_RYU_YOUNG);
    Party_JoinMember(CHAR_ID_NINA_YOUNG);
    Party_JoinMember(CHAR_ID_MOMO);
    Party_LoadPalettes();
    g_PartyBattleOrder[0] = 7;
    D_80144F5E[0]         = 8;
    D_80144F5F            = 5;
}

MATCH void Scene_SetPartyRyuAdultGarrPeco(void) {
    SCENE_SET_PARTY(CHAR_ID_RYU_ADULT, CHAR_ID_GARR, CHAR_ID_PECO);
}

#include "overlays/scenario/Scene_SetPartyRyuAdultGarrNinaAdult.h"

MATCH void func_801FC0C8(void) {
    EMI_LoadPartyArchives(CHAR_ID_RYU_ADULT, CHAR_ID_REI, *D_80144908, 0U);
    g_Game.party_size = 0;
    Party_JoinMember(CHAR_ID_RYU_ADULT);
    Party_JoinMember(CHAR_ID_REI);
    Party_JoinMember(*D_80144908);
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
        Party_RemoveMember(D_80144908[slot]);
    }
    EMI_LoadPartyArchives(CHAR_ID_RYU_ADULT, CHAR_ID_NINA_ADULT, CHAR_ID_REI, 0);
    g_Game.party_size = 0;
    Party_JoinMember(CHAR_ID_RYU_ADULT);
    Party_LoadPalettes();
}

MATCH void func_801FC1E8(void) {
    EMI_LoadPartyArchives(CHAR_ID_RYU_ADULT, CHAR_ID_GARR, CHAR_ID_PECO, 0);
    g_Game.party_size = 0;
    Party_JoinMember(CHAR_ID_RYU_ADULT);
    Party_LoadPalettes();
}

#include "overlays/scenario/Scene_SetPartyRyuAdultNinaAdultRei.h"

MATCH void func_801FC280(void) {
    u8 slot;
    u8 character;

    for (slot = 0; slot < 3; slot++) {
        character = D_80144908[slot];
        if (character != CHAR_ID_RYU_ADULT && character != CHAR_ID_REI) {
            break;
        }
    }
    EMI_LoadPartyArchives(CHAR_ID_RYU_ADULT, CHAR_ID_REI, character, 0);
    g_Game.party_size = 0;
    Party_JoinMember(CHAR_ID_RYU_ADULT);
    Party_JoinMember(CHAR_ID_REI);
    Party_JoinMember(character);
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
            Party_RemoveMember(ids[slot]);
        }
    }
}
