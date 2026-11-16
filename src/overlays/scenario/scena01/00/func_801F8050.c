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
                    SND_RequestBGM(0);
                    while (!EMI_IsReady()) {
                        SYS_ThreadWait(1);
                    }
                    g_ScriptVars[0]       = 0;
                    g_ScriptVars[1]       = 0;
                    g_ScriptVars[2]       = 0;
                    g_ScriptVars[3]       = 0;
                    g_AreaDrawFlags       = 0;
                    g_SceneState.step_05  = 0;
                    g_SceneState.state_04 = 0xD;
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
                    g_ScriptVars[0]       = 0;
                    g_AreaDrawFlags       = 0;
                    g_SceneState.step_05  = 0;
                    g_SceneState.state_04 = 0xC;
                    g_GameFlags |= 7;
                }
                break;
            case 1:
                SND_RequestBGM(8);
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
                g_SceneState.step_05  = 3;
                g_ScriptVars[0]       = 0;
                g_SceneState.state_04 = 0x10;
                break;
        }
    }
    if (g_GameAreaId == 7) {
        if (!SYS_TestFlag(g_SceneFlags, 0x19)) {
            Game_SetScriptActive();
            g_ScriptVars[0]       = 0;
            g_AreaDrawFlags       = 0;
            g_SceneState.step_05  = 0;
            g_SceneState.state_04 = 0xB;
        }
    }
    if (g_GameAreaId == 8) {
        switch (g_ScriptVars[2]) {
            case 0:
            case 1:
                break;
            case 2:
                if (!SYS_TestFlag(g_SceneFlags, 6)) {
                    g_SceneState.step_05  = 0;
                    g_SceneState.state_04 = 6;
                    g_GameFlags |= 6;
                }
                break;
            case 3:
                if (!SYS_TestFlag(g_SceneFlags, 5)) {
                    SND_StopSequence(0, 0);
                    g_SceneState.step_05  = 0xA;
                    g_SceneState.state_04 = 6;
                }
                break;
            case 4:
                g_ScriptVars[0]       = 0;
                g_ScriptVars[1]       = 0;
                g_ScriptVars[2]       = 0;
                g_ScriptVars[3]       = 0;
                g_SceneState.timer_06 = 0;
                SND_StopSequence(0, 0);
                g_AreaDrawFlags = 0x1F;
                break;
        }
    }
    if (g_GameAreaId == 9) {
        if (!SYS_TestFlag(g_SceneFlags, 0)) {
            if (g_ScriptVars[2] == 0) {
                g_AreaDrawFlags = 0;
                Game_SetScriptActive();
                g_SceneState.step_05  = 0;
                g_SceneState.state_04 = 1;
            }
        }
    }
    if (g_GameAreaId == 0xA) {
        switch (g_ScriptVars[2]) {
            case 0:
                if (!SYS_TestFlag(g_SceneFlags, 1)) {
                    g_AreaDrawFlags       = 0x1F;
                    g_SceneState.state_04 = 2;
                }
                break;
            case 3:
            case 4:
                g_SceneState.state_04 = 7;
                g_GameFlags |= 2;
                break;
            case 7:
                if (!SYS_TestFlag(g_SceneFlags, 1)) {
                    g_ScratchPad.cells.bytes[0] = Actor_FindFreeSpawned();
                    if (g_ScratchPad.cells.bytes[0] != GAME_NONE) {
                        g_SpawnedActors[g_ScratchPad.cells.bytes[0]].header.flags = 1;
                        g_SpawnedActors[g_ScratchPad.cells.bytes[0]].type         = 0x12;
                    }
                    g_SceneState.state_04 = 2;
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
            if (SYS_TestFlag(g_SceneFlags, 0x3C) && !SYS_TestFlag(g_SceneFlags, 0x3E) && D_80143F03 == 1) {
                g_AreaDrawFlags = 0;
                Game_SetScriptActive();
                g_ScriptVars[0]       = 0;
                g_ScriptVars[1]       = 0;
                *script_phase         = 0;
                g_SceneState.step_05  = 0;
                g_SceneState.state_04 = 0xE;
            }
        }
    }
    if (g_GameAreaId == 0xE) {
        {
            u8* script_phase = &g_ScriptVars[2];

            if (*script_phase == 0) {
                if (!SYS_TestFlag(g_SceneFlags, 0x1B)) {
                    g_ScriptVars[0]       = 0;
                    g_ScriptVars[1]       = 0;
                    *script_phase         = 0;
                    g_ScriptVars[3]       = 0;
                    g_SceneState.step_05  = 0;
                    g_SceneState.state_04 = 0;
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
        g_ScriptVars[0]       = 0;
        g_ScriptVars[1]       = 0;
        g_ScriptVars[2]       = 0;
        g_ScriptVars[3]       = 0;
        g_SceneState.step_05  = 0;
        g_SceneState.state_04 = 0;
    }
    if (g_GameAreaId == 0x16) {
        if (!SYS_TestFlag(g_SceneFlags, 0xB)) {
            g_SceneState.step_05  = 0;
            g_SceneState.state_04 = 9;
            SYS_SetFlag(g_SceneFlags, 0xB);
        } else if (!SYS_TestFlag(g_SceneFlags, 0xC)) {
            g_SceneState.step_05  = 3;
            g_SceneState.state_04 = 9;
        } else if (!SYS_TestFlag(g_SceneFlags, 0xD)) {
            Game_SetScriptActive();
            g_SceneState.step_05  = 8;
            g_SceneState.state_04 = 9;
            SYS_SetFlag(g_SceneFlags, 0xD);
        } else if (!SYS_TestFlag(g_SceneFlags, 0xF)) {
            g_SceneState.step_05  = 9;
            g_SceneState.state_04 = 9;
        } else if (!SYS_TestFlag(g_SceneFlags, 0x10)) {
            g_SceneState.step_05  = 0x11;
            g_SceneState.state_04 = 9;
        }
    }
    if (g_GameAreaId == 0x17) {
        switch (g_ScriptVars[2]) {
            case 0:
                if (!SYS_TestFlag(g_SceneFlags, 9)) {
                    g_ScriptVars[0]       = 0;
                    g_ScriptVars[1]       = 0;
                    g_ScriptVars[2]       = 0;
                    g_ScriptVars[3]       = 0;
                    g_SceneState.step_05  = 0;
                    g_SceneState.state_04 = 8;
                }
                break;
            case 1:
                if (!SYS_TestFlag(g_SceneFlags, 0xA)) {
                    SND_StopSequence(0, 0);
                    g_SceneState.step_05  = 0x13;
                    g_SceneState.state_04 = 8;
                }
                break;
            case 2:
                if (!SYS_TestFlag(g_SceneFlags, 0xA)) {
                    g_SceneState.step_05  = 0x37;
                    g_SceneState.state_04 = 8;
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
                    flags_byte = &D_80146871;
                    *flags_byte &= 0xFE;
                    Area_RunBundleOpcodes();
                    Area_SetCellPalette(0x49, 0xC);
                    g_AreaDrawFlags = 0;
                    SYS_SetFlag(g_SceneFlags, 0x39);
                    SYS_SetFlag(g_SceneFlags, 0x3F);
                }
                break;
            case 5:
                g_ScriptVars[0] = 0;
                break;
            case 7:
                g_SceneState.step_05  = 0x37;
                g_SceneState.state_04 = 8;
                break;
        }
    }
    if (g_GameAreaId == 0x21 || g_GameAreaId == 0x10) {
        g_ScriptVars[0]       = 0;
        g_ScriptVars[1]       = 0;
        g_ScriptVars[2]       = 0;
        g_ScriptVars[3]       = 0;
        g_SceneState.state_04 = 0;
        g_SceneState.step_05  = 0;
        g_SceneState.timer_06 = 0;
    }
    g_SceneState.mode_02 = 2;
}
