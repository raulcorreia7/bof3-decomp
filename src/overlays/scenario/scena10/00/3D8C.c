#include "scena10_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

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
        if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
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

/* Pick up the item hidden at the actor's cell: add it to the inventory, mark its trigger and show the message. */
MATCH void func_801FD5C0(Actor* actor) {
    u8 i;

    i = 0;
    do {
        if (D_801FE894[i].x == COORD_INT(g_Task->pos.x) && D_801FE894[i].y == COORD_INT(g_Task->pos.y)) {
            g_Task->param.unk_0B = D_801FE894[i].script + 0x4E;
            strncpy(g_TextVariables[0], Item_GetRecord(0, g_Task->param.unk_0B), 12);
            g_TextVariables[0][12] = 0;
            if (Item_Add(0, g_Task->param.unk_0B, 1, 0)) {
                /* FAKE: retail passes the bit index unmasked, as s32. */
                ((void (*)(void*, s32))SYS_SetFlag)(g_SceneFlags, SCENE_TRIGGER_FLAG_BASE + D_801FE894[i].flag);
                Message_Request(2);
                SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
                actor->unk_7E++;
                Game_SetScriptActive();
            } else {
                Message_Request(3);
            }
            g_GameStateIndex = GAME_REQUEST_MESSAGE;
            return;
        }
        i++;
    } while (i < ARRAY_COUNT(D_801FE894));
}

MATCH void func_801FD734(void) {
    u8 i;

    i = 0;
    do {
        if (D_801FE894[i].x == COORD_INT(g_Task->pos.x) && D_801FE894[i].y == COORD_INT(g_Task->pos.y)) {
            if (SYS_TestFlag(g_SceneFlags, SCENE_TRIGGER_FLAG_BASE + D_801FE894[i].flag) == 0) {
                Actor_SelectScript(D_801FE894[i].script);
                g_Task->unk_2A = 0;
            } else {
                g_Task->header.flags = 0;
            }
            return;
        }
        i++;
    } while (i < ARRAY_COUNT(D_801FE894));
}

MATCH void func_801FD814(void) {
    u8 saved_slot;

    saved_slot               = g_Task->param.actor_slot;
    g_Task->param.actor_slot = Actor_FindFreeSpawned();
    if (g_Task->param.actor_slot != GAME_NONE) {
        g_SpawnedActors[g_Task->param.actor_slot].header.flags = 1;
        g_SpawnedActors[g_Task->param.actor_slot].type         = 0x5D;
        g_SpawnedActors[g_Task->param.actor_slot].unk_06       = saved_slot;
        g_SpawnedActors[g_Task->param.actor_slot].unk_07       = 0;
    } else {
        g_Task->param.actor_slot = saved_slot;
        g_ScriptState->cursor -= 2;
    }
}

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

MATCH s32 func_801FE00C(s32 x, s32 y) {
    if (g_GameAreaId == AREA_ID_JUNK_TOWN) {
        if (SYS_TestFlag(g_SceneFlags, 8) && SYS_TestFlag(g_SceneFlags, 9) == 0 && y >= TO_COORD(48) && (u32)((x >> 16) - 28) < 5) {
            Game_SetScriptActive();
            SYS_SetFlag(g_SceneFlags, 9);
            SYS_SetFlag(g_SceneEventFlags, 67);
            g_ScriptVars[0] = 10;
            return 1;
        }
    }
    if (g_GameAreaId == AREA_ID_TIDAL_CAVES_OUTSIDE && D_80143F03 == 0 && SYS_TestFlag(g_SceneFlags, 53) == 0 && (y >> 16) >= 29) {
        Game_SetScriptActive();
        g_SceneState.state_04 = 12;
        g_SceneState.step_05  = 0;
        return 1;
    }
    if (g_GameAreaId == AREA_ID_CLIFF_GAIST && D_80143F03 == 5 && SYS_TestFlag(g_SceneFlags, 59) && SYS_TestFlag(g_SceneFlags, 60) == 0 && y == TO_COORD(116) + COORD_HALF && x == TO_COORD(37)) {
        Game_SetScriptActive();
        g_SceneState.state_04 = 13;
        g_SceneState.step_05  = 15;
    }
    if (g_GameAreaId == AREA_ID_MACHINE_GUILD_DOCK) {
        if (SYS_TestFlag(g_SceneFlags, 10) == 0 && y > TO_COORD(42) - 1 && (u32)((x >> 16) - 32) < 5) {
            Game_SetScriptActive();
            g_SceneState.state_04 = 3;
            g_SceneState.step_05  = 0;
            return 1;
        }
        if (SYS_TestFlag(g_SceneFlags, 11) && SYS_TestFlag(g_SceneFlags, 13) == 0 && y <= TO_COORD(55) && (u32)((x >> 16) - 31) < 2) {
            Game_SetScriptActive();
            g_SceneState.state_04 = 4;
            g_SceneState.step_05  = 10;
            return 1;
        }
    }
    return 0;
}

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
