#ifndef OVERLAY_BMAGIC_MAGIC001_00_H
#define OVERLAY_BMAGIC_MAGIC001_00_H

/* The bmagic/magic001/00 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* battle/battle/15: the sprite cell of a battle record, and its copies into the cell rows. */
/* func_800AFB48 */
u32  Battle_CopyCellPalette(void* record);
/* func_800AFAB8 */
void Battle_ClearCellPaletteEntry(void* record);

#define MAGIC001_STEP_COUNT 11

typedef struct Magic001Steps {
    Callback steps[MAGIC001_STEP_COUNT];
} Magic001Steps;

#define MAGIC001_SECOND_STEP_COUNT 3

typedef struct Magic001SecondSteps {
    Callback steps[MAGIC001_SECOND_STEP_COUNT];
} Magic001SecondSteps;

extern Magic001Steps       D_801EEC10;
extern Magic001SecondSteps D_801EEC3C;
extern Callback            D_801EEC48[];

void func_801F0238(void);

static inline void BMagic_ClearWorkFlagsAndStep(void) {
    if (SELF(PartyMember)->param.unk_0B == 0) {
        func_800AFC54();
        BATTLE_ACTIVE_WORK->header.flags &= ~PARTY_MEMBER_FLAG_HANDLER_BUSY;
        SELF(PartyMember)->header.mode += 1;
    }
}

#endif
