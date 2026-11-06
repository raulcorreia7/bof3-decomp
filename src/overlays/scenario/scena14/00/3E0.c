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
    ORDER_LOCK(D_801FC418[index]());
}

MATCH void func_801F7014(void) {
    D_80146872 = 1;
}

INCLUDE_ASM(func_801F7028);

/* blocker: color register; first diff: +0x30 lhu a1,0(a2). */
INCLUDE_ASM(func_801F7960);

/* needs: D_801FC4C0 declaration. */
INCLUDE_ASM(func_801F7A18);

MATCH void func_801F7B5C(void) {
    SYS_DISPATCH_BYTE(D_801FC424, g_SceneState.state_04);
}

MATCH void func_801F7B98(void) {
}

INCLUDE_ASM(func_801F7BA0);

INCLUDE_ASM(func_801F7FB8);

MATCH void func_801F8800(u8 amount) {
    s32 step;

    step                     = D_801FC44C[g_FrameCount & 3] * amount;
    g_AreaCameraRefreshCount = 2;
    g_AreaCameraOffsetY += step;
}

MATCH void func_801F8850(void) {
    u8* flags;

    flags = &D_80145FF4;
    *flags &= 0xFE;
    D_80146134 &= 0xFE;
    Game_RequestAreaChange(AREA_ID_DESERT_MANMO, 0x298000, 0x168000, 0x80);
    Game_SetScriptActive();
    D_80146874 = 2;
    D_80146875 = 0;
    D_80146871 &= 0xFE;
}

INCLUDE_ASM(func_801F88DC);

INCLUDE_ASM(func_801F8CE4);

INCLUDE_ASM(func_801F924C);

INCLUDE_ASM(func_801F9320);

INCLUDE_ASM(func_801F9834);

INCLUDE_ASM(func_801FA904);

INCLUDE_ASM(func_801FA9C8);

MATCH void func_801FB374(void) {
}

MATCH void func_801FB37C(void* entity) {
    SceneFunc handler;
    u8        index;

    index   = ((Actor*)entity)->callback_index;
    handler = D_801FC468[index];
    handler(entity, g_SceneFlags);
}

/* Starts the area message `message`: the area overlay's own lookup (func_801F326C
 * for area 0xC0, func_801F37AC otherwise) maps it to a message index. */
#define SCENA14_START_AREA_MESSAGE(message)               \
    if (g_GameAreaId == 0xC0) {                           \
        Message_StartAreaMessage(func_801F326C(message)); \
    } else {                                              \
        Message_StartAreaMessage(func_801F37AC(message)); \
    }                                                     \
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
    MATCH_FAKE_BARRIER();
    actor->unk_7E = actor->unk_7E + 1;
}

MATCH void func_801FB5F8(void* entity) {
    Actor* actor;

    actor = entity;
    Game_SetScriptActive();
    D_80146874 = 7;
    D_80146875 = 30;
    /* FAKE: preserve the store order. */
    MATCH_FAKE_BARRIER();
    actor->unk_7E = actor->unk_7E + 1;
}

INCLUDE_ASM(func_801FB648);

INCLUDE_ASM(func_801FB84C);

MATCH void Scene_JoinPartyRyuAdultReiNinaAdult(void) {
    EMI_LoaderStreamFamily(CHAR_ID_RYU_ADULT, CHAR_ID_NINA_ADULT, CHAR_ID_REI, 0);
    g_PartySize = 0;
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

INCLUDE_ASM(func_801FBE10);

MATCH void func_801FBF18(void) {
    g_Characters[g_CharSlot[10]].unk_07 &= 0xFE;
    EMI_LoaderStreamFamily(CHAR_ID_RYU_ADULT, CHAR_ID_REI, CHAR_ID_NINA_ADULT, 0);
    g_PartySize = 0;
    Party_JoinMember(CHAR_ID_RYU_ADULT);
    Party_JoinMember(CHAR_ID_REI);
    Party_JoinMember(CHAR_ID_NINA_ADULT);
    func_801C1630();
}

MATCH void func_801FBFA8(void) {
    EMI_LoaderStreamFamily(CHAR_ID_RYU_YOUNG, CHAR_ID_NINA_YOUNG, CHAR_ID_MOMO, 0);
    g_PartySize = 0;
    Party_JoinMember(CHAR_ID_RYU_YOUNG);
    Party_JoinMember(CHAR_ID_NINA_YOUNG);
    Party_JoinMember(CHAR_ID_MOMO);
    func_801C1630();
    D_80144F5D[0] = 7;
    D_80144F5E    = 8;
    D_80144F5F    = 5;
}

MATCH void Scene_SetPartyRyuAdultGarrPeco(void) {
    SCENE_SET_PARTY(CHAR_ID_RYU_ADULT, CHAR_ID_GARR, CHAR_ID_PECO);
}

#include "overlays/scenario/Scene_SetPartyRyuAdultGarrNinaAdult.h"

MATCH void func_801FC0C8(void) {
    EMI_LoaderStreamFamily(CHAR_ID_RYU_ADULT, CHAR_ID_REI, *D_80144908, 0U);
    g_PartySize = 0;
    Party_JoinMember(CHAR_ID_RYU_ADULT);
    Party_JoinMember(CHAR_ID_REI);
    Party_JoinMember(*D_80144908);
    func_801C1630();
}

/* blocker: frame 0x20 against 0x18; first diff: +0x0 addiu sp,sp,-32. */
INCLUDE_ASM(func_801FC130);

MATCH void func_801FC1E8(void) {
    EMI_LoaderStreamFamily(CHAR_ID_RYU_ADULT, CHAR_ID_GARR, CHAR_ID_PECO, 0);
    g_PartySize = 0;
    Party_JoinMember(CHAR_ID_RYU_ADULT);
    func_801C1630();
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
    EMI_LoaderStreamFamily(CHAR_ID_RYU_ADULT, CHAR_ID_REI, character, 0);
    g_PartySize = 0;
    Party_JoinMember(CHAR_ID_RYU_ADULT);
    Party_JoinMember(CHAR_ID_REI);
    Party_JoinMember(character);
    func_801C1630();
}

INCLUDE_ASM(func_801FC328);
