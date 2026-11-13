#ifndef OVERLAY_WORLD03_AREA145_14_H
#define OVERLAY_WORLD03_AREA145_14_H

/* The world03/area145/14 overlay: one file per split function
 * and its data. Only this image includes the file. */

#define GAME_SCRATCH_BASE_SCALAR
#include "game/spawn.h"
#include "overlays/area/world03.h"
#include "area/spad.h"

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
void func_801F332C(s32* first, s32* second);
/* The semi-transparent quad that joins the two marker fans. */
void func_801F3618(s16 x1, s16 y1, s16 radius1, u16 angle1, s16 x2, s16 y2, s16 radius2, u16 angle2);
/* The draw step that reads the three-word work position. */
void func_801F3980(u32* pos);

/* Claims an actor slot of type 0x3F, seeds its two points and returns 1 when no slot is free. */
u8 func_801F5190(s32 x1, s32 y1, s32 x2, s32 y2);

/* The two corner cells of each of the four areas the step covers. */
typedef struct CellBox {
    u8 x1;
    u8 y1;
    u8 x2;
    u8 y2;
} CellBox;

extern CellBox  D_801F543C[4];
extern Callback D_801F544C[];
void            func_801F2F30(s32* first, s32* second);

/* The actor row table and the per-actor 16-byte turn records. */
extern Actor D_80147A58[];
extern s8    D_80147CB9[];
extern s8    D_80147CBA[];
extern s32   D_80147CC4[];

extern SceneTrigger D_801F5CC0[];
extern u8           D_80144EF0[];

/* g_Game.current */
extern PartyMember* D_80146250;

#endif
