/* Moves the sprite along twice its normal, widens it by 0x80 and counts its life down. */
/* AREA_SPRITE_EXPAND_STEP (area024 0x801F31B4, area108 0x801F30FC). */
#define AREA_SPRITE_EXPAND_STEP(SPRITE)                                           \
    AreaSprite* work;                                                             \
    u8          count;                                                            \
    work           = (AreaSprite*)SPRITE;                                         \
    count          = (work->flags_02 - 1u);                                       \
    work->flags_02 = count;                                                       \
    work->origin.x += (work->normal.vx * 2);                                      \
    work->origin.y += (work->normal.vy * 2);                                      \
    work->origin.z += (work->normal.vz * 2);                                      \
    work->half_size = (work->half_size + 0x80u);                                  \
    if (!(count & BYTE_MASK)) {                                                   \
        ((AreaSprite*)SPRITE)->flags_02 = 0x40u;                                  \
        ((AreaSprite*)SPRITE)->flags_01 = (((AreaSprite*)SPRITE)->flags_01 + 1u); \
    }
