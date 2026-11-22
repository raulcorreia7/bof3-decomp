#include "scena15_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* Step script: the cutscene that swaps the party's loaded character, then the area changes that follow it. */
MATCH void func_801FB788(void) {
    SpawnedActor* actor;
    s32           slot;

    switch (g_ScenarioState.step) {
        case 0:
            EMI_ArchiveLoad(0x292);
            func_801BE1B0(0);
            g_ScenarioState.step = 1;
            break;
        case 1:
            if (g_ScriptVars[3] == 0x10) {
                slot = func_8019601C() & 0xFF;
                if (slot != 0xFF) {
                    actor               = &g_SpawnedActors[slot];
                    actor->header.flags = 1;
                    actor->pos.x.fixed  = 0x3B8000;
                    actor->type         = 0x88;
                    actor->unk_06       = 1;
                    actor->pos.y.fixed  = 0x220000;
                    actor->pos.z.fixed  = TO_COORD(0x800);
                    actor->vx           = 0x3F8000;
                    actor->selection    = 0x220000;
                    actor->unk_14       = TO_COORD(0x600);
                }
                g_ScenarioState.timer_06 = 0x20;
                g_ScenarioState.step     = 2;
            }
            break;
        case 2:
            if (--g_ScenarioState.timer_06 == 0) {
                g_ScriptVars[3]      = 0x18;
                g_ScenarioState.step = 3;
            }
            break;
        case 3:
            if (g_ScriptVars[3] == 0) {
                func_801BE1B0(7);
                g_ScenarioState.step = 4;
            }
            break;
        case 4:
            if (EMI_IsReady() && g_ScriptVars[0] == 0xF) {
                D_801FE748 = func_8019601C();
                if (D_801FE748 != 0xFF) {
                    g_SpawnedActors[D_801FE748].header.flags = 1;
                    g_SpawnedActors[D_801FE748].type         = 0xA0;
                }
                SND_StartDecrescendo(0, 0, 0x64, 0x10);
                g_ScenarioState.step = 5;
            }
            break;
        case 5:
            if (g_ScriptVars[0] == 0x11) {
                D_801FE748 = func_8019601C();
                if (D_801FE748 != 0xFF) {
                    g_SpawnedActors[D_801FE748].header.flags = 1;
                    g_SpawnedActors[D_801FE748].type         = 0x9F;
                    g_ScenarioState.step                     = 6;
                }
                SND_SeqStop(0, 0);
            }
            break;
        case 6:
            if (g_ScriptVars[0] == 0x12) {
                g_ScenarioState.timer_06 = 0x1E;
                g_ScenarioState.step     = 7;
            }
            break;
        case 7:
            if (--g_ScenarioState.timer_06 == 0) {
                SND_BGMRequest(0xA2);
                g_ScenarioState.step = 8;
                g_ScriptVars[0]++;
            }
            break;
        case 8:
            if (g_ScriptVars[0] == 0x14 && EMI_IsReady()) {
                func_801C601C(1);
                g_ScenarioState.step = 9;
            }
            break;
        case 9:
            if (g_ScriptVars[0] == 0x15) {
                g_ScenarioState.step = 10;
            }
            break;
        case 10:
            if (g_ScriptVars[0] == 0x16) {
                u8* loaded;

                loaded     = &g_EmiLoadedCharacterIndex;
                D_801FE74C = *loaded;
                EMI_PartyLoad(7, 4, 2, 0);
                if (D_801FE74C != *loaded) {
                    D_801FE74C = *loaded;
                    *loaded    = 0xFF;
                } else {
                    D_801FE74C = 0xFF;
                }
                g_ScenarioState.timer_06 = 0x3C;
                g_ScenarioState.step     = 11;
            }
            break;
        case 11:
            if (g_ScenarioState.timer_06 == 0) {
                if (!EMI_IsReady()) {
                    break;
                }
                if (D_801FE74C != 0xFF) {
                    u8* loaded = &g_EmiLoadedCharacterIndex;

                    *loaded = D_801FE74C;
                    func_801C1DF0(0);
                    *loaded = 0xFF;
                    EMI_PartyLoadCode(7, 4, 2);
                    *loaded = D_801FE74C;
                } else {
                    func_801C1DF0(0);
                }
                func_801BE1B0(8);
                func_801FC100();
                g_ScriptVars[0]++;
                SND_BGMPlay(0xA2, 0x64, 8);
                g_SpawnedActors[D_801FE748].header.mode++;
                g_ScenarioState.step = 12;
            } else {
                g_ScenarioState.timer_06--;
            }
            break;
        case 12:
            if (g_ScriptVars[0] == 0x2B && EMI_IsReady()) {
                SYS_SetFlag(g_SceneFlags, 9);
                func_8019FA28(0xC4, 0x120000, 0x140000, 0x81);
                g_GamePrevSelection  = 0x95;
                g_ScenarioState.step = 13;
            }
            break;
        case 13:
            if (g_ScriptVars[0] == 1) {
                func_8019FA28(0x2D, 0xF8000, 0x358000, 0x87);
                g_GameRequestType    = 1;
                g_GamePrevSelection  = 0xA2;
                g_ScenarioState.step = 14;
            }
            break;
        case 14:
            if (g_ScriptVars[0] == 2) {
                func_8019FA28(0xAE, 0x320000, 0x270000, 0x89);
                g_GamePrevSelection  = 0xA2;
                g_GameEntryMode      = 0;
                g_ScenarioState.step = 15;
            }
            break;
        case 15:
            if (g_ScriptVars[0] == 0xD) {
                SYS_SetFlag(g_SceneFlags, 0xA);
                func_8019FA28(0x98, 0x180000, 0x270000, 0x80);
                g_GameRequestType    = 1;
                g_GamePrevSelection  = 0xA2;
                g_ScenarioState.step = 16;
            }
            break;
        case 16:
            if (g_ScriptVars[0] == 0) {
                SYS_SetFlag(g_SceneFlags, 0xA);
                func_8019FA28(0xAE, 0x2F8000, 0x278000, 0x8A);
                g_GameRequestType    = 0xFF;
                g_GamePrevSelection  = 0xFF;
                g_GameEntryMode      = 0;
                g_ScenarioState.step = 17;
            }
            break;
        case 17:
            if (g_UiWindowEffectBusy == 0) {
                SCENARIO_MESSAGE_WAIT(MSG_SCENA15_030, 18);
            }
            break;
        case 18:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE && EMI_IsReady()) {
                SND_BGMPlay(0xA2, 0x64, 8);
                g_AreaDrawFlags = 0x1F;
                UI_ModeSet(1);
                g_ScriptVars[0]      = 1;
                g_ScenarioState.step = 19;
            }
            break;
        case 19:
            if (g_ScriptVars[0] == 0x14) {
                g_ScriptVars[0]++;
                g_ScenarioState.timer_06 = 0x5A;
                g_ScenarioState.step     = 20;
            }
            break;
        case 20:
            if (g_ScriptVars[0] == 0x26 && --g_ScenarioState.timer_06 == 0) {
                Scene_SpawnActor(0x13, -0x2AA, g_AreaCameraAngle.vy, 0x5E, 0x40, 0);
                g_ScenarioState.step = 21;
            }
            break;
        case 21:
            if (g_ScriptVars[0] == 0x2B) {
                Scene_SpawnActor(0x13, -0x2AA, g_AreaCameraAngle.vy, 0x200, 0x28, 0);
                g_ScenarioState.step = 22;
            }
            break;
        case 22:
            if (g_ScriptVars[0] == 0x3C) {
                SND_BGMRequest(0x79);
                g_ScenarioState.step = 23;
            }
            break;
        case 23:
            if (g_ScriptVars[0] == 0x3F && EMI_IsReady()) {
                g_ScenarioState.step = 24;
                g_ScriptVars[0]++;
            }
            break;
        case 24:
            if (g_ScriptVars[0] == 0) {
                Game_ClearScriptActive();
                SYS_SetFlag(g_SceneFlags, 0xB);
                g_ScenarioState.state_04 = 0;
                g_ScenarioState.step     = 0;
            }
            break;
    }
}
