#include "engine/slus/slus.h"

/* steps the menu cursor bob: the cursor offset D_801490BA walks between -3 and 3 (the direction is g_MessageChoiceStep), and at
 * each end the D_801490BB blink counter runs, reloading the D_801490CA timer and, at zero, counting g_MessageChoiceTimer down.
 */
/* Reversing the blink cases and adding store barriers leave the exit jump different at +0x30. */
#ifdef NON_MATCHING
NON_MATCHING void func_80151C00(void) {
    s8  pos;
    u8* step = &g_MessageChoiceStep;

    if (*step != 0) {
        if (D_801490BA[0] == 3) {
            *step -= 1;
            return;
        }
        pos = D_801490BA[0] + 1;
    } else {
        if (D_801490BA[0] == -3) {
            *step += 1;
            return;
        }
        pos = D_801490BA[0] - 1;
    }
    D_801490BA[0] = pos;
    if (D_801490CA == 0) {
        D_801490BB[0] += (u8)D_801490C8;
        if ((s8)D_801490BB[0] == -10) {
            D_801490CA = 0xF;
            D_801490C8 = 1;
        } else if ((s8)D_801490BB[0] == 0) {
            D_801490CA = 0xF;
            D_801490C8 = -1;
            if (g_MessageChoiceTimer != 0xFFFF) {
                g_MessageChoiceTimer -= 1;
                if (g_MessageChoiceTimer == 0xFFFF) {
                    g_MessageChoiceMode = 0;
                    D_801490BB[0]       = 0;
                    D_801490BA[0]       = 0;
                }
            }
        } else {
            D_801490CA = 3;
        }
    } else {
        D_801490CA = D_801490CA - 1;
    }
}
#else
INCLUDE_ASM(func_80151C00);
#endif
