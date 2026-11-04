#ifndef OVERLAY_SCENARIO_SCENA02_00_H
#define OVERLAY_SCENARIO_SCENA02_00_H

/* The scenario/scena02/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/scenario/scenario.h"

/* The four script variable bytes read as one word. */
#define g_ScriptVarsWord (*(s32*)&g_ScriptVars)

extern u8 D_80146874;

extern u8 D_80146875;

extern u32      D_801F6C00;
extern Callback D_801FE294[];

extern Callback  D_801FE288[];
extern SceneFunc D_801FE304[66];

extern s32 D_80145EC4;

extern u8  D_80146865;
extern u8  D_80146866;
extern u8  D_80146867;
extern u16 g_GameAreaId;

/* The party-in-range triggers of 5A4.c: while D_80143F03 is 0, start func_801FCB54 when the party
 * position (D_80145EC4, D_80145EC8) lies inside a window around g_Actors[actor_id]. Each macro is one
 * window shape; the members differ only in the distances. Every change must verify every member. */

/* Within `y_pad` of the actor's y, and from its x to `x_len` past it. */
#define SCENA02_TRIGGER_NEAR_Y(actor_id, y_pad, x_len)                                                        \
    if (D_80143F03 == 0) {                                                                                    \
        if (g_Actors[actor_id].y.fixed + (y_pad) >= D_80145EC8 &&                                             \
            D_80145EC8 >= g_Actors[actor_id].y.fixed - (y_pad) && D_80145EC4 >= g_Actors[actor_id].x.fixed && \
            g_Actors[actor_id].x.fixed + (x_len) >= D_80145EC4) {                                             \
            func_801FCB54();                                                                                  \
        }                                                                                                     \
    }

/* Within `x_pad` of the actor's x, and from its y to `y_len` past it. */
#define SCENA02_TRIGGER_NEAR_X(actor_id, x_pad, y_len)                                                        \
    if (D_80143F03 == 0) {                                                                                    \
        if (g_Actors[actor_id].x.fixed + (x_pad) >= D_80145EC4 &&                                             \
            D_80145EC4 >= g_Actors[actor_id].x.fixed - (x_pad) && D_80145EC8 >= g_Actors[actor_id].y.fixed && \
            g_Actors[actor_id].y.fixed + (y_len) >= D_80145EC8) {                                             \
            func_801FCB54();                                                                                  \
        }                                                                                                     \
    }

/* From `y_below` under to `y_above` over the actor's y, and from its x to `x_len` past it. */
#define SCENA02_TRIGGER_BAND_Y(actor_id, y_above, y_below, x_len)                                               \
    if (D_80143F03 == 0) {                                                                                      \
        if (g_Actors[actor_id].y.fixed + (y_above) >= D_80145EC8 &&                                             \
            D_80145EC8 >= g_Actors[actor_id].y.fixed - (y_below) && D_80145EC4 >= g_Actors[actor_id].x.fixed && \
            g_Actors[actor_id].x.fixed + (x_len) >= D_80145EC4) {                                               \
            func_801FCB54();                                                                                    \
        }                                                                                                       \
    }

#endif
