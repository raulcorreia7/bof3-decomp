#ifndef OVERLAY_BMAGIC_MAGIC120_03_H
#define OVERLAY_BMAGIC_MAGIC120_03_H

/* The bmagic/magic120/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern Callback D_801F0CB0[];

u8   Battle_SlotIsBlocked(u32 slot);
void BMagic_DrawWhelpBreath(void);
void func_801F0274(void);
void func_801F08AC(void);
void func_801F0974(void);

/* D_801F0CC4 */
extern Callback BMagic_StepTable[];

#endif
