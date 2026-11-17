/* Moves the sprite along twice its normal, widens it by 0x80 and counts its life down; at zero it restarts the count at 0x40 and advances the sprite's stage. */
/* AREA_SPRITE_EXPAND_STEP (area024 0x801F31B4, area108 0x801F30FC) */
#define AREA_SPRITE_EXPAND_STEP(SPRITE)                                     \
    AreaSprite* work;                                                       \
    u8          count;                                                      \
    work        = (AreaSprite*)SPRITE;                                      \
    count       = (work->count - 1u);                                       \
    work->count = count;                                                    \
    work->origin.x += (work->normal.vx * 2);                                \
    work->origin.y += (work->normal.vy * 2);                                \
    work->origin.z += (work->normal.vz * 2);                                \
    work->half_size = (work->half_size + 0x80u);                            \
    if (!(count & BYTE_MASK)) {                                             \
        ((AreaSprite*)SPRITE)->count = 0x40u;                               \
        ((AreaSprite*)SPRITE)->stage = (((AreaSprite*)SPRITE)->stage + 1u); \
    }
