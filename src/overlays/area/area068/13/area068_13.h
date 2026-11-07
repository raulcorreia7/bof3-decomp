#ifndef OVERLAY_WORLD01_AREA068_13_H
#define OVERLAY_WORLD01_AREA068_13_H

/* The world01/area068/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world01.h"
#include "work/area_spad.h"

/* Frames without a press before a well minigame phase ends, and steps of the bucket swish. */
#define WELL_IDLE_FRAMES_MAX 0x1C
#define WELL_SWISH_STEPS     8

extern u8  D_80145E97;
extern s32 D_80145EC4;
extern u8  D_80145EDA;
extern u16 D_80145EE8;
extern u8  D_80145FA8;
extern u8  D_80146865;
extern u8  D_801F3FE4[];
extern u8  D_801F3FF4[];
extern u8  D_801F4004[];
extern u8  D_801F4060[];
extern u8  D_801F406C[];
extern u16 D_801F4D64[];
extern u16 D_801F4D68[];
extern u8  D_801F4DCC[];

extern u8  D_801F4DE4[];
/* D_801F4DFC */
extern u8  g_WellLowerTimer;
/* D_801F4E00 */
extern u8  g_WellRaiseTimer;
/* D_801F4E04 */
extern u16 g_WellPressCount;
/* D_801F4E08 */
extern u16 g_WellLowerCount;
/* D_801F4E0C */
extern u8  g_WellIdleFrames;
/* D_801F4E10 */
extern u8  g_WellSwishStep;
/* D_801F4E14 */
extern u16 g_WellSwishButtons;

#endif
