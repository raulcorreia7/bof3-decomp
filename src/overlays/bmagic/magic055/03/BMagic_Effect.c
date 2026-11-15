#include "magic055_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/Effect_DrawActor.h"

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
        slot                               = Battle_AllocEffect(1, 52);
        work                               = g_Task;
        g_BattleEffects[slot].arg.unk_09   = anchor;
        g_BattleEffects[slot].target.party = work;
        g_Task->param.unk_0B += 1;
        anchor += 6;
    }
    i   = 1;
    dst = MEM_PTR(u16, 0x8003AC02u);
    src = MEM_PTR(u16, 0x80036C02u);
    for (; i < 16; i++) {
        *dst++ = *src++ | 0x8000;
    }
    *MEM_PTR(u16, 0x8003AC00u) = 0;
    g_GfxPalettePending        = 1;
    SND_QueueSelectionEffect(0x100);
    Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10);
    g_Task->unk_09 = 1;
    g_Task->timer  = 1;
    g_Task->header.mode += 1;
}

#include "overlays/bmagic/func_801EEE3C.h"

#include "overlays/bmagic/Effect_DecayTimersAndPlay.h"

#include "overlays/bmagic/func_801EEF74.h"

/* func_801EEFFC */
#include "overlays/bmagic/Effect_FollowTarget.h"

#include "overlays/bmagic/func_801EF09C.h"

#include "overlays/bmagic/func_801EF124.h"

#include "overlays/bmagic/func_801EF1B8.h"

#include "overlays/bmagic/func_801EF240.h"

MATCH void func_801EF240(void) {
    POLY_GT4* prim;
    long      depth;
    long      flag;
    s32       i;
    s32       tpage;
    s32       x;
    s32       y;
    s32       phase;

    BMAGIC_DRAW_RING_BAND(2);
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"

#include "overlays/bmagic/func_801EF7B0.h"

#include "overlays/bmagic/func_801EF9E4.h"
