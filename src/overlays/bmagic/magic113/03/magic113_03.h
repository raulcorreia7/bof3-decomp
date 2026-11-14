#ifndef OVERLAY_BMAGIC_MAGIC113_03_H
#define OVERLAY_BMAGIC_MAGIC113_03_H

/* The bmagic/magic113/03 overlay. Only this image includes the file. */

#include "overlays/bmagic/bmagic.h"

/* The orbit radius the effect keeps in the scratchpad word; func_801EF944 scales its sin and cos by it. */
#define s_Magic113OrbitRadius D_1F800000.view.scenario.math_00
/* The three corners func_801EF4F0 projects for each ring triangle. */

/* Count the effect timer up and finish the effect at 12. */
static inline void Effect_CountUpTimer(void) {
    PartyMember* work;
    u8           next;

    work        = g_Task;
    next        = work->timer + 1;
    work->timer = next;
    if (next == 0xC) {
        BATTLE_ACTIVE_WORK->param.unk_0B--;
        func_801E5988();
    }
}

/* Claims effect slot 3 for the effect's target, copies its coordinates into it
 * and advances the mode; MODE is the new effect's mode. A statement macro: the
 * member declares u32 slot, PartyMember* work and u8 facing. */
#define MAGIC113_SPAWN_EFFECT(MODE)                                                \
    slot                                   = Battle_AllocEffect(1, 3) & BYTE_MASK; \
    work                                   = g_Task;                               \
    g_BattleEffects[slot].header.mode      = (MODE);                               \
    g_BattleEffects[slot].target.party     = work;                                 \
    facing                                 = g_BattleEffectBattler->facing;        \
    g_BattleEffects[slot].arg.unk_09       = 0;                                    \
    g_BattleEffects[slot].unk_0A           = 0;                                    \
    g_BattleEffects[slot].unk_08           = (facing + 2) & 3;                     \
    g_BattleEffects[slot].pos.x            = g_Task->pos.x;                        \
    g_BattleEffects[slot].pos.y            = g_Task->pos.y;                        \
    COORD_INT(g_BattleEffects[slot].pos.z) = COORD_INT(g_Task->pos.z);             \
    g_Task->header.mode += 1

void func_8015D104(s32 slot, s32 amount);
void SND_StartVolumeSweep(s32 voice);

#define MAGIC113_STEP_COUNT 8

typedef struct Magic113Steps {
    Callback handlers[MAGIC113_STEP_COUNT];
} Magic113Steps;

extern Magic113Steps D_801EEC04;

extern Callback D_801F0BAC[];
extern s32      D_801F0BA4[];

extern Callback D_801F0BC0[];
void            func_801EFDA0(void);

extern Callback D_801F0BCC[];
extern Callback D_801F0BD8[];
void            func_801F02CC(void);

/* The corner angles of the outline, in steps of 273 (a fifteenth of a turn). */
extern s8 D_801F0BB8[];

#endif
