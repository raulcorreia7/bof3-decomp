#ifndef OVERLAY_WORLD01_AREA068_13_H
#define OVERLAY_WORLD01_AREA068_13_H

/* The world01/area068/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world01.h"
#include "work/area_spad.h"

/* Frames without a press before a well minigame phase ends, and steps of the bucket swish. */
#define WELL_IDLE_FRAMES_MAX    0x1C
#define WELL_SWISH_STEPS        8
#define WELL_SWISH_DELAY_FRAMES 0xC

/* The lowering and raising phases each last one of 16 random times. */
#define WELL_TIME_LIMIT_COUNT   16
#define WELL_TIME_LIMIT_MASK    (WELL_TIME_LIMIT_COUNT - 1)

/* Task modes of the well minigame, the index of its handler table. Lowering and raising run the same
 * ready, count and repeat cycle: a press in "ready" goes to "count", which goes to "repeat"; a press in
 * "repeat" goes back to "ready". */
enum WellMode {
    WELL_MODE_BEGIN        = 0,
    WELL_MODE_LOWER_READY  = 1,
    WELL_MODE_LOWER_COUNT  = 3,
    WELL_MODE_LOWER_REPEAT = 4,
    WELL_MODE_LOWER_DONE   = 0xA,
    WELL_MODE_SWISH_INPUT  = 0xB,
    WELL_MODE_SWISH_DELAY  = 0xC,
    WELL_MODE_SWISH_STEP   = 0xD,
    WELL_MODE_RAISE_BEGIN  = 0xF,
    WELL_MODE_RAISE_READY  = 0x10,
    WELL_MODE_RAISE_COUNT  = 0x11,
    WELL_MODE_RAISE_REPEAT = 0x12,
    WELL_MODE_RAISE_CHECK  = 0x14,
    WELL_MODE_SUCCESS      = 0x15,
    WELL_MODE_FAIL         = 0x16,
};

/* Sound cues of the well minigame (bank 2). */
#define WELL_CUE_LOWER_END_READY  EMI_CUE_ID(2, 0)
#define WELL_CUE_LOWER_END_REPEAT EMI_CUE_ID(2, 1)
#define WELL_CUE_SWISH            EMI_CUE_ID(2, 2)

extern u8  D_80145E97;
extern s32 D_80145EC4;
extern u8  D_80145EDA;
extern u16 D_80145EE8;
extern u8  D_80145FA8;
extern u8  D_80146865;
extern u8  g_WellTimeLimits[WELL_TIME_LIMIT_COUNT];
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

/* One tick of the lowering timer: running out stores the press count and ends the phase; a press counts
 * and takes press_mode, otherwise idle_mode. */
#define WELL_TICK_LOWER(end_cue, press_mode, idle_mode) \
    if (--g_WellLowerTimer == 0) {                      \
        SND_PlayCue(end_cue);                           \
        g_WellLowerTimer    = 0;                        \
        g_WellLowerCount    = g_WellPressCount;         \
        g_Task->header.mode = WELL_MODE_LOWER_DONE;     \
    } else if (g_InputPressed == PADRup) {              \
        g_WellIdleFrames = 0;                           \
        g_WellPressCount += 1;                          \
        g_Task->header.mode = (press_mode);             \
    } else {                                            \
        g_Task->header.mode = (idle_mode);              \
    }

#endif
