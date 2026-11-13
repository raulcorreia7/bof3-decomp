#ifndef OVERLAY_WORLD01_AREA048_13_H
#define OVERLAY_WORLD01_AREA048_13_H

/* The world01/area048/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world01.h"
#include "area/spad.h"

extern u8 D_8014686B;
extern u8 D_80146874;
extern u8 D_80146875;
extern u8 D_80147CC8;
extern u8 D_801F4D68[];
/* One-byte views of the colour triplets in the payload table: the retail code
 * names the second and third channel by its own address. */
extern u8 D_801F4D5C[];
extern u8 D_801F4D5D[];
extern u8 D_801F4D5E[];
s32       func_801F3AE4(s32, s32, s32);

extern u8 D_801F4D80[];

extern u8 D_801F4E54[];
extern u8 D_801F4E6C[];
extern u8 D_801F4E70[];
extern u8 D_801F4E74[];

s32  func_801F4C28(s32 x, s32 y);
void func_801F2EC0(void);
void func_801F41F0(s32 page, s32 column);

void func_801F302C(void* arg0, void* arg1, void* arg2);
void func_801F4258(s32 arg0);

/* Start the scripted move off the ledge: face `facing`, then take the high-ledge
 * route the event byte and the actor type pick. Every change must verify
 * func_801F48DC and func_801F49C8. */
static inline void Area_StartScriptedMove(u8 facing) {
    g_Task->direction_08  = facing;
    g_ScriptState->unk_07 = D_8014686B * 4;
    if (g_ScriptState->unk_07 != 0) {
        if (Actor_GetType() != 2) {
            func_801ABBA8(g_ScriptState, g_Task->direction_08);
            g_ScriptState->flag_00 |= 0x80;
        } else {
            func_801C5DFC(g_Task->direction_08);
            g_AreaCameraHeightStep = 0;
            g_ScriptState->flag_00 |= 0x40;
        }
    }
    g_Task->vz               = 0;
    COORD_INT(g_Task->pos.z) = 1152;
}

#endif
