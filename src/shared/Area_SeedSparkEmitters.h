/* Starts every emitter of the table at its cell of `cells`, resting at the ground height there, with a random
 * shade byte and timer. Every change must verify every member. */
/* func_801D19A0 (sce15ef3), func_801F2FE0 (area143) */
#define AREA_SEED_SPARK_EMITTERS(cells)                                                    \
    {                                                                                      \
        u16           i;                                                                   \
        SparkEmitter* emitter;                                                             \
                                                                                           \
        emitter = g_SparkEmitters;                                                         \
        for (i = 0; i < SPARK_EMITTER_COUNT; i++) {                                        \
            emitter->active = 1;                                                           \
            emitter->unk_01 = 0;                                                           \
            emitter->unk_02 = rand() | 0xF0;                                               \
            emitter->timer  = RANDOM_MASK(0x1F);                                           \
            emitter->pos.vx = (cells)[i][0] << 16;                                         \
            emitter->pos.vy = (cells)[i][1] << 16;                                         \
            {                                                                              \
                Coord sample_x = {emitter->pos.vx};                                        \
                Coord sample_y = {emitter->pos.vy};                                        \
                                                                                           \
                emitter->pos.vz = Area_HeightSample(sample_x.fixed, sample_y.fixed) << 16; \
            }                                                                              \
            emitter++;                                                                     \
        }                                                                                  \
    }
