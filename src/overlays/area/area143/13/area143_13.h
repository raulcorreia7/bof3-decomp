#ifndef OVERLAY_WORLD03_AREA143_13_H
#define OVERLAY_WORLD03_AREA143_13_H

/* The world03/area143/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/worlds/world03.h"
#include "menu/save_data.h"

/* The shop panel step the request sets. */

/* The shop panel sub-step the request handlers advance. */

/* The game-overlay state bytes the cancel path resets. */

/* The variant byte the cancel path stores in the game-overlay state. */
#define AREA_RESET_VARIANT 0xFF
extern s8 D_801F42E8[][2];

/* The character work record the span step reads. */

/* The scratchpad work pointer; the dispatch entry bytes select a handler. */

/* The scene position words the work step copies. */

/* The state handler tables the dispatchers index. */
extern Callback D_801F4308[];
extern Callback D_801F4314[];

/* The texture-coordinate base pair the beam's ring band picks by its flag. */
extern u8                  D_801F4320[][2];
/* D_801F52FC */
extern PartyMemberMessages g_PartyMemberMessages[1];
extern Callback            D_801F5308[];

/* The battle-step selector the handler tests. */
/* The frame word the request compares. */

/* The selection-arm and work-reset calls shared with the field. */
/* The scene steps the work step enters. */
/* The overlay's gate the request wrapper tests. */
s32  func_801F2EF0();
void func_801F3584(s32 height, s32 y, s32 flag);
void func_801F2FE0(void);
/* The focus-point projection and the frame step the handlers enter. */
s32  Area_StepSparkEmitters(void);
/* The draw step that reads the three-word work position. */
void Area_DrawLightPillar(s32* pos);

#include "area/effects.h"

void       func_801F2DB8(SpriteSpark* spark);
/* The number of sprite sparks the spark step updated this frame. */
extern u16 D_801F5310;

/* The emitters seeded at fixed cells, resting at the ground height. */
#define SPARK_EMITTER_COUNT 16

#endif
