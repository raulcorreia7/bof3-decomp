#include "engine/slus/slus.h"
#include "func_80151C00.h"

#define BOB   (D_801490BA_byte)
#define BLINK (D_801490BB_byte)

/* Steps the menu cursor bob and its blink timer. */
/* func_80151C00 */
MATCH void func_80151C00(void) {
    s8  pos;
    u16 timer;
    u8* step = &g_UIMessageChoiceStep;

    if (*step != 0) {
        if (BOB == 3) {
            *step -= 1;
            return;
        }
        pos = BOB + 1;
    } else {
        if (BOB == -3) {
            *step += 1;
            return;
        }
        pos = BOB - 1;
    }
    /* FAKE: the loop keeps the retail pos register and store order. */
    do {
        BOB = pos;
    } while (0);
    if (g_UIMessageWindow.cue_timer == 0) {
        BLINK += (u8)g_UIMessageWindow.cue_counter;
        switch ((s8)BLINK) {
            case 0:
                g_UIMessageWindow.cue_timer = 15;
                /* FAKE: the barrier keeps the timer load below the cue_timer store. */
                FAKE_BARRIER();
                timer                         = g_UIMessageChoiceTimer;
                g_UIMessageWindow.cue_counter = -1;
                if (timer != 0xFFFF) {
                    /* FAKE: 0xFFFF keeps retail's addu; the u16 store wraps it to timer - 1. */
                    g_UIMessageChoiceTimer = timer + 0xFFFF;
                    if (timer == 0) {
                        g_UIMessageChoiceMode = 0;
                        BLINK                 = 0;
                        BOB                   = 0;
                    }
                }
                break;
            case -10:
                g_UIMessageWindow.cue_timer   = 15;
                g_UIMessageWindow.cue_counter = 1;
                break;
            default:
                g_UIMessageWindow.cue_timer = 3;
                break;
        }
    } else {
        g_UIMessageWindow.cue_timer--;
    }
}
