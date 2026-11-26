#include "scena10_00.h"

MATCH u16 func_801FD278(void) {
    SCENA10_PARTY_LOOKUP(4, D_801FE950, D_801FE954, 0);
}

MATCH u16 func_801FD31C(void) {
    SCENA10_PARTY_LOOKUP(5, D_801FE95C, D_801FE964, 0);
}

MATCH u16 func_801FD3C0(void) {
    SCENA10_PARTY_LOOKUP(3, D_801FE970, D_801FE974, 0xFFFF);
}

#include "overlays/scenario/shared/Scene_DispatchActor.h"

MATCH void func_801FD4A4(void) {
    Game_SetScriptActive();
    Scene_SetupParty(1);
}

MATCH void func_801FD4CC(void) {
    Game_SetScriptActive();
    Scene_SetupParty(4);
}

MATCH void func_801FD4F4(void) {
    Game_SetScriptActive();
    g_ScenarioState.state_04 = 2;
    g_ScenarioState.step     = 0;
}

MATCH void func_801FD528(void) {
    Game_SetScriptActive();
    g_ScenarioState.state_04 = 3;
    g_ScenarioState.step     = 0xA;
    g_ScriptVars[0]          = 0xA;
}

MATCH void func_801FD568(Actor* actor) {
    SCENA10_ACTOR_START(0, 5, 0xF);
}

/* Pick up the item hidden at the actor's cell: add it to the inventory, mark its trigger and show the message. */
MATCH void func_801FD5C0(Actor* actor) {
    u8 i;

    i = 0;
    do {
        if (D_801FE894[i].x == COORD_INT(SELF(Actor)->pos.x) && D_801FE894[i].y == COORD_INT(SELF(Actor)->pos.y)) {
            SELF(Actor)->param.unk_0B = D_801FE894[i].script + ITEM_PART_A;
            strncpy(g_TextVariables[0], Item_GetRecord(ITEM_CATEGORY_ITEM, SELF(Actor)->param.unk_0B), 12);
            g_TextVariables[0][12] = 0;
            if (Item_Add(ITEM_CATEGORY_ITEM, SELF(Actor)->param.unk_0B, 1, 0)) {
                /* FAKE: retail passes the bit index unmasked, as s32. */
                ((void (*)(void*, s32))SYS_SetFlag)(g_SceneFlags, SCENE_TRIGGER_FLAG_BASE + D_801FE894[i].flag);
                UI_MessageRequest(MSG_SYSTEM_FOUND_ITEM);
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
                actor->unk_7E++;
                Game_SetScriptActive();
            } else {
                UI_MessageRequest(MSG_SYSTEM_FOUND_ITEM_NO_ROOM);
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
        if (D_801FE894[i].x == COORD_INT(SELF(Actor)->pos.x) && D_801FE894[i].y == COORD_INT(SELF(Actor)->pos.y)) {
            if (SYS_TestFlag(g_SceneFlags, SCENE_TRIGGER_FLAG_BASE + D_801FE894[i].flag) == 0) {
                Script_Select(D_801FE894[i].script);
                SELF(Actor)->mirror = 0;
            } else {
                SELF(Actor)->header.flags = 0;
            }
            return;
        }
        i++;
    } while (i < ARRAY_COUNT(D_801FE894));
}

MATCH void func_801FD814(void) {
    u8 saved_slot;

    saved_slot                    = SELF(Actor)->param.actor_slot;
    SELF(Actor)->param.actor_slot = Actor_FindFreeSpawned();
    if (SELF(Actor)->param.actor_slot != GAME_NONE) {
        g_SpawnedActors[SELF(Actor)->param.actor_slot].header.flags = 1;
        g_SpawnedActors[SELF(Actor)->param.actor_slot].type         = 0x5D;
        g_SpawnedActors[SELF(Actor)->param.actor_slot].unk_06       = saved_slot;
        g_SpawnedActors[SELF(Actor)->param.actor_slot].unk_07       = 0;
    } else {
        SELF(Actor)->param.actor_slot = saved_slot;
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
    Scene_SetupParty(1);
    SYS_SetFlag(g_SceneFlags, 21);
    state = &g_ScenarioState.step;
    *state += 1;
    actor->unk_7E += 1;
}

MATCH void func_801FDA74(void) {
    SYS_SetFlag(g_SceneFlags, 25U);
}

MATCH void func_801FDA9C(void) {
    Game_SetScriptActive();
    g_ScenarioState.state_04 = 0xA;
    g_ScenarioState.step     = 1;
}

MATCH void func_801FDAD4(void) {
    *SP_REF(s8*, 0x44) = 0;
    Game_SetScriptActive();
    g_ScenarioState.state_04 = 0xD;
    g_ScenarioState.step     = 5;
}

/* Starts the scene script for the trigger cell at (x, y) in the current area; returns 1 when one starts. */
MATCH s32 func_801FDB14(s32 x, s32 y) {
    u8 i;

    if (LOHU(g_GameAreaId) == AREA_ID_STEEL_BEACH && g_GameCellType == 1 && !SYS_TestFlag(g_SceneFlags, 0x10) && x <= TO_COORD(4) && (u32)((y >> 16) - 0x6B) < 4) {
        Game_SetScriptActive();
        g_ScenarioState.state_04 = 4;
        g_ScenarioState.step     = 0x1E;
        return 1;
    }
    if (LOHU(g_GameAreaId) == AREA_ID_ANGEL_TOWER_OUTSIDE && g_GameCellType == 0) {
        if ((u32)((y >> 16) - 0x3C) < 5 && (u32)((x >> 16) - 0x22) < 4) {
            g_ScratchPad.cells.bytes[0] = g_Game.members[0].facing;
            if (g_ScratchPad.cells.bytes[0] != 5 && g_ScratchPad.cells.bytes[0] != 6 && g_ScratchPad.cells.bytes[0] != 4) {
                if (!func_801FE2B0()) {
                    g_ScriptVars[0] = 0x10;
                    Game_SetScriptActive();
                    return 1;
                }
                if (!SYS_TestFlag(g_SceneFlags, 0x3D) && !SYS_TestFlag(g_SceneFlags, 0x33)) {
                    SYS_SetFlag(g_SceneFlags, 0x33);
                    Game_SetScriptActive();
                    g_ScenarioState.state_04 = 0xB;
                    g_ScenarioState.step     = 0x23;
                    return 1;
                }
            }
        }
        if (SYS_TestFlag(g_SceneFlags, 0x3D) && (u32)((y >> 16) - 0x23) < 2 && x == 0x458000) {
            SYS_SetFlag(g_SceneFlags, 7);
        }
    }
    if (LOHU(g_GameAreaId) == AREA_ID_CLIFF_GAIST) {
        if (g_GameCellType == 0 && x == 0x58000 && (u32)((y >> 16) - 0x11) < 4 && !SYS_TestFlag(g_SceneFlags, 0x37)) {
            for (i = 0; i < g_Game.party_size; i++) {
                if (g_Game.members[i].chr.character_id == CHAR_ID_GARR) {
                    break;
                }
            }
            if (i < g_Game.party_size) {
                Game_SetScriptActive();
                SYS_SetFlag(g_SceneFlags, 0x37);
                func_8019FA28(0x78, 0x260000, 0x710000, 0x80);
                g_GamePrevSelection      = 0xFF;
                g_ScenarioState.state_04 = 0xD;
                g_ScenarioState.step     = 0;
                return 1;
            }
        }
        if (g_GameCellType == 5 && SYS_TestFlag(g_SceneFlags, 0x3B) && !SYS_TestFlag(g_SceneFlags, 0x3C) && x == 0x2B8000 && (u32)((y >> 16) - 0x74) < 2) {
            Game_SetScriptActive();
            g_ScenarioState.state_04 = 0xD;
            g_ScenarioState.step     = 0xA;
            return 1;
        }
    }
    if (LOHU(g_GameAreaId) == AREA_ID_MACHINE_GUILD_DOCK) {
        if (g_GameCellType == 0 && SYS_TestFlag(g_SceneFlags, 0xB) && !SYS_TestFlag(g_SceneFlags, 0xE) && y == 0x118000 && (u32)((x >> 16) - 0x18) < 5) {
            g_ScratchPad.cells.bytes[0] = g_Game.members[0].facing;
            if (g_ScratchPad.cells.bytes[0] < 2 || g_ScratchPad.cells.bytes[0] == 2) {
                Game_SetScriptActive();
                g_ScenarioState.state_04 = 4;
                g_ScenarioState.step     = 0x14;
                return 1;
            }
        }
        if (g_GameCellType == 3 && SYS_TestFlag(g_SceneFlags, 0xC) && x == 0x520000 && (u32)((y >> 16) - 7) < 3) {
            Game_SetScriptActive();
            g_ScenarioState.state_04 = 4;
            g_ScenarioState.step     = 0;
            SYS_ClearFlag(g_SceneFlags, 0xC);
            return 1;
        }
    }
    return 0;
}

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
    if (g_GameAreaId == AREA_ID_TIDAL_CAVES_OUTSIDE && g_GameCellType == 0 && SYS_TestFlag(g_SceneFlags, 53) == 0 && (y >> 16) >= 29) {
        Game_SetScriptActive();
        g_ScenarioState.state_04 = 12;
        g_ScenarioState.step     = 0;
        return 1;
    }
    if (g_GameAreaId == AREA_ID_CLIFF_GAIST && g_GameCellType == 5 && SYS_TestFlag(g_SceneFlags, 59) && SYS_TestFlag(g_SceneFlags, 60) == 0 && y == TO_COORD(116) + COORD_HALF && x == TO_COORD(37)) {
        Game_SetScriptActive();
        g_ScenarioState.state_04 = 13;
        g_ScenarioState.step     = 15;
    }
    if (g_GameAreaId == AREA_ID_MACHINE_GUILD_DOCK) {
        if (SYS_TestFlag(g_SceneFlags, 10) == 0 && y > TO_COORD(42) - 1 && (u32)((x >> 16) - 32) < 5) {
            Game_SetScriptActive();
            g_ScenarioState.state_04 = 3;
            g_ScenarioState.step     = 0;
            return 1;
        }
        if (SYS_TestFlag(g_SceneFlags, 11) && SYS_TestFlag(g_SceneFlags, 13) == 0 && y <= TO_COORD(55) && (u32)((x >> 16) - 31) < 2) {
            Game_SetScriptActive();
            g_ScenarioState.state_04 = 4;
            g_ScenarioState.step     = 10;
            return 1;
        }
    }
    return 0;
}

MATCH u8 func_801FE2B0(void) {
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
        Party_MemberRemove(g_Game.members[i].chr.character_id);
    }
    EMI_PartyLoadArchives(CHAR_ID_RYU_ADULT, CHAR_ID_MOMO, CHAR_ID_NINA_ADULT, 0);
    g_Game.party_size = 0;
    Party_MemberJoin(CHAR_ID_RYU_ADULT);
    Party_MemberJoin(CHAR_ID_MOMO);
}

/* func_801FE3F8 */
MATCH void Party_JoinNinaAdult(void) {
    Party_MemberJoin(CHAR_ID_NINA_ADULT);
}

/* func_801FE418 */
MATCH void Party_JoinMomo(void) {
    Party_MemberJoin(CHAR_ID_MOMO);
}

MATCH void func_801FE438(void) {
    u8 ids[PARTY_SLOT_COUNT];
    u8 slot;

    for (slot = 0; slot < PARTY_SLOT_COUNT; slot++) {
        ids[slot] = D_80144908[slot];
    }
    EMI_PartyLoadArchives(ids[0], ids[1], ids[2], 0);
    for (slot = 0; slot < PARTY_SLOT_COUNT; slot++) {
        if (ids[slot] != CHAR_ID_RYU_ADULT) {
            Party_MemberJoin(ids[slot]);
        }
    }
}

#include "overlays/scenario/shared/Scene_RebuildRyuGarrParty.h"

MATCH void func_801FE5B0(void) {
    g_Characters[g_CharSlot[5]].party_flags &= 254;
    Party_MemberRemove(CHAR_ID_MOMO);
    Party_LoadPalettes();
}

#include "overlays/scenario/shared/Scene_RemoveMomo.h"

MATCH void func_801FE63C(void) {
    u8 ids[PARTY_SLOT_COUNT];
    u8 slot;

    for (slot = 0; slot < PARTY_SLOT_COUNT; slot++) {
        ids[slot] = g_Game.members[slot].chr.character_id;
    }
    for (slot = 0; slot < PARTY_SLOT_COUNT; slot++) {
        if (ids[slot] != CHAR_ID_RYU_ADULT) {
            Party_MemberRemove(ids[slot]);
        }
    }
    Party_LoadPalettes();
}

#include "overlays/scenario/shared/Scene_StashPartyExceptRyuAdult.h"
