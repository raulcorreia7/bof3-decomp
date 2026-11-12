#ifndef OVERLAY_BMAGIC_MAGIC120_03_H
#define OVERLAY_BMAGIC_MAGIC120_03_H

/* The bmagic/magic120/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern Callback D_801F0CB0[];

/* The z half of an enemy battler row: func_801F08AC loads it unsigned (lhu),
 * where a part.integer load sign-extends. */
extern u8 D_801EB66E[];

void BMagic_DrawWhelpBreath(void);
u8   func_801DB524(u32 slot);
void func_801F0274(void);
void func_801F08AC(void);
void func_801F0974(void);

/* D_801F0CC4 */
extern Callback BMagic_StepTable[];

#endif
