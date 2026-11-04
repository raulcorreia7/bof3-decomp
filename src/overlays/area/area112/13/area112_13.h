#ifndef OVERLAY_WORLD02_AREA112_13_H
#define OVERLAY_WORLD02_AREA112_13_H

/* The world02/area112/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/world02.h"
#include "work/area_spad.h"

/* The per-slot tag compared with the battle row byte. */

/* The per-slot message index. */

/* The battle record rows whose first byte is the slot tag. */
extern u8                  D_80145F09[][BATTLE_PARTY_STRIDE];
extern u8                  D_801F41F8[];
/* D_801F48FC */
extern PartyMemberMessages g_PartyMemberMessages[1];
extern u8                  D_801F493C[];

void GFX_FreePaletteFadeTarget(void* target);
void func_801F2EA8(void);
void func_801F3274(void);
void func_801F3EEC(void*);

#endif
