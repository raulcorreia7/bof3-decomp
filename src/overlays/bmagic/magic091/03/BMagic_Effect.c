#include "magic091_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/Effect_DrawActor.h"

MATCH void func_801EECCC(void) {
    u32          i;
    u8           slot;
    s8           anchor;
    PartyMember* actor;
    PartyMember* task;
    PartyMember* work;
    u16*         src;
    u16*         dst;

    actor          = g_Battle.selected_actor;
    g_Task->facing = actor->facing;
    task           = g_Task;
    WorldPos_Copy(&task->pos, &actor->pos);
    task->param.unk_0B = 0;
    for (i = 0, anchor = 1; i < 6; i++) {
        slot                               = Battle_AllocEffect(1, 22);
        work                               = g_Task;
        g_BattleEffects[slot].arg.unk_09   = anchor;
        g_BattleEffects[slot].target.party = work;
        g_Task->param.unk_0B += 1;
        anchor += 6;
    }
    i   = 1;
    dst = BATTLE_EFFECT_PALETTE_COLORS;
    src = BATTLE_PALETTE_SOURCE_COLORS;
    for (; i < 16; i++) {
        *dst++ = *src++ | PSX_COLOR_STP_BIT;
    }
    g_BattleEffectPalette[0] = 0;
    g_GfxPalettePending      = 1;
    Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10);
    SND_QueueSelectionSE(0x100);
    g_Task->unk_09 = 1;
    g_Task->timer  = 1;
    g_Task->header.mode += 1;
}

#include "overlays/bmagic/shared/func_801EEE3C.h"

#include "overlays/bmagic/shared/Effect_DecayTimersAndPlay.h"

#include "overlays/bmagic/shared/func_801EEF74.h"

/* func_801EEFFC */
#include "overlays/bmagic/shared/Effect_FollowTarget.h"

#include "overlays/bmagic/shared/func_801EF09C.h"

#include "overlays/bmagic/shared/func_801EF124.h"

#include "overlays/bmagic/shared/func_801EF1B8.h"

#include "overlays/bmagic/shared/func_801EF240.h"

MATCH void func_801EF240(void) {
    POLY_GT4* prim;
    long      depth;
    long      flag;
    s32       i;
    s32       tpage;
    s32       x;
    s32       y;
    s32       phase;

    BMAGIC_DRAW_RING_BAND(1);
}

#include "overlays/bmagic/shared/Effect_SetActorMatrix.h"

#include "overlays/bmagic/shared/func_801EF7B0.h"

#include "overlays/bmagic/shared/func_801EF9E4.h"
