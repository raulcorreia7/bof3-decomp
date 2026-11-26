#ifndef OVERLAY_WORLD03_AREA145_14_H
#define OVERLAY_WORLD03_AREA145_14_H

/* The world03/area145/14 overlay: one file per split function
 * and its data. Only this image includes the file. */
#include "game/spawn.h"
#include "overlays/area/worlds/world03.h"

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
/* The two-quad join between two segments of the marker line. */
void func_801F311C(s16 x0, s16 y0, s16 x1, s16 y1);
void func_801F332C(s32* first, s32* second);
/* The semi-transparent quad that joins the two marker fans. */
void func_801F3618(s16 x1, s16 y1, s16 radius1, u16 angle1, s16 x2, s16 y2, s16 radius2, u16 angle2);
/* The draw step that reads the three-word work position. */
void Area_DrawMatrixLightPillar(s32* pos);

/* Claims an actor slot of type 0x3F, seeds its two points and returns 1 when no slot is free. */
u8 func_801F5190(s32 x1, s32 y1, s32 x2, s32 y2);

extern CellBlock D_801F543C[4];
extern Callback  D_801F544C[];
void             func_801F2F30(s32* first, s32* second);
extern u8        D_80144EF0[];

/* The actor row table and the per-actor 16-byte turn records. */

/* The work word the stage route reads. */
/* The shared route steps the stage table indexes. */
extern s8           D_80181B00[][2];
extern SceneTrigger D_801F5CC0[];
/* The stage table: the route index, the stage length and the next stage code. */
extern u8           D_801F5CDC[];
extern u8           D_801F5CDD[];
extern u8           D_801F5CDE[];

/* The per-direction stage steps of a full stage and of a half stage: the route
 * index, the stage length and the next stage code in each four-byte record. */
/* One walk step per facing: the heading into D_80181B00 and the frames it lasts. */
typedef struct {
    u8 heading;
    u8 duration;
    u8 unk_2;
    u8 unk_3;
} Area145Step;

extern Area145Step D_801F5CEC[];
extern Area145Step D_801F5CFC[];
extern Area145Step D_801F5D0C[];
extern Area145Step D_801F5D1C[];

u8 func_801F4DA4(u32 frame);
u8 func_801F4EDC(s32 t, u32 stage);

#endif
