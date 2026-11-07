#ifndef MENU_DRAW_H
#define MENU_DRAW_H

#include "types.h"

/* Shared calls made by the start and shop character-sheet renderers. */
/* emi/etc/game/00: draws one 8x8 sprite, using the low bytes of texture_index and shade_mode. */
/* emi/etc/game/00: counts commands over the first twelve encoded bytes. */

/* One portrait cell of a character atlas: the u and v of its corner and the x and y of its palette
 * (Menu_DrawPortrait reads them by portrait index). */
typedef struct MenuPortraitSprite {
    u8 u;
    u8 v;
    u8 clut_x;
    u8 clut_y;
} MenuPortraitSprite;

ASSERT_SIZE(MenuPortraitSprite, 4);
ASSERT_OFFSET(MenuPortraitSprite, clut_x, 0x02);
ASSERT_OFFSET(MenuPortraitSprite, clut_y, 0x03);

#endif
