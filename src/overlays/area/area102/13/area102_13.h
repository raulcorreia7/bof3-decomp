#ifndef OVERLAY_WORLD02_AREA102_13_H
#define OVERLAY_WORLD02_AREA102_13_H

/* The world02/area102/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/worlds/world02.h"
#include "sys/scratchpad.h"

extern u8 D_801F3930[];
extern u8 D_801F3944[];
extern u8 D_801F3948[];
/* The countdowns the cell byte pair selects. */
extern u8 D_801F395C[];

s32 func_801F3194();

/* The texture page and colour bits of the cell quads' primitive code. */
#define AREA_CELL_QUAD_CODE ((0xBAu << 24) | 0x9124u)

void func_801F2F44(s32 steps);

void func_801F36B4(s32 steps);

/* Counts the task timer down while the game is idle; on zero it advances the step
 * and plays the area SE when the gate reports ready. */
#define AREA_TICK_TASK_TIMER()                              \
    if (g_GameStateIndex == GAME_REQUEST_IDLE) {            \
        SELF(Actor)->timer -= 1;                            \
        if (SELF(Actor)->timer == 0) {                      \
            SELF(Actor)->header.step += 1;                  \
            if (func_801F3194() != 0) {                     \
                SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x00)); \
            }                                               \
        }                                                   \
    }

#endif
