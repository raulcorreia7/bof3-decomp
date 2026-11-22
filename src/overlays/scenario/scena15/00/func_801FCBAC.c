#include "scena15_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* Scene 15's step script: the rooftop approach, the battle and the world-map return. */
MATCH void func_801FCBAC(void) {
    u8 slot;

    switch (g_ScenarioState.step) {
        case 0:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaDrawFlags = 0xFB;
            UI_ModeSet(1);
            g_ScenarioState.step = 1;
            g_ScriptVars[0]++;
            EMI_ArchiveLoad(0x293);
            break;
        case 1:
            if (!EMI_IsReady()) {
                break;
            }
            if (g_ScriptVars[0] != 5) {
                break;
            }
            SND_BGMRequest(0x5F);
            g_ScenarioState.step = 2;
            break;
        case 2:
            if (g_ScriptVars[0] != 8) {
                break;
            }
            slot = Actor_FindFreeSpawned();
            if (slot != GAME_NONE) {
                g_SpawnedActors[slot].header.flags = 1;
                g_SpawnedActors[slot].type         = 0xA9;
            }
            g_ScenarioState.step = 3;
            break;
        case 3:
            if (g_ScriptVars[0] != 9) {
                break;
            }
            g_ScenarioState.timer_06 = 0x1E;
            g_ScenarioState.step     = 4;
            break;
        case 4:
            if (--g_ScenarioState.timer_06 == 0) {
                g_ScenarioState.step = 5;
                g_ScriptVars[0]++;
            }
            break;
        case 5:
            if (g_ScriptVars[0] != 0xB) {
                break;
            }
            if (!EMI_IsReady()) {
                break;
            }
            if (!(u8)Scene_SpawnActor(0x31, g_AreaCameraAngle.vx, D_801492DA, D_801492DC, 0x20, 0x380)) {
                break;
            }
            SND_BGMPlay(0x5F, 100, 8);
            g_ScenarioState.step = 6;
            break;
        case 6:
            if (g_SpawnedActors[D_801FE748].header.flags & 1) {
                break;
            }
            g_ScenarioState.timer_06 = 0x1E;
            g_ScenarioState.step     = 7;
            break;
        case 7:
            if (--g_ScenarioState.timer_06 != 0) {
                break;
            }
            slot = Actor_FindFreeSpawned();
            if (slot != GAME_NONE) {
                g_SpawnedActors[slot].header.flags = 1;
                g_SpawnedActors[slot].type         = 0xA8;
            }
            g_AreaDrawFlags = 0x1F;
            func_801BFE34(TO_COORD(0x17), TO_COORD(0x12), 0x22);
            g_ScenarioState.step = 8;
            break;
        case 8:
            g_ScenarioState.step = 9;
            g_ScriptVars[0]++;
            break;
        case 9:
            if (g_ScriptVars[0] != 0xD) {
                break;
            }
            g_ScenarioState.step = 0xA;
            break;
        case 10:
            if (g_ScriptVars[0] != 0xE) {
                break;
            }
            SND_StartDecrescendo(0, 0, 100, 0x10);
            g_ScenarioState.step = 0xB;
            break;
        case 11:
            if (g_ScriptVars[0] != 0xF) {
                break;
            }
            slot = Actor_FindFreeSpawned();
            if (slot != GAME_NONE) {
                g_SpawnedActors[slot].header.flags = 1;
                g_SpawnedActors[slot].type         = 0xAA;
            }
            SND_SeqStop(0, 0);
            g_ScenarioState.timer_06 = 4;
            g_ScenarioState.step     = 0xC;
            break;
        case 12:
            if (--g_ScenarioState.timer_06 != 0) {
                break;
            }
            if (!(u8)Scene_SpawnActor(0x31, g_AreaCameraAngle.vx, D_801492DA, D_801492DC, 0x20, 0)) {
                break;
            }
            g_ScenarioState.step = 0xD;
            break;
        case 13:
            if (g_SpawnedActors[D_801FE748].header.flags & 1) {
                break;
            }
            func_801C7A54(0x37);
            g_ScenarioState.step = 0xE;
            break;
        case 15:
            if (!EMI_IsReady()) {
                break;
            }
            g_ScriptVars[0] = 0;
            EMI_ArchiveLoad(0x294);
            func_801BE1B0(1);
            g_ScenarioState.step = 0x10;
            break;
        case 16:
            if (!EMI_IsReady()) {
                break;
            }
            if (g_ScriptVars[0] != 1) {
                break;
            }
            slot = Actor_FindFreeSpawned();
            if (slot != GAME_NONE) {
                g_SpawnedActors[slot].header.flags = 1;
                g_SpawnedActors[slot].type         = 0xAB;
            }
            g_ScenarioState.timer_06 = 0x3C;
            g_ScenarioState.step     = 0x11;
            break;
        case 17:
            if (--g_ScenarioState.timer_06 != 0) {
                break;
            }
            D_801FE74C = 0;
            func_801FDB84();
            SND_SEPlay(0x206);
            g_ScenarioState.timer_06 = 0x3C;
            g_ScenarioState.step     = 0x12;
            break;
        case 18:
            if (--g_ScenarioState.timer_06 == 0) {
                g_ScriptVars[0]      = 2;
                g_ScenarioState.step = 0x13;
            }
            func_801FDB84();
            break;
        case 19:
            if (g_ScriptVars[0] == 0) {
                g_ScenarioState.timer_06 = 0x3C;
                g_ScenarioState.step     = 0x14;
            }
            func_801FDB84();
            break;
        case 20:
            if (--g_ScenarioState.timer_06 == 0) {
                UI_ModeSet(0);
                g_ScenarioState.step = 0x15;
            }
            func_801FDB84();
            break;
        case 21:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaDrawFlags = 0;
            SND_SEPlay(0x206);
            g_ScenarioState.timer_06 = 0x78;
            g_ScenarioState.step     = 0x16;
            break;
        case 22:
            if (--g_ScenarioState.timer_06 != 0) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 0x13);
            func_8019FA28(0xAE, TO_COORD(0x35), TO_COORD(0x27), 0);
            g_GameEntryMode      = 0xFF;
            g_GamePrevSelection  = 0xFF;
            g_ScenarioState.step = 0x17;
            break;
        case 23:
            if (g_ScriptVars[0] != 3) {
                break;
            }
            SND_BGMRequest(0x5F);
            D_801FE750 = 1;
            D_801FE754 = 4;
            SND_SEPlay(0x205);
            g_ScenarioState.timer_06 = 8;
            g_ScenarioState.step     = 0x18;
            break;
        case 24:
            if (--g_ScenarioState.timer_06 != 0) {
                break;
            }
            D_801FE750           = 0;
            g_ScenarioState.step = 0x19;
            g_ScriptVars[0]++;
            break;
        case 25:
            if (g_ScriptVars[0] != 7) {
                break;
            }
            SND_BGMPlay(0x5F, 100, 8);
            D_801FE750           = 1;
            D_801FE754           = 3;
            g_ScenarioState.step = 0x1A;
            break;
        case 26:
            if (g_ScriptVars[0] != 9) {
                break;
            }
            slot = Actor_FindFreeSpawned();
            if (slot != GAME_NONE) {
                g_SpawnedActors[slot].header.flags = 1;
                g_SpawnedActors[slot].type         = 0xAD;
            }
            g_ScenarioState.step = 0x1B;
            break;
        case 27:
            if (g_ScriptVars[0] != 0xB) {
                break;
            }
            func_8019FA28(0xC6, TO_COORD(0x17), TO_COORD(0x12), 0x82);
            g_GamePrevSelection  = 0x5F;
            g_ScenarioState.step = 0x1C;
            break;
        case 28:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            slot = Actor_FindFreeSpawned();
            if (slot != GAME_NONE) {
                g_SpawnedActors[slot].header.flags = 1;
                g_SpawnedActors[slot].type         = 0xAE;
            }
            g_ScenarioState.timer_06 = 0xC;
            g_ScenarioState.step     = 0x1D;
            break;
        case 29:
            if (--g_ScenarioState.timer_06 != 0) {
                break;
            }
            g_ScenarioState.step = 0x1E;
            g_ScriptVars[0]++;
            break;
        case 30:
            if (g_ScriptVars[0] != 0) {
                break;
            }
            UI_ModeSet(0);
            g_ScenarioState.step = 0x1F;
            break;
        case 31:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaDrawFlags = 0;
            UI_MessageStartArea(0xA);
            g_GameStateIndex     = 2;
            g_ScenarioState.step = 0x20;
            break;
        case 32:
            if (g_GameStateIndex == 2) {
                break;
            }
            g_ScenarioState.step = 0x21;
            break;
        case 33:
            SYS_SetFlag(g_SceneFlags, 0x14);
            func_8019FA28(0xAE, TO_COORD(0x34), TO_COORD(0x27), 0x94);
            g_GameEntryMode      = 0xFF;
            g_GamePrevSelection  = 0x5F;
            g_ScenarioState.step = 0x22;
            break;
        case 34:
            if (g_ScriptVars[0] != 3) {
                break;
            }
            UI_ModeSet(0);
            g_ScenarioState.step = 0x23;
            break;
        case 35:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaDrawFlags = 0;
            UI_MessageStartArea(0x6B);
            g_GameStateIndex     = 2;
            g_ScenarioState.step = 0x24;
            break;
        case 36:
            if (g_GameStateIndex == 2) {
                break;
            }
            g_ScenarioState.step = 0x25;
            break;
        case 37:
            func_8019FA28(0xC6, TO_COORD(0x17), TO_COORD(0x12), 0x82);
            g_GameEntryMode      = 0xFF;
            g_GamePrevSelection  = 0x5F;
            g_ScenarioState.step = 0x26;
            break;
        case 38:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            g_ScriptVars[0] = 0;
            UI_ModeSet(0);
            g_ScenarioState.step = 0x27;
            break;
        case 39:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaDrawFlags = 0;
            UI_MessageStartArea(0xC);
            g_GameStateIndex     = 2;
            g_ScenarioState.step = 0x28;
            break;
        case 40:
            if (g_GameStateIndex == 2) {
                break;
            }
            g_ScenarioState.step = 0x29;
            break;
        case 41:
            SYS_SetFlag(g_SceneFlags, 0x15);
            SYS_SetFlag(g_SceneEventFlags, 0x58);
            func_8019FA28(0xAD, TO_COORD(0x2E), TO_COORD(0x61), 0);
            g_GameEntryMode      = 0xFF;
            g_GamePrevSelection  = 0xA1;
            g_ScenarioState.step = 0x2A;
            break;
        case 42:
            if (g_ScriptVars[0] != 1) {
                break;
            }
            g_AreaSceneMode      = 2;
            g_ScenarioState.step = 0x2B;
            break;
        case 43:
            if (g_ScriptVars[0] != 3) {
                break;
            }
            g_ScriptVars[0] = 0;
            UI_ModeSet(0);
            g_ScenarioState.step = 0x2C;
            break;
        case 44:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaDrawFlags = 0;
            UI_MessageStartArea(0xC);
            g_GameStateIndex     = 2;
            g_ScenarioState.step = 0x2D;
            break;
        case 45:
            if (g_GameStateIndex == 2) {
                break;
            }
            g_ScenarioState.step = 0x2E;
            break;
        case 46:
            func_8019FA28(0xC6, TO_COORD(0x17), TO_COORD(0x12), 0x82);
            g_GameEntryMode      = 0xFF;
            g_GamePrevSelection  = 0x5F;
            g_ScenarioState.step = 0x2F;
            break;
        case 47:
            if (g_ScriptVars[0] != 2) {
                break;
            }
            D_801FE754           = 3;
            g_ScenarioState.step = 0x30;
            break;
        case 48:
            if (g_ScriptVars[0] != 3) {
                break;
            }
            if (!(u8)Scene_SpawnActor(0x31, g_AreaCameraAngle.vx, D_801492DA, D_801492DC, 0x80, 0xB00)) {
                break;
            }
            g_ScenarioState.step = 0x31;
            break;
        case 49:
            if (g_AreaCameraOffsetZ < 0x781) {
                break;
            }
            SYS_SetFlag(g_SceneFlags, 0x16);
            func_8019FA28(0x95, TO_COORD(0x8), TO_COORD(0xC), 0x82);
            g_GameEntryMode      = 8;
            g_GameRequestType    = 9;
            g_GamePrevSelection  = 0x5F;
            g_ScenarioState.step = 0x32;
            break;
        case 50:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_ScenarioState.step = 0x33;
            break;
        case 51:
            if (g_ScriptVars[0] == 0x15) {
                SND_StartDecrescendo(0, 0, 100, 8);
                SND_SEPlay(2);
                UI_ModeSet(0xF);
                g_ScenarioState.step = 0x34;
            }
            func_801F32D4();
            break;
        case 52:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            SND_SeqStop(0, 0);
            g_AreaDrawFlags = 0;
            UI_ModeSet(0x10);
            g_ScenarioState.step = 0x35;
            break;
        case 53:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_ScenarioState.timer_06 = 0x96;
            g_ScenarioState.step     = 0x36;
            break;
        case 54:
            if (--g_ScenarioState.timer_06 != 0) {
                break;
            }
            func_8019FA28(0xC7, TO_COORD(0xB6), TO_COORD_HALF(0x12), 7);
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step     = 0;
            D_80143F49               = 0;
            D_80146258 &= 0xFFF7;
            func_801A78F8();
            break;
    }
    func_801FDC10(D_801FE754);
}
