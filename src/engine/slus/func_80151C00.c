#include "engine/slus/slus.h"

/* steps the menu cursor bob: the cursor offset D_801490BA walks between -3 and 3 (the direction is g_MessageChoiceStep), and at
 * each end the D_801490BB blink counter runs, reloading the D_801490CA timer and, at zero, counting g_MessageChoiceTimer down.
 */
#define BOB   (D_801490B8[2])
#define BLINK (D_801490B8[3])

#ifdef NON_MATCHING
NON_MATCHING void func_80151C00(void) {
    s8  pos;
    u8* step = &g_MessageChoiceStep;

    if (*step != 0) {
        if ((s8)BOB == 3) {
            *step -= 1;
            return;
        }
        pos = (s8)BOB + 1;
    } else {
        if ((s8)BOB == -3) {
            *step += 1;
            return;
        }
        pos = (s8)BOB - 1;
    }
    BOB = pos;
    if (g_MessageWindow.cue_timer == 0) {
        BLINK += (u8)g_MessageWindow.cue_counter;
        switch ((s8)BLINK) {
            case 0:
                g_MessageWindow.cue_timer   = 15;
                g_MessageWindow.cue_counter = -1;
                if (g_MessageChoiceTimer != 0xFFFF) {
                    if (g_MessageChoiceTimer-- == 0) {
                        g_MessageChoiceMode = 0;
                        BLINK               = 0;
                        BOB                 = 0;
                    }
                }
                break;
            case -10:
                g_MessageWindow.cue_timer   = 15;
                g_MessageWindow.cue_counter = 1;
                break;
            default:
                g_MessageWindow.cue_timer = 3;
                break;
        }
    } else {
        g_MessageWindow.cue_timer--;
    }
}
#else
INCLUDE_ASM(func_80151C00);
#endif
