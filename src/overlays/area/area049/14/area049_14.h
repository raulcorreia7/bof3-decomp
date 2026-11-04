#ifndef OVERLAY_WORLD01_AREA049_14_H
#define OVERLAY_WORLD01_AREA049_14_H

/* The world01/area049/14 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world01.h"

void Area_SetCellCode(s16 column, s16 row, u8 code);

#define g_SceneFlags ((void*)g_SceneFlags)

extern u8  D_801F398C[];
extern u16 D_801F5CD4[];
extern u16 D_801F5CD8[];

extern u8 D_80145F09;

extern u8 D_80146874;

extern u8 D_80146875;

/* A bare statement macro, used as a member's whole body. Clear the interaction bit; when the party confirmed (D_80145F09 is 6), run the script and store the
 * two step bytes. */
#define AREA_INTERACT_CONFIRM(step_next)                                       \
    if (D_80145F09 == 6) {                                                     \
        ((Actor*)g_CurrentActor)->flags_74 &= ~ACTOR_FLAG_INTERACTION_PENDING; \
        Game_SetScriptActive();                                                \
        D_80146874 = 4;                                                        \
        D_80146875 = (step_next);                                              \
    } else {                                                                   \
        ((Actor*)g_CurrentActor)->flags_74 &= ~ACTOR_FLAG_INTERACTION_PENDING; \
    }

#endif
