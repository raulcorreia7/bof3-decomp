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

/* Places the orbit point of a KaiserBreath ring: the angle TABLE[unk_07]
 * shifted SHIFT goes to the scratchpad cell, and the point follows the area
 * scroll target at the radius phase_0C. A statement macro: the member declares
 * s16* angle_cell and u8 phase. */
#define MAGIC131_ORBIT_PLACE(TABLE, SHIFT)                                                                       \
    phase                   = TABLE[D_801F24E0->unk_07];                                                         \
    angle_cell              = &D_1F800006;                                                                       \
    *angle_cell             = phase << (SHIFT);                                                                  \
    D_801F24E0->pos.x.fixed = g_AreaScrollTargetX + ((rsin(phase << (SHIFT)) * (s16)D_801F24E0->phase_0C) >> 3); \
    D_801F24E0->pos.y.fixed = g_AreaScrollTargetY + ((rcos(*angle_cell) * (s16)D_801F24E0->phase_0C) >> 3)

/* The grow step of a KaiserBreath orbit: unk_06 advances by two, phase_0C by
 * 0x20, the point follows at the placed angle, and the step advances at phase
 * 0x200. A statement macro: the member declares s16* angle_cell and u8 phase. */
#define MAGIC131_ORBIT_GROW(TABLE, SHIFT)     \
    D_801F24E0->unk_06 += 2;                  \
    D_801F24E0->phase_0C += 0x20;             \
    MAGIC131_ORBIT_PLACE(TABLE, SHIFT);       \
    if ((s16)D_801F24E0->phase_0C == 0x200) { \
        D_801F24E0->header.step++;            \
    }

/* The closing step of a KaiserBreath orbit: phase_0C advances by 0x10, the
 * point follows at the placed angle, and timer_05 counts down by two; at zero
 * the effect clears. A statement macro: the member declares s16* angle_cell,
 * u8 phase and u8 timer. */
#define MAGIC131_ORBIT_CLOSE(TABLE, SHIFT)           \
    D_801F24E0->phase_0C += 0x10;                    \
    MAGIC131_ORBIT_PLACE(TABLE, SHIFT);              \
    timer                = D_801F24E0->timer_05 - 2; \
    D_801F24E0->timer_05 = timer;                    \
    if (timer == 0) {                                \
        g_BattleEffectBattler->param.unk_0B -= 1;    \
        func_801F1AC4();                             \
    }

void func_801F0DF4(void);

void func_801F1844(void);
void func_801F1AC4(void);
void func_801F1B14(void);

#endif
