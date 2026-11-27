#ifndef OVERLAY_WORLD04_AREA172_13_H
#define OVERLAY_WORLD04_AREA172_13_H

/* The world04/area172/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/worlds/world04.h"
#include "area/effects.h"

#define AREA_SPIN_RADIUS     24
#define AREA_SPIN_PITCH      (RANDOM_MASK(0x7FF) - 0x400)
#define AREA_SPIN_SCALE_MASK 0x3
#define AREA_SPIN_SCALE_BASE 4
#define AREA_SPIN_FADE       0

/* The scratchpad cell holding this mode's work pointer. */

/* The payload's first words: the per-state handler pointers. */
extern u8 D_801F507C[];
extern s8 D_801F6780[];

/* The overlay's flag word. */

extern void func_801F2DF4(s32 blend_mode);
void        func_801F4060(s16 level);
void        func_801F4138(s16 x, s16 y, s16 radius, s16 color0, s16 color1);
void        func_801F47F0(void);
void        func_801F4E8C(s16 x, s16 y);

/* The palette counters the fade advances, one 12-byte row per palette index. */
extern u8 D_80145BD6[];

#define AREA_SPAWN_SLOT_LIFE        0x20
#define AREA_SPAWN_SLOT_RADIUS      0x180
#define AREA_SPAWN_SLOT_CORE_SHADE  SELF(Actor)->tint.bytes.rgb.r
#define AREA_SPAWN_SLOT_RADIUS_STEP 0xC

void func_801F36C0(void* position, s32 radius, s32 colors);
void func_801F3BFC(const SpinEffect* spin);
void func_801F3FAC(void);

void func_801F4F70(s32 x, s32 y);

#endif
