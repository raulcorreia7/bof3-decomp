#ifndef OVERLAY_BMAGIC_MAGIC120_03_H
#define OVERLAY_BMAGIC_MAGIC120_03_H

/* The bmagic/magic120/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern Callback D_801F0CB0[];

extern u8 D_801F0D0C[];

/* The offset of each of the three rows of breath pieces from an enemy, in 16.16. */
extern Point3l D_801F0CE4[];

void func_801F078C(void);

void func_800B0118(void);

/* The z half of an enemy battler row: func_801F08AC loads it unsigned (lhu),
 * where a part.integer load sign-extends. */
extern u8 D_801EB66E[];

void BMagic_DrawWhelpBreath(void);
void func_801F0274(void);
void func_801F08AC(void);
void func_801F0974(void);

/* D_801F0CC4 */
extern Callback BMagic_Steps[];

#endif
