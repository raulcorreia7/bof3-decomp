#include "area077_14.h"

/* Slides and spins the banner at (130, 10) while its scene flag is set, then steps the task out
 * on a confirm press or when the banner stops on its line. */
MATCH void func_801F2EC0(void) {
    u8 i;

    if ((COORD_INT(TASK(Actor)->pos.x) == 8) && ((s16)TASK(Actor)->screen_x == 0x20)) {
        TASK(Actor)->tint.steps.delta.r = -0x80;
    }
    func_801F31EC(130, 10);
    i = 0;
    do {
        TASK(Actor)->screen_x++;
        if ((s16)TASK(Actor)->screen_x >= 72) {
            TASK(Actor)->screen_x         = 0;
            COORD_INT(TASK(Actor)->pos.x) = (COORD_INT(TASK(Actor)->pos.x) - 8) & 0x1F;
        }
        func_801F35E0(130, 10, TASK(Actor)->screen_x, TASK(Actor)->screen_y, TASK(Actor)->unk_32, COORD_INT(TASK(Actor)->pos.x));
        if ((s16)TASK(Actor)->screen_x == 2) {
            SND_SEPlay(0x205);
        }
        i++;
    } while (i < 2);

    func_801F36E8(130, 10);
    if ((g_PadStates[0].pressed & g_InputMasks[INPUT_SLOT_CONFIRM]) != 0) {
        if ((COORD_INT(TASK(Actor)->pos.x) == 8) && ((u32)(TASK(Actor)->screen_x - 0x1C) < 9)) {
            SYS_SetFlag(g_SceneFlags, 0x26);
        } else {
            SYS_ClearFlag(g_SceneFlags, 0x26);
        }
        TASK(Actor)->header.mode = 3;
    } else if ((g_PadStates[0].pressed & g_InputMasks[INPUT_SLOT_CANCEL]) != 0) {
        TASK(Actor)->header.mode = 3;
    }
}
