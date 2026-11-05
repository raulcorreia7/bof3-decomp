#ifndef OVERLAY_WORLD03_AREA148_13_H
#define OVERLAY_WORLD03_AREA148_13_H

/* The world03/area148/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world03.h"

/* The scratchpad work pointer; the dispatch entry bytes select a handler. */

/* The active battle-step selector. */

/* The shared flag word the close path clears a bit of. */
/* The scenario state bytes the hit path sets. */

/* The party position in 16.16 fixed point. */
extern s32                 D_80145EC4;

void Area_Update(s32 arg);
/* The field focus point the work position copies. */
/* D_80147A90 */
extern s32                 g_AreaFocusY;
/* The facing routes the projection reads, one FacingStep per spawn index. */
/* D_80181AC0 */
extern FacingStep          g_FacingOffsets[];
/* The state handler tables the dispatchers index. */
extern u8                  D_801F4FC4[];
extern Callback            D_801F5024[];
/* D_801F6144 */
extern PartyMemberMessages g_PartyMemberMessages[2];
extern Callback            D_801F6160[];

/* The setup step the selector enters. */
void func_801F37B8(s32 mode, s32 value);

#endif
