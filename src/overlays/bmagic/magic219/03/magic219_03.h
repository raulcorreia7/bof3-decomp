#ifndef OVERLAY_BMAGIC_MAGIC219_03_H
#define OVERLAY_BMAGIC_MAGIC219_03_H

/* The bmagic/magic219/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* The ring radius, a word at scratch 0x00: the effect view names only halfwords there, so the word goes through
 * the scratch math word view. */
#define MAGIC219_RING_RADIUS g_ScratchPad.cells.words[0]
/* The orbit angle, the word after it. */
#define MAGIC219_ORBIT_ANGLE g_ScratchPad.cells.words[1]

/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern Callback     D_801EFA04[];
extern BattleEffect D_801EFA14[];
#define BMAGIC_EFFECT_SLOTS D_801EFA14
#define BMAGIC_EFFECT_COUNT 32
u32 func_800AF720(s32 start, s32 end, s32 value);

#define MAGIC219_STEP_COUNT 4

typedef struct Magic219Steps {
    Callback steps[MAGIC219_STEP_COUNT];
} Magic219Steps;

extern Magic219Steps D_801EEC04;
extern u8            D_801EF9E8[];

#endif
