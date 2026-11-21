#include "area143_13.h"

MATCH s32 func_801F2EF0(void) {
    SpriteSpark* spark;
    MATRIX       camera;
    s32          active;
    s32          step;
    u16          i;
    u8           life;

    active     = 0;
    D_801F5310 = 0;
    Camera_SetMatrix(&camera);
    spark = MEM_PTR(SpriteSpark, AREA_WORK);
    i     = 0;
    do {
        if (spark->active != 0) {
            D_801F5310++;
            step          = spark->z_step + 0x20000;
            spark->z_step = step;
            spark->pos.vz += step;
            spark->blink ^= 1;
            func_801F2DB8(spark);
            life        = spark->life - 1;
            spark->life = life;
            active      = 1;
            if (life == 0) {
                spark->active = 0;
                spark->unk_01 = 0;
            }
        }
        spark++;
        i++;
    } while (i < SPRITE_SPARK_COUNT);
    return active;
}
