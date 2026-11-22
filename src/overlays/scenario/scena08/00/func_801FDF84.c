#include "scena08_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FDF84(void) {
    g_Characters[CHAR_INDEX_REI].exp += 10000;
    Char_ApplyLevelUps(CHAR_INDEX_REI);
    g_Characters[CHAR_INDEX_REI].equip.weapon = WEAPON_MOON_SWORD;
    g_Characters[CHAR_INDEX_REI].equip.shield = ARMOR_STEEL_GAUNTLETS;
    g_Characters[CHAR_INDEX_REI].equip.helmet = ARMOR_BANDANA;
    g_Characters[CHAR_INDEX_REI].equip.armor  = ARMOR_LIGHT_CLOTHING;
    Char_RebuildStats(&g_Characters[CHAR_INDEX_REI]);
    Char_HPRestore(CHAR_INDEX_REI, 0, 0);
    Char_APRestore(CHAR_INDEX_REI, 0, 0);
}

#include "overlays/scenario/shared/Scene_DispatchActor.h"

MATCH void func_801FE058(void) {
    g_ScriptVars[0] = 0;
    Game_SetScriptActive();
    g_ScenarioState.state_04 = 7;
    g_ScenarioState.timer_06 = 32;
    g_ScenarioState.step     = 0;
}

MATCH void func_801FE0A0(void) {
    g_ScriptVars[0] = 0;
    Game_SetScriptActive();
    g_ScenarioState.state_04 = 7;
    g_ScenarioState.step     = 0xA;
}

MATCH void func_801FE0E0(void) {
    g_ScriptVars[0] = 0;
    Game_SetScriptActive();
    g_ScenarioState.state_04 = 10;
    g_ScenarioState.step     = 0;
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
            g_ScenarioState.state_04 = 4;
            g_ScenarioState.step     = 5;
            return 1;
        }
        if (SYS_TestFlag(g_SceneFlags, 7) == 0) {
            Game_SetScriptActive();
            *g_ScriptVars            = 0;
            g_ScenarioState.state_04 = 5;
            g_ScenarioState.step     = 0;
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

/* Starts the scene script for the cell at x, y in the mine, the Cedar Woods house, the farm, the Ogre Road and the Mikba checkpoint; returns 1 when one starts. */
MATCH s32 func_801FE2A0(s32 x, s32 y) {
    if (LOHU(g_GameAreaId) == AREA_ID_DAUNA_MINE_ADULT && !SYS_TestFlag(g_SceneFlags, 5) && (u32)((x >> 16) - 0x1C) < 2 && (u32)((y >> 16) - 0x2B) < 2) {
        g_ScenarioState.state_04 = 4;
        g_ScenarioState.step     = 0;
        Game_SetScriptActive();
        return 1;
    }
    if (LOHU(g_GameAreaId) == AREA_ID_CEDAR_WOODS_HOUSE_AFTER_BALIO_SUNDER && SYS_TestFlag(g_SceneFlags, 0xB) && !SYS_TestFlag(g_SceneFlags, 0xD)) {
        if (x == TO_COORD(0x2F) && y <= TO_COORD(0x1F) && g_ScenarioState.state_04 != 8) {
            Game_SetScriptActive();
            g_ScenarioState.state_04 = 8;
            g_ScenarioState.step     = 10;
            g_ScenarioState.timer_06 = 20;
            return 1;
        }
        if (x == TO_COORD(0x1B) && y == TO_COORD(0x11) && !SYS_TestFlag(g_SceneFlags, 0x18)) {
            SYS_SetFlag(g_SceneFlags, 0x18);
            SND_SEPlay(0x201);
        }
        if (x == TO_COORD(0x16) && y == TO_COORD(0xD) && !SYS_TestFlag(g_SceneFlags, 0x19)) {
            SYS_SetFlag(g_SceneFlags, 0x19);
            SND_SEPlay(0x202);
        }
        if (x == TO_COORD(0x11) && y == TO_COORD(0x13) && !SYS_TestFlag(g_SceneFlags, 0x1A)) {
            SYS_SetFlag(g_SceneFlags, 0x1A);
            SND_SEPlay(0x203);
        }
        if (x == TO_COORD(7) && y == TO_COORD(0x13)) {
            SND_SEPlay(0x204);
            Game_SetScriptActive();
            g_ScenarioState.state_04 = 8;
            g_ScenarioState.step     = 20;
            return 1;
        }
    }
    if (LOHU(g_GameAreaId) == AREA_ID_FARM && !SYS_TestFlag(g_SceneFlags, 0x10) && SYS_TestFlag(g_SceneFlags, 0xF) && y <= 0x38000 && (u32)((x >> 16) - 0x1C) < 2) {
        Game_SetScriptActive();
        g_ScenarioState.state_04 = 9;
        g_ScenarioState.step     = 5;
        return 1;
    }
    if (LOHU(g_GameAreaId) == AREA_ID_OGRE_ROAD && !SYS_TestFlag(g_SceneFlags, 8) && (u32)((x >> 16) - 0x45) < 3 && (u32)((y >> 16) - 0x37) < 3) {
        g_ScratchPad.cells.bytes[0] = g_Game.members[0].facing;
        if (g_ScratchPad.cells.bytes[0] != 6 && g_ScratchPad.cells.bytes[0] != 7 && g_ScratchPad.cells.bytes[0] != 0) {
            g_ScenarioState.state_04 = 6;
            g_ScenarioState.step     = 0;
            Game_SetScriptActive();
            return 1;
        }
    }
    if (LOHU(g_GameAreaId) == AREA_ID_MIKBA_CHECKPOINT && SYS_TestFlag(g_SceneFlags, 0x14) && !SYS_TestFlag(g_SceneFlags, 0x15)) {
        if (y >= TO_COORD(0xF) && (u32)((x >> 16) - 0x20) < 6) {
            Game_SetScriptActive();
            g_ScenarioState.state_04 = 0xB;
            g_ScenarioState.step     = 0;
            g_ScriptVars[0]          = 0;
            return 1;
        }
    }
    return 0;
}

/* func_801FE698 */
MATCH void Scene_SetPartyWhelp(void) {
    EMI_PartyLoadArchives(CHAR_ID_RYU_ADULT, CHAR_ID_GARR, CHAR_ID_WHELP, 0);
    g_Game.party_size = 0;
    Party_MemberJoin(CHAR_ID_WHELP);
    Party_LoadPalettes();
}

/* func_801FE6DC */
MATCH void Scene_SetPartyRyuAdult(void) {
    g_Characters[g_CharSlot[10]].party_flags &= ~PARTY_FLAG_JOINED;
    g_Game.party_size = 0;
    Party_MemberJoin(CHAR_ID_RYU_ADULT);
}

/* func_801FE740 */
MATCH void Party_JoinGarr(void) {
    Party_MemberJoin(CHAR_ID_GARR);
}

MATCH void func_801FE760(void) {
    EMI_PartyLoadArchives(CHAR_ID_RYU_ADULT, CHAR_ID_GARR, CHAR_ID_REI, 0);
    g_Game.party_size = 0;
    Party_MemberJoin(CHAR_ID_RYU_ADULT);
    Party_MemberJoin(CHAR_ID_GARR);
    Party_LoadPalettes();
}

#include "overlays/scenario/shared/Scene_SetPartyRyuAdultGarrNinaAdult.h"

MATCH void func_801FE800(void) {
    g_Game.party_size = 0;
    Party_MemberJoin(CHAR_ID_RYU_ADULT);
    Party_MemberJoin(CHAR_ID_NINA_ADULT);
    Party_MemberJoin(CHAR_ID_REI);
    Party_LoadPalettes();
}

MATCH void func_801FE840(void) {
    EMI_PartyLoadArchives(CHAR_ID_RYU_ADULT, CHAR_ID_NINA_ADULT, CHAR_ID_REI, 0U);
    func_801FE800();
}

/* func_801FE874 */
MATCH void Party_RemoveGarr(void) {
    Party_MemberRemove(CHAR_ID_GARR);
}
