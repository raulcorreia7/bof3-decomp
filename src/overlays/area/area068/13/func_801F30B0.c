#include "area068_13.h"

MATCH void func_801F30B0(void) {
    Actor* work;
    u16*   input;

    if (g_InputPressed == PADLup || g_InputPressed == PADLdown || g_InputPressed == PADLright ||
        g_InputPressed == PADLleft || g_InputPressed == (PADLup | PADLright) ||
        g_InputPressed == (PADLdown | PADLright) || g_InputPressed == (PADLup | PADLleft) ||
        g_InputPressed == (PADLdown | PADLleft)) {
        input      = &g_InputPressed;
        D_801F4E14 = *input;
        SND_PlayCue(0x202);
        switch (*input) {
            case 0x1000:
            case 0x3000:
                work        = g_Task;
                g_GameState = (GameState*)g_BattlePartyBattlers;
                g_Task      = (Actor*)g_BattlePartyBattlers;
                D_80145EC8 -= 0x800;
                g_Task = work;
                break;
            case 0x2000:
            case 0x6000:
                work        = g_Task;
                g_GameState = (GameState*)g_BattlePartyBattlers;
                g_Task      = (Actor*)g_BattlePartyBattlers;
                D_80145EC4 += 0x800;
                g_Task = work;
                break;
            case 0x4000:
            case 0xC000:
                work        = g_Task;
                g_GameState = (GameState*)g_BattlePartyBattlers;
                g_Task      = (Actor*)g_BattlePartyBattlers;
                D_80145EC8 += 0x800;
                g_Task = work;
                break;
            case 0x8000:
            case 0x9000:
                work        = g_Task;
                g_GameState = (GameState*)g_BattlePartyBattlers;
                g_Task      = (Actor*)g_BattlePartyBattlers;
                D_80145EC4 -= 0x800;
                g_Task = work;
                break;
        }
        g_Task->mode   = 0xC;
        g_Task->unk_09 = 0xC;
    }
}
