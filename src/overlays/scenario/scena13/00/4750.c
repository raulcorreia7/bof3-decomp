#include "scena13_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/scenario/Scene_DispatchActor.h"

MATCH void func_801FB390(void* entity) {
    ((Actor*)entity)->unk_7E = (((Actor*)entity)->unk_7E + 1);
}

MATCH void func_801FB3A4(void) {
    Game_SetScriptActive();
    g_SceneState.state_04 = 3;
    g_SceneState.step_05  = 5;
}

MATCH void func_801FB3DC(void) {
    Game_SetScriptActive();
    g_SceneState.state_04 = 6;
    g_SceneState.step_05  = 0x19;
}

MATCH void func_801FB414(void) {
    SYS_SetFlag(g_SceneFlags, 28);
    Scene_StartEvent(44, 0);
    g_SceneEventSelection = 17;
}

INCLUDE_ASM(func_801FB464);

MATCH s32 func_801FBA34(s32 x, s32 y) {
    if (LOHU(g_GameAreaId) == 0x8F && D_80143F03 == 0 && SYS_TestFlag(g_SceneFlags, 0x1C) != 0 && SYS_TestFlag(g_SceneFlags, 0x1D) == 0 && (x >> 16) == 0x2E && (u32)((y >> 16) - 0x1F) < 4U) {
        Game_SetScriptActive();
        D_80146874 = 8;
        D_80146875 = 0;
        return 1;
    }
    if (LOHU(g_GameAreaId) != 0x91) {
        return 0;
    }
    if (D_80143F03 != 5) {
        return 0;
    }
    if (SYS_TestFlag(g_SceneFlags, 0xA) != 0) {
        return 0;
    }
    if ((u32)((x >> 16) - 0x40) >= 2U) {
        return 0;
    }
    if ((y >> 16) != 0x6A) {
        return 0;
    }
    SYS_SetFlag(g_SceneFlags, 0xA);
    Area_SetCellPalette(0x40, 0x6B);
    return 0;
}

MATCH void Scene_JoinPartyRyuAdultPecoMomo(void) {
    EMI_LoadPartyArchives(CHAR_ID_RYU_ADULT, CHAR_ID_MOMO, CHAR_ID_PECO, 0);
    g_Game.party_size = 0;
    Party_JoinMember(CHAR_ID_RYU_ADULT);
    Party_JoinMember(CHAR_ID_PECO);
    Party_JoinMember(CHAR_ID_MOMO);
}

MATCH void func_801FBBC4(void) {
    u8 slot;

    for (slot = 0; slot < 3; slot++) {
        D_80144908[slot] = g_PartyFieldOrder[slot];
        D_8014490B[slot] = g_PartyBattleOrder[slot];
    }
    for (slot = 0; slot < 3; slot++) {
        Party_RemoveMember(D_80144908[slot]);
    }
    EMI_LoadPartyArchives(CHAR_ID_RYU_ADULT, CHAR_ID_REI, CHAR_ID_NINA_ADULT, 0);
    g_Game.party_size = 0;
    Party_JoinMember(CHAR_ID_RYU_ADULT);
    Party_LoadPalettes();
}

/* func_801FBC88 */
MATCH void Scene_LoadPartyRyuAdult(void) {
    EMI_LoadPartyArchives(CHAR_ID_RYU_ADULT, CHAR_ID_MOMO, CHAR_ID_NINA_ADULT, 0U);
    g_Game.party_size = 0;
    Party_JoinMember(CHAR_ID_RYU_ADULT);
}

MATCH void func_801FBCC4(void) {
    u8 ids[3];
    u8 slot;

    for (slot = 0; slot < 3; slot++) {
        ids[slot] = D_80144908[slot];
    }
    EMI_LoadPartyArchives(ids[0], ids[1], ids[2], 0);
    g_Game.party_size = 0;
    Party_JoinMember(ids[0]);
    Party_JoinMember(ids[1]);
    Party_JoinMember(ids[2]);
    for (slot = 3; slot < 6; slot++) {
        g_PartyFieldOrder[slot] = D_80144908[slot];
    }
}

MATCH void Scene_SetPartyRyuAdultMomoNinaAdult(void) {
    SCENE_SET_PARTY(CHAR_ID_RYU_ADULT, CHAR_ID_MOMO, CHAR_ID_NINA_ADULT);
}

MATCH void func_801FBDD8(void) {
    u8 ids[3];
    u8 slot;

    for (slot = 0; slot < 3; slot++) {
        ids[slot] = g_Game.members[slot].chr.character_id;
    }
    for (slot = 0; slot < 3; slot++) {
        Party_RemoveMember(ids[slot]);
    }
    EMI_LoadPartyArchives(CHAR_ID_RYU_ADULT, CHAR_ID_REI, CHAR_ID_GARR, 0);
    g_Game.party_size = 0;
    Party_JoinMember(CHAR_ID_RYU_ADULT);
    Party_LoadPalettes();
}

/* func_801FBE98 */
MATCH void Scene_JoinRei(void) {
    Party_JoinMember(CHAR_ID_REI);
    Party_LoadPalettes();
}

/* func_801FBEC0 */
MATCH void Scene_JoinGarr(void) {
    Party_JoinMember(CHAR_ID_GARR);
    Party_LoadPalettes();
}

MATCH void func_801FBEE8(void) {
}
