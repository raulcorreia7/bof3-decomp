#ifndef OVERLAY_WORLD01_AREA049_13_H
#define OVERLAY_WORLD01_AREA049_13_H

/* The world01/area049/13 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/area/world01.h"
#include "overlays/scenario/scenario.h"

/* The work-window byte offset and row stride this overlay scans. */
#define SCRATCH_ROW_OFFSET 0x00
#define SCRATCH_ROW_STRIDE 0x28

extern u32      D_80117000;
extern u16      D_80146258;
extern u8  D_80144ED0[];
void func_80117B60(s32 arg0);
extern Callback D_8011818C[];
extern Callback D_8011819C[];
extern Callback D_801181AC[];
extern Callback D_801181B4[];

u8   func_80117410();
u8   func_80117900(void);

void func_801172D0(void);
void func_80117E78(s32 arg0, s32 arg1);

#endif
