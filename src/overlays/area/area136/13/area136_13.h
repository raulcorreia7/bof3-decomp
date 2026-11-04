#ifndef OVERLAY_WORLD03_AREA136_13_H
#define OVERLAY_WORLD03_AREA136_13_H

/* The world03/area136/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world03.h"
#include "menu/party.h"
#include "work/area_spad.h"

extern u8 D_801F4400[];

/* The field step bytes the palette path tests. */
/* The request value blob the selection handlers index. */
/* The request value tables indexed by the selection byte. */
extern u16 D_801F43F8[];
extern u16 D_801F43FC[];
/* The world slot counter and its active-step byte. */
/* The request selector and the bytes the cancel path sets. */
/* The area kind byte the request selector reads. */
extern u8  D_801FD288;

/* The map marker the room layout steps draw. */
void Area_SetCellCode(s16 column, s16 row, u8 code);

#endif
