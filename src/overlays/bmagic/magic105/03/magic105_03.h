#ifndef OVERLAY_BMAGIC_MAGIC105_03_H
#define OVERLAY_BMAGIC_MAGIC105_03_H

/* The bmagic/magic105/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

#define MAGIC105_STEP_COUNT 4

typedef struct Magic105Steps {
    Callback steps[MAGIC105_STEP_COUNT];
} Magic105Steps;

extern Magic105Steps D_801EEC04;
/* The ray colours the work counter picks: red, green and blue per row. */
extern u8            D_801F005C[][3];
/* The x/y speed pairs the step indexes by the work counter. */
extern s16           D_801F004C[];

void                func_801EF2F0(void);
void                func_801EF880(void);
void                func_801EFCF0(void);
extern s16          D_801F004E[];
/* The step handlers the bank-swap runner dispatches. */
extern Callback     D_801F0078[];
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect D_801F00A0[];
#define BMAGIC_EFFECT_SLOTS D_801F00A0
#define BMAGIC_EFFECT_COUNT 64

void      func_801EF3A0(void);
/* The sprite cell sizes the cell record picks with its low nibble: width and height. */
extern u8 D_801F0080[][2];

#endif
