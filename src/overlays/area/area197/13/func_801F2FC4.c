#include "area197_13.h"

/* One of the 128 falling sparks at AREA_WORK: it falls, bounces off the ground and fades out. */
typedef struct AreaSparkRow {
    u8      active; /* 0x00 - 0 marks a free spark */
    u8      unk_01; /* 0x01 */
    u8      life;   /* 0x02 - frames left; clears the spark at 0 */
    u8      shade;  /* 0x03 - fades to black as the spark dies */
    u8      frame;  /* 0x04 - indexes the draw routine's corner table */
    u8      pad_05[3];
    s32     vx; /* 0x08 */
    s32     vy; /* 0x0C */
    s32     vz; /* 0x10 - the fall speed and the bounce */
    u8      pad_14[4];
    Point3l pos;       /* 0x18 */
    u8      pad_24[4]; /* 0x24 */
} AreaSparkRow;

ASSERT_SIZE(AreaSparkRow, 0x28);
ASSERT_OFFSET(AreaSparkRow, pos, 0x18);

MATCH s32 func_801F2FC4(void) {
    AreaSparkRow* spark;
    s32           alive;
    u16           i;
    u8            life;

    alive = 0;
    spark = (AreaSparkRow*)AREA_WORK;
    i     = 0;
    do {
        if (spark->active != 0) {
            spark->pos.x += spark->vx;
            spark->pos.y += spark->vy;
            spark->pos.z += spark->vz;
            spark->vz -= 0x40000;
            if (spark->pos.z < -0x02000000) {
                spark->pos.z = -0x02000000;
                spark->vz    = -spark->vz;
            }
            spark->shade -= 2;
            spark->frame = rand() & 7;
            life         = spark->life - 1;
            spark->life  = life;
            if (life == 0) {
                spark->active = 0;
            }
            func_801F2E74(spark);
            alive = 1;
        }
        spark++;
        i++;
    } while (i < 128);
    return alive;
}
