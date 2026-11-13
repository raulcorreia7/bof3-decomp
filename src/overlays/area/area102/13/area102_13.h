#ifndef OVERLAY_WORLD02_AREA102_13_H
#define OVERLAY_WORLD02_AREA102_13_H

/* The world02/area102/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world02.h"
#include "area/spad.h"

extern u8 D_801F3930[];
extern u8 D_801F3944[];
extern u8 D_801F3948[];

s32 func_801F3194();

void func_801F36B4(s32 arg0);

void func_801F2F44(s32 arg0);

/* Counts the task timer down while the game is idle; on zero it advances the step
 * and plays the area cue when the gate reports ready. */
#define AREA_TICK_TASK_TIMER()                                \
    if (g_GameStateIndex == GAME_REQUEST_IDLE) {              \
        (g_Task)->timer -= 1;                                 \
        if ((g_Task)->timer == 0) {                           \
            (g_Task)->header.step += 1;                       \
            if (func_801F3194() != 0) {                       \
                SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0x00)); \
            }                                                 \
        }                                                     \
    }

#endif
