#ifndef OVERLAY_BMAGIC_MAGIC225_03_H
#define OVERLAY_BMAGIC_MAGIC225_03_H

/* The bmagic/magic225/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

u32 BMagic_AllocEffect(void);

/* The step table the effect handler copies onto its stack by value, as retail does. */
typedef struct Magic225Steps {
    void (*steps[4])(void);
} Magic225Steps;

extern Magic225Steps D_801EEC04;
extern Callback      D_801F0398[];
extern Callback      D_801F03AC[];
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect  D_801F03BC[];
#define BMAGIC_EFFECT_SLOTS D_801F03BC
#define BMAGIC_EFFECT_COUNT 32

#endif
