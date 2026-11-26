#ifndef SLUS_UI_H
#define SLUS_UI_H

#include "types.h"
#include "engine/ui/text/text.h"
#include "engine/ui/message/message.h"
#include "engine/ui/menu/menu.h"

/* The text colour cells of stage palette row 0: the low nibble of a UI_TextDraw palette, the cell argument of the other drawers. */
enum {
    UI_TEXT_NORMAL    = 0,
    UI_TEXT_HIGHLIGHT = 2,
    UI_TEXT_DIM       = 7,
};

/* The width and height of one UI_IconDrawCell icon. */
#define UI_ICON_CELL_SIZE 16

#endif
