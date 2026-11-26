#ifndef OVERLAY_WORLD03_AREA149_13_H
#define OVERLAY_WORLD03_AREA149_13_H

/* The world03/area149/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/worlds/world03.h"

/* The scratchpad work pointer; the dispatch entry bytes select a handler. */

/* The camera words and the slot flags the reset path sets. */
extern u8       D_80146158;
/* The integer half of the focus x, stepped by the scene trigger. */
extern u16      D_80147A8E;
/* The event countdown D_801448EE, stepped and tested unsigned. */
extern u16      D_801448EE_U16;
/* The state handler tables the dispatchers index. */
extern u8       D_801F37D0[];
extern Callback D_801F4580[];

/* The intro-controller state byte the request steps advance. */

/* The overlay's companion step the wrapper enters. */
/* The sprite-span step the handler enters. */
void func_801F3140(s8 span);

#endif
