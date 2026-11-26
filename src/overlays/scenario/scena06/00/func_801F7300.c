#include "scena06_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801F7300(void) {
    /* FAKE: retail materializes the argument as li a0,2 in the dispatch delay slot; the a0 pin keeps a fresh constant instead of a copy of the switch value. */
    FAKE_REG(s32, arg, "a0");
    if (g_GameAreaId == AREA_ID_WYNDIA_CASTLE) {
        if (!SYS_TestFlag(g_SceneFlags, 3)) {
            g_ScriptVars[0] = 0;
            g_ScriptVars[1] = 0;
            switch (g_EmiLoadedCharacterIndex & 0x7F) {
                case 0:
                    g_Characters[g_CharSlot[5]].party_flags &= 0xFE;
                    /* FAKE: pins the g_CharSlot[6] load behind the first store (retail keeps the nop). */
                    FAKE_BARRIER();
                    g_Characters[g_CharSlot[6]].party_flags &= 0xFE;
                    func_801C1E3C(0);
                    break;
                case 1:
                    g_Characters[g_CharSlot[6]].party_flags &= 0xFE;
                    /* FAKE: same pin as case 0. */
                    FAKE_BARRIER();
                    g_Characters[g_CharSlot[2]].party_flags &= 0xFE;
                    func_801C1E3C(1);
                    break;
                case 2:
                    arg = 2;
                    g_Characters[g_CharSlot[2]].party_flags &= 0xFE;
                    /* FAKE: same pin as case 0. */
                    FAKE_BARRIER();
                    g_Characters[g_CharSlot[5]].party_flags &= 0xFE;
                    func_801C1E3C(arg);
                    break;
            }
        }
    }
    if (g_GameAreaId == AREA_ID_RHAPALA_CHECKPOINT) {
        if (SYS_TestFlag(g_SceneFlags, 0xB) && !SYS_TestFlag(g_SceneFlags, 0x3C)) {
            g_AreaDrawFlags = 0;
            Game_SetScriptActive();
            SCRIPT_VARS_CLEAR_ALL();
            g_ScenarioState.step     = 0;
            g_ScenarioState.state_04 = 0x11;
            SYS_SetFlag(g_SceneFlags, 0x3C);
            switch (g_EmiLoadedCharacterIndex & 0x7F) {
                case 0:
                    break;
                case 1:
                    func_801C1E3C(6);
                    func_801C1DF0(7);
                    break;
                case 2:
                    func_801C1E3C(4);
                    func_801C1DF0(7);
                    break;
                case 3:
                    func_801C1E3C(6);
                    func_801C1DF0(8);
                    break;
                case 4:
                    func_801C1E3C(4);
                    func_801C1DF0(8);
                    break;
                case 5:
                    break;
                case 6:
                    func_801C1E3C(7);
                    func_801C1DF0(9);
                    break;
            }
        }
    }
    if (g_GameAreaId == AREA_ID_CAMP_BEFORE_ANGEL_TOWER) {
        if (!SYS_TestFlag(g_SceneFlags, 0xB)) {
            func_801C1DF0(0);
            SCRIPT_VARS_CLEAR_ALL();
        }
        if (SYS_TestFlag(g_SceneFlags, 0xE) && !SYS_TestFlag(g_SceneFlags, 0x11)) {
            g_AreaDrawFlags = 0x1F;
            func_801FCD38();
        }
    }
    if (g_GameAreaId == AREA_ID_LIGHTHOUSE_OUTSIDE) {
        if (SYS_TestFlag(g_SceneFlags, 0x2C) && !SYS_TestFlag(g_SceneFlags, 0x3F)) {
            SCRIPT_VARS_CLEAR_ALL();
            SYS_SetFlag(g_SceneFlags, 0x3F);
            Scene_RequestChapterAdvance();
        }
    }
    if (g_GameAreaId == AREA_ID_RHAPALA_WORLD_MAP) {
        u8* script_phase = &g_ScriptVars[2];

        switch (*script_phase) {
            case 0:
                break;
            case 1:
                if (!SYS_TestFlag(g_SceneFlags, 0x1F)) {
                    g_AreaDrawFlags = 0x1F;
                    Game_ClearScriptActive();
                    g_ScriptVars[0]          = 0;
                    g_ScriptVars[1]          = 0;
                    *script_phase            = 0;
                    g_ScriptVars[3]          = 0;
                    g_ScenarioState.step     = 0;
                    g_ScenarioState.state_04 = 0;
                }
                break;
            case 2:
                if (!SYS_TestFlag(g_SceneFlags, 0x21)) {
                    SYS_SetFlag(g_SceneFlags, 0x21);
                    Game_ClearScriptActive();
                    g_ScriptVars[0]          = 0;
                    g_ScriptVars[1]          = 0;
                    *script_phase            = 0;
                    g_ScriptVars[3]          = 0;
                    g_ScenarioState.step     = 0;
                    g_ScenarioState.state_04 = 0;
                }
                break;
        }
    }
    if (g_GameAreaId == AREA_ID_BEYD_TRAINING) {
        switch (g_ScriptVars[2]) {
            case 0:
                break;
            case 1:
                if (!SYS_TestFlag(g_SceneFlags, 0x1A)) {
                    g_AreaDrawFlags = 0;
                }
                break;
            case 2:
                g_AreaDrawFlags = 0x1F;
                break;
            case 3:
                break;
            case 4:
                func_801BFE34(TO_COORD(0x1D), TO_COORD(0x3E), 0x1B);
                break;
        }
    }
    if (g_GameAreaId == AREA_ID_RHAPALA_DOCK) {
        switch (g_ScriptVars[2]) {
            case 0:
                break;
            case 1:
                if (!SYS_TestFlag(g_SceneFlags, 0xF)) {
                    g_AreaDrawFlags = 0x1F;
                }
                break;
            case 2:
                if (!SYS_TestFlag(g_SceneFlags, 0x13)) {
                    g_AreaCameraOffsetZ      = 0x480;
                    g_ScriptVars[3]          = 0;
                    g_AreaCameraRefreshCount = 2;
                    g_AreaDrawFlags          = 0;
                    func_801FCD38();
                }
                break;
        }
        if (SYS_TestFlag(g_SceneFlags, 0x11) && !SYS_TestFlag(g_SceneFlags, 0x3B)) {
            SYS_SetFlag(g_SceneFlags, 0x3B);
            g_AreaDrawFlags = 0;
            func_801FCD38();
            g_ScenarioState.step     = 0x1E;
            g_ScenarioState.state_04 = 6;
        }
    }
    if (g_GameAreaId == AREA_ID_WYNDIA_WORLD_MAP || g_GameAreaId == AREA_ID_MOMO_TOWER_WORLD_MAP || g_GameAreaId == AREA_ID_RHAPALA_WORLD_MAP || g_GameAreaId == AREA_ID_YRAAL_WORLD_MAP) {
        SCRIPT_VARS_CLEAR_ALL();
    }
    g_ScenarioState.mode_02 = 2;
}
