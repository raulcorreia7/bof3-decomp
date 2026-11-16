#include "area077_14.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F2D0C(void) {
    u8  i;
    s16 count;

    /* FAKE: func_801F31EC reads two arguments; the shared area prototype gives none. */
    ((void (*)(s32, s32))func_801F31EC)(0x82, 10);
    i = 0;
    do {
        g_Task->screen_x++;
        if ((s16)g_Task->screen_x >= 0x48) {
            g_Task->screen_x = 0;
        }
        if (SYS_TestFlag(g_SceneFlags, 0x25) != 0) {
            g_Task->screen_y -= 0x10;
            if ((s16)g_Task->screen_y < 0x200) {
                g_Task->screen_y = 0x200;
            }
            count = LOH(g_Task->unk_32);
            if ((g_FrameCount & 3) == 0) {
                count++;
            }
            LOH(g_Task->unk_32) = count;
            if (LOH(g_Task->unk_32) >= 0x19) {
                LOH(g_Task->unk_32) = 0x18;
            }
            COORD_INT(g_Task->pos.x) = 0;
        }
        func_801F35E0(0x82, 10, g_Task->screen_x, g_Task->screen_y, g_Task->unk_32, COORD_INT(g_Task->pos.x));
        i++;
    } while (i < 2);

    func_801F36E8(0x82, 10);
    if (LOW(g_Task->screen_y) == 0x180200) {
        g_Task->header.mode = g_Task->header.mode + 1;
    } else if ((g_InputPressed & g_InputMasks[INPUT_SLOT_CONFIRM]) != 0) {
        g_Task->header.mode = 3;
    } else if ((g_InputPressed & g_InputMasks[INPUT_SLOT_CANCEL]) != 0) {
        g_Task->header.mode = 3;
    }
}
#else
INCLUDE_ASM(func_801F2D0C);
#endif
