#ifndef OVERLAY_BMAGIC_MAGIC113_03_H
#define OVERLAY_BMAGIC_MAGIC113_03_H

/* The bmagic/magic113/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* The orbit radius the effect keeps in the scratchpad word; BMagic_NotingDrawRing scales its sin and cos by it. */
#define s_BMagicNotingRadius g_ScratchPad.cells.words[0]
/* The three corners BMagic_NotingDrawShadow projects for each ring triangle. */

/* The stage byte (0x0B of the effect battler, which is the task) the effects use to cue one another. */
typedef enum BMagicNotingStage {
    BMAGIC_NOTING_STAGE_RINGS    = 3,
    BMAGIC_NOTING_STAGE_STAR     = 4,
    BMAGIC_NOTING_STAGE_WALL     = 5,
    BMAGIC_NOTING_STAGE_ACTORS   = 6,
    BMAGIC_NOTING_STAGE_RELEASED = 0x80,
    BMAGIC_NOTING_STAGE_RELEASE  = 0x84
} BMagicNotingStage;

/* The effects the task starts: header.mode picks the routine g_BMagicEffectModes runs. */
typedef enum BMagicNotingEffectMode {
    BMAGIC_NOTING_EFFECT_RING  = 0,
    BMAGIC_NOTING_EFFECT_STAR  = 1,
    BMAGIC_NOTING_EFFECT_WALL  = 2,
    BMAGIC_NOTING_EFFECT_ACTOR = 3
} BMagicNotingEffectMode;

/* Count the timer (byte 0x0A) up; at 12 lower the effect battler's stage and reset the effect. */
static inline void Effect_CountUpTimer(void) {
    PartyMember* work;
    u8           next;

    work        = TASK(PartyMember);
    next        = work->timer + 1;
    work->timer = next;
    if (next == 0xC) {
        BATTLE_ACTIVE_WORK->param.unk_0B--;
        Effect_Reset();
    }
}

/* Starts an effect of id 3 on the task, copies the task's position into it and advances the
 * mode; MODE is the new effect's mode. A statement macro: the member declares u32 slot,
 * PartyMember* work and u8 facing. */
#define BMAGIC_NOTING_SPAWN_EFFECT(MODE)                                           \
    slot                                   = Battle_AllocEffect(1, 3) & BYTE_MASK; \
    work                                   = g_Task;                               \
    g_BattleEffects[slot].header.mode      = (MODE);                               \
    g_BattleEffects[slot].target.party     = work;                                 \
    facing                                 = g_BattleEffectBattler->facing;        \
    g_BattleEffects[slot].arg.unk_09       = 0;                                    \
    g_BattleEffects[slot].unk_0A           = 0;                                    \
    g_BattleEffects[slot].unk_08           = (facing + 2) & 3;                     \
    g_BattleEffects[slot].pos.x            = TASK(PartyMember)->pos.x;             \
    g_BattleEffects[slot].pos.y            = TASK(PartyMember)->pos.y;             \
    COORD_INT(g_BattleEffects[slot].pos.z) = COORD_INT(TASK(PartyMember)->pos.z);  \
    TASK(PartyMember)->header.mode += 1

#define BMAGIC_NOTING_STEP_COUNT 8

typedef struct BMagicNotingSteps {
    Callback steps[BMAGIC_NOTING_STEP_COUNT];
} BMagicNotingSteps;

/* D_801EEC04 */
extern BMagicNotingSteps g_BMagicNotingSteps;

/* D_801F0BA4 */
extern s32      g_BMagicNotingRingRadii[];
/* D_801F0BAC */
extern Callback g_BMagicNotingRingSteps[];
/* D_801F0BB8: the corner angles of the star, in steps of 273 (a fifteenth of a turn). */
extern s8       g_BMagicNotingStarCorners[];
/* D_801F0BC0 */
extern Callback g_BMagicNotingStarSteps[];
/* D_801F0BCC */
extern Callback g_BMagicNotingWallSteps[];
/* D_801F0BD8 */
extern Callback g_BMagicNotingActorSteps[];
/* func_801EFDA0 */
void            BMagic_NotingDrawStar(void);
/* func_801F02CC */
void            BMagic_NotingDrawWall(void);

/* Advance the effect's step when the effect battler's stage (byte 0x0B) is `param_value`. A statement
 * macro: the member declares PartyMember* active and PartyMember* work. */
#define BMAGIC_NOTING_ADVANCE_AT_STAGE(param_value) \
    active = BATTLE_ACTIVE_WORK;                    \
    if (active->param.unk_0B == (param_value)) {    \
        work              = TASK(PartyMember);      \
        work->header.step = work->header.step + 1;  \
    }

#endif
