#ifndef OVERLAY_BMAGIC_MAGIC131_03_H
#define OVERLAY_BMAGIC_MAGIC131_03_H

/* The bmagic/magic131/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

extern Callback D_801F1BF4[];

extern u8       D_801F1C38[];
extern Callback D_801F1C08[];
extern u8       D_801F1C54[];
extern u8       D_801F1C74[];
void            func_801F030C(void);

extern Callback D_801F1C24[];
void            func_801F06B4(void);
void            func_801F0D44(void);

/* Pointers to character-indexed archive ids, one row of two per g_Battle.dragon_form; the battle's
 * scroll direction picks the row's first or second pointer and g_EmiLoadedCharacterIndex picks the id. */
extern u16* D_800B499C[][2];

extern Callback          D_801F1C48[];
extern Callback          D_801F1C94[];
extern BMagicEffectWork* D_801F24E0;
extern BMagicEffectWork  D_801F1CA0[48];

void func_801F0DF4(void);

void func_801F1844(void);
void func_801F1AC4(void);
void func_801F1B14(void);

#endif
