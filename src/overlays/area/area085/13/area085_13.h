#ifndef OVERLAY_WORLD02_AREA085_13_H
#define OVERLAY_WORLD02_AREA085_13_H

/* The world02/area085/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world02.h"
#include "work/area_spad.h"

#define g_CurrentActor ((void*)g_CurrentActor)

extern u8           D_801F3D2C[];
extern u8           D_801F4330[];
extern Callback     D_801F3D40[];
extern PartyBattler D_801469B8;

/* func_80196718 */
void GFX_FreePaletteFadeTarget(void* target);
void func_801F2FCC(void);
void func_801F3C3C(s32 arg0);

#endif
