#ifndef OVERLAY_BMAGIC_MAGIC113_03_H
#define OVERLAY_BMAGIC_MAGIC113_03_H

/* The bmagic/magic113/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* Count the effect timer up and finish the effect at 12. */
static inline void Effect_CountUpTimer(void) {
    PartyBattler* work;
    u8            next;

    work                        = g_SpadWork;
    next                        = work->word_08.byte.timer_0A + 1;
    work->word_08.byte.timer_0A = next;
    if (next == 0xC) {
        BATTLE_ACTIVE_WORK->word_08.byte.unk_0B--;
        func_801E5988();
    }
}

extern Callback D_801F0BCC[];
void            func_801F02CC(void);

extern Callback D_801F0BC0[];
void            func_801EFDA0(void);

#endif
