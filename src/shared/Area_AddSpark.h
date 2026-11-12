#include "shared/AreaSpark.h"

/* Adds a falling spark at a random angle around the work position, at most the work screen width away. */
/* func_801F7AE4 (scena01), func_801F75D8 (scena15), func_801F393C (area082) */
MATCH void Area_AddSpark(void) {
    AreaSpark* spark;
    s16        radius;
    u16        angle;
    u8         i;

    spark = MEM_PTR(AreaSpark, AREA_WORK);
    for (i = 0; i < AREA_SPARK_COUNT; spark++, i++) {
        if (spark->active != 0) {
            continue;
        }
        spark->active = 1;
        spark->unk_01 = 0x40;
        if ((s16)g_Task->screen_x != 0) {
            radius = RANDOM_MOD((s16)g_Task->screen_x);
        } else {
            radius = 0;
        }
        angle             = RANDOM_MASK(0xFFF);
        spark->pos.x      = g_Task->pos.x.fixed + ((radius * rcos(angle)) >> 4);
        spark->pos.y      = g_Task->pos.y.fixed + ((radius * rsin(angle)) >> 4);
        spark->pos.z      = g_Task->pos.z.fixed + ((s16)g_Task->screen_y << 16);
        spark->fall_speed = RANDOM_MASK(0xFFF) + 0x1000;
        return;
    }
}
