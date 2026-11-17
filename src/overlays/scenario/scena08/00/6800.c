#include "scena08_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FD400(void) {
    u8 slot;

    switch (g_SceneState.step_05) {
        case 0:
            Game_ClearScriptActive();
            Scene_SetupParty(1);
            g_SceneState.state_04 = 0;
            g_SceneState.step_05  = 0;
            break;
        case 10:
            slot                        = Actor_FindFreeSpawned();
            g_ScratchPad.cells.bytes[0] = slot;
            if ((slot & BYTE_MASK) != GAME_NONE) {
                g_SpawnedActors[slot].header.flags                          = ACTOR_FLAG_IN_USE;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type           = 0x13;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.x = -748;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.y = g_AreaCameraAngle.vy;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].camera_angle.z = 182;
                g_SpawnedActors[g_ScratchPad.cells.bytes[0]].layer          = 0x20;
                g_SceneState.step_05                                        = 11;
            }
            break;
        case 11:
            if (g_ScriptVars[0] == 0x6) {
                slot       = Actor_FindFreeSpawned();
                D_801FEA6C = slot;
                if ((slot & BYTE_MASK) != GAME_NONE) {
                    g_SpawnedActors[slot].header.flags         = ACTOR_FLAG_IN_USE;
                    g_SpawnedActors[D_801FEA6C].type           = 0x13;
                    g_SpawnedActors[D_801FEA6C].camera_angle.x = -682;
                    g_SpawnedActors[D_801FEA6C].camera_angle.y = g_AreaCameraAngle.vy;
                    g_SpawnedActors[D_801FEA6C].camera_angle.z = ANGLE_45;
                    g_SpawnedActors[D_801FEA6C].layer          = 0x20;
                    g_SceneState.step_05                       = 12;
                }
            }
            break;
        case 12:
            if ((g_SpawnedActors[D_801FEA6C].header.flags & ACTOR_FLAG_IN_USE) == 0) {
                Game_ClearScriptActive();
                SYS_SetFlag(g_SceneFlags, 0x14);
                g_SceneState.state_04 = 0;
                g_SceneState.step_05  = 0;
            }
            break;
    }
}

INCLUDE_ASM(func_801FD704);

MATCH void func_801FDF84(void) {
    g_Characters[CHAR_INDEX_REI].exp += 10000;
    Char_GetExp(CHAR_INDEX_REI);
    g_Characters[CHAR_INDEX_REI].equip.weapon = WEAPON_MOON_SWORD;
    g_Characters[CHAR_INDEX_REI].equip.shield = ARMOR_STEEL_GAUNTLETS;
    g_Characters[CHAR_INDEX_REI].equip.helmet = ARMOR_BANDANA;
    g_Characters[CHAR_INDEX_REI].equip.armor  = ARMOR_LIGHT_CLOTHING;
    Char_RebuildStats(&g_Characters[CHAR_INDEX_REI]);
    Char_RestoreHP(CHAR_INDEX_REI, 0, 0);
    Char_RestoreAP(CHAR_INDEX_REI, 0, 0);
}

#include "overlays/scenario/Scene_DispatchActor.h"

MATCH void func_801FE058(void) {
    g_ScriptVars[0] = 0;
    Game_SetScriptActive();
    g_SceneState.state_04 = 7;
    g_SceneState.timer_06 = 32;
    g_SceneState.step_05  = 0;
}

MATCH void func_801FE0A0(void) {
    g_ScriptVars[0] = 0;
    Game_SetScriptActive();
    g_SceneState.state_04 = 7;
    g_SceneState.step_05  = 0xA;
}

MATCH void func_801FE0E0(void) {
    g_ScriptVars[0] = 0;
    Game_SetScriptActive();
    g_SceneState.state_04 = 10;
    g_SceneState.step_05  = 0;
    SYS_SetFlag(g_SceneFlags, 19);
}

MATCH void func_801FE12C(void) {
    s32 index;
    u8* item;

    item  = g_VitalItemIds;
    index = 0;
    do {
        if (*item == 4) {
            *item = 0xE;
        }
        index += 1;
        item += 1;
    } while ((index & BYTE_MASK) < 0x20U);
}

MATCH s32 func_801FE170(s32 x, s32 y) {
    if ((LOHU(g_GameAreaId) == AREA_ID_DAUNA_MINE_ADULT) && (x == TO_COORD(51) + COORD_HALF) && (((y >> 16) - 39) < 2U)) {
        if (SYS_TestFlag(g_SceneFlags, 6) == 0) {
            Game_SetScriptActive();
            g_SceneState.state_04 = 4;
            g_SceneState.step_05  = 5;
            return 1;
        }
        if (SYS_TestFlag(g_SceneFlags, 7) == 0) {
            Game_SetScriptActive();
            *g_ScriptVars         = 0;
            g_SceneState.state_04 = 5;
            g_SceneState.step_05  = 0;
            return 1;
        }
        goto block_7;
    }
block_7:
    if ((LOHU(g_GameAreaId) == AREA_ID_MOUNT_LEVETT) && (x == TO_COORD(56) + COORD_HALF) && (((y >> 16) - 46) < 4U)) {
        SYS_SetFlag(g_SceneFlags, 22U);
    }
    return 0;
}

#ifdef NON_MATCHING
NON_MATCHING void func_801FE2A0(void) {
}
#else
INCLUDE_ASM(func_801FE2A0);
#endif

/* func_801FE698 */
MATCH void Scene_SetPartyWhelp(void) {
    EMI_LoadPartyArchives(CHAR_ID_RYU_ADULT, CHAR_ID_GARR, CHAR_ID_WHELP, 0);
    g_Game.party_size = 0;
    Party_JoinMember(CHAR_ID_WHELP);
    Party_LoadPalettes();
}

/* func_801FE6DC */
MATCH void Scene_SetPartyRyuAdult(void) {
    g_Characters[g_CharSlot[10]].party_flags &= ~PARTY_FLAG_JOINED;
    g_Game.party_size = 0;
    Party_JoinMember(CHAR_ID_RYU_ADULT);
}

/* func_801FE740 */
MATCH void Party_JoinGarr(void) {
    Party_JoinMember(CHAR_ID_GARR);
}

MATCH void func_801FE760(void) {
    EMI_LoadPartyArchives(CHAR_ID_RYU_ADULT, CHAR_ID_GARR, CHAR_ID_REI, 0);
    g_Game.party_size = 0;
    Party_JoinMember(CHAR_ID_RYU_ADULT);
    Party_JoinMember(CHAR_ID_GARR);
    Party_LoadPalettes();
}

#include "overlays/scenario/Scene_SetPartyRyuAdultGarrNinaAdult.h"

MATCH void func_801FE800(void) {
    g_Game.party_size = 0;
    Party_JoinMember(CHAR_ID_RYU_ADULT);
    Party_JoinMember(CHAR_ID_NINA_ADULT);
    Party_JoinMember(CHAR_ID_REI);
    Party_LoadPalettes();
}

MATCH void func_801FE840(void) {
    EMI_LoadPartyArchives(CHAR_ID_RYU_ADULT, CHAR_ID_NINA_ADULT, CHAR_ID_REI, 0U);
    func_801FE800();
}

/* func_801FE874 */
MATCH void Party_RemoveGarr(void) {
    Party_RemoveMember(CHAR_ID_GARR);
}
