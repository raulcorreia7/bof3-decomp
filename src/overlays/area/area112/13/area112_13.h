#ifndef OVERLAY_WORLD02_AREA112_13_H
#define OVERLAY_WORLD02_AREA112_13_H

/* The world02/area112/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world02.h"
#include "area/spad.h"

/* The scenario flag byte the answer path tests. */
extern u8 D_80144EF0[];

/* A trigger cell of the area's flag switch. */
typedef struct AreaFlagCell {
    /* 0x0 */ u8 x;
    /* 0x1 */ u8 y;
    /* 0x2 */ u8 direction_flags; /* bits 0-3 clear a direction's scene flag, bits 4-7 set it */
    /* 0x3 */ u8 flag_id;
} AreaFlagCell;

ASSERT_SIZE(AreaFlagCell, 4);

/* The four trigger cells of the area's flag switch. */
extern AreaFlagCell D_801F4908[4];
/* The scene flag of each direction the trigger cells select. */
extern u8           D_801F4928[4];

/* The battle record rows whose first byte is the slot tag. */
extern u8                  D_801F41F8[];
/* D_801F48FC */
extern PartyMemberMessages g_PartyMemberMessages[1];
extern u8                  D_801F493C[];

void func_801F2EA8(void);
void func_801F3274(void);
void Area_DrawLightPillar(s32* pos);

/* The scene flag id of each cell the step handles, by cell column. */
extern u8  D_801F420C[];
/* The ground height of each cell, by cell column. */
extern u16 D_801F4210[];

#endif
