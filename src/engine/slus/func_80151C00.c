#include "engine/slus/slus.h"

/* The unit read the cue bytes as scalars; the header holds their base form for the units that
 * take their address. */
extern s8 D_801490BA_byte __asm__("D_801490BA");
extern u8 D_801490BB_byte __asm__("D_801490BB");

/* Steps the menu cursor bob: the offset D_801490BA_byte walks between -3 and 3 (the direction is
 * g_UiMessageChoiceStep); at each end the D_801490BB_byte blink counter runs, reloading the
 * cue timer and, at zero, counting g_UiMessageChoiceTimer down.
 */
/* func_80151C00 */
MATCH void func_80151C00(void) {
    s8  pos;
    u16 timer;
    u8* step = &g_UiMessageChoiceStep;

    if (*step != 0) {
        if (D_801490BA_byte == 3) {
            *step -= 1;
            return;
        }
        pos = D_801490BA_byte + 1;
    } else {
        if (D_801490BA_byte == -3) {
            *step += 1;
            return;
        }
        pos = D_801490BA_byte - 1;
    }
    /* FAKE: the loop keeps the retail pos register and store order. */
    do {
        D_801490BA_byte = pos;
    } while (0);
    if (g_UiMessageWindow.cue_timer == 0) {
        D_801490BB_byte += (u8)g_UiMessageWindow.cue_counter;
        switch ((s8)D_801490BB_byte) {
            case 0:
                g_UiMessageWindow.cue_timer = 15;
                /* FAKE: the barrier keeps the timer load below the cue_timer store. */
                FAKE_BARRIER();
                timer                         = g_UiMessageChoiceTimer;
                g_UiMessageWindow.cue_counter = -1;
                if (timer != 0xFFFF) {
                    /* FAKE: 0xFFFF keeps retail's addu; the u16 store wraps it to timer - 1. */
                    g_UiMessageChoiceTimer = timer + 0xFFFF;
                    if (timer == 0) {
                        g_UiMessageChoiceMode = 0;
                        D_801490BB_byte       = 0;
                        D_801490BA_byte       = 0;
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
