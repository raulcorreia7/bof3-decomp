#ifndef OVERLAY_BMAGIC_MAGIC076_03_H
#define OVERLAY_BMAGIC_MAGIC076_03_H

/* The bmagic/magic076/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

#define MAGIC076_STEP_COUNT 3

typedef struct Magic076Steps {
    Callback steps[MAGIC076_STEP_COUNT];
} Magic076Steps;

#define MAGIC076_MAIN_STEP_COUNT 6

typedef struct Magic076MainSteps {
    Callback steps[MAGIC076_MAIN_STEP_COUNT];
} Magic076MainSteps;

extern s16               D_1F800004;
extern Magic076MainSteps D_801EEC04;
extern Magic076Steps     D_801EEC1C;
extern Callback          D_801F048C[];
/* The number of effects each kind spawns. */
extern u8                D_801F049C[];
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect      D_801F04A4[];
#define BMAGIC_EFFECT_SLOTS D_801F04A4
#define BMAGIC_EFFECT_COUNT 64

u8   func_801EF2E8(void);
void func_801EF698(void);
void func_801EF8A8(void);

#endif
