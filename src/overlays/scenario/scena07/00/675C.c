#include "scena07_00.h"

#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FD35C(void) {
    u8* timer;

    timer = &g_SceneState.step_05;
    if (*timer == 0 && g_GameStateIndex != GAME_REQUEST_MESSAGE) {
        Game_ClearScriptActive();
        g_SceneState.state_04 = 0;
        *timer                = 0;
    }
}

#include "overlays/scenario/Scene_DispatchActor.h"

MATCH void func_801FD3FC(Actor* actor) {
    SYS_SetFlag(g_SceneFlags, 10);
    Game_SetScriptActive();
    SCENE_START_ACTOR(actor, 3, 0x5);
}

MATCH void func_801FD45C(Actor* actor) {
    SYS_SetFlag(g_SceneFlags, 11);
    Item_VitalAdd(VITAL_ITEM_GUILD_LETTER);
    Game_SetScriptActive();
    SCENE_START_ACTOR(actor, 4, 6);
}

MATCH void func_801FD4C4(Actor* actor) {
    SYS_SetFlag(g_SceneFlags, 12);
    Game_SetScriptActive();
    SCENE_START_ACTOR(actor, 9, 0x1D);
}

MATCH void func_801FD524(void) {
    Game_SetScriptActive();
    g_ScriptVars[0] = 0;
    g_ScriptVars[1] = 0;
    g_ScriptVars[2] = 0;
    g_ScriptVars[3] = 0;
    if (SYS_TestFlag(D_80144EB8, 34) == 0) {
        g_SceneState.step_05 = 0;
    } else {
        g_SceneState.step_05 = 0x14;
    }
    g_SceneState.state_04 = 7;
}

MATCH void func_801FD5A0(void) {
    Game_SetScriptActive();
    g_ScriptVars[0] = 0;
    D_80146865      = 0;
    D_80146866      = 0;
    D_80146867      = 0;
    if (SYS_TestFlag(D_80144EB8, 35)) {
        D_80146875 = 0x14;
    } else {
        D_80146875 = 0xA;
    }
    D_80146874 = 7;
}

MATCH SpawnedActor* func_801FD610(u8 mode) {
    SpawnedActor* slot;
    s32           index;

    index = Actor_FindFreeSpawned() & BYTE_MASK;
    slot  = &g_SpawnedActors[index];
    if (index != GAME_NONE) {
        slot->header.flags = 1;
        slot->type         = 0x49;
        slot->header.mode  = mode;
    }
    return slot;
}

INCLUDE_ASM(func_801FD67C);

MATCH s32 func_801FD960(s32 x, s32 y) {
    s32 value;

    if (g_GameAreaId == AREA_ID_MOUNT_ZUBLO_GISSHAN) {
        if ((SYS_TestFlag(g_SceneFlags, 3) == 0) && (y <= TO_COORD(32))) {
            if (((x >> 16) - 74) < 2U) {
                Game_SetScriptActive();
                value = g_SndBGMId * 4;
                SND_StartDecrescendo(g_SelectionCues[value], g_SelectionCues[value + 1], 0x64, 0x20);
                g_SceneState.state_04 = 4;
                g_SceneState.step_05  = 0;
                return 1;
            }
        }
    }
    return 0;
}

MATCH bool func_801FDA34(void) {
    u8 i;

    for (i = 0; i < g_Game.party_size; i++) {
        if (g_Game.members[i].chr.character_id == CHAR_ID_GARR) {
            return 1;
        }
    }
    return 0;
}

#include "overlays/scenario/Scene_DispatchByPosition.h"

MATCH void func_801FDAFC(void) {
    Game_SetScriptActive();
    g_SceneState.state_04 = 6;
    g_SceneState.step_05  = 0xA;
}

#include "overlays/scenario/Scene_SetPartyRyuYoungNinaYoungMomo.h"

MATCH void Scene_SetPartyRyuYoungNinaYoungGarr(void) {
    SCENE_SET_PARTY_NO_RESTAGE(CHAR_ID_RYU_YOUNG, CHAR_ID_NINA_YOUNG, CHAR_ID_GARR);
}

MATCH void func_801FDBCC(void) {
    Party_RemoveMember(D_80146189);
}

MATCH void func_801FDBF4(void) {
    Party_RemoveMember(CHAR_ID_GARR);
    g_Characters[g_CharSlot[CHAR_ID_NINA_YOUNG]].party_flags &= 0xFE;
    /* FAKE: the slot map is const here, so the retail empty load delay needs the barrier. */
    FAKE_BARRIER();
    g_Characters[g_CharSlot[CHAR_ID_MOMO]].party_flags &= 0xFE;
    /* FAKE: the slot map is const here, so the retail empty load delay needs the barrier. */
    FAKE_BARRIER();
    g_Characters[g_CharSlot[CHAR_ID_PECO]].party_flags &= 0xFE;
    /* FAKE: the slot map is const here, so the retail empty load delay needs the barrier. */
    FAKE_BARRIER();
    g_Characters[g_CharSlot[CHAR_ID_GARR]].party_flags &= 0xFE;
}
