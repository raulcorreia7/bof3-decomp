#ifndef OVERLAY_WORLD02_AREA112_13_H
#define OVERLAY_WORLD02_AREA112_13_H

/* The world02/area112/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world02.h"
#include "area/spad.h"

/* The scenario flag byte the answer path tests. */
extern u8 D_80144EF0[];

/* The battle record rows whose first byte is the slot tag. */
extern u8                  D_801F41F8[];
/* D_801F48FC */
extern PartyMemberMessages g_PartyMemberMessages[1];
extern u8                  D_801F493C[];

void func_801F2EA8(void);
void func_801F3274(void);
void Area_DrawLightPillar(s32* pos);

#endif
