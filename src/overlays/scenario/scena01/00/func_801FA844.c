#include "scena01_00.h"
#include "area/map.h"
#include "overlays/area/shared/Area_DrawDimQuad.h"
#include "overlays/area/shared/Actor_SeedPartySlot.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801FA844(void) {
    switch (g_ScenarioState.step) {
        case 0:
            g_ScenarioState.step = 1;
            g_GameFlags |= 0x100;
            break;
        case 1:
            UI_MessageStartArea(1);
            g_GameStateIndex     = GAME_REQUEST_MESSAGE;
            g_ScenarioState.step = 2;
            break;
        case 2:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScenarioState.step     = 0;
                g_ScenarioState.state_04 = 0;
                g_ScriptVars[0]          = 0;
                g_GameFlags ^= 0x100;
            }
            break;
        case 3:
            if (g_Game.members[0].pos.y.part.integer == 0xD) {
                if (g_Game.members[0].pos.x.part.integer == 0x5B) {
                    g_ScenarioState.step = 4;
                    g_GameFlags |= 0x100;
                }
                if (g_Game.members[0].pos.x.part.integer == 0x5C) {
                    g_ScenarioState.step = 4;
                    g_GameFlags |= 0x100;
                }
                if (g_Game.members[0].pos.x.part.integer == 0x5D) {
                    g_ScenarioState.step = 4;
                    g_GameFlags |= 0x100;
                }
                if (g_Game.members[0].pos.x.part.integer == 0x5E) {
                    g_ScenarioState.step = 4;
                    g_GameFlags |= 0x100;
                }
            }
            break;
        case 4:
            UI_MessageStartArea(2);
            g_GameStateIndex     = GAME_REQUEST_MESSAGE;
            g_ScenarioState.step = 5;
            break;
        case 5:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                func_801A4BC0(0x51, 0x1F, 0);
                func_801A4BC0(0x52, 0x1F, 0);
                func_801A4BC0(0x51, 0x20, 0);
                func_801A4BC0(0x52, 0x20, 0);
                g_ScenarioState.step = 6;
                g_GameFlags ^= 0x100;
                SYS_SetFlag(g_SceneFlags, 0xC);
            }
            break;
        case 6:
        case 7:
            break;
        case 8:
            if (g_ScriptVars[0] == 7) {
                func_801A4BC0(0x51, 0x1F, 0xC0);
                func_801A4BC0(0x52, 0x1F, 0xC0);
                func_801A4BC0(0x51, 0x20, 0xA1);
                func_801A4BC0(0x52, 0x20, 0xA1);
                Game_ClearScriptActive();
                g_ScenarioState.step = 9;
            }
            break;
        case 9:
            if (g_Game.members[0].pos.x.part.integer == 0x41 && g_Game.members[0].pos.y.part.integer == 9) {
                g_ScenarioState.step = 0xB;
            }
            break;
        case 10:
            break;
        case 11:
            if (g_ScriptVars[0] == 0x1E) {
                func_801BE1B0(2);
                g_ScenarioState.step = 0xC;
                SYS_SetFlag(g_SceneFlags, 0xF);
            }
            if (g_ScriptVars[0] == 0x32) {
                func_801BE1B0(4);
                g_ScenarioState.step = 0xE;
                SYS_SetFlag(g_SceneFlags, 0xF);
            }
            break;
        case 12:
            if (g_ScriptVars[0] == 0x21) {
                func_801BE1B0(3);
                func_801C601C(1);
                g_ScenarioState.step = 0xD;
            }
            break;
        case 13:
            if (g_AreaCameraMoving == 0) {
                if (g_ScriptVars[0] == 0x22) {
                    g_ScenarioState.step = 0xF;
                    func_801A4BC0(4, 7, 0xC0);
                    func_801A4BC0(4, 8, 0xC0);
                    func_801A4BC0(3, 7, 0xA1);
                    func_801A4BC0(3, 8, 0xA1);
                    Game_ClearScriptActive();
                }
            }
            break;
        case 14:
            if (g_ScriptVars[0] == 0x35) {
                g_ScenarioState.step = 0x11;
                func_801A4BC0(4, 7, 0xC0);
                func_801A4BC0(4, 8, 0xC0);
                func_801A4BC0(3, 7, 0xA1);
                func_801A4BC0(3, 8, 0xA1);
                Game_ClearScriptActive();
            }
            break;
        case 15:
        case 16:
            break;
        case 17:
            if (SYS_TestFlag(g_SceneFlags, 0x12)) {
                g_ScenarioState.step     = 0;
                g_ScenarioState.state_04 = 0;
            }
            break;
        case 18:
            UI_MessageStartArea(0xC);
            g_GameStateIndex     = GAME_REQUEST_MESSAGE;
            g_ScenarioState.step = 0x13;
            break;
        case 19:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScenarioState.step = 0x14;
            }
            break;
        case 20:
            if (g_ScriptVars[0] == 0x3C) {
                SYS_SetFlag(g_SceneFlags, 0x10);
                func_801BE1B0(5);
                g_ScenarioState.step = 0x15;
            }
            if (g_ScriptVars[0] == 0x46) {
                Game_ClearScriptActive();
                g_ScenarioState.step = 0x11;
            }
            break;
        case 21:
            g_ScenarioState.step = 0x16;
            break;
        case 22:
            g_ScenarioState.step = 0x17;
            break;
        case 23:
            if (g_ScriptVars[0] == 0x45) {
                g_ScenarioState.step = 0x18;
                func_8019FA28(0x16, 0x540000, 0x70000, 0x86);
            }
            break;
        case 24:
            if (g_ScriptVars[0] == 4) {
                if (SYS_TestFlag(g_SceneFlags, 0x1D) == 0) {
                    g_ScenarioState.step = 0x19;
                    SYS_SetFlag(g_SceneFlags, 0x1D);
                    func_8019FA28(0x16, 0x3D0000, 0x470000, 0x87);
                } else {
                    g_ScenarioState.step = 0x19;
                    func_8019FA28(0x16, 0x3D0000, 0x470000, 0x8E);
                }
            }
            break;
        case 25:
            if (g_ScriptVars[0] == 9) {
                Game_ClearScriptActive();
                g_ScenarioState.step = 0x1A;
                g_GameFlags ^= 8;
            }
            break;
        case 26:
            if (g_Game.members[0].pos.y.part.integer < 0x2B) {
                if (g_Game.members[0].pos.x.part.integer == 0x3D) {
                    g_ScenarioState.step = 0x1E;
                    SND_SEQueueVolume(0x1206, 0x50, 0x50);
                    Game_SetScriptActive();
                }
                if (g_Game.members[0].pos.x.part.integer == 0x3E) {
                    g_ScenarioState.step = 0x1E;
                    SND_SEQueueVolume(0x1206, 0x50, 0x50);
                    Game_SetScriptActive();
                }
                if (g_Game.members[0].pos.x.part.integer == 0x3F) {
                    g_ScenarioState.step = 0x1E;
                    SND_SEQueueVolume(0x1206, 0x50, 0x50);
                    Game_SetScriptActive();
                }
            }
            if ((g_Game.members[0].pos.y.fixed == TO_COORD(72) || g_Game.members[0].pos.y.fixed == TO_COORD_HALF(72)) && (u32)(g_Game.members[0].pos.x.fixed - TO_COORD(62)) <= TO_COORD_HALF(1)) {
                g_ScenarioState.step     = 0;
                g_ScenarioState.state_04 = 0xA;
                Game_SetScriptActive();
                func_8019FA28(0x16, 0x540000, 0xA0000, 0x8C);
            }
            break;
        case 27:
            if (g_GameCellType == 4) {
                g_ScenarioState.step = 0x1A;
            }
            break;
        case 28:
        case 29:
            break;
        case 30:
            g_ScriptVars[0] = 0x64;
            SND_SEPlay(0x202);
            g_ScriptVars[0] = 0x65;
            func_801BE1B0(9);
            func_801C601C(0);
            g_ScenarioState.step = 0x1F;
            break;
        case 31:
            if (g_ScriptVars[0] == 0x66) {
                SND_SeqStop(0, 0);
                SND_BGMPlay(0x19, 0x64, 8);
                g_ScenarioState.step = 0x20;
            }
            break;
        case 32:
            g_ScenarioState.step = 0x21;
            break;
        case 33:
            g_ScenarioState.step = 0x22;
            break;
        case 34:
            g_ScenarioState.step = 0x23;
            break;
        case 35:
            if (g_ScriptVars[0] == 0x68) {
                func_801BFE34(0x3F0000, 0x320000, 3);
                g_ScenarioState.step = 0x24;
            }
            break;
        case 36:
            if (g_ScriptVars[0] == 0x6C) {
                func_801C7A54(3);
                g_ScenarioState.step = 0x25;
            }
            break;
        case 37:
            if (g_ScriptVars[0] == 0x6D) {
                SYS_SetFlag(g_SceneFlags, 0x12);
                SYS_ClearFlag(g_SceneFlags, 0x3F);
                func_801BE1B0(0xA);
                g_ScenarioState.step = 0x26;
            }
            break;
        case 38:
            SND_SEPlay(0x203);
            g_ScriptVars[0]      = 0x6E;
            g_ScenarioState.step = 0x27;
            break;
        case 39:
            if (g_ScriptVars[0] == 0x78) {
                g_GameFlags |= 0x20;
                Game_ClearScriptActive();
                g_ScenarioState.step     = 0x2D;
                g_ScriptVars[1]          = 0;
                g_ScenarioState.state_04 = 9;
            }
            break;
        case 40:
            g_ScenarioState.step = 0x29;
            func_8019FA28(0x16, 0x2A0000, 0x490000, 0x8D);
            break;
        case 41:
            Game_ClearScriptActive();
            g_ScenarioState.step     = 0x2D;
            g_ScenarioState.state_04 = 9;
            break;
        case 42:
        case 43:
        case 44:
            break;
        case 45:
            if (g_Game.members[0].pos.y.fixed == TO_COORD(72) || g_Game.members[0].pos.y.fixed == TO_COORD_HALF(72)) {
                if ((u32)(g_Game.members[0].pos.x.fixed - TO_COORD(62)) <= TO_COORD_HALF(1)) {
                    g_ScenarioState.step     = 0;
                    g_ScenarioState.state_04 = 0xA;
                    Game_SetScriptActive();
                    func_8019FA28(0x16, 0x540000, 0xA0000, 0x8C);
                }
            }
            break;
    }
}
