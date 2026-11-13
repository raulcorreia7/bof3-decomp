#ifndef BMAGIC_FAMILY_H
#define BMAGIC_FAMILY_H

#include "common/vector.h"
#include "game.h"
#include "gfx/prim.h"
#include "overlays/battle/battle.h"
#include "sys/task.h"

#define BMAGIC_PHASE_ANGLE(phase) ((phase) << 6)
#define BMAGIC_PHASE_MASK         0x3F

/* The bytes a sparkle ray reserves in its cell packet. */
#define BMAGIC_RAY_CELL_SIZE      32

/* Per-slot column views over the 0x78-byte effect slots: the trailing padding
 * carries the slot stride so each column keeps its own field base. */
typedef struct BattleEffectByteColumn {
    u8 value;
    u8 pad[BATTLE_EFFECT_STRIDE - 1];
} BattleEffectByteColumn;

typedef struct BattleEffectTargetColumn {
    BattleEffectTarget target;
    u8                 pad[BATTLE_EFFECT_STRIDE - sizeof(BattleEffectTarget)];
} BattleEffectTargetColumn;

ASSERT_SIZE(BattleEffectByteColumn, BATTLE_EFFECT_STRIDE);
ASSERT_SIZE(BattleEffectTargetColumn, BATTLE_EFFECT_STRIDE);

/* The statements of Effect_SetActorMatrix after its rotation is set; each
 * member declares pos, rot, matrix and flags. SPAN_WORK is the work record
 * whose vertical span halves into the depth. */
#define BMAGIC_PROJECT_ACTOR_MATRIX(SPAN_WORK)    \
    pos.vx = (g_Task->pos.x.fixed >> 9) - 0x4000; \
    pos.vy = (g_Task->pos.y.fixed >> 9) - 0x4000; \
    pos.vz = -COORD_INT((SPAN_WORK)->pos.z) / 2;  \
    RotTransMatrix(&pos, matrix, &flags);         \
    Camera_SetModelMatrix(&rot, &matrix)

/* The statements of Effect_SetActorMatrix with a zero rotation. */
#define BMAGIC_SET_ACTOR_MATRIX_SPAN(SPAN_WORK) \
    PushMatrix();                               \
    rot.vx = 0;                                 \
    rot.vy = 0;                                 \
    rot.vz = 0;                                 \
    BMAGIC_PROJECT_ACTOR_MATRIX(SPAN_WORK)

#define BMAGIC_SET_ACTOR_MATRIX() BMAGIC_SET_ACTOR_MATRIX_SPAN(g_Task)

/* The battler the target selector names: a party row below
 * BATTLE_PARTY_CHARACTERS_COUNT, else an enemy row. A statement macro: the
 * member declares u8 selector and PartyMember* battler. */
#define BMAGIC_SELECT_TARGET_BATTLER()                                              \
    selector = LOBU(g_Battle.target_selector);                                      \
    if (selector < BATTLE_PARTY_CHARACTERS_COUNT) {                                 \
        battler = &g_Game.members[selector];                                        \
    } else {                                                                        \
        battler = (PartyMember*)(g_BattleEnemies + selector * BATTLE_ENEMY_STRIDE); \
    }

/* Free the palette fade of the battler the target selector names (a party row
 * below BATTLE_PARTY_CHARACTERS_COUNT, else an enemy row), tell the battle UI and
 * the effect player about the selector, then raise the effect-playing state.
 * A statement macro: the member declares u32 slot, u8* selector and
 * PartyMember* battler. */
#define BMAGIC_RELEASE_TARGET_AND_PLAY()                                        \
    slot = LOBU(g_Battle.target_selector);                                      \
    if (slot < BATTLE_PARTY_CHARACTERS_COUNT) {                                 \
        battler = &g_Game.members[slot];                                        \
    } else {                                                                    \
        battler = (PartyMember*)(g_BattleEnemies + slot * BATTLE_ENEMY_STRIDE); \
    }                                                                           \
    func_80196718(battler);                                                     \
    selector = (u8*)&g_Battle.target_selector;                                  \
    func_800AF814(*selector);                                                   \
    Battle_MarkDamaged(*selector);                                              \
    g_Battle.state |= BATTLE_STATE_EFFECT_PLAYING;                              \
    func_801E5988()

/* The sway step of the effect work record WORK points to: phase_0C advances and
 * its low six bits set the wave (also stored in the scratchpad halfword at
 * 0x1F800006), which moves unk_20 around unk_08 by 0x18 * sin; unk_22 grows by
 * unk_0A; unk_06 drops every fourth frame; at timer_05 zero the effect steps
 * and CLEAR (the image's work-clearing function) runs. A statement macro: the
 * member declares u16 phase and u8 timer. */
#define BMAGIC_SWAY_EFFECT_WORK(WORK, CLEAR)                                              \
    phase            = (WORK)->phase_0C + 1;                                              \
    (WORK)->phase_0C = phase;                                                             \
    phase            = phase & BMAGIC_PHASE_MASK;                                         \
    SP_REF(s16, 6)   = BMAGIC_PHASE_ANGLE(phase);                                         \
    (WORK)->unk_20   = (WORK)->unk_08 + FIXED_MUL(rsin(BMAGIC_PHASE_ANGLE(phase)), 0x18); \
    (WORK)->unk_22   = (WORK)->unk_22 + (WORK)->unk_0A;                                   \
    if ((g_FrameCount & 3) == 0) {                                                        \
        (WORK)->unk_06 = (WORK)->unk_06 - 1;                                              \
    }                                                                                     \
    timer            = (WORK)->timer_05 - 1;                                              \
    (WORK)->timer_05 = timer;                                                             \
    if (timer == 0) {                                                                     \
        g_BattleEffectBattler->param.unk_0B -= 1;                                         \
        CLEAR();                                                                          \
    }

/* The sway-advance step of the effect work record WORK points to: phase_0C
 * advances and its low six bits set the wave (also stored in the scratchpad
 * halfword at 0x1F800006), which moves unk_20 around unk_08 by 0x18 * sin;
 * unk_22 grows by unk_0A; unk_06 counts up and the step advances whenever the
 * count reaches unk_07. A statement macro: the member declares s32 wave, u16
 * phase and u8 tick. The rsin argument keeps its (s16) truncation: the wave is
 * passed twice and the second, recomputed shift lands in the call's delay slot. */
#define BMAGIC_SWAY_ADVANCE_WORK(WORK)                                                             \
    phase            = (WORK)->phase_0C + 1;                                                       \
    (WORK)->phase_0C = phase;                                                                      \
    wave             = phase & BMAGIC_PHASE_MASK;                                                  \
    SP_REF(s16, 6)   = (s16)BMAGIC_PHASE_ANGLE(wave);                                              \
    (WORK)->unk_20   = (WORK)->unk_08 + FIXED_MUL((s32)rsin((s16)BMAGIC_PHASE_ANGLE(wave)), 0x18); \
    tick             = (WORK)->unk_06 + 1;                                                         \
    (WORK)->unk_22   = (WORK)->unk_22 + (WORK)->unk_0A;                                            \
    (WORK)->unk_06   = tick;                                                                       \
    if ((tick & BYTE_MASK) == (WORK)->unk_07) {                                                    \
        (WORK)->header.step += 1;                                                                  \
    }

/* One remembered position of an effect's trail. */
typedef Point2D TrailPoint;

#define BMAGIC_TRAIL_LENGTH 32

/* Shift the points of the trail TRAIL[unk_04] from unk_0B up to unk_0A - 1 one
 * place toward the end, freeing the point at unk_0B. A statement macro: the
 * member declares s32 i. */
#define BMAGIC_SHIFT_TRAIL(TRAIL)                                        \
    i = g_Task->timer - 1;                                               \
    while (i >= g_Task->param.unk_0B) {                                  \
        (TRAIL)[g_Task->unk_04][i + 1].x = (TRAIL)[g_Task->unk_04][i].x; \
        (TRAIL)[g_Task->unk_04][i + 1].y = (TRAIL)[g_Task->unk_04][i].y; \
        i -= 1;                                                          \
    }

/* Decrement the active effect ticker. */
#define BMAGIC_TICK_EFFECT_WORK() (BATTLE_ACTIVE_WORK->param.unk_0B--)

/* Run the module step handler the task step selects. A bare statement macro:
 * the member declares `handlers`. Kept: as an inline taking the table by value
 * the frame is 56 bytes where retail has 48 (func_801EEC1C in magic086). */
#define BMAGIC_DISPATCH_STEP_HANDLERS(table, field) \
    handlers = (table);                             \
    handlers.handlers[g_Task->field]()
#define g_Task ((PartyMember*)g_Task)

/* The 0x74 bytes of a battler's work record that a queued effect slot copies;
 * GCC expands the copy into its 16-byte block-move loop. */
typedef struct BattleWorkImage {
    u32 words[29];
} BattleWorkImage;

ASSERT_SIZE(BattleWorkImage, 0x74);

/* Copy the active battler's work image into a free effect slot. A statement
 * macro: the member declares u32 index, u8 active and BattleEffect* slot. */
#define BMAGIC_ALLOC_BATTLER_EFFECT()                                              \
    index  = Battle_AllocEffect(1, 31);                                            \
    active = g_Battle.active_battler;                                              \
    if (BATTLER_IS_PLAYER(active)) {                                               \
        BattleWorkImage* row;                                                      \
                                                                                   \
        row                     = (BattleWorkImage*)&g_Game.members[active];       \
        slot                    = &g_BattleEffects[index & BYTE_MASK];             \
        *(BattleWorkImage*)slot = *row;                                            \
    } else {                                                                       \
        BattleWorkImage* row;                                                      \
        u32              enemy;                                                    \
                                                                                   \
        slot                    = &g_BattleEffects[index & BYTE_MASK];             \
        enemy                   = active - BATTLE_PARTY_CHARACTERS_COUNT;          \
        row                     = (BattleWorkImage*)&g_BattleEnemyBattlers[enemy]; \
        *(BattleWorkImage*)slot = *row;                                            \
    }

/* Go to the effect's next step. */
static inline void BMagic_NextStep(void) {
    PartyMember* work = g_Task;

    work->header.step = (u8)(work->header.step + 1);
}

/* Clear the local effect work. */
static inline void BMagic_ResetLocalWork(void) {
    g_Task->header.flags = 0;
    g_Task->header.mode  = 0;
    g_Task->header.step  = 0;
    g_Task->unk_03       = 0;
    g_Task->unk_04       = 0;
}

/* Run the task handler the spad task byte selects. */
static inline void BMagic_DispatchTaskPair(Callback first, Callback second) {
    Callback handlers[2] = {first, second};

    handlers[g_Task->header.mode]();
}

/* Add `step` to the work counter, count the effect timer down and finish the
 * effect at zero. */
static inline void BMagic_CountDownEffectTimer(u8 step) {
    PartyMember* work;
    PartyMember* active;
    u8           count;

    work = g_Task;
    work->unk_09 += step;
    work        = g_Task;
    count       = work->timer - 1;
    work->timer = count;
    if (count == 0) {
        active = BATTLE_ACTIVE_WORK;
        active->param.unk_0B--;
        func_801E5988();
    }
}

/* Go to the next effect mode and reload the work timer while the ticker is
 * under `limit`. */
static inline void BMagic_AdvanceEffectStep(u8 limit) {
    PartyMember* work;

    work = g_Task;
    if (work->param.unk_0B < limit) {
        work->unk_09      = 8;
        work              = g_Task;
        work->header.mode = work->header.mode + 1;
    }
}

/* Set the top bit of every halfword of palette row 26 — the BATL_OVR bank — in
 * the working palette. A statement macro: the member declares its pointers and
 * index, and the setup order is retail's. */
#define BMAGIC_BRIGHTEN_PALETTE_ROW(dst, src, i)                      \
    (i)   = 0;                                                        \
    (dst) = MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW);  \
    (src) = MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW); \
    for (; (i) < 256; (i)++) {                                        \
        (dst)[i] = (src)[i] | 0x8000u;                                \
    }

/* Swing the area camera pitch by 20 each tick, up on odd timer values and down
 * on even ones; at zero, rest it at -60 degrees, reload the timer with
 * `settle_ticks` and go to the next step. A statement macro: as an inline the
 * function is two instructions longer. */
#define BMAGIC_SWING_CAMERA(settle_ticks)          \
    do {                                           \
        if ((g_Task->unk_09 & 1) != 0) {           \
            g_AreaCameraAngle.vx += 20;            \
        } else {                                   \
            g_AreaCameraAngle.vx -= 20;            \
        }                                          \
        if (--g_Task->unk_09 == 0) {               \
            g_AreaCameraAngle.vx = -DEG(60);       \
            g_Task->unk_09       = (settle_ticks); \
            g_Task->header.step++;                 \
        }                                          \
    } while (0)

typedef struct BMagicEffectFuncs {
    Callback handlers[6];
} BMagicEffectFuncs;

ASSERT_SIZE(BMagicEffectFuncs, 0x18);
ASSERT_OFFSET(BMagicEffectFuncs, handlers, 0x00);

/* The step handlers Effect_DrawRings runs, indexed by header.step (byte 0x02). */
typedef struct BMagicStepHandlers {
    Callback steps[3];
} BMagicStepHandlers;

ASSERT_SIZE(BMagicStepHandlers, 0xC);

extern BMagicStepHandlers BMagic_EffectSteps;

/* The effect work record D_801F17B4 points to: func_801F006C clears bytes 0-4,
 * func_801EF33C dispatches on mode. magic070-072 keep a pool of them, one
 * record per sparkle; magic131 keeps a pool of 48. */
typedef struct BMagicEffectWork {
    /* 0x00 */ TaskHeader   header;
    /* 0x03 */ u8           unk_03;
    /* 0x04 */ u8           unk_04;
    /* 0x05 */ u8           timer_05;
    /* 0x06 */ u8           unk_06;
    /* 0x07 */ u8           unk_07;
    /* 0x08 */ u16          unk_08;
    /* 0x0A */ u16          unk_0A;
    /* 0x0C */ u16          phase_0C;
    /* 0x0E */ u8           pad_0E[6];
    /* 0x14 */ WorldPos     pos;
    /* 0x20 */ s16          unk_20;
    /* 0x22 */ u16          unk_22;
    /* 0x24 */ u8           pad_24[2];
    /* 0x26 */ s16          unk_26;
    /* 0x28 */ PartyMember* battler;
} BMagicEffectWork;

/* header.flags bit of a BMagicEffectWork slot that is running. */
#define BMAGIC_EFFECT_IN_USE 0x01

ASSERT_SIZE(BMagicEffectWork, 0x2C);

ASSERT_OFFSET(BMagicEffectWork, unk_03, 0x03);
ASSERT_OFFSET(BMagicEffectWork, unk_04, 0x04);
ASSERT_OFFSET(BMagicEffectWork, timer_05, 0x05);
ASSERT_OFFSET(BMagicEffectWork, unk_06, 0x06);
ASSERT_OFFSET(BMagicEffectWork, unk_07, 0x07);
ASSERT_OFFSET(BMagicEffectWork, unk_08, 0x08);
ASSERT_OFFSET(BMagicEffectWork, unk_0A, 0x0A);
ASSERT_OFFSET(BMagicEffectWork, phase_0C, 0x0C);
ASSERT_OFFSET(BMagicEffectWork, pos, 0x14);
ASSERT_OFFSET(BMagicEffectWork, unk_20, 0x20);
ASSERT_OFFSET(BMagicEffectWork, unk_22, 0x22);
ASSERT_OFFSET(BMagicEffectWork, unk_26, 0x26);
ASSERT_OFFSET(BMagicEffectWork, battler, 0x28);

/* The record of an effect that orbits its battler: the angle advances every frame and the radius scales sin and cos. */
typedef struct BMagicOrbitWork {
    /* 0x00 */ TaskHeader header;
    /* 0x03 */ u8         unk_03;
    /* 0x04 */ u8         unk_04;
    /* 0x05 */ u8         timer_05;
    /* 0x06 */ u8         timer_06;
    /* 0x07 */ u8         timer_07;
    /* 0x08 */ u8         frames_left;
    /* 0x09 */ u8         unk_09;
    /* 0x0A */ u8         unk_0A;
    /* 0x0B */ u8         unk_0B;
    /* 0x0C */ s16        radius;
    /* 0x0E */ u16        angle;
    /* 0x10 */ s32        unk_10;
    /* 0x14 */ s32        unk_14;
    /* 0x18 */ s32        unk_18;
} BMagicOrbitWork;

ASSERT_OFFSET(BMagicOrbitWork, radius, 0x0C);
ASSERT_OFFSET(BMagicOrbitWork, angle, 0x0E);
ASSERT_OFFSET(BMagicOrbitWork, unk_14, 0x14);

/* D_801F05F8 (magic106), D_801F1054 (magic063) */
extern BMagicOrbitWork* g_BMagicOrbitWork;

extern MagicModule       D_801EEC00;
/* D_801EF3E8 (magic161), D_801EF414 (magic145), D_801EF420 (magic159), D_801EF510 (magic065), D_801EF658 (magic054),
   D_801EF6CC (magic154), D_801EF718 (magic166), D_801EF72C (magic138), D_801EF770 (magic218), D_801EF784 (magic158),
   D_801EF7A0 (magic075), D_801EF818 (magic048), D_801EF89C (magic009), D_801EF8A0 (magic213), D_801EF8BC (magic115),
   D_801EF8D8 (magic045), D_801EF990 (magic017), D_801EF9A4 (magic038), D_801EF9B4 (magic146), D_801EFA00 (magic219),
   D_801EFA44 (magic130), D_801EFA84 (magic081), D_801EFA9C (magic050), D_801EFA9C (magic111), D_801EFB70 (magic042),
   D_801EFBB0 (magic012), D_801EFC2C (magic223), D_801EFC6C (magic040), D_801EFC88 (magic043), D_801EFCBC (magic101),
   D_801EFCC8 (magic068), D_801EFD54 (magic123), D_801EFD58 (magic132), D_801EFD8C (magic041), D_801EFDCC (magic100),
   D_801EFE00 (magic021), D_801EFE58 (magic004), D_801EFEB8 (magic020), D_801EFEE8 (magic143), D_801EFEEC (magic058),
   D_801EFF34 (magic046), D_801F0028 (magic088), D_801F0048 (magic105), D_801F0064 (magic066), D_801F00F8 (magic137),
   D_801F02A4 (magic079), D_801F02CC (magic122), D_801F0340 (magic098), D_801F0354 (magic086), D_801F0388 (magic225),
   D_801F03BC (magic013), D_801F0400 (magic063), D_801F041C (magic169), D_801F0424 (magic039), D_801F046C (magic110),
   D_801F0488 (magic076), D_801F04A8 (magic096), D_801F04B4 (magic001), D_801F04B8 (magic067), D_801F04D0 (magic144),
   D_801F04F8 (magic069), D_801F0508 (magic087), D_801F0550 (magic053), D_801F0554 (magic074), D_801F05B4 (magic129),
   D_801F05D8 (magic125), D_801F0668 (magic073), D_801F066C (magic059), D_801F06DC (magic220), D_801F0744 (magic056),
   D_801F0794 (magic103), D_801F07BC (magic092), D_801F0878 (magic078), D_801F089C (magic093), D_801F08B0 (magic167),
   D_801F08DC (magic124), D_801F08E8 (magic104), D_801F0988 (magic173), D_801F0994 (magic099), D_801F0A14 (magic044),
   D_801F0A24 (magic006), D_801F0AC0 (magic097), D_801F0B00 (magic003), D_801F0B74 (magic172), D_801F0B94 (magic113),
   D_801F0BB0 (magic060), D_801F0C10 (magic062), D_801F0C38 (magic121), D_801F0C40 (magic226), D_801F0CA8 (magic120),
   D_801F0D14 (magic082), D_801F0D54 (magic222), D_801F0EEC (magic083), D_801F121C (magic114), D_801F125C (magic126),
   D_801F1394 (magic064), D_801F1630 (magic015), D_801F1BC4 (magic131), D_801F1BEC (magic008), D_801F24A4 (magic151) */
extern Callback          g_BMagicEffectModes[];
extern BMagicEffectWork* D_801F17B0;
extern BMagicEffectWork* D_801F17B4;

/* The four scratch vectors the effect draws project their corners from; the flat name keeps the retail
 * bytes, the scratchpad view does not. */
extern SVECTOR D_1F800014[];

/* Pointers to character-indexed archive ids, one row of two per g_Battle.dragon_form; the caller picks
 * the row's column and g_EmiLoadedCharacterIndex picks the id. */
extern u16* D_800B499C[][2];

void Battle_ApplyDamageFlags(u8 selector, u16 flags);
/* Per-image effect entry points whose name is a different symbol in another
 * overlay; battle/battle/03 keeps its own view. */
void func_800AFC54(void);
void func_801EEC5C(void);
void func_801EECE4(void);
void func_801EED1C(void);
void Effect_PlayOnZeroTick(void);
void Effect_StartOnZeroTick(void);
void func_801EEEC8(void);
void func_801EEF38(void);
void func_801EF240(void);
void func_801EF4F0(void);
void func_801EF970(void);
void func_801EFA48(void);
void func_801F0068(void);
void BMagic_DrawRingTriangles(void);
void BMagic_DrawRingQuads(void);

void func_801F006C(void);

/* Defined in BMagic_AllocEffect.h, which a member includes after its first call. */
u32  BMagic_AllocEffect(void);
/* Defined in Effect_DrawBolt.h, which a member includes after its first call. */
void Effect_DrawBolt(void);
/* Defined in Effect_DrawSparkleRays.h, which a member includes after its first call. */
void Effect_DrawSparkleRays(u16 angle, u16 radius);
/* Defined in Effect_DrawSparkleWedges.h, which a member includes after its first call. */
void Effect_DrawSparkleWedges(u16 angle, u16 radius);
/* Defined in Effect_SetActorMatrix.h, which a member includes after its first call. */
void Effect_SetActorMatrix(void);
/* Defined in Effect_SetActorMatrixQuarterRoll.h, which a member includes after its first call. */
void Effect_SetActorMatrixQuarterRoll(void);
/* Defined in Effect_DrawScreenFade.h, which a member includes after its first call. */
void Effect_DrawScreenFade(void);
/* Defined in Effect_DrawSparkleDisc.h, which a member includes after its first call. */
void Effect_DrawSparkleDisc(void);
/* Defined in Effect_DrawTexturedQuad.h, which a member includes after its first call. */
void Effect_DrawTexturedQuad(void);

#define EFFECT_ADVANCE_AT_COUNT(increment, limit) \
    do {                                          \
        g_Task->unk_09 += (increment);            \
        if (g_Task->unk_09 == (limit)) {          \
            g_Task->header.step += 1;             \
        }                                         \
    } while (0)

void func_801F07A8(void);

#endif
