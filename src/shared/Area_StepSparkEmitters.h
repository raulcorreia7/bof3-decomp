/* Counts down every active emitter and, as a timer runs out, spawns two sprite sparks near it; returns whether any
 * emitter is active. SPARK_EMITTER_COUNT is the image's emitter count; every change must verify every member. */
/* func_801D1A60 (sce15ef3), func_801F30A0 (area143) */
MATCH s32 Area_StepSparkEmitters(void) {
    u16           i;
    u16           n;
    s32           alive;
    SparkEmitter* emitter;
    SpriteSpark*  spark;

    alive   = 0;
    emitter = g_SparkEmitters;
    for (i = 0; i < SPARK_EMITTER_COUNT; emitter++, i++) {
        if (emitter->active != 0) {
            alive = 1;
            if (emitter->timer-- == 0) {
                for (n = 0; n < 2; n++) {
                    spark = Area_FindFreeSpriteRow();
                    if (spark != NULL) {
                        spark->active = 1;
                        spark->life   = (rand() & 0x1F) + 0x20;
                        spark->pos.vx = emitter->pos.vx + ((rand() & 0xFF) << 8) - 0x10000;
                        spark->pos.vy = emitter->pos.vy + ((rand() & 0xFF) << 8) - 0x10000;
                        spark->pos.vz = emitter->pos.vz;
                        spark->z_step = 0;
                        spark->blink  = rand() & 1;
                    }
                }
                emitter->timer = rand() & 7;
            }
        }
    }
    return alive;
}
