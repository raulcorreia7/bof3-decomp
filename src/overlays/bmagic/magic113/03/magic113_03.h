#ifndef OVERLAY_BMAGIC_MAGIC113_03_H
#define OVERLAY_BMAGIC_MAGIC113_03_H

/* The bmagic/magic113/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* Count the effect timer up and finish the effect at 12. */
static inline void Effect_CountUpTimer(void) {
    PartyBattler* work;
    u8            next;

    work        = g_Task;
    next        = work->timer + 1;
    work->timer = next;
    if (next == 0xC) {
        BATTLE_ACTIVE_WORK->unk_0B--;
        func_801E5988();
    }
}

extern Callback D_801F0BC0[];
void            func_801EFDA0(void);

extern Callback D_801F0BCC[];
void            func_801F02CC(void);

#endif
