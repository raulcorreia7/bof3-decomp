#include "scena05_00.h"
#include "area/map.h"
#include "overlays/area/shared/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F7AC8(void) {
    if (g_GameAreaId == AREA_ID_WYNDIA_WORLD_MAP) {
        if (SYS_TestFlag(g_SceneFlags, 0x32)) {
            if (!SYS_TestFlag(g_SceneFlags, 0x3E)) {
                SYS_SetFlag(g_SceneFlags, 0x3E);
                Scene_RequestChapterAdvance();
            }
        }
    }
    if (g_GameAreaId == AREA_ID_PLANT) {
        if (SYS_TestFlag(g_SceneFlags, 9) && !SYS_TestFlag(g_SceneFlags, 0xA)) {
            g_ScenarioState.state_04 = 6;
            g_ScenarioState.step     = 0;
            SCRIPT_VARS_CLEAR_ALL();
            switch (g_EmiLoadedCharacterIndex & 0x7F) {
                case 2:
                    func_801C1E3C(3);
                    func_801C1DF0(5);
                    Scene_SetupParty(4);
                    break;
                case 6:
                    func_801C1E3C(3);
                    func_801C1DF0(6);
                    Scene_SetupParty(4);
                    break;
                case 1:
                    Scene_SetupParty(4);
                    break;
            }
        }
    }
    if (g_GameAreaId == AREA_ID_DUMP) {
        if (!SYS_TestFlag(g_SceneFlags, 9)) {
            switch (g_ScriptVars[2]) {
                case 0:
                    break;
                case 1:
                    if (!SYS_TestFlag(g_SceneFlags, 3)) {
                        g_ScriptVars[0] = 0;
                    }
                    break;
                case 2:
                    break;
                case 3:
                    func_801C1E3C(0);
                    SCRIPT_VARS_CLEAR_ALL();
                    break;
                case 4:
                    g_ScriptVars[0] = 0;
                    SYS_ClearFlag(g_SceneEventFlags, 0x26);
                    break;
                case 5:
                    g_AreaDrawFlags = 0x1F;
                    break;
            }
        }
    }
    if (g_GameAreaId == AREA_ID_MOMO_TOWER_WORLD_MAP) {
        if (!SYS_TestFlag(g_SceneFlags, 0xC)) {
            g_ScenarioState.state_04 = 0;
            g_ScenarioState.step     = 0;
            SCRIPT_VARS_CLEAR_ALL();
        } else if (!SYS_TestFlag(g_SceneFlags, 0xD)) {
            g_ScenarioState.state_04 = 9;
            g_ScenarioState.step     = 0;
            SCRIPT_VARS_CLEAR_ALL();
        }
    }
    if (g_GameAreaId == AREA_ID_CAFE) {
        switch (g_ScriptVars[2]) {
            case 0:
                break;
            case 1:
                if (!SYS_TestFlag(g_SceneFlags, 1)) {
                    g_ScenarioState.state_04 = 1;
                    g_ScenarioState.step     = 2;
                }
                break;
        }
    }
    if (g_GameAreaId == AREA_ID_EYGNOCK_ROAD) {
        if (g_ScriptVars[2] == 0) {
            if (!SYS_TestFlag(g_SceneFlags, 0x10)) {
                SND_BGMRequest(1);
                while (!EMI_IsReady()) {
                    SYS_ThreadWait(1);
                }
                SCRIPT_VARS_CLEAR_ALL();
                g_ScenarioState.state_04 = 9;
                g_ScenarioState.step     = 0;
            }
        }
    }
    if (g_GameAreaId == AREA_ID_CONTEST_OUTER) {
        switch (g_ScriptVars[2]) {
            case 0:
                if (!SYS_TestFlag(g_SceneFlags, 0x18)) {
                    SND_BGMRequest(0x4A);
                    while (!EMI_IsReady()) {
                        SYS_ThreadWait(1);
                    }
                    SND_BGMPlay(0x4B, 0x64, 8);
                    g_ScenarioState.state_04 = 0xA;
                    g_ScenarioState.step     = 0;
                    SCRIPT_VARS_CLEAR_ALL();
                    g_Characters[CHAR_ID_PECO].party_flags &= 0xFE;
                    g_Characters[CHAR_ID_MOMO].party_flags |= PARTY_FLAG_JOINED;
                }
                break;
            case 1:
                if (!SYS_TestFlag(g_SceneFlags, 0x14)) {
                    g_ScenarioState.state_04 = 0xA;
                    g_ScenarioState.step     = 4;
                    SCRIPT_VARS_CLEAR_ALL();
                    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0));
                }
                break;
            case 2:
                if (!SYS_TestFlag(g_SceneFlags, 0x18)) {
                    SND_BGMRequest(0x4A);
                    while (!EMI_IsReady()) {
                        SYS_ThreadWait(1);
                    }
                    SND_BGMPlay(0x4B, 0x64, 8);
                    g_ScenarioState.state_04 = 0xA;
                    g_ScenarioState.step     = 0;
                    SCRIPT_VARS_CLEAR_ALL();
                    func_801C1DF0(5);
                    Scene_SetupParty(0);
                }
                break;
            case 3:
                if (!SYS_TestFlag(g_SceneFlags, 0x18)) {
                    SND_BGMRequest(0x4A);
                    while (!EMI_IsReady()) {
                        SYS_ThreadWait(1);
                    }
                    SND_BGMPlay(0x4B, 0x64, 8);
                    g_ScenarioState.state_04 = 0xA;
                    g_ScenarioState.step     = 0;
                    SCRIPT_VARS_CLEAR_ALL();
                    func_801C1DF0(6);
                    Scene_SetupParty(0);
                }
                break;
            case 4:
                if (!SYS_TestFlag(g_SceneFlags, 0x14)) {
                    func_801C1E3C(2);
                    g_ScenarioState.state_04 = 0xA;
                    g_ScenarioState.step     = 4;
                    SCRIPT_VARS_CLEAR_ALL();
                    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0));
                    func_801C1DF0(7);
                    g_Characters[CHAR_ID_MOMO].party_flags &= 0xFE;
                    g_Characters[CHAR_ID_PECO].party_flags |= PARTY_FLAG_JOINED;
                    Scene_SetupParty(4);
                }
                break;
            case 5:
                func_801C1E3C(2);
                g_ScenarioState.state_04 = 0xD;
                g_ScenarioState.step     = 6;
                SCRIPT_VARS_CLEAR_ALL();
                SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0));
                func_801C1DF0(7);
                g_Characters[CHAR_ID_MOMO].party_flags &= 0xFE;
                g_Characters[CHAR_ID_PECO].party_flags |= PARTY_FLAG_JOINED;
                Scene_SetupParty(0xF);
                break;
            case 6:
                func_801C1E3C(3);
                g_ScenarioState.state_04 = 0xD;
                g_ScenarioState.step     = 6;
                SCRIPT_VARS_CLEAR_ALL();
                SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0));
                func_801C1DF0(5);
                g_Characters[CHAR_ID_PECO].party_flags &= 0xFE;
                g_Characters[CHAR_ID_MOMO].party_flags |= PARTY_FLAG_JOINED;
                Scene_SetupParty(0x10);
                break;
        }
    }
    if (g_GameAreaId == AREA_ID_CONTEST_FIRST_FIGHT) {
        u8* script_phase = &g_ScriptVars[2];

        if (*script_phase == 0) {
            if (!SYS_TestFlag(g_SceneFlags, 0x1D)) {
                g_ScriptVars[0] = 0;
                g_ScriptVars[1] = 0;
                *script_phase   = 0;
                g_ScriptVars[3] = 0;
            }
        }
    }
    if (g_GameAreaId == AREA_ID_CONTEST_GARR_FIGHT) {
        switch (g_ScriptVars[2]) {
            case 0:
                break;
            case 1:
                if (!SYS_TestFlag(g_SceneFlags, 0x2F)) {
                    SND_BGMRequest(0x66);
                    while (!EMI_IsReady()) {
                        SYS_ThreadWait(1);
                    }
                }
                break;
        }
    }
    if (g_GameAreaId == AREA_ID_CONTEST_EMITAI_FIGHT) {
        u8* script_phase = &g_ScriptVars[2];

        switch (*script_phase) {
            case 1:
                g_ScriptVars[0] = 0;
                g_ScriptVars[1] = 0;
                *script_phase   = 0;
                g_ScriptVars[3] = 0;
                break;
            case 2:
                g_ScriptVars[0] = 0;
                g_ScriptVars[1] = 0;
                *script_phase   = 0;
                g_ScriptVars[3] = 0;
                func_801BFE34(TO_COORD(0xC9), TO_COORD(0xE), 0x15);
                break;
        }
    }
    g_ScenarioState.mode_02 = 2;
}
