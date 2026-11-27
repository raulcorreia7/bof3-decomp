#ifndef OVERLAY_WORLD04_AREA188_13_H
#define OVERLAY_WORLD04_AREA188_13_H

/* The world04/area188/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/worlds/world04.h"

#include "area/effects.h"
#include "overlays/area/shared/Area_DrawDimQuad.h"

/* The shop panel byte the confirmed answer clears. */
extern u8 D_8014865F;
/* The two bytes of the answer pair table, one entry per choice. */
extern u8 D_801F688C[];
extern u8 D_801F688D[];
/* The per-scene y limit bytes the walk step reads, in 16.16 units. */
extern u8 D_801F6898[];

#define AREA_SPIN_RADIUS     16
#define AREA_SPIN_PITCH      (RANDOM_MASK(0x7FF) - 0x400)
#define AREA_SPIN_SCALE_MASK 0x2
#define AREA_SPIN_SCALE_BASE 3
#define AREA_SPIN_FADE       0x20

/* The party position in 16.16 fixed point: x, y and the ground height. */

/* The image payload as its byte view; its leading bytes are the fade ramp the
 * transition step walks. */
extern u8 D_801F4DF0[];

/* The scrolling halfword and the selection byte the store paths write. */

/* The scratchpad work row the state dispatchers read. */
/* The per-state handler tables the dispatchers index. */
extern Callback D_801F4DF4[];
extern Callback D_801F4DFC[];
extern Callback D_801F4E04[];
/* The fade ramp index and the fade colour it selects. */
extern u8       D_801F689C;
extern u8       D_801F68A0;

#define AREA_SPAWN_SLOT_LIFE        0x10
#define AREA_SPAWN_SLOT_RADIUS      0x100
#define AREA_SPAWN_SLOT_CORE_SHADE  0x40
#define AREA_SPAWN_SLOT_RADIUS_STEP 0x10
void func_801F44B4(void);

/* The per-image spawn step Area_UpdateSpawn runs between the slot claim and the slot pass. */
#define AREA_SPAWN_TICK func_801F44B4

/* func_801F38E0 */
void GFX_DrawColorFan(void* position, s32 radius, s32 colors);
/* func_801F3ADC */
void Area_DrawYellowLine(s32* from, s32* to, u8 intensity);
void func_801F40F4(s32 arg0);

/* Draws the screen fade: advances the timer, takes the next fade colour when the
 * timer reaches its threshold and resets it, then covers the screen with one
 * semi-transparent quad.
 * func_801F2F6C and func_801F3148 draw it; every change must verify both. */
static inline void Area_DrawFadeQuad(void) {
    POLY_G4* prim;

    if (SELF(Actor)->timer++ >= 16) {
        D_801F68A0         = D_801F4DF0[D_801F689C];
        SELF(Actor)->timer = 0;
        if (D_801F689C++ != 0) {
            D_801F689C = 0;
        }
    }

    AREA_DRAW_DIM_QUAD(2, D_801F68A0);
}

/* Restarts the area task at mode 1 and resets the fade colour and its ramp index. */
#define AREA_RESET_TASK_TO_MODE1()  \
    SELF(Actor)->timer       = 0;   \
    SELF(Actor)->header.mode = 1;   \
    D_801F68A0               = 0xF; \
    D_801F689C               = 0;

#endif
