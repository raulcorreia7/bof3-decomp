#ifndef OVERLAY_BMAGIC_MAGIC087_03_H
#define OVERLAY_BMAGIC_MAGIC087_03_H

/* The bmagic/magic087/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern Callback D_801F0530[];

extern Callback     D_801F0540[];
/* The effect slot table BMagic_AllocEffect scans, and its row count. */
extern BattleEffect D_801F054C[];
#define BMAGIC_EFFECT_SLOTS         D_801F054C
#define BMAGIC_EFFECT_COUNT         80
#define BMAGIC_EFFECT_START_HANDLER Effect_PlayOnZeroTick
void func_801EED04(void);
#define BMAGIC_EFFECT_SLOT_STEP func_801EF958
void      func_801EFF50(void);
void      func_801F0014(void);
/* The shade step of the square's outline for each value of the frame counter (unk_04). */
extern u8 D_801F0548[];

void func_801EF580(s32 phase);

#endif
