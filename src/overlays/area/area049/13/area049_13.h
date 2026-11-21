#ifndef OVERLAY_WORLD01_AREA049_13_H
#define OVERLAY_WORLD01_AREA049_13_H

/* The world01/area049/13 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/area/worlds/world01.h"
#include "overlays/area/shared/AreaSprite.h"
#include "overlays/scenario/scenario.h"

/* The work-window byte offset and row stride this overlay scans. */
#define SCRATCH_ROW_OFFSET 0x00
#define SCRATCH_ROW_STRIDE 0x28

extern u32      D_80117000;
extern u8       D_80144ED0[];
extern u16      D_80146258;
void            func_80117B60(s32 scale);
extern Callback D_8011818C[];
extern Callback D_80118194[];
extern Callback D_8011819C[];
extern Callback D_801181AC[];
extern Callback D_801181B4[];

/* The fixed x/y pair and the flag bit a scene spawns its helper actors with,
 * both indexed by the task's cell column. */
extern Offset2 D_801181C0[];
extern u8      D_801181D0[];

/* The visible cell window per column: first row, first column, last row, last column. */
extern u8          D_801181D4[][4];
extern AreaSprite* D_801181DC;
extern u16         D_1F800034_U16[2];

void func_801170D8(AreaSprite* sprite);
u8   func_80117410(void);
u8   func_80117900(void);

void func_801172D0(void);
void func_80117E78(s32 arg0, s32 arg1);

#endif
