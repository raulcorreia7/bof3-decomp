#include "scena07_00.h"

#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FD35C(void) {
    u8* timer;

    timer = &g_ScenarioState.step;
    if (*timer == 0 && g_GameStateIndex != GAME_REQUEST_MESSAGE) {
        Game_ClearScriptActive();
        g_ScenarioState.state_04 = 0;
        *timer                   = 0;
    }
}

#include "overlays/scenario/shared/Scene_DispatchActor.h"

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
        g_ScenarioState.step = 0;
    } else {
        g_ScenarioState.step = 0x14;
    }
    g_ScenarioState.state_04 = 7;
}

MATCH void func_801FD5A0(void) {
    Game_SetScriptActive();
    g_ScriptVars[0] = 0;
    g_ScriptVars[1] = 0;
    g_ScriptVars[2] = 0;
    g_ScriptVars[3] = 0;
    if (SYS_TestFlag(D_80144EB8, 35)) {
        g_ScenarioState.step = 0x14;
    } else {
        g_ScenarioState.step = 0xA;
    }
    g_ScenarioState.state_04 = 7;
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

MATCH s32 func_801FD67C(s32 x, s32 y) {
    if ((g_GameAreaId == AREA_ID_URKAN_TAPA) && (SYS_TestFlag(g_SceneFlags, 4) != 0) && (SYS_TestFlag(g_SceneFlags, 7) == 0) && (x == 0x348000) && ((u32)((y >> 16) - 0x13) < 4U)) {
        Game_SetScriptActive();
        g_ScenarioState.state_04 = 5;
        g_ScenarioState.step     = 0;
        return 1;
    }
    if ((g_GameAreaId == AREA_ID_ANGEL_TOWER_OUTSIDE) && ((u32)((y >> 16) - 0x3C) < 5U) && ((u32)((x >> 16) - 0x22) < 4U)) {
        if ((SYS_TestFlag(g_SceneFlags, 4) == 0) || ((func_801FDA34() & BYTE_MASK) == 0)) {
            u16 facing;

            facing                      = g_Game.members[0].facing;
            g_ScratchPad.cells.bytes[0] = facing;
            if (((u32)(facing - 5) >= 2U) && ((u8)facing != 4)) {
                g_ScriptVars[0] = 0x10;
                Game_SetScriptActive();
                return 1;
            }
        }
    }
    if ((g_GameAreaId == AREA_ID_ANGEL_TOWER_GARR_FIGHT) && (y == 0x1C8000) && ((u32)((x >> 16) - 0x25) < 2U) && (SYS_TestFlag(g_SceneFlags, 9) == 0)) {
        UI_MessageStartArea(MSG_SCENA07_002);
        g_GameStateIndex         = 2;
        g_ScenarioState.state_04 = 6;
        g_ScenarioState.step     = 5;
        g_GameFlags |= 0x100;
        return 1;
    }
    if (g_GameAreaId == AREA_ID_TIDAL_CAVES_OUTSIDE) {
        u8 facing;

        facing                      = g_Game.members[0].facing;
        g_ScratchPad.cells.bytes[0] = facing;
        if (((u32)facing >= 2U) && (facing != 2) && ((y >> 16) >= 0x1E)) {
            Game_SetScriptActive();
            UI_MessageStartArea(MSG_SCENA07_001);
            g_GameStateIndex         = 2;
            g_ScenarioState.state_04 = 8;
            g_ScenarioState.step     = 0;
            return 1;
        }
    }
    if ((g_GameAreaId == AREA_ID_FAIRY_VILLAGE_DOLPHIN) && (SYS_TestFlag(g_SceneFlags, 0) != 0) && (SYS_TestFlag(g_SceneFlags, 1) == 0) && ((u32)((y >> 16) - 0x20) < 5U) &&
        ((u32)((x >> 16) - 0x18) < 0x16U)) {
        Game_SetScriptActive();
        g_ScenarioState.state_04 = 2;
        g_ScenarioState.step     = 0;
        return 1;
    }
    return 0;
}

MATCH s32 func_801FD960(s32 x, s32 y) {
    s32 value;

    if (g_GameAreaId == AREA_ID_MOUNT_ZUBLO_GISSHAN) {
        if ((SYS_TestFlag(g_SceneFlags, 3) == 0) && (y <= TO_COORD(32))) {
            if (((x >> 16) - 74) < 2U) {
                Game_SetScriptActive();
                value = g_SndBGMId * 4;
                SND_StartDecrescendo(g_SelectionSepSlots[value], g_SelectionSepSlots[value + 1], 0x64, 0x20);
                g_ScenarioState.state_04 = 4;
                g_ScenarioState.step     = 0;
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

#include "overlays/scenario/shared/Scene_DispatchByPosition.h"

MATCH void func_801FDAFC(void) {
    Game_SetScriptActive();
    g_ScenarioState.state_04 = 6;
    g_ScenarioState.step     = 0xA;
}

#include "overlays/scenario/shared/Scene_SetPartyRyuYoungNinaYoungMomo.h"

MATCH void Scene_SetPartyRyuYoungNinaYoungGarr(void) {
    SCENE_SET_PARTY_NO_RESTAGE(CHAR_ID_RYU_YOUNG, CHAR_ID_NINA_YOUNG, CHAR_ID_GARR);
}

MATCH void func_801FDBCC(void) {
    Party_MemberRemove(g_Game.members[2].chr.character_id);
}

MATCH void func_801FDBF4(void) {
    Party_MemberRemove(CHAR_ID_GARR);
    g_Characters[g_CharSlot[CHAR_ID_NINA_YOUNG]].party_flags &= ~PARTY_FLAG_JOINED;
    g_Characters[g_CharSlot[CHAR_ID_MOMO]].party_flags &= ~PARTY_FLAG_JOINED;
    g_Characters[g_CharSlot[CHAR_ID_PECO]].party_flags &= ~PARTY_FLAG_JOINED;
    g_Characters[g_CharSlot[CHAR_ID_GARR]].party_flags &= ~PARTY_FLAG_JOINED;
}
