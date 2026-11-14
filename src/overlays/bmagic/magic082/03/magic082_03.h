#ifndef OVERLAY_BMAGIC_MAGIC082_03_H
#define OVERLAY_BMAGIC_MAGIC082_03_H

/* The bmagic/magic082/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern BMagicEffectFuncs D_801EEC04;

extern Callback D_801F0D1C[];
void            func_801EF720(void);
void            func_801EFA00(void);

void func_801F03E0(void);

void func_801F0A84(s32 radius);
s32  func_801EF3A0(void);

/* battle/battle/15: the target selector of each effect side, and the test of a selector against the target. */
extern u8 D_800B6BF0[];
u8        func_800AED5C(s32 selector, u32 battler_index);

/* The red, green and blue of each colour row, indexed by the effect byte 0x04. */
extern u8 D_801F0CFC[][3];

/* The ring colours, laid out as D_801F0CFC. */
extern u8 D_801F0D08[][3];

/* The colours of the four triangles of the upper and the lower fan, per colour row. */
extern u8 D_801F0C9C[][4][3];
extern u8 D_801F0CCC[][4][3];

/* battle/battle/15: links count packets of size bytes from base into the map cell at the position,
 * ordered by values[]. */
void func_800AF0F8(s32 pos_x, s32 pos_y, s32* values, u8* base, u8 count, u8 size, u8 seed);

#endif
