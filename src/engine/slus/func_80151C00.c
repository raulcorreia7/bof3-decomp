#include "engine/slus/slus.h"

/* steps the menu cursor bob: the cursor offset D_801490BA walks between -3 and 3 (the direction is g_UiMessageChoiceStep), and at
 * each end the D_801490BB blink counter runs, reloading the D_801490CA timer and, at zero, counting g_UiMessageChoiceTimer down.
 */
#define BOB   (D_801490B8[2])
#define BLINK (D_801490B8[3])

#ifdef NON_MATCHING
NON_MATCHING void func_80151C00(void) {
    s8  pos;
    u8* step = &g_UiMessageChoiceStep;

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
    if (g_UiMessageWindow.cue_timer == 0) {
        BLINK += (u8)g_UiMessageWindow.cue_counter;
        switch ((s8)BLINK) {
            case 0:
                g_UiMessageWindow.cue_timer   = 15;
                g_UiMessageWindow.cue_counter = -1;
                if (g_UiMessageChoiceTimer != 0xFFFF) {
                    if (g_UiMessageChoiceTimer-- == 0) {
                        g_UiMessageChoiceMode = 0;
                        BLINK                 = 0;
                        BOB                   = 0;
                    }
                }
                break;
            case -10:
                g_UiMessageWindow.cue_timer   = 15;
                g_UiMessageWindow.cue_counter = 1;
                break;
            default:
                g_UiMessageWindow.cue_timer = 3;
                break;
        }
    } else {
        g_UiMessageWindow.cue_timer--;
    }
}
#else
INCLUDE_ASM(func_80151C00);
#endif
