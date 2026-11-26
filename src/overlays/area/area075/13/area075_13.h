#ifndef OVERLAY_WORLD01_AREA075_13_H
#define OVERLAY_WORLD01_AREA075_13_H

/* The world01/area075/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/worlds/world01.h"

extern s32      D_80144ED8;
extern s8       D_80146B81;
extern s8       D_80146BF7;
extern s8       D_80146BF8;
extern s16      D_80146BFE;
extern u8       D_801F4FD4[];
extern u8       D_801F57B0[][0x11];
extern u8       D_801F5808[];
extern u8       D_801F5810[];
extern u8       D_801F5818[];
extern Callback D_801F5820[];

/* A pose sequence: step and duration pairs, and how many the sequence holds. */
typedef struct Area075PoseSequence {
    u8* steps; /* 0x0 */
    u8  count; /* 0x4 */
    u8  pad_05[3];
} Area075PoseSequence;

extern u8                  D_801F2C94[];
void                       func_801F4034(void);
void                       func_801F4080(void);
extern void                func_801F4874(void);
extern Area075PoseSequence D_801F5858[3];
extern u8                  D_801F5870[16];
extern u8                  D_801F5880[16];
extern u8                  D_801F5890[4][4];
extern u8                  D_801F58A0[][15];
extern u8                  D_801F58C0;
extern u8                  D_801F58C3;
extern u16                 D_801F58C4;
extern u8                  D_801F58C6;
extern u8                  D_801F58C7;
extern u8                  D_801F58C8;
extern u8                  D_801F58C9;
extern u16                 D_801F58CA;
extern u16                 D_801F58CC;
extern u16                 g_Area075OpponentGauge[1]; /* D_801F58CC, the gauge func_801F45A8 lowers on its timing table */
extern u8                  D_801F58CE[2];
extern u8                  D_801F58D0;
extern u8                  D_801F58D1;

extern u8 D_801F58D2;

extern u8 D_801F58D3;

/* func_801F4A50 */
void UI_WindowDrawPanel(s16 x, s16 y, s16 width, s16 height, u8 mode);

void func_801F2E64(s32 phase, s32 semi_trans);

#endif
