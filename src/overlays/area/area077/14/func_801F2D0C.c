#include "area077_14.h"

/* Slides the HUD banner down while its scene flag is set and steps the task out
 * on a cancel press or when the banner reaches its stop line. */
MATCH void func_801F2D0C(void) {
    u8  i;
    s16 count;

    /* FAKE: func_801F31EC reads two arguments; the shared area prototype gives none. */
    ((void (*)(s32, s32))func_801F31EC)(130, 10);
    i = 0;
    do {
        g_Task->screen_x++;
        if ((s16)g_Task->screen_x >= 72) {
            g_Task->screen_x = 0;
        }
        if (SYS_TestFlag(g_SceneFlags, 0x25) != 0) {
            g_Task->screen_y -= 16;
            if ((s16)g_Task->screen_y < 512) {
                g_Task->screen_y = 512;
            }
            g_Task->unk_32 = g_Task->unk_32 + ((g_FrameCount & 3) == 0);
            if (g_Task->unk_32 >= 25) {
                g_Task->unk_32 = 24;
            }
            COORD_INT(g_Task->pos.x) = 0;
        }
        func_801F35E0(130, 10, g_Task->screen_x, g_Task->screen_y, g_Task->unk_32, COORD_INT(g_Task->pos.x));
        i++;
    } while (i < 2);

    func_801F36E8(130, 10);
    if (LOW(g_Task->screen_y) == 0x180200) { /* screen_y 512 with the counter at 24 */
        g_Task->header.mode++;
    } else if (((g_PadStates[0].pressed & g_InputMasks[INPUT_SLOT_CANCEL]) != 0) || ((g_PadStates[0].pressed & g_InputMasks[INPUT_SLOT_CONFIRM]) != 0)) {
        g_Task->header.mode = 3;
    }
}
