#ifndef OVERLAY_WORLD02_AREA086_13_H
#define OVERLAY_WORLD02_AREA086_13_H

/* The world02/area086/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world02.h"

extern Callback D_801F3658[];

void func_801F2DE8(void);
void func_801F3070(void);

extern u8  D_801F3664[];
extern u16 D_801F3668[];

/* The three cell triggers: the cell pair, the facing that arms one and the flag it turns on. */
extern u8 D_801F3CEC[];
extern u8 D_801F3CED[];
extern u8 D_801F3CEE[];
extern u8 D_801F3CEF[];
/* The cell rectangle each trigger scans. */
extern u8 D_801F3CF8[];
extern u8 D_801F3CF9[];
extern u8 D_801F3CFA[];
extern u8 D_801F3CFB[];

s8 func_801F34F8(s32 x, s32 y);

#endif
