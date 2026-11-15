#include "area040_13.h"

MATCH void func_801F3254(void) {
    u16  held;
    u16* input;
    s8*  step;

    step = &g_SceneEventStep;
    switch (*step) {
        case 0:
            Game_ClearScriptActive();
            /* The event flags sit 0x63C bytes past the step byte. */
            if (SYS_TestFlag(step + 0x63C, 0x27) == 0) {
                func_801BE1B0(4);
                *step = 1;
                /* The flag word has no named bits 12 and 1-2; the load sets them. */
                g_GameFlags |= 0x1000;
            } else {
                *step = 10;
            }
            break;
        case 1:
            if (g_ScriptVars[0] == 0x63) {
                g_ScriptVars[0] = 0;
                *step           = 2;
                g_GameFlags |= 0x6;
            }
            break;
        case 2:
            if (g_GameStateIndex == GAME_REQUEST_IDLE) {
                input                               = &g_InputHeld;
                held                                = *input;
                D_1F800000.view.area.entity_counter = held;
                *input                              = held & 0xFFF;
                *input |= D_801F4984[held >> 12] << 12;
            }
            func_801F37D4();
            break;
    }
    if (g_GameAreaId != 0x28 || g_SceneEventStep == 10 || D_80143F03 != 6) {
        g_SceneEventMode = 0;
        g_SceneEventStep = 0;
        g_GameFlags &= ~0x1006;
    }
}
