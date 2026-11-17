#include "area077_14.h"

/* Slides and spins the banner at (130, 10) while its scene flag is set, then steps the task out
 * on a confirm press or when the banner stops on its line. */
MATCH void func_801F2EC0(void) {
    u8 i;

    if ((COORD_INT(g_Task->pos.x) == 8) && ((s16)g_Task->screen_x == 0x20)) {
        g_Task->tint.signed_bytes.delta.red = -0x80;
    }
    /* FAKE: func_801F31EC reads two arguments; the shared area prototype gives none. */
    ((void (*)(s32, s32))func_801F31EC)(130, 10);
    i = 0;
    do {
        g_Task->screen_x++;
        if ((s16)g_Task->screen_x >= 72) {
            g_Task->screen_x         = 0;
            COORD_INT(g_Task->pos.x) = (COORD_INT(g_Task->pos.x) - 8) & 0x1F;
        }
        func_801F35E0(130, 10, g_Task->screen_x, g_Task->screen_y, g_Task->unk_32, COORD_INT(g_Task->pos.x));
        if ((s16)g_Task->screen_x == 2) {
            SND_PlaySE(0x205);
        }
        i++;
    } while (i < 2);

    func_801F36E8(130, 10);
    if ((g_InputPressed & g_InputMasks[INPUT_SLOT_CONFIRM]) != 0) {
        if ((COORD_INT(g_Task->pos.x) == 8) && ((u32)(g_Task->screen_x - 0x1C) < 9)) {
            SYS_SetFlag(g_SceneFlags, 0x26);
        } else {
            SYS_ClearFlag(g_SceneFlags, 0x26);
        }
        g_Task->header.mode = 3;
    } else if ((g_InputPressed & g_InputMasks[INPUT_SLOT_CANCEL]) != 0) {
        g_Task->header.mode = 3;
    }
}
