#ifndef OVERLAY_WORLD04_AREA188_13_H
#define OVERLAY_WORLD04_AREA188_13_H

/* The world04/area188/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world04.h"
#include "area/spad.h"

#include "shared/WorldSpin.h"

/* The per-scene y limit bytes the walk step reads, in 16.16 units. */
extern u8 D_801F6898[];

#define AREA_SPIN_RADIUS     16
#define AREA_SPIN_PITCH      (RANDOM_MASK(0x7FF) - 0x400)
#define AREA_SPIN_SCALE_MASK 0x2
#define AREA_SPIN_SCALE_BASE 3
#define AREA_SPIN_FADE       0x20

/* The party position in 16.16 fixed point: x, y and the ground height. */

/* The shared record table as its byte view. */

/* The scrolling halfword and the selection byte the store paths write. */

/* The scratchpad work row the state dispatchers read. */
/* The per-state handler tables the dispatchers index. */
extern Callback D_801F4DF4[];
extern Callback D_801F4DFC[];
extern Callback D_801F4E04[];
extern u8       D_801F689C;
/* The image's two sticky state bytes. */
extern u8       D_801F68A0;

/* The game-overlay state bytes the cancel path resets. */

#define AREA_SPAWN_SLOT_LIFE        0x10
#define AREA_SPAWN_SLOT_RADIUS      0x100
#define AREA_SPAWN_SLOT_CORE_SHADE  0x40
#define AREA_SPAWN_SLOT_RADIUS_STEP 0x10
void func_801F44B4(void);

/* The per-image spawn step Area_UpdateSpawn runs between the slot claim and the slot pass. */
#define AREA_SPAWN_TICK func_801F44B4

void func_801F38E0(void* arg0, s32 arg1, s32 arg2);
void func_801F3ADC(void* arg0, void* arg1, s32 arg2);
void func_801F40F4(s32 arg0);

/* Restarts the area task at mode 1 and clears the two sticky state bytes. */
#define AREA_RESET_TASK_TO_MODE1() \
    g_Task->timer       = 0;       \
    g_Task->header.mode = 1;       \
    D_801F68A0          = 0xF;     \
    D_801F689C          = 0;

#endif
