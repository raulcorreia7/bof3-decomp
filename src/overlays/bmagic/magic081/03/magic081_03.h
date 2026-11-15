#ifndef OVERLAY_BMAGIC_MAGIC081_03_H
#define OVERLAY_BMAGIC_MAGIC081_03_H

/* The bmagic/magic081/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern BattleEffect* D_801EC2E0;

#define MAGIC081_STEP_COUNT 3

typedef struct Magic081Steps {
    Callback steps[MAGIC081_STEP_COUNT];
} Magic081Steps;

#define MAGIC081_SECOND_STEP_COUNT 4

typedef struct Magic081SecondSteps {
    Callback steps[MAGIC081_SECOND_STEP_COUNT];
} Magic081SecondSteps;

extern Magic010SharedSteps D_801EEC04;
extern Magic081Steps       D_801EEC14;
extern Magic081SecondSteps D_801EEC20;
/* The effect slot table BMagic_AllocEffect scans. */
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect        D_801EFA8C[];
#define BMAGIC_EFFECT_SLOTS D_801EFA8C
#define BMAGIC_EFFECT_COUNT BATTLE_EFFECT_COUNT

/* Retail orders the target load after the palette store; the plain member form
 * lets the compiler move it up, so the address goes through its own type. */
static inline PartyMember* BattleEffect_GetTarget(BattleEffect* effect) {
    return *(PartyMember**)&effect->target.party;
}

void func_801EF6A0(void);

#endif
