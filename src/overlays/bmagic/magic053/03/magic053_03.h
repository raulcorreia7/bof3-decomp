#ifndef OVERLAY_BMAGIC_MAGIC053_03_H
#define OVERLAY_BMAGIC_MAGIC053_03_H

/* The bmagic/magic053/03 overlay. Only this image includes the file. */

/* The acting battler cell is read as its record. */
#define BATTLE_PARTY_CELL_RECORD
#include "overlays/bmagic/bmagic.h"
#include "sys/scene.h"

extern s16          D_1F800004;
extern u16          D_1F80000A;
extern Callback     D_801F056C[];
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect D_801F0578[];
#define BMAGIC_EFFECT_SLOTS D_801F0578
#define BMAGIC_EFFECT_COUNT 32
void func_801F01C0(void);
void Actor_Clear(void);
void func_801EFD50(void);

#define MAGIC053_STEP_COUNT 3

typedef struct Magic053Steps {
    Callback steps[MAGIC053_STEP_COUNT];
} Magic053Steps;

extern Magic053Steps D_801EEC04;

extern Callback D_801F0554[];
/* Per spark: the start byte; its high nibble picks the spark kind. */
extern u8       D_801F0548[];

#endif
