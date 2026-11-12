#ifndef OVERLAY_BMAGIC_MAGIC113_03_H
#define OVERLAY_BMAGIC_MAGIC113_03_H

/* The bmagic/magic113/03 overlay. Only this image includes the file. */

/* 0x1F800000 scratchpad */
#define GAME_SCRATCH_BASE_WORD

#include "overlays/bmagic/bmagic.h"

/* The orbit radius the effect keeps in the scratchpad word; func_801EF944 scales its sin and cos by it. */
#define s_Magic113OrbitRadius D_1F800000

/* Count the effect timer up and finish the effect at 12. */
static inline void Effect_CountUpTimer(void) {
    PartyMember* work;
    u8           next;

    work        = g_Task;
    next        = work->timer + 1;
    work->timer = next;
    if (next == 0xC) {
        BATTLE_ACTIVE_WORK->param.unk_0B--;
        func_801E5988();
    }
}

#define MAGIC113_STEP_COUNT 8

typedef struct Magic113Steps {
    Callback handlers[MAGIC113_STEP_COUNT];
} Magic113Steps;

extern Magic113Steps D_801EEC04;

extern Callback D_801F0BAC[];
extern s32      D_801F0BA4[];

extern Callback D_801F0BC0[];
void            func_801EFDA0(void);

extern Callback D_801F0BCC[];
extern Callback D_801F0BD8[];
void            func_801F02CC(void);

#endif
