#ifndef OVERLAY_WORLD02_AREA085_13_H
#define OVERLAY_WORLD02_AREA085_13_H

/* The world02/area085/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/worlds/world02.h"

#define g_CurrentActor ((void*)g_CurrentActor)

extern PartyMember D_801469B8;
extern u8          D_801F3D2C[];
extern Callback    D_801F3D40[];
extern u8          D_801F3D4C[0x24];

/* One row of D_801F3D70: an actor script selector, its script id and start position. */
typedef struct Area085ScriptPick {
    u8 selector;
    u8 script_index;
    u8 position;
} Area085ScriptPick;

extern Area085ScriptPick D_801F3D70[5];
extern u8                D_801F4330[];

void func_801F2FCC(void);
void func_801F3C3C(s32 delta);

#endif
