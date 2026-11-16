#ifndef OVERLAY_WORLD04_AREA191_13_H
#define OVERLAY_WORLD04_AREA191_13_H

/* The world04/area191/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world04.h"
#include "area/spad.h"

/* The scenario state byte and its flag word. */

/* The game-overlay state bytes the request paths write. */
extern u8 D_80146874;
extern u8 D_80146875;
/* The scratchpad work row. */
/* The state dispatch table in the trailing payload. */
extern u8 D_801F3C54[];
/* The selection record and its two step tables. */
extern u8 D_801F41D0[];
extern u8 D_801F41D1[];

/* func_801F37AC: the table of character ids has five entries; each message table
 * holds a row of nine entries per character, one per area column 0 to 8. */
#define CAMP_MESSAGE_CHARACTER_COUNT 5
#define CAMP_MESSAGE_ROW_SIZE        9
#define CAMP_MESSAGE_AREA_LAST       (CAMP_MESSAGE_ROW_SIZE - 1)

/* The five character ids, the per-area row offsets and the two result rows
 * func_801F37AC picks between. */
extern u8 D_801F4248[];
extern u8 D_801F4250[];
extern u8 D_801F41E8[];
extern u8 D_801F4218[];

/* The area counter and the area flag store the selection pass reads. */
extern u8 D_80144EF8[];

extern u8  D_801F4260[];
/* The neighbour tables the cell lookup reads. */
extern u8  D_801F4290[];
/* The spawn-row table the selection pass walks, one row set per mode. */
extern u8* D_801F43D8[];

/* The published field work row and the state byte the reset writes. */

/* The draw pass this image's entry runs. */

void func_801F39AC(void);
void func_801F3AB0(void);

/* The camp message the selection row picks. */
u16 func_801F3924(s32 base, s32 character_id, s32 row, s32 mode);

#endif
