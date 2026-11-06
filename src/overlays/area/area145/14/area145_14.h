#ifndef OVERLAY_WORLD03_AREA145_14_H
#define OVERLAY_WORLD03_AREA145_14_H

/* The world03/area145/14 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world03.h"
#include "work/area_spad.h"
#include "work/save.h"

/* The scratchpad work pointer; the dispatch entry bytes select a handler. */

/* The state handler tables the dispatchers index. */
extern u8                  D_801F5434[];
extern Callback            D_801F5454[];
extern Callback            D_801F545C[];
extern Callback            D_801F5C94[];
/* D_801F5C9C */
extern PartyMemberMessages g_PartyMemberMessages[3];

/* The selected win entry and the cue wrappers that act on it. */

/* The game-overlay state bytes the win-close path resets. */
/* The scenario request step bytes the arm sets. */
/* The stage byte the sound step tests. */

/* The selection-arm and work-reset calls shared with the field. */
/* The bounds step and the choice query the handlers enter. */
void func_801F332C(u8* first, u8* second);
/* The draw step that reads the three-word work position. */
void func_801F3980(u32* pos);

#endif
