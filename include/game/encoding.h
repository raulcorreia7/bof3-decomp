#ifndef GAME_ENCODING_H
#define GAME_ENCODING_H

#include "types.h"

#define FORMATION_SLOT_EMPTY 0xFF
#define MASTER_SKILL_EMPTY   0xFF63
#define MASTER_ID_NONE       0xFF
#define ENEMY_COND_UNUSED    0x63
#define PTR_SLOT_EMPTY_LOW   0x00000
#define PTR_SLOT_EMPTY_HIGH  0xFFFFF

/* Element bits in the battle ability and weapon masks. */
typedef enum ElementFlags {
    ELEM_FIRE     = 1 << 0,
    ELEM_FROST    = 1 << 1,
    ELEM_ELECTRIC = 1 << 2,
    ELEM_EARTH    = 1 << 3,
    ELEM_WIND     = 1 << 4,
    ELEM_HOLY     = 1 << 5,
    ELEM_PSIONIC  = 1 << 6,
    ELEM_STATUS   = 1 << 7,
    ELEM_DEATH    = 1 << 8,
    ELEM_ALL      = (1 << 9) - 1,
} ElementFlags;

#endif
