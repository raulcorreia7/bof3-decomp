#include "magic158_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/Effect_RunSlotsWithSetup.h"

/* The image's setup step: clears the effect slot table, copies the selected
 * battler's pose into the effect and spawns sixteen hidden child effects. */
MATCH void func_801EED04(void) {
    PartyMember* battler;
    PartyMember* work;
    u8           i;
    u8           none;
    u8           slot;

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        BMAGIC_EFFECT_SLOTS[i].header.flags = 0;
        BMAGIC_EFFECT_SLOTS[i].header.mode  = 0;
        BMAGIC_EFFECT_SLOTS[i].header.step  = 0;
    }
    battler            = g_BattleSelectedActor;
    g_Task->facing     = battler->facing;
    /* kept: the facing store makes retail reread the work cell; one local for the whole copy merges the two loads. */
    work               = g_Task;
    work->pos.x        = battler->pos.x;
    work->pos.y        = battler->pos.y;
    work->pos.z        = battler->pos.z;
    work->param.unk_0B = 0;
    g_Task->header.mode++;
    /* kept: the GAME_NONE local holds 0xFF in a callee-saved register across the spawn loop; the literal is reloaded each pass. */
    for (i = 0, none = GAME_NONE; i < 16; i++) {
        slot = BMagic_AllocEffect();
        if (slot != none) {
            BMAGIC_EFFECT_SLOTS[slot].target.party = g_Task;
            BMAGIC_EFFECT_SLOTS[slot].unk_0B       = i;
            BMAGIC_EFFECT_SLOTS[slot].header.flags |= BMAGIC_EFFECT_IN_USE | ACTOR_FLAG_HIDDEN;
            BMAGIC_EFFECT_SLOTS[slot].arg.unk_09 = RANDOM_MASK(0x1F) + 1;
            g_Task->param.unk_0B++;
        }
    }
    SND_QueueSelectionFx(0x100);
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EEEF0 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEF34(void) {
    SYS_DISPATCH_BYTE(D_801EF788, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801EF2F0();
        func_801EF3EC();
        PopMatrix();
    }
}

/* At the ticker's zero, places the effect half a cell from the battler by the
 * angle byte 0x0B and starts its rise from a random tint row. */
MATCH void func_801EEFBC(void) {
    u8   count;
    s32  phase;
    s32  entry;
    s16* angle_cell;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (count == 0) {
        angle_cell          = &D_1F800004;
        phase               = g_Task->param.unk_0B & 0xF;
        *angle_cell         = phase << 8;
        /* kept: (s16) types the rsin angle; without it GCC folds the two shifts and the body is 4 bytes short. */
        g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + ((rsin((s16)(phase << 8)) * 0x8000) >> 12);
        g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + ((rcos(*angle_cell) * 0x8000) >> 12);
        g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed + TO_COORD(0x480);
        entry               = RANDOM_MASK(7) * 3;
        g_Task->unk_5D      = D_801EF76C[entry];
        g_Task->unk_5E      = D_801EF76D[entry];
        g_Task->unk_5F      = D_801EF76E[entry];
        g_Task->unk_14      = 0x80;
        g_Task->unk_20      = -0x10;
        g_Task->unk_09      = 8;
        g_Task->timer       = 2;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF140(void) {
    u8 count;
    u8 timer;

    count                    = g_Task->unk_09;
    COORD_INT(g_Task->pos.z) = COORD_INT(g_Task->pos.z) - 0x60;
    if ((count & BYTE_MASK) != 0x10) {
        g_Task->unk_09 = count + 1;
    }
    timer = g_Task->timer;
    if (timer != 16) {
        g_Task->timer = timer + 2;
    }
    if (COORD_INT(g_Task->pos.z) == COORD_INT(BATTLE_ACTIVE_WORK->pos.z)) {
        g_Task->header.step += 1;
    }
}

INCLUDE_ASM(func_801EF1C8);

#include "overlays/bmagic/BMagic_SetupEffectMatrix.h"

MATCH void func_801EF2F0(void) {
    BMAGIC_SETUP_EFFECT_MATRIX();
}

INCLUDE_ASM(func_801EF3EC);

/* func_801EF708 */
#include "overlays/bmagic/BMagic_AllocEffect.h"
