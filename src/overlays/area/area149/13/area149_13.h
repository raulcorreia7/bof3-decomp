#ifndef OVERLAY_WORLD03_AREA149_13_H
#define OVERLAY_WORLD03_AREA149_13_H

/* The world03/area149/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world03.h"
#include "work/area_spad.h"

/* The scratchpad work pointer; the dispatch entry bytes select a handler. */

/* The camera words and the slot flags the reset path sets. */
extern u8       D_80146018;
extern u8       D_80146158;
/* The field focus point the work position copies. */
/* D_80147A90 */
extern s32      g_AreaFocusY;
/* The state handler tables the dispatchers index. */
extern u8       D_801F37D0[];
extern Callback D_801F4580[];
extern s8       D_80147AD0;

/* The intro-controller state byte the request steps advance. */

/* The overlay's companion step the wrapper enters. */
void func_801F2DE0(void);
/* The sprite-span step the handler enters. */
void func_801F3140(s32 span);

extern u8 D_80147AD0;

#endif
