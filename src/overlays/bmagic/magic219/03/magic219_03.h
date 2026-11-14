#ifndef OVERLAY_BMAGIC_MAGIC219_03_H
#define OVERLAY_BMAGIC_MAGIC219_03_H

/* The bmagic/magic219/03 overlay. Only this image includes the file. */

#define BATTLE_PARTY_CELL_RECORD

#include "overlays/bmagic/bmagic.h"

extern SVECTOR D_1F800014[];
/* The ring radius, a word at scratch 0x00: the effect view names only halfwords there, so the word goes through
 * the scratch math word view. */
#define MAGIC219_RING_RADIUS D_1F800000.view.scenario.math_00
/* The orbit angle, the word after it. */
#define MAGIC219_ORBIT_ANGLE D_1F800000.view.scenario.math_04

/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern Callback     D_801EFA04[];
extern BattleEffect D_801EFA14[];
#define BMAGIC_EFFECT_SLOTS D_801EFA14
#define BMAGIC_EFFECT_COUNT 32
/* func_801EF024 */
void BMagic_DispatchEffectMode(void);

#define MAGIC219_STEP_COUNT 4

typedef struct Magic219Steps {
    Callback steps[MAGIC219_STEP_COUNT];
} Magic219Steps;

extern Magic219Steps D_801EEC04;
extern u8            D_801EF9E8[];

#endif
