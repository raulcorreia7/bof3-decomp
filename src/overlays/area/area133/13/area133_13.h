#ifndef OVERLAY_WORLD03_AREA133_13_H
#define OVERLAY_WORLD03_AREA133_13_H

/* The world03/area133/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world03.h"

/* The per-choice script entry bytes the confirm step copies into the work record. */
typedef struct MessageChoiceEntry {
    u8 unk_0; /* 0x0 */
    u8 unk_1; /* 0x1 */
} MessageChoiceEntry;

ASSERT_SIZE(MessageChoiceEntry, 2);

extern MessageChoiceEntry D_801F3DF0[];

/* The return counter the confirm step restarts. */
extern u8 D_8014865F;

#endif
