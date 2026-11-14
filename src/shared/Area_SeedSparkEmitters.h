/* Starts every emitter of the table at its cell of `cells`, resting at the ground height there, with a random
 * shade byte and timer. Every change must verify every member. */
/* func_801D19A0 (sce15ef3), func_801F2FE0 (area143) */
#define AREA_SEED_SPARK_EMITTERS(cells)                                        \
    {                                                                          \
        u16           i;                                                       \
        SparkEmitter* emitter;                                                 \
        /* FAKE: the retail frame holds 0x10 bytes no statement explains. */   \
        FAKE_STACK_PADS(u8, 0x10);                                             \
                                                                               \
        emitter = g_SparkEmitters;                                             \
        for (i = 0; i < SPARK_EMITTER_COUNT; i++) {                            \
            emitter->active = 1;                                               \
            emitter->unk_1  = 0;                                               \
            emitter->unk_2  = rand() | 0xF0;                                   \
            emitter->timer  = RANDOM_MASK(0x1F);                               \
            emitter->x      = (cells)[i][0] << 16;                             \
            emitter->y      = (cells)[i][1] << 16;                             \
            emitter->z      = Area_SampleHeight(emitter->x, emitter->y) << 16; \
            emitter++;                                                         \
        }                                                                      \
    }
