#include "area068_13.h"

MATCH void func_801F30B0(void) {
    Actor* work;
    u16*   input;

    if (g_InputPressed == 0x1000 || g_InputPressed == 0x4000 || g_InputPressed == 0x2000 || g_InputPressed == 0x8000 ||
        g_InputPressed == 0x3000 || g_InputPressed == 0x6000 || g_InputPressed == 0x9000 || g_InputPressed == 0xC000) {
        input      = &g_InputPressed;
        D_801F4E14 = *input;
        SND_PlayCue(0x202);
        switch (*input) {
            case 0x1000:
            case 0x3000:
                work        = g_SpadWork;
                g_GameState = (GameStateRecord*)g_BattlePartyBattlers;
                g_SpadWork  = (Actor*)g_BattlePartyBattlers;
                D_80145EC8 -= 0x800;
                g_SpadWork = work;
                break;
            case 0x2000:
            case 0x6000:
                work        = g_SpadWork;
                g_GameState = (GameStateRecord*)g_BattlePartyBattlers;
                g_SpadWork  = (Actor*)g_BattlePartyBattlers;
                D_80145EC4 += 0x800;
                g_SpadWork = work;
                break;
            case 0x4000:
            case 0xC000:
                work        = g_SpadWork;
                g_GameState = (GameStateRecord*)g_BattlePartyBattlers;
                g_SpadWork  = (Actor*)g_BattlePartyBattlers;
                D_80145EC8 += 0x800;
                g_SpadWork = work;
                break;
            case 0x8000:
            case 0x9000:
                work        = g_SpadWork;
                g_GameState = (GameStateRecord*)g_BattlePartyBattlers;
                g_SpadWork  = (Actor*)g_BattlePartyBattlers;
                D_80145EC4 -= 0x800;
                g_SpadWork = work;
                break;
        }
        g_SpadWork->unk_01 = 0xC;
        g_SpadWork->unk_09 = 0xC;
    }
}
