#ifndef OVERLAY_WORLD03_AREA143_13_H
#define OVERLAY_WORLD03_AREA143_13_H

/* The world03/area143/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world03.h"
#include "area/spad.h"
#define AREA_SPARKS        ((AreaSpark*)0x800E6000)

/* The shop panel step the request sets. */

/* The shop panel sub-step the request handlers advance. */

/* The game-overlay state bytes the cancel path resets. */

/* The variant byte the cancel path stores in the game-overlay state. */
#define AREA_RESET_VARIANT 0xFF

/* The character work record the span step reads. */

/* The scratchpad work pointer; the dispatch entry bytes select a handler. */

/* The scene position words the work step copies. */

/* The state handler tables the dispatchers index. */
extern Callback            D_801F4308[];
extern Callback            D_801F4314[];
/* D_801F52FC */
extern PartyMemberMessages g_PartyMemberMessages[1];
extern Callback            D_801F5308[];
extern s8                  D_801F42E8[][2];

/* The battle-step selector the handler tests. */
/* The frame word the request compares. */

/* The selection-arm and work-reset calls shared with the field. */
/* The scene steps the work step enters. */
/* The overlay's gate the request wrapper tests. */
s32  func_801F2EF0();
void func_801F2FE0(void);
/* The focus-point projection and the frame step the handlers enter. */
s32  func_801F30A0(void);
/* The draw step that reads the three-word work position. */
void Area_DrawLightPillar(s32* pos);

typedef struct AreaSpark {
    u8  live;
    u8  unk_01;
    u8  unk_02;
    u8  unk_03;
    s32 x;
    s32 y;
    s32 z;
    s32 pad;
} AreaSpark;

#endif
