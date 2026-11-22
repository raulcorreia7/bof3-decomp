#include "area068_13.h"

/* func_801F30B0 */
MATCH void Well_ReadSwishInput(void) {
    Actor* work;
    u16*   input;

    if (g_PadStates[0].pressed == PADLup || g_PadStates[0].pressed == PADLdown || g_PadStates[0].pressed == PADLright || g_PadStates[0].pressed == PADLleft ||
        g_PadStates[0].pressed == (PADLup | PADLright) || g_PadStates[0].pressed == (PADLdown | PADLright) || g_PadStates[0].pressed == (PADLup | PADLleft) ||
        g_PadStates[0].pressed == (PADLdown | PADLleft)) {
        input              = &g_PadStates[0].pressed;
        g_WellSwishButtons = *input;
        SND_SEPlay(WELL_CUE_SWISH);
        switch (*input) {
            case PADLup:
            case (PADLup | PADLright):
                work        = TASK(Actor);
                g_GameState = g_Game.members;
                TASK_SET(g_Game.members);
                g_Game.members[0].pos.y.fixed -= 0x800;
                g_Task = work;
                break;
            case PADLright:
            case (PADLdown | PADLright):
                work        = TASK(Actor);
                g_GameState = g_Game.members;
                TASK_SET(g_Game.members);
                g_Game.members[0].pos.x.fixed += 0x800;
                g_Task = work;
                break;
            case PADLdown:
            case (PADLleft | PADLdown):
                work        = TASK(Actor);
                g_GameState = g_Game.members;
                TASK_SET(g_Game.members);
                g_Game.members[0].pos.y.fixed += 0x800;
                g_Task = work;
                break;
            case PADLleft:
            case (PADLleft | PADLup):
                work        = TASK(Actor);
                g_GameState = g_Game.members;
                TASK_SET(g_Game.members);
                g_Game.members[0].pos.x.fixed -= 0x800;
                g_Task = work;
                break;
        }
        TASK(Actor)->header.mode = WELL_MODE_SWISH_DELAY;
        TASK(Actor)->timer       = WELL_SWISH_DELAY_FRAMES;
    }
}
