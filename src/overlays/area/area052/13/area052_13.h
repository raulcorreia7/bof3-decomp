#ifndef OVERLAY_WORLD01_AREA052_13_H
#define OVERLAY_WORLD01_AREA052_13_H

/* The world01/area052/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world01.h"
#include "area/spad.h"

/* The work-window byte offset and row stride this overlay scans. */
#define SCRATCH_ROW_OFFSET 0x15
#define SCRATCH_ROW_STRIDE 0x18

extern u8 D_801F44B8[];

/* A rectangle of world cells that a scene event step tests the party against. */
typedef struct AreaTriggerRect {
    u8 x;
    u8 y;
    u8 width;
    u8 height;
} AreaTriggerRect;

extern AreaTriggerRect D_801F510C[2];
s32                    func_801F31C0();
void                   func_801F3C4C(s32 x, s32 y);

void func_801F431C(void);

#endif
