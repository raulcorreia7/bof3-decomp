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

/* The grow step of a KaiserBreath orbit: unk_06 advances by two, phase_0C by
 * 0x20, and the orbit point follows the area scroll target at the angle
 * TABLE[unk_07] shifted SHIFT; the step advances at phase 0x200. A statement
 * macro: the member declares s16* angle_cell and u8 phase. */
#define MAGIC131_ORBIT_GROW(TABLE, SHIFT)                                                                        \
    D_801F24E0->unk_06 += 2;                                                                                     \
    D_801F24E0->phase_0C += 0x20;                                                                                \
    phase                   = TABLE[D_801F24E0->unk_07];                                                         \
    angle_cell              = &D_1F800006;                                                                       \
    *angle_cell             = phase << (SHIFT);                                                                  \
    D_801F24E0->pos.x.fixed = g_AreaScrollTargetX + ((rsin(phase << (SHIFT)) * (s16)D_801F24E0->phase_0C) >> 3); \
    D_801F24E0->pos.y.fixed = g_AreaScrollTargetY + ((rcos(*angle_cell) * (s16)D_801F24E0->phase_0C) >> 3);      \
    if ((s16)D_801F24E0->phase_0C == 0x200) {                                                                    \
        D_801F24E0->header.step++;                                                                               \
    }

void func_801F0DF4(void);

void func_801F1844(void);
void func_801F1AC4(void);
void func_801F1B14(void);

#endif
