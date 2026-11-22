#include "scena01_00.h"
#include "area/map.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F8050(void) {
    s32 phase;
    u32 scene_flags;
    u8* flags_byte;

    if (g_GameAreaId == 0) {
        phase = g_ScriptVars[2];
        if (phase != 1) {
            if (phase < 2 && phase == 0) {
                if (!SYS_TestFlag(g_SceneFlags, 0x3A)) {
                    SND_BGMRequest(0);
                    while (!EMI_IsReady()) {
                        SYS_ThreadWait(1);
                    }
                    SCRIPT_VARS_CLEAR_ALL();
                    g_AreaDrawFlags          = 0;
                    g_ScenarioState.step     = 0;
                    g_ScenarioState.state_04 = 0xD;
                }
            }
        } else {
            if (!SYS_TestFlag(g_SceneFlags, 0x3A)) {
                g_AreaCameraRefreshCount = 2;
                g_AreaCameraOffsetZ += 0xA00;
            }
        }
    }
    if (g_GameAreaId == 5) {
        switch (g_ScriptVars[2]) {
            case 0:
                if (!SYS_TestFlag(g_SceneFlags, 0x15)) {
                    g_ScriptVars[0]          = 0;
                    g_AreaDrawFlags          = 0;
                    g_ScenarioState.step     = 0;
                    g_ScenarioState.state_04 = 0xC;
                    g_GameFlags |= 7;
                }
                break;
            case 1:
                SND_BGMRequest(8);
                while (!EMI_IsReady()) {
                    SYS_ThreadWait(1);
                }
                break;
            case 2:
                g_AreaDrawFlags = 0x1F;
                g_GameFlags ^= 7;
                break;
            case 5:
                g_AreaDrawFlags = 0x1F;
                break;
            case 4:
                g_ScenarioState.step     = 3;
                g_ScriptVars[0]          = 0;
                g_ScenarioState.state_04 = 0x10;
                break;
        }
    }
    if (g_GameAreaId == 7) {
        if (!SYS_TestFlag(g_SceneFlags, 0x19)) {
            Game_SetScriptActive();
            g_ScriptVars[0]          = 0;
            g_AreaDrawFlags          = 0;
            g_ScenarioState.step     = 0;
            g_ScenarioState.state_04 = 0xB;
        }
    }
    if (g_GameAreaId == 8) {
        switch (g_ScriptVars[2]) {
            case 0:
            case 1:
                break;
            case 2:
                if (!SYS_TestFlag(g_SceneFlags, 6)) {
                    g_ScenarioState.step     = 0;
                    g_ScenarioState.state_04 = 6;
                    g_GameFlags |= 6;
                }
                break;
            case 3:
                if (!SYS_TestFlag(g_SceneFlags, 5)) {
                    SND_SeqStop(0, 0);
                    g_ScenarioState.step     = 0xA;
                    g_ScenarioState.state_04 = 6;
                }
                break;
            case 4:
                SCRIPT_VARS_CLEAR_ALL();
                g_ScenarioState.timer_06 = 0;
                SND_SeqStop(0, 0);
                g_AreaDrawFlags = 0x1F;
                break;
        }
    }
    if (g_GameAreaId == 9) {
        if (!SYS_TestFlag(g_SceneFlags, 0)) {
            if (g_ScriptVars[2] == 0) {
                g_AreaDrawFlags = 0;
                Game_SetScriptActive();
                g_ScenarioState.step     = 0;
                g_ScenarioState.state_04 = 1;
            }
        }
    }
    if (g_GameAreaId == 0xA) {
        switch (g_ScriptVars[2]) {
            case 0:
                if (!SYS_TestFlag(g_SceneFlags, 1)) {
                    g_AreaDrawFlags          = 0x1F;
                    g_ScenarioState.state_04 = 2;
                }
                break;
            case 3:
            case 4:
                g_ScenarioState.state_04 = 7;
                g_GameFlags |= 2;
                break;
            case 7:
                if (!SYS_TestFlag(g_SceneFlags, 1)) {
                    g_ScratchPad.cells.bytes[0] = Actor_FindFreeSpawned();
                    if (g_ScratchPad.cells.bytes[0] != GAME_NONE) {
                        g_SpawnedActors[g_ScratchPad.cells.bytes[0]].header.flags = 1;
                        g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type         = 0x12;
                    }
                    g_ScenarioState.state_04 = 2;
                }
                break;
            case 8:
                g_AreaDrawFlags = 0x1F;
                break;
        }
    }
    if (g_GameAreaId == 0xD) {
        {
            u8* script_phase = &g_ScriptVars[2];

            if (*script_phase == 1) {
                g_AreaDrawFlags = 0x1F;
            }
            if (SYS_TestFlag(g_SceneFlags, 0x3C) && !SYS_TestFlag(g_SceneFlags, 0x3E) && g_GameCellType == 1) {
                g_AreaDrawFlags = 0;
                Game_SetScriptActive();
                g_ScriptVars[0]          = 0;
                g_ScriptVars[1]          = 0;
                *script_phase            = 0;
                g_ScenarioState.step     = 0;
                g_ScenarioState.state_04 = 0xE;
            }
        }
    }
    if (g_GameAreaId == 0xE) {
        {
            u8* script_phase = &g_ScriptVars[2];

            if (*script_phase == 0) {
                if (!SYS_TestFlag(g_SceneFlags, 0x1B)) {
                    g_ScriptVars[0] = 0;
                    g_ScriptVars[1] = 0;
                    *script_phase   = 0;
                    g_ScriptVars[3] = 0;
                    SCENARIO_RETURN_TO_START();
                } else if (!SYS_TestFlag(g_SceneFlags, 0x1C)) {
                    scene_flags     = g_SceneFlags;
                    g_ScriptVars[0] = 0;
                    g_ScriptVars[1] = 0;
                    *script_phase   = 0;
                    g_ScriptVars[3] = 0;
                    SYS_SetFlag(scene_flags, 0x1C);
                    func_801C1DF0(1);
                    g_AreaCameraRefreshCount = 2;
                    g_AreaCameraOffsetZ += 0xB80;
                }
            }
        }
    }
    if (g_GameAreaId == 0x11) {
        SCRIPT_VARS_CLEAR_ALL();
        SCENARIO_RETURN_TO_START();
    }
    if (g_GameAreaId == 0x16) {
        if (!SYS_TestFlag(g_SceneFlags, 0xB)) {
            g_ScenarioState.step     = 0;
            g_ScenarioState.state_04 = 9;
            SYS_SetFlag(g_SceneFlags, 0xB);
        } else if (!SYS_TestFlag(g_SceneFlags, 0xC)) {
            g_ScenarioState.step     = 3;
            g_ScenarioState.state_04 = 9;
        } else if (!SYS_TestFlag(g_SceneFlags, 0xD)) {
            Game_SetScriptActive();
            g_ScenarioState.step     = 8;
            g_ScenarioState.state_04 = 9;
            SYS_SetFlag(g_SceneFlags, 0xD);
        } else if (!SYS_TestFlag(g_SceneFlags, 0xF)) {
            g_ScenarioState.step     = 9;
            g_ScenarioState.state_04 = 9;
        } else if (!SYS_TestFlag(g_SceneFlags, 0x10)) {
            g_ScenarioState.step     = 0x11;
            g_ScenarioState.state_04 = 9;
        }
    }
    if (g_GameAreaId == 0x17) {
        switch (g_ScriptVars[2]) {
            case 0:
                if (!SYS_TestFlag(g_SceneFlags, 9)) {
                    SCRIPT_VARS_CLEAR_ALL();
                    g_ScenarioState.step     = 0;
                    g_ScenarioState.state_04 = 8;
                }
                break;
            case 1:
                if (!SYS_TestFlag(g_SceneFlags, 0xA)) {
                    SND_SeqStop(0, 0);
                    g_ScenarioState.step     = 0x13;
                    g_ScenarioState.state_04 = 8;
                }
                break;
            case 2:
                if (!SYS_TestFlag(g_SceneFlags, 0xA)) {
                    g_ScenarioState.step     = 0x37;
                    g_ScenarioState.state_04 = 8;
                }
                break;
            case 3:
                g_ScratchPad.cells.bytes[0] = Actor_FindFreeSpawned();
                if (g_ScratchPad.cells.bytes[0] != GAME_NONE) {
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].header.flags = 1;
                    g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type         = 0x11;
                    func_801C1DF0(2);
                }
                break;
            case 4:
                if (!SYS_TestFlag(g_SceneFlags, 0x39)) {
                    flags_byte = &g_ScenarioState.flags_01;
                    *flags_byte &= 0xFE;
                    Area_BundleRunOpcodes();
                    Area_CellSetPalette(0x49, 0xC);
                    g_AreaDrawFlags = 0;
                    SYS_SetFlag(g_SceneFlags, 0x39);
                    SYS_SetFlag(g_SceneFlags, 0x3F);
                }
                break;
            case 5:
                g_ScriptVars[0] = 0;
                break;
            case 7:
                g_ScenarioState.step     = 0x37;
                g_ScenarioState.state_04 = 8;
                break;
        }
    }
    if (g_GameAreaId == 0x21 || g_GameAreaId == 0x10) {
        SCRIPT_VARS_CLEAR_ALL();
        g_ScenarioState.state_04 = 0;
        g_ScenarioState.step     = 0;
        g_ScenarioState.timer_06 = 0;
    }
    g_ScenarioState.mode_02 = 2;
}
