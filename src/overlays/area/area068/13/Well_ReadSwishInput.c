#include "area068_13.h"

/* func_801F30B0 */
MATCH void Well_ReadSwishInput(void) {
    Actor* work;
    u16*   input;

    if (g_InputPressed == PADLup || g_InputPressed == PADLdown || g_InputPressed == PADLright || g_InputPressed == PADLleft || g_InputPressed == (PADLup | PADLright) ||
        g_InputPressed == (PADLdown | PADLright) || g_InputPressed == (PADLup | PADLleft) || g_InputPressed == (PADLdown | PADLleft)) {
        input              = &g_InputPressed;
        g_WellSwishButtons = *input;
        SND_PlayCue(WELL_CUE_SWISH);
        switch (*input) {
            case 0x1000:
            case 0x3000:
                work        = g_Task;
                g_GameState = g_Game.members;
                TASK_SET(g_Game.members);
                g_Game.members[0].pos.y.fixed -= 0x800;
                g_Task = work;
                break;
            case 0x2000:
            case 0x6000:
                work        = g_Task;
                g_GameState = g_Game.members;
                TASK_SET(g_Game.members);
                g_Game.members[0].pos.x.fixed += 0x800;
                g_Task = work;
                break;
            case 0x4000:
            case 0xC000:
                work        = g_Task;
                g_GameState = g_Game.members;
                TASK_SET(g_Game.members);
                g_Game.members[0].pos.y.fixed += 0x800;
                g_Task = work;
                break;
            case 0x8000:
            case 0x9000:
                work        = g_Task;
                g_GameState = g_Game.members;
                TASK_SET(g_Game.members);
                g_Game.members[0].pos.x.fixed -= 0x800;
                g_Task = work;
                break;
        }
        g_Task->header.mode = WELL_MODE_SWISH_DELAY;
        g_Task->timer       = WELL_SWISH_DELAY_FRAMES;
    }
}
