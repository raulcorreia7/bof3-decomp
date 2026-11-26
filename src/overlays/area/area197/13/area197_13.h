#ifndef OVERLAY_WORLD04_AREA197_13_H
#define OVERLAY_WORLD04_AREA197_13_H

/* The world04/area197/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

/* The shared area.h gives this symbol no arguments; this image's function reads four. */
#define func_801F34A0 Area_SharedVoidProto
#include "overlays/area/worlds/world04.h"
#include "area/effects.h"
#undef func_801F34A0

/* The state handler banks the step dispatchers index. */
extern u8       D_801F431C[];
extern Callback D_801F4368[];

/* The scratchpad work row and the published record the step paths read. */

/* The character work record, viewed as bytes here. */

/* The area-flag bit store. */
/* D_801F4A2C */
extern PartyMemberMessages g_PartyMemberMessages[7];
extern Callback            D_801F4A80[];
/* The two-byte step table the falling path indexes. */
extern s8                  D_801F4A88[];
s32                        func_801F2FC4(void);
void                       func_801F30E4(void);
void                       func_801F3110(u16 start, u16 end, Pos3* from, Pos3* to);
void                       func_801F34A0(u16 start, u16 end, Pos3* from, Pos3* to);
s32                        func_801F3368(void);

void func_801F3474(void);

/* The image's step passes. */
void func_801F3768(s32 shade, s32 rise);

/* The seeded sparks' launch speed, lifetime and shade; the dropped rows fall
 * twice as fast. */
#define AREA_SPARK_SPEED     0x1000
#define AREA_DROP_SPEED      0x2000
#define AREA_SPARK_LIFE_BASE 0x18
#define AREA_SPARK_SHADE     0x48

extern TriangleOffset D_801F4328[];

void func_801F2E74(SparkParticle* spark);

/* The dropped sparks follow the sparks at AREA_WORK. */
#define AREA_SPARK_ROW_COUNT 128
#define AREA_DROP_COUNT      128
#define AREA_DROP_ROWS       (AREA_WORK + AREA_SPARK_ROW_COUNT * sizeof(SparkParticle))

/* One dropped spark: it falls and bounces like an SparkParticle. */
typedef struct AreaDropParticle {
    EffectSlotHeader header;
    VECTOR           velocity; /* 0x04 */
    VECTOR           pos;      /* 0x14 */
} AreaDropParticle;

ASSERT_OFFSET(AreaDropParticle, velocity, 0x04);
ASSERT_OFFSET(AreaDropParticle, pos, 0x14);
ASSERT_SIZE(AreaDropParticle, 0x24);

void func_801F32A4(Actor* actor);

#endif
