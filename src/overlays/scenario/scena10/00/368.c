#include "scena10_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/scenario/Scene_DispatchEntity.h"

INCLUDE_ASM(func_801F6FAC);

INCLUDE_ASM(func_801F7068);

INCLUDE_ASM(func_801F719C);

INCLUDE_ASM(func_801F73EC);

MATCH void func_801F74F8(void) {
    Actor_Clear();
}

MATCH void func_801F7518(void) {
    SYS_DISPATCH_TASK(D_801FE820, 1, g_Task);
}

MATCH void func_801F755C(void) {
    g_Task->unk_06 = 0x4E;
    func_801F6FAC();
    g_Task->header.step = 0;
}

INCLUDE_ASM(func_801F7590);

INCLUDE_ASM(func_801F7758);

INCLUDE_ASM(func_801F781C);

INCLUDE_ASM(func_801F79E8);

INCLUDE_ASM(func_801F7AD4);

INCLUDE_ASM(func_801F7C34);

INCLUDE_ASM(func_801F7DDC);

MATCH void func_801F7F50(void) {
    SYS_DISPATCH_BYTE(D_801FE8F4, D_80146872);
}

MATCH void func_801F7F8C(void) {
    D_80146872 = 1;
}

INCLUDE_ASM(func_801F7FA0);

INCLUDE_ASM(func_801F8550);

MATCH void func_801F8694(void) {
    SYS_DISPATCH_BYTE(D_801FE900, g_SceneState.state_04);
}

MATCH void func_801F86D0(void) {
}

INCLUDE_ASM(func_801F86D8);

INCLUDE_ASM(func_801F8C00);

INCLUDE_ASM(func_801F95B8);

MATCH void func_801F9FC4(void) {
    D_1F800000.view.area.entity_counter = Actor_FindFree();
    if (D_1F800000.view.area.entity_counter != 255) {
        func_801A4D54(D_801FE938);
    }
}

INCLUDE_ASM(func_801FA010);

MATCH u8 func_801FA5EC(void) {
    u8 i;
    u8 count;

    for (i = 0; i < 8; i += 1) {
        count = Item_Count(ITEM_CAT_ITEM, i + 0x4E, 0);
        if (count != 0) {
            return count;
        }
    }
    return 0;
}

INCLUDE_ASM(func_801FA644);

INCLUDE_ASM(func_801FA6BC);

INCLUDE_ASM(func_801FA98C);

MATCH void func_801FC220(void) {
    if (D_801FE9DC != 0) {
        s8 step                  = D_801FE94C[g_FrameCount & 0x3];
        g_AreaCameraRefreshCount = 2;
        g_AreaCameraOffsetY += step * 4;
    }
}

INCLUDE_ASM(func_801FC280);

MATCH void func_801FC830(void) {
    if (g_SceneState.step_05 == 1) {
        if (g_GameStateIndex != 2) {
            func_801BE1B0(2);
            SYS_SetFlag(g_SceneFlags, 52);
            g_SceneState.state_04 = 0;
            g_SceneState.step_05  = 0;
        }
    }
}

MATCH void func_801FC8A0(void) {
    if (g_SceneState.step_05 == 0x23) {
        Game_ClearScriptActive();
        func_801BE1B0(4);
        *g_ScriptVars         = 0x20;
        g_SceneState.state_04 = 0;
        g_SceneState.step_05  = 0;
    }
}

INCLUDE_ASM(func_801FC900);

INCLUDE_ASM(func_801FCD80);

MATCH u16 func_801FD278(void) {
    SCENA10_PARTY_LOOKUP(4, D_801FE950, D_801FE954, 0);
}

MATCH u16 func_801FD31C(void) {
    SCENA10_PARTY_LOOKUP(5, D_801FE95C, D_801FE964, 0);
}

MATCH u16 func_801FD3C0(void) {
    SCENA10_PARTY_LOOKUP(3, D_801FE970, D_801FE974, 0xFFFF);
}

#include "overlays/scenario/Scene_DispatchActor.h"

MATCH void func_801FD4A4(void) {
    Game_SetScriptActive();
    func_801BE1B0(1);
}

MATCH void func_801FD4CC(void) {
    Game_SetScriptActive();
    func_801BE1B0(4);
}

MATCH void func_801FD4F4(void) {
    Game_SetScriptActive();
    g_SceneState.state_04 = 2;
    g_SceneState.step_05  = 0;
}

MATCH void func_801FD528(void) {
    Game_SetScriptActive();
    g_SceneState.state_04 = 3;
    g_SceneState.step_05  = 0xA;
    g_ScriptVars[0]       = 0xA;
}

MATCH void func_801FD568(Actor* actor) {
    SCENA10_ACTOR_START(0, 5, 0xF);
}

INCLUDE_ASM(func_801FD5C0);

INCLUDE_ASM(func_801FD734);

INCLUDE_ASM(func_801FD814);

MATCH void func_801FD95C(Actor* actor) {
    SCENA10_ACTOR_START(0xA, 0x1E, 0x13);
}

MATCH void func_801FD9B4(Actor* actor) {
    SCENA10_ACTOR_START(0xB, 0x1F, 0x13);
}

MATCH void func_801FDA0C(Actor* actor) {
    u8* state;

    Game_SetScriptActive();
    func_801BE1B0(1);
    SYS_SetFlag(g_SceneFlags, 21);
    state = &D_80146875;
    *state += 1;
    actor->unk_7E += 1;
}

MATCH void func_801FDA74(void) {
    SYS_SetFlag(g_SceneFlags, 25U);
}

MATCH void func_801FDA9C(void) {
    Game_SetScriptActive();
    g_SceneState.state_04 = 0xA;
    g_SceneState.step_05  = 1;
}

MATCH void func_801FDAD4(void) {
    *SP_REF(s8*, 0x44) = 0;
    Game_SetScriptActive();
    g_SceneState.state_04 = 0xD;
    g_SceneState.step_05  = 5;
}

INCLUDE_ASM(func_801FDB14);

INCLUDE_ASM(func_801FE00C);

MATCH bool func_801FE2B0(void) {
    u8 i;

    for (i = 0; i < g_Game.party_size; i++) {
        if (g_Game.members[i].chr.character_id == CHAR_ID_GARR) {
            return 1;
        }
    }
    return 0;
}

MATCH void Scene_JoinPartyRyuAdultGarrNinaAdult(void) {
    SCENE_SET_PARTY_NO_RESTAGE(CHAR_ID_RYU_ADULT, CHAR_ID_GARR, CHAR_ID_NINA_ADULT);
}

MATCH void func_801FE360(void) {
    u8 i;

    for (i = 0; i < g_Game.party_size; i++) {
        Party_RemoveMember(g_Game.members[i].chr.character_id);
    }
    EMI_LoadPartyArchives(CHAR_ID_RYU_ADULT, CHAR_ID_MOMO, CHAR_ID_NINA_ADULT, 0);
    g_Game.party_size = 0;
    Party_JoinMember(CHAR_ID_RYU_ADULT);
    Party_JoinMember(CHAR_ID_MOMO);
}

/* func_801FE3F8 */
MATCH void Party_JoinNinaAdult(void) {
    Party_JoinMember(CHAR_ID_NINA_ADULT);
}

/* func_801FE418 */
MATCH void Party_JoinMomo(void) {
    Party_JoinMember(CHAR_ID_MOMO);
}

MATCH void func_801FE438(void) {
    u8 ids[PARTY_SLOT_COUNT];
    u8 slot;

    for (slot = 0; slot < PARTY_SLOT_COUNT; slot++) {
        ids[slot] = D_80144908[slot];
    }
    EMI_LoadPartyArchives(ids[0], ids[1], ids[2], 0);
    for (slot = 0; slot < PARTY_SLOT_COUNT; slot++) {
        if (ids[slot] != CHAR_ID_RYU_ADULT) {
            Party_JoinMember(ids[slot]);
        }
    }
}

#include "overlays/scenario/Scene_RebuildRyuGarrParty.h"

MATCH void func_801FE5B0(void) {
    g_Characters[g_CharSlot[5]].unk_07 &= 254;
    Party_RemoveMember(CHAR_ID_MOMO);
    Party_LoadPalettes();
}

#include "overlays/scenario/Scene_RemoveMomo.h"

MATCH void func_801FE63C(void) {
    u8 ids[PARTY_SLOT_COUNT];
    u8 slot;

    for (slot = 0; slot < PARTY_SLOT_COUNT; slot++) {
        ids[slot] = g_Game.members[slot].chr.character_id;
    }
    for (slot = 0; slot < PARTY_SLOT_COUNT; slot++) {
        if (ids[slot] != CHAR_ID_RYU_ADULT) {
            Party_RemoveMember(ids[slot]);
        }
    }
    Party_LoadPalettes();
}

#include "overlays/scenario/Scene_StashPartyExceptRyuAdult.h"
