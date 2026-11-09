/* Moves the sprite along its normal while its two counters run down and frees the sprite when the second reaches zero. */
/* AREA_SPRITE_DRIFT_STEP (area024 0x801F3250, area108 0x801F3198) */
#define AREA_SPRITE_DRIFT_STEP(SPRITE)                                        \
    AreaSprite* work;                                                         \
    u8          count;                                                        \
    u8          tick;                                                         \
    work = (AreaSprite*)SPRITE;                                               \
    tick = (work->flags_03 - 1u);                                             \
    work->origin.x += work->normal.vx;                                        \
    work->origin.y += work->normal.vy;                                        \
    work->flags_03 = tick;                                                    \
    work->origin.z += work->normal.vz;                                        \
    count                           = (((AreaSprite*)SPRITE)->flags_02 - 1u); \
    ((AreaSprite*)SPRITE)->flags_02 = count;                                  \
    if (!(count & BYTE_MASK)) {                                               \
        ((AreaSprite*)SPRITE)->flags = 0u;                                    \
    }
