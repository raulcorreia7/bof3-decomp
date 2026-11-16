#ifndef OVERLAY_SCENARIO_SCENA02_00_H
#define OVERLAY_SCENARIO_SCENA02_00_H

/* The scenario/scena02/00 overlay's local declarations. Only this image
 * includes the file. */

#include "overlays/scenario/scenario.h"
#include "sys/exe.h"

extern u8        D_801460FB;
extern u32       D_801F6C00;
extern Callback  jtbl_801F6CF4[6];
extern Callback  jtbl_801F704C[18];
extern u8        D_801FE26C[];
extern Callback  D_801FE288[];
extern Callback  D_801FE294[];
extern SceneFunc D_801FE304[66];

/* The party-in-range triggers of 5A4.c: while g_GameCellType is 0, start func_801FCB54 when the party position (g_Game.members[0].pos.x.fixed, g_Game.members[0].pos.y.fixed) lies inside a window around g_Actors[actor_id]. Each macro is one window shape; the members differ only in the distances. */

/* Within `y_pad` of the actor's y, and from its x to `x_len` past it. */
#define SCENA02_TRIGGER_NEAR_Y(actor_id, y_pad, x_len)                                                                                                                    \
    {                                                                                                                                                                     \
        if (g_GameCellType == 0) {                                                                                                                                        \
            if (g_Actors[actor_id].pos.y.fixed + (y_pad) >= g_Game.members[0].pos.y.fixed && g_Game.members[0].pos.y.fixed >= g_Actors[actor_id].pos.y.fixed - (y_pad) && \
                g_Game.members[0].pos.x.fixed >= g_Actors[actor_id].pos.x.fixed && g_Actors[actor_id].pos.x.fixed + (x_len) >= g_Game.members[0].pos.x.fixed) {           \
                func_801FCB54();                                                                                                                                          \
            }                                                                                                                                                             \
        }                                                                                                                                                                 \
    }

/* Within `x_pad` of the actor's x, and from its y to `y_len` past it. */
#define SCENA02_TRIGGER_NEAR_X(actor_id, x_pad, y_len)                                                                                                                    \
    {                                                                                                                                                                     \
        if (g_GameCellType == 0) {                                                                                                                                        \
            if (g_Actors[actor_id].pos.x.fixed + (x_pad) >= g_Game.members[0].pos.x.fixed && g_Game.members[0].pos.x.fixed >= g_Actors[actor_id].pos.x.fixed - (x_pad) && \
                g_Game.members[0].pos.y.fixed >= g_Actors[actor_id].pos.y.fixed && g_Actors[actor_id].pos.y.fixed + (y_len) >= g_Game.members[0].pos.y.fixed) {           \
                func_801FCB54();                                                                                                                                          \
            }                                                                                                                                                             \
        }                                                                                                                                                                 \
    }

/* From `y_below` under to `y_above` over the actor's y, and from its x to `x_len` past it. */
#define SCENA02_TRIGGER_BAND_Y(actor_id, y_above, y_below, x_len)                                                                                                             \
    {                                                                                                                                                                         \
        if (g_GameCellType == 0) {                                                                                                                                            \
            if (g_Actors[actor_id].pos.y.fixed + (y_above) >= g_Game.members[0].pos.y.fixed && g_Game.members[0].pos.y.fixed >= g_Actors[actor_id].pos.y.fixed - (y_below) && \
                g_Game.members[0].pos.x.fixed >= g_Actors[actor_id].pos.x.fixed && g_Actors[actor_id].pos.x.fixed + (x_len) >= g_Game.members[0].pos.x.fixed) {               \
                func_801FCB54();                                                                                                                                              \
            }                                                                                                                                                                 \
        }                                                                                                                                                                     \
    }

/* From `x_len` before the actor's x up to it, and within `y_pad` of its y. */
#define SCENA02_TRIGGER_BEHIND_X(actor_id, x_len, y_pad)                                                                                                                  \
    {                                                                                                                                                                     \
        if (g_GameCellType == 0) {                                                                                                                                        \
            if (g_Game.members[0].pos.x.fixed >= g_Actors[actor_id].pos.x.fixed - (x_len) && g_Actors[actor_id].pos.x.fixed >= g_Game.members[0].pos.x.fixed &&           \
                g_Game.members[0].pos.y.fixed >= g_Actors[actor_id].pos.y.fixed - (y_pad) && g_Actors[actor_id].pos.y.fixed + (y_pad) >= g_Game.members[0].pos.y.fixed) { \
                func_801FCB54();                                                                                                                                          \
            }                                                                                                                                                             \
        }                                                                                                                                                                 \
    }

void func_801FBF94(u8 actor_id);
void func_801FC044(u8 actor_id);
void func_801FC0F4(u8 actor_id);
void func_801FC1A4(u8 actor_id);
void func_801FC25C(u8 actor_id);
void func_801FC308(u8 actor_id);
void func_801FC3B4(s32 actor_id);
void func_801FC46C(u8 actor_id);
void func_801FC518(s32 actor_id);
void func_801FC5D0(s32 actor_id);
void func_801FC688(u8 actor_id);
void func_801FC734(u8 actor_id);
void func_801FC7E4(void);
void func_801FC9CC(void);
void func_801FCB54(void);
void func_801FCBDC(s32 delta);

/* D_80146258: the world input/scheduler lock word; retail reads and writes it as a halfword. */
extern u16 D_80146258;
/* D_80146871: g_SceneState.flags_01; retail folds its address into each access. */
extern u8  D_80146871;

/* Starts the scene script 0x1A with the camera shake state cleared. */
#define SCENA02_START_SCRIPT_1A() \
    Game_SetScriptActive();       \
    *g_ScriptVars         = 0x23; \
    g_ScriptVars[1]       = 0;    \
    g_ScriptVars[2]       = 0;    \
    g_ScriptVars[3]       = 0;    \
    g_SceneState.step_05  = 0;    \
    g_SceneState.state_04 = 0x1A

#endif
