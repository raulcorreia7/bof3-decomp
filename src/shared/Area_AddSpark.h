#ifndef SHARED_AREA_ADD_SPARK_H
#define SHARED_AREA_ADD_SPARK_H

#include "shared/AreaSpark.h"

/* Adds one falling spark to the first free row of the 128-row work table at the area work base: it marks the row
 * active with byte 0x01 = 0x40, gives it a fall speed of 0x1000-0x1FFF and places it around the work position at a
 * random angle, the radius under the work screen width. */
/* func_801F7AE4 (scena01), func_801F75D8 (scena15), func_801F393C (area082) */
MATCH void Area_AddSpark(void) {
    AreaSpark* spark;
    s16        radius;
    s16        angle;
    u8         i;

    spark = (AreaSpark*)AREA_WORK;
    i     = 0;
    for (; i < AREA_SPARK_COUNT; spark++, i++) {
        if (spark->active != 0) {
            continue;
        }
        spark->active = 1;
        spark->unk_01 = 0x40;
        if ((s16)g_Task->screen_x != 0) {
            radius = rand() % (s16)g_Task->screen_x;
        } else {
            radius = 0;
        }
        angle             = rand() & 0xFFF;
        spark->pos.x      = g_Task->pos.x.fixed + ((radius * rcos(angle)) >> 4);
        spark->pos.y      = g_Task->pos.y.fixed + ((radius * rsin(angle)) >> 4);
        spark->pos.z      = g_Task->pos.z.fixed + ((s32)(s16)g_Task->screen_y << 16);
        spark->fall_speed = (rand() & 0xFFF) + 0x1000;
        return;
    }
}

#endif
