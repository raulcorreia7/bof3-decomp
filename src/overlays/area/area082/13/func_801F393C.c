#include "area082_13.h"

MATCH void func_801F393C(void) {
    AreaSpark* spark;
    s16        radius;
    u16        angle;
    u8         i;

    spark = (AreaSpark*)AREA_WORK;
    i     = 0;
    while (i < AREA_SPARK_COUNT) {
        if (spark->active == 0) {
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
        spark++;
        i++;
    }
}
