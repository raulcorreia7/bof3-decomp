#include "scena10_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FC280(void) {
    u8 i;

    switch (g_ScenarioState.step) {
        case 0:
            for (i = 0; i < g_Game.party_size; i++) {
                if ((u8)g_Game.members[i].u.field.mode.value == 3) {
                    break;
                }
            }
            if (i == g_Game.party_size) {
                D_801FE9DC = 0;
                func_801BE1B0(0);
                g_ScenarioState.step = 1;
            }
            break;
        case 1:
            if (g_ScriptVars[0] == 2) {
                UI_ModeSet(0);
                for (i = 0; i < g_PartySize; i++) {
                    D_80144908[i] = g_Game.members[i].chr.character_id;
                }
                g_ScenarioState.step = 2;
            }
            break;
        case 2:
            if (g_SysThreads[2].state == 0) {
                g_AreaDrawFlags = 0;
                func_801C1E3C(2);
                g_ScenarioState.step = 3;
            }
            break;
        case 3:
            SYS_SetFlag(g_SceneFlags, 0x12);
            func_8019FA28(0x79, TO_COORD(43), TO_COORD(57), 0x80);
            g_GameRequestType    = 0xFF;
            g_GameEntryMode      = 0xFF;
            g_GamePrevSelection  = 0x86;
            g_ScenarioState.step = 4;
            break;
        case 4:
            if (g_SysThreads[2].state == 0) {
                g_AreaSceneMode = 2;
                g_AreaDrawFlags = 0x1F;
                UI_ModeSet(1);
                g_AreaCameraAngle.vx = -0x3B2;
                g_AreaCameraAngle.vz = 0x200;
                g_AreaCameraOffsetZ  = 0x55C;
                func_801BE1B0(0);
                func_801C601C(1);
                g_ScenarioState.step = 5;
            }
            break;
        case 5:
            if (g_ScriptVars[0] == 2) {
                g_ScenarioState.step = 6;
            }
            break;
        case 6:
            D_801FE9D8 = func_8019601C();
            if (D_801FE9D8 != 0xFF) {
                g_SpawnedActors[D_801FE9D8].header.flags   = 1;
                g_SpawnedActors[D_801FE9D8].type           = 0x31;
                g_SpawnedActors[D_801FE9D8].camera_angle.x = -0x1A2;
                g_SpawnedActors[D_801FE9D8].camera_angle.y = g_AreaCameraAngle.vy;
                g_SpawnedActors[D_801FE9D8].camera_angle.z = g_AreaCameraAngle.vz;
                g_SpawnedActors[D_801FE9D8].vx             = -0x2A4;
                g_SpawnedActors[D_801FE9D8].layer          = 0x3E;
                func_8019FA28(0x83, TO_COORD(7), TO_COORD(92), 0x81);
                g_GameEntryMode      = 0xD;
                g_ScenarioState.step = 7;
            }
            break;
        case 7:
            if (g_SysThreads[2].state == 0 && g_ScriptVars[0] == 3) {
                Game_ClearScriptActive();
                g_ScriptVars[0] = 0;
                SYS_SetFlag(g_SceneFlags, 0x18);
                g_ScenarioState.step = 9;
            }
            break;
        case 10:
            func_801BE1B0(2);
            g_ScenarioState.step = 11;
            break;
        case 11:
            if (g_ScriptVars[0] == 2) {
                g_ScenarioState.step = 12;
            }
            break;
        case 12:
            if (EMI_IsReady()) {
                g_ScenarioState.step = 13;
                g_ScriptVars[0]++;
            }
            break;
        case 13:
            if (g_ScriptVars[0] == 5) {
                UI_ModeSet(0);
                g_ScenarioState.step = 14;
            }
            break;
        case 14:
            if (g_SysThreads[2].state == 0) {
                g_AreaDrawFlags = 0;
                func_801C1DF0(4);
                g_ScenarioState.step = 15;
            }
            break;
        case 15:
            g_ScriptVars[0] = 0;
            SYS_SetFlag(g_SceneFlags, 0x12);
            func_8019FA28(0x79, TO_COORD(39), TO_COORD(55), 7);
            g_GameEntryMode = 0xFF;
            Game_ClearScriptActive();
            if (SYS_TestFlag(g_SceneFlags, 0x1A)) {
                SYS_SetFlag(D_8014554F, 9);
            }
            func_801A78F8();
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step     = 0;
            break;
        case 20:
            if (g_SysThreads[2].state == 0) {
                Game_ClearScriptActive();
                g_AreaDrawFlags = 0x1F;
                UI_ModeSet(0xB);
                func_801A78F8();
                g_ScenarioState.state_04 = 0;
                g_ScenarioState.step     = 0;
            }
            break;
    }
    if (g_ScenarioState.step >= 7) {
        func_801FC220();
    }
}
