#ifndef OVERLAY_WORLD03_AREA148_13_H
#define OVERLAY_WORLD03_AREA148_13_H

/* The world03/area148/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world03.h"
#include "area/spad.h"

/* The scratchpad work pointer; the dispatch entry bytes select a handler. */

/* The active battle-step selector. */

/* The shared flag word the close path clears a bit of. */
/* The scenario state bytes the hit path sets. */

/* The party position in 16.16 fixed point. */

/* The field focus point the work position copies. */
/* D_80147A90 */
extern s32     g_AreaFocusY;
/* The facing routes the projection reads, one Offset2 per spawn index. */
/* D_80181AC0 */
extern Offset2 g_FacingOffsets[];
/* The state handler tables the dispatchers index. */
extern u8      D_801F4FC4[];
/* The four scratch vectors RotTransPers4 projects. */
/* g_ScratchPadVectors */
extern SVECTOR g_ScratchPadVectors[];

/* The three part quads func_801F37B8 draws: their vertex offsets, the scroll
 * factors of each direction, and the texture word of each mode. */
extern u8                  D_801F5034[];
extern u8                  D_801F5038[];
extern u32                 D_801F5080[];
/* The three colour bytes func_801F4DF0 reads for each task row. */
extern u8                  D_801F6138[];
extern u8                  D_801F6139[];
extern u8                  D_801F613A[];
extern Callback            D_801F5024[];
/* D_801F6144 */
extern PartyMemberMessages g_PartyMemberMessages[2];
extern Callback            D_801F6160[];
/* The trail step of each follower per walk phase, and the cell offset of a
 * trail step by facing block: one winding around the walking leader. */
extern s8                  g_PartyTrailStep[10][2];
extern s8                  g_PartyTrailOffset[32][2];

/* The setup step the selector enters. */
void func_801F37B8(s32 mode, s32 value);

/* func_801F4544 */
void Area_SampleForwardHeight(void);
void func_801F45C8(void);
void func_801F4798(void* first, void* second);
/* The ring the line's far end joins and the quad between its ends. */
void func_801F4DF0(s32 x, s32 y, s16 radius, u16 angle);
void func_801F4A50(s16 x0, s16 y0, s16 radius0, u16 angle0, s16 x1, s16 y1, s16 radius1, u16 angle1);

void func_801F4614(void);

extern SceneTrigger D_801F615C[];

#endif
