#ifndef BMAGIC_FAMILY_H
#define BMAGIC_FAMILY_H

/* Declarations shared by two or more bmagic images; an image header that
 * reads one includes this file. */

#include "game.h"
#include "gfx/prim.h"
#include "overlays/battle/battle.h"

#define BMAGIC_HANDLER_TABLE4_SIZE 0x10

/* The statements of Effect_SetActorMatrix after its rotation is set; each
 * member declares pos, rot, matrix and flags. SPAN_WORK is the work record
 * whose vertical span halves into the depth. */
#define BMAGIC_PROJECT_ACTOR_MATRIX(SPAN_WORK)           \
    pos.vx = (g_SpadWork->coord_x_34.raw >> 9) - 0x4000; \
    pos.vy = (g_SpadWork->coord_y_38.raw >> 9) - 0x4000; \
    pos.vz = -(SPAN_WORK)->word_3C.half.span_3E / 2;     \
    RotTrans(&pos, &matrix.t, &flags);                   \
    RotMatrix(&rot, &matrix);                            \
    MulMatrix2((MATRIX*)g_CameraMatrix, &matrix);        \
    SetRotMatrix(&matrix);                               \
    SetTransMatrix(&matrix)

/* The statements of Effect_SetActorMatrix with a zero rotation. */
#define BMAGIC_SET_ACTOR_MATRIX_SPAN(SPAN_WORK) \
    PushMatrix();                               \
    rot.vx = 0;                                 \
    rot.vy = 0;                                 \
    rot.vz = 0;                                 \
    BMAGIC_PROJECT_ACTOR_MATRIX(SPAN_WORK)

#define BMAGIC_SET_ACTOR_MATRIX() BMAGIC_SET_ACTOR_MATRIX_SPAN(g_SpadWork)

/* Decrement the active effect ticker. */
#define BMAGIC_TICK_EFFECT_WORK() (BATTLE_ACTIVE_WORK->unk_0B--)

/* Run the module step handler the task step selects. A bare statement macro:
 * the member declares `handlers`. Kept: as an inline taking the table by value
 * the frame is 56 bytes where retail has 48 (func_801EEC1C in magic086). */
#define BMAGIC_DISPATCH_STEP_HANDLERS(table, field) \
    handlers = (table);                             \
    handlers.handlers[g_SpadWork->field]()
#define g_SpadWork ((PartyBattler*)g_SpadWork)

/* Go to the effect's next step. */
static inline void Bmagic_NextStep(void) {
    PartyBattler* work = g_SpadWork;

    work->unk_02 = (u8)(work->unk_02 + 1);
}

/* Clear the local effect work. */
static inline void Bmagic_ResetLocalWork(void) {
    g_SpadWork->flags_00 = 0;
    g_SpadWork->step_01  = 0;
    g_SpadWork->unk_02   = 0;
    g_SpadWork->unk_03   = 0;
    g_SpadWork->unk_04   = 0;
}

/* Run the task handler the spad task byte selects. */
static inline void Bmagic_DispatchTaskPair(Callback first, Callback second) {
    Callback handlers[2] = {first, second};

    handlers[((u8*)g_SpadWork)[1]]();
}

typedef struct MagicTaskFuncs {
    Callback handlers[4];
} MagicTaskFuncs;

ASSERT_SIZE(MagicTaskFuncs, BMAGIC_HANDLER_TABLE4_SIZE);
ASSERT_OFFSET(MagicTaskFuncs, handlers, 0x00);

typedef struct BmagicEffectFuncs {
    Callback handlers[6];
} BmagicEffectFuncs;

ASSERT_SIZE(BmagicEffectFuncs, 0x18);
ASSERT_OFFSET(BmagicEffectFuncs, handlers, 0x00);

extern PaletteFade D_80145BD4[];
extern MagicModule D_801EEC00;
/* D_801EF3E8 (magic161), D_801EF414 (magic145), D_801EF420 (magic159), D_801EF510 (magic065), D_801EF658 (magic054), D_801EF6CC (magic154), D_801EF718 (magic166), D_801EF72C (magic138), D_801EF770 (magic218), D_801EF784 (magic158), D_801EF7A0 (magic075), D_801EF818 (magic048), D_801EF89C (magic009), D_801EF8A0 (magic213), D_801EF8BC (magic115), D_801EF8D8 (magic045), D_801EF990 (magic017), D_801EF9A4 (magic038), D_801EF9B4 (magic146), D_801EFA00 (magic219), D_801EFA44 (magic130), D_801EFA84 (magic081), D_801EFA9C (magic050), D_801EFA9C (magic111), D_801EFB70 (magic042), D_801EFBB0 (magic012), D_801EFC2C (magic223), D_801EFC6C (magic040), D_801EFC88 (magic043), D_801EFCBC (magic101), D_801EFCC8 (magic068), D_801EFD54 (magic123), D_801EFD58 (magic132), D_801EFD8C (magic041), D_801EFDCC (magic100), D_801EFE00 (magic021), D_801EFE58 (magic004), D_801EFEB8 (magic020), D_801EFEE8 (magic143), D_801EFEEC (magic058), D_801EFF34 (magic046), D_801F0028 (magic088), D_801F0048 (magic105), D_801F0064 (magic066), D_801F00F8 (magic137), D_801F02A4 (magic079), D_801F02CC (magic122), D_801F0340 (magic098), D_801F0354 (magic086), D_801F0388 (magic225), D_801F03BC (magic013), D_801F0400 (magic063), D_801F041C (magic169), D_801F0424 (magic039), D_801F046C (magic110), D_801F0488 (magic076), D_801F04A8 (magic096), D_801F04B4 (magic001), D_801F04B8 (magic067), D_801F04D0 (magic144), D_801F04F8 (magic069), D_801F0508 (magic087), D_801F0550 (magic053), D_801F0554 (magic074), D_801F05B4 (magic129), D_801F05D8 (magic125), D_801F0668 (magic073), D_801F066C (magic059), D_801F06DC (magic220), D_801F0744 (magic056), D_801F0794 (magic103), D_801F07BC (magic092), D_801F0878 (magic078), D_801F089C (magic093), D_801F08B0 (magic167), D_801F08DC (magic124), D_801F08E8 (magic104), D_801F0988 (magic173), D_801F0994 (magic099), D_801F0A14 (magic044), D_801F0A24 (magic006), D_801F0AC0 (magic097), D_801F0B00 (magic003), D_801F0B74 (magic172), D_801F0B94 (magic113), D_801F0BB0 (magic060), D_801F0C10 (magic062), D_801F0C38 (magic121), D_801F0C40 (magic226), D_801F0CA8 (magic120), D_801F0D14 (magic082), D_801F0D54 (magic222), D_801F0EEC (magic083), D_801F121C (magic114), D_801F125C (magic126), D_801F1394 (magic064), D_801F1630 (magic015), D_801F1BC4 (magic131), D_801F1BEC (magic008), D_801F24A4 (magic151) */
extern Callback    g_BMagicEffectFuncs[];
extern u8*         D_801F17B0;
extern u8*         D_801F17B4;

/* Per-image effect entry points whose name is a different symbol in another
 * overlay; battle/battle/03 keeps its own view. */
void func_801EEC5C(void);
void func_801EEEC8(void);
void func_801EEF38(void);

void func_800A9610(u8 selector, u16 flags);

/* Defined in Effect_SetActorMatrix.h, which a member includes after its first call. */
void Effect_SetActorMatrix(void);

#endif
