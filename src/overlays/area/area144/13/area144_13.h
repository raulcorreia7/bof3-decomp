#ifndef OVERLAY_WORLD03_AREA144_13_H
#define OVERLAY_WORLD03_AREA144_13_H

/* The world03/area144/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world03.h"
#include "area/spad.h"

/* The scratchpad work pointer; the dispatch entry bytes select a handler. */

/* The scroll height the camera step advances, and the flag that gates it. */
extern s32      D_80143F84;
extern u8       D_80143FC3;
/* The state handler tables the dispatchers index. */
extern Callback D_801F3E68[];
/* The palette-dirty byte the setup step clears. */
extern u8       D_801F4960;

void func_801F2E18(void);
/* The palette row clear the setup step enters. */
void func_801F30CC(void);

/* The mode gate the step tests. */
u8 func_801F34FC(void);

/* A 16-byte point row of the table at D_801F3D80. */
typedef struct AreaPoint {
    s32 x;
    s32 y;
    s32 z;
    s32 pad;
} AreaPoint;

extern AreaPoint D_801F3D80[];

#endif
