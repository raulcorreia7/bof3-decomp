#ifndef OVERLAY_WORLD03_AREA144_13_H
#define OVERLAY_WORLD03_AREA144_13_H

/* The world03/area144/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/worlds/world03.h"

/* The scratchpad work pointer; the dispatch entry bytes select a handler. */

/* The flag that gates the camera step. */
extern u8       D_80143FC3;
/* The state handler tables the dispatchers index. */
extern Callback D_801F3E68[];
/* The palette-dirty byte the setup step clears. */
extern u8       D_801F4960;

void func_801F2E18(void);
/* The palette row clear the setup step enters. */
void func_801F30CC(void);

/* Projects the 14 points, then steps and draws the six records at AREA_WORK; nonzero while any is active. */
u8   func_801F34FC(void);
/* Draws one rising record of AREA_WORK as three semi-transparent triangles. */
void func_801F3124(u8* data);

/* One of the six rising light records at AREA_WORK: five projected points, a colour and its step state. */
typedef struct LightRow {
    /* 0x00 */ DVECTOR* points[5];
    /* 0x14 */ u8       r;
    /* 0x15 */ u8       g;
    /* 0x16 */ u8       b;
    /* 0x17 */ u8       step;
    /* 0x18 */ u8       active;
    /* 0x19 */ u8       timer;
    /* 0x1A */ u8       script; /* the script the record selects ten frames into its first fade */
    /* 0x1B */ u8       unk_1B;
} LightRow;

ASSERT_SIZE(LightRow, 0x1C);

#define g_LightRows   ((LightRow*)AREA_WORK)
/* The 14 projected points of D_801F3D80, after the six rows. */
#define g_LightPoints ((DVECTOR*)(AREA_WORK + 0xA8))

/* A 16-byte point row of the table at D_801F3D80. */
typedef VECTOR AreaPoint;

extern AreaPoint D_801F3D80[];
/* The sound effect ids the rising records play in turn, after the 14 points of D_801F3D80. */
extern u16       D_801F3E60[];

#endif
