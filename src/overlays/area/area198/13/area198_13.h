#ifndef OVERLAY_WORLD04_AREA198_13_H
#define OVERLAY_WORLD04_AREA198_13_H

/* The world04/area198/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/worlds/world04.h"

/* The scenario state byte the update gates on. */
/* The global state byte this entry tests. */
/* The object pointer whose palette field this entry updates. */

/* The current map row in the field-loader table. */
/* The scratchpad work pointer the palette pass reads. */
/* The state handler banks the step dispatchers index. */
extern u8 D_801F3DFC[];
/* The script steps the scene entry starts, one per count phase. */
extern u8 D_801F43AC[];
extern s8 D_801F43B0[];

/* A scene seed: the scene record the actor selects, the script it starts and
 * four bytes the entry does not read. */
typedef struct AreaSceneSeed {
    u16 scene_record; /* 0x00 */
    u8  script;       /* 0x02 */
    u8  pad_03;       /* 0x03 */
    u8  unk_04[4];    /* 0x04 */
} AreaSceneSeed;

ASSERT_SIZE(AreaSceneSeed, 8);

/* The sprite offset an actor type starts at: the x and y deltas the draw adds to the
 * screen position. */
typedef struct SpriteOffset {
    s16 x;         /* 0x00 */
    s16 y;         /* 0x02 */
    u8  unk_04[4]; /* 0x04 */
} SpriteOffset;

ASSERT_SIZE(SpriteOffset, 8);

/* One sprite offset per actor type, indexed by SELF(Actor)->unk_06. */
extern SpriteOffset D_801F43D4[];

/* This image's copy of the sprite coordinate rounding (link-only name: the slus copy shares it). */
s32 Area_RoundSpriteCoordinate_801F3DCC(s32 pair, s32 step);

/* The setup callback table. */
extern Callback D_801F4324[17];
/* The palette source bytes passed to the slot claim. */
extern u8       D_801F4368[];
/* The actor script ids the phase starts, one per phase. */
extern u8       D_801F43AC[];

/* The spark trail the spawn starts. */
extern u8 D_801F43C0[];

/* The scene seeds, one per scene index. */
extern AreaSceneSeed D_801F43D8[];
extern Callback      D_801F43EC[];

/* The state update's fallback handler. */
/* The image's setup pass. */
void func_801F2D28(s32 scale);

#endif
