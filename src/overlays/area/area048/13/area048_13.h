#ifndef OVERLAY_WORLD01_AREA048_13_H
#define OVERLAY_WORLD01_AREA048_13_H

/* The world01/area048/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/worlds/world01.h"
#include "area/spad.h"

extern u8  D_8014686B;
/* The disc's colour rows: one byte table per channel, indexed by the work record's byte 6. */
extern u8  D_801F4D5C[];
extern u8  D_801F4D5D[];
extern u8  D_801F4D5E[];
extern u8  D_801F4D68[];
extern u8  D_801F4D78[];
extern u8  D_801F4D79[];
/* The vertex triplets the curtain projects: x, y and z bytes, four per quad. */
extern s8  D_801F4D94[];
extern s8  D_801F4D95[];
extern s8  D_801F4D96[];
/* The quad table the curtain walks: eight entries per variant, a word each. */
extern u32 D_801F4DF4[];
extern s8  D_801F4E34[];

void func_801F3AE4(u32 angle, s32 pos, s32 variant);

extern u8 D_801F4D80[];

extern u8 D_801F4E54[];
extern u8 D_801F4E6C[];
extern u8 D_801F4E70[];
extern u8 D_801F4E74[];

s32  func_801F4C28(s32 x, s32 y);
void func_801F2EC0(void);
void func_801F41F0(s32 page, s32 column);

void func_801F302C(s32* first, s32* second, Actor* task);
void func_801F3274(s32 x, s32 y, s16 radius, u16 angle);
void func_801F3434(s16 x1, s16 y1, s16 radius1, u16 angle1, s16 x2, s16 y2, s16 radius2, u16 angle2);
void func_801F4258(s32 mode);

/* Start the scripted move off the ledge: face `facing`, then take the high-ledge
 * route the event byte and the actor type pick. Every change must verify
 * func_801F48DC and func_801F49C8. */
static inline void Area_StartScriptedMove(u8 facing) {
    g_Task->direction    = facing;
    g_ScriptState->steps = D_8014686B * 4;
    if (g_ScriptState->steps != 0) {
        if (Actor_GetOwner() != 2) {
            Area_MoveActorRoute(g_ScriptState, g_Task->direction);
            g_ScriptState->flags |= 0x80;
        } else {
            Area_SetFacingOffsetX(g_Task->direction);
            g_AreaCameraHeightStep = 0;
            g_ScriptState->flags |= 0x40;
        }
    }
    g_Task->vz               = 0;
    COORD_INT(g_Task->pos.z) = 1152;
}

#endif
