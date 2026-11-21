#include "area197_13.h"

MATCH s32 func_801F2FC4(void) {
    SparkParticle* spark;
    s32            alive;
    u16            i;
    u8             life;

    alive = 0;
    spark = MEM_PTR(SparkParticle, AREA_WORK);
    i     = 0;
    do {
        if (spark->active != 0) {
            spark->pos.vx += spark->velocity.vx;
            spark->pos.vy += spark->velocity.vy;
            spark->pos.vz += spark->velocity.vz;
            spark->velocity.vz -= TO_COORD(4);
            if (spark->pos.vz < -TO_COORD(512)) {
                spark->pos.vz      = -TO_COORD(512);
                spark->velocity.vz = -spark->velocity.vz;
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
