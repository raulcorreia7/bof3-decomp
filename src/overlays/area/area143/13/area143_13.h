#ifndef OVERLAY_WORLD03_AREA143_13_H
#define OVERLAY_WORLD03_AREA143_13_H

/* The world03/area143/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world03.h"
#include "work/area_spad.h"

/* The shop panel step the request sets. */

/* The shop panel sub-step the request handlers advance. */

/* The game-overlay state bytes the cancel path resets. */

/* The variant byte the cancel path stores in the game-overlay state. */
#define AREA_RESET_VARIANT 0xFF

/* The character work record the span step reads. */

/* The scratchpad work pointer; the dispatch entry bytes select a handler. */

/* The scene position words the work step copies. */
extern u32 D_80145EC4;

/* The state handler tables the dispatchers index. */
extern Callback            D_801F4308[];
extern Callback            D_801F4314[];
/* D_801F52FC */
extern PartyMemberMessages g_PartyMemberMessages[1];
extern Callback            D_801F5308[];

/* The battle-step selector the handler tests. */
/* The frame word the request compares. */

/* The selection-arm and work-reset calls shared with the field. */
void GFX_FreePaletteFadeTarget(void* target);
/* The scene steps the work step enters. */
/* The overlay's gate the request wrapper tests. */
s32  func_801F2EF0();
void func_801F2FE0(void);
/* The focus-point projection and the frame step the handlers enter. */
void func_801F30A0(void);
/* The draw step that reads the three-word work position. */
void func_801F3FDC(u32* pos);

#endif
