/* Drops every live spark by its fall speed, draws it and frees it below the work floor; returns whether any spark was
 * live. */
/* Area_StepSparks (scena01 and area082) */
MATCH u8 Area_StepSparks(void) {
    AreaSpark* spark;
    u8         i;
    bool       alive;

    alive = false;
    spark = MEM_PTR(AreaSpark, AREA_WORK);
    i     = 0;
    do {
        if (spark->active != 0) {
            spark->pos.vz -= spark->fall_speed << 8;
            Area_DrawSparkCell(spark);
            if (spark->pos.vz < SELF(Actor)->pos.z.fixed) {
                spark->active = 0;
            }
            alive = true;
        }
        spark++;
        i++;
    } while (i < AREA_SPARK_COUNT);
    return alive;
}
