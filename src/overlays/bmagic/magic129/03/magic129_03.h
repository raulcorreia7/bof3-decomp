#ifndef OVERLAY_BMAGIC_MAGIC129_03_H
#define OVERLAY_BMAGIC_MAGIC129_03_H

/* The bmagic/magic129/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern Callback     D_801F05B8[];
extern BattleEffect D_801F05D8[];
#define BMAGIC_EFFECT_SLOTS D_801F05D8
#define BMAGIC_EFFECT_COUNT 64
void func_801EFF40(void);
void func_801F030C(void);

#define MAGIC129_STEP_COUNT 3

typedef struct Magic129Steps {
    Callback steps[MAGIC129_STEP_COUNT];
} Magic129Steps;

extern Magic129Steps D_801EEC04;
/* The two staged screen points: the target (+0x04) and the start (+0x00). */
extern s16           D_1F800008[];

#endif
