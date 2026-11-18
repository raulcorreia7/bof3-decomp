#include "scena02_00.h"
#include "area/map.h"
#include "area/spad.h"
#include "overlays/area/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F71FC(void) {
    u8* flags_byte;
    u16 area_id;

    if (g_GameAreaId == AREA_ID_MCNEIL) {
        if (!SYS_TestFlag(g_SceneFlags, 0x37)) {
            g_AreaDrawFlags = 0x1F;
        }
        if (SYS_TestFlag(g_SceneFlags, 0x19)) {
            SYS_SetFlag(g_SceneFlags, 3);
        }
    }
    if (g_GameAreaId == AREA_ID_CEDAR_WOODS_BUNYAN) {
        if (SYS_TestFlag(g_SceneFlags, 0x1D)) {
            if (!SYS_TestFlag(g_SceneFlags, 0x1F)) {
                func_801C1E3C(1);
                func_801FD6FC(3);
                func_801FD6FC(4);
                SCRIPT_VARS_CLEAR_ALL();
                g_ScenarioState.state_04 = 0x15;
                g_ScenarioState.step_05  = 0;
            }
            if (!SYS_TestFlag(g_SceneFlags, 0x20)) {
                SND_RequestBGM(0xF);
                while (!EMI_IsReady()) {
                    SYS_ThreadWait(1);
                }
                SCRIPT_VARS_CLEAR_ALL();
            }
        }
    }
    if (g_GameAreaId == AREA_ID_CEDAR_WOODS_HOUSE) {
        switch (g_ScriptVars[2]) {
            case 0:
                break;
            case 1:
                break;
            case 2:
                g_GameFlags ^= 7;
                break;
            case 3:
                break;
            case 5:
                g_AreaDrawFlags = 0x1F;
                break;
            case 4:
                g_ScenarioState.step_05  = 3;
                g_ScriptVars[0]          = 0;
                g_ScenarioState.state_04 = 6;
                break;
            case 6:
                if (!SYS_TestFlag(g_SceneFlags, 0x19)) {
                    g_AreaDrawFlags          = 0x1F;
                    g_ScriptVars[0]          = 0;
                    g_ScriptVars[1]          = 0;
                    g_ScriptVars[3]          = 0;
                    g_ScenarioState.state_04 = 0x11;
                    SYS_SetFlag(g_SceneFlags, 0x19);
                    SYS_SetFlag(g_SceneFlags, 0x37);
                }
                break;
        }
    }
    if (g_GameAreaId == AREA_ID_CEDAR_WOODS_HOUSE_BALIO_SUNDER) {
        if (!SYS_TestFlag(g_SceneFlags, 0x1D)) {
            g_ScenarioState.state_04 = 0x13;
            g_AreaDrawFlags          = 0;
            g_ScriptVars[0]          = 0;
            g_ScenarioState.step_05  = 0xA;
        }
    }
    if (g_GameAreaId == AREA_ID_FARM) {
        u8* script_phase = &g_ScriptVars[2];

        switch (*script_phase) {
            case 0:
                if (SYS_TestFlag(g_SceneFlags, 0x1A) && !SYS_TestFlag(g_SceneFlags, 0x1B) && g_GameCellType == 1) {
                    g_AreaDrawFlags = 0;
                    Game_SetScriptActive();
                    g_ScriptVars[0]          = 0;
                    g_ScriptVars[1]          = 0;
                    *script_phase            = 0;
                    g_ScenarioState.step_05  = 5;
                    g_ScriptVars[3]          = 0;
                    g_ScenarioState.state_04 = 0x12;
                }
                break;
            case 1:
                g_AreaDrawFlags = 0x1F;
                break;
        }
    }
    if (g_GameAreaId == AREA_ID_MCNEIL_MANOR_AREA) {
        if (!SYS_TestFlag(g_SceneFlags, 0)) {
            SYS_SetFlag(g_SceneFlags, 0);
            flags_byte = &D_80146871;
            *flags_byte |= 1;
            g_GameFlags |= 0x80;
            Game_SetScriptActive();
            g_GameFlags |= 0x30;
            SCRIPT_VARS_CLEAR_ALL();
            g_ScenarioState.step_05  = 0;
            g_ScenarioState.state_04 = 2;
        }
    }
    area_id = g_GameAreaId;
    if (area_id == AREA_ID_YRAAL_ROAD || (area_id >= AREA_ID_NUE_CAVE && area_id <= AREA_ID_MOUNT_GLAUS) || area_id == AREA_ID_YRAAL_BATTLEFIELD_BEFORE_NUE || area_id == AREA_ID_WYNDIA_WORLD_MAP) {
        SCRIPT_VARS_CLEAR_ALL();
        g_ScenarioState.step_05  = 0;
        g_ScenarioState.state_04 = 0;
        g_ScenarioState.timer_06 = 0;
    }
    if (g_GameAreaId == AREA_ID_MCNEIL_MANOR_COURTYARD) {
        u8* script_phase = &g_ScriptVars[2];

        switch (*script_phase) {
            case 0:
                Game_ClearScriptActive();
                g_ScriptVars[0] = 0;
                g_ScriptVars[1] = 0;
                *script_phase   = 0;
                g_ScriptVars[3] = 0;
                break;
            case 1:
                if (!SYS_TestFlag(g_SceneFlags, 7)) {
                    g_ScriptVars[0]         = 0;
                    g_ScriptVars[1]         = 0;
                    g_ScriptVars[3]         = 0;
                    g_ScenarioState.step_05 = 4;
                }
                break;
            case 3:
                if (!SYS_TestFlag(g_SceneFlags, 0xC)) {
                    g_ScriptVars[0]         = 0;
                    g_ScriptVars[1]         = 0;
                    g_ScriptVars[3]         = 0;
                    g_ScenarioState.step_05 = 0xF;
                }
                break;
        }
    }
    if (g_GameAreaId == AREA_ID_MCNEIL_MANOR) {
        switch (g_ScriptVars[2]) {
            case 0:
                if (!SYS_TestFlag(g_SceneFlags, 8)) {
                    SCRIPT_VARS_CLEAR_ALL();
                    SYS_SetFlag(g_SceneFlags, 8);
                }
                break;
            case 1:
                break;
            case 2:
                g_AreaDrawFlags = 0x1F;
                break;
            case 3:
                break;
            case 4:
                g_ScriptVars[0] = 0;
                break;
        }
    }
    if (g_GameAreaId == AREA_ID_MCNEIL_MANOR_ROOF) {
        u8* script_phase = &g_ScriptVars[2];

        switch (*script_phase) {
            case 0:
                if (!SYS_TestFlag(g_SceneFlags, 0x15)) {
                    g_ScriptVars[0]          = 0;
                    g_ScriptVars[1]          = 0;
                    *script_phase            = 0;
                    g_ScriptVars[3]          = 0;
                    g_AreaDrawFlags          = 0;
                    g_ScenarioState.step_05  = 0;
                    g_ScenarioState.state_04 = 0x10;
                }
                break;
            case 1:
                break;
            case 2:
                SYS_SetFlag(g_SceneFlags, 0x16);
                Area_SetCellPalette(0x27, 0x15);
                break;
        }
    }
    if (g_GameAreaId == AREA_ID_CAMP_ANGEL_TOWER) {
        if ((D_80146871 & 1) != 0 && !SYS_TestFlag(g_SceneFlags, 2)) {
            SYS_SetFlag(g_SceneFlags, 2);
            SND_StopSequence(0, 0);
            SND_RequestBGM(0x4D);
            while (!EMI_IsReady()) {
                SYS_ThreadWait(1);
            }
            SND_PlayBGM(0x4D, 0x64, 8);
        }
    }
    if (g_GameAreaId == AREA_ID_YRAAL_WORLD_MAP) {
        SCRIPT_VARS_CLEAR_ALL();
        g_ScenarioState.step_05  = 0;
        g_ScenarioState.state_04 = 0;
        g_ScenarioState.timer_06 = 0;
        if ((D_80146871 & 1) != 0 && g_GameLastAreaId == AREA_ID_CAMP_ANGEL_TOWER) {
            SYS_ClearFlag(g_SceneFlags, 2);
            SND_StopSequence(0, 0);
            SND_RequestBGM(0x11);
            while (!EMI_IsReady()) {
                SYS_ThreadWait(1);
            }
            SND_PlayBGM(0x11, 0x64, 8);
        }
    }
    g_ScenarioState.mode_02 = 2;
}
