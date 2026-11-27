#include "magic055_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/Effect_DrawActor.h"

/* Task mode 0: copies the selected actor's facing and position into the task, starts BMAGIC_RING_COUNT ring bands, queues the selection sound and applies the damage flags. */
/* func_801EECCC */
MATCH void BMagic_RingStart(void) {
    u32          i;
    u8           slot;
    s8           delay;
    PartyMember* actor;
    PartyMember* task;
    PartyMember* work;
    u16*         src;
    u16*         dst;

    actor                     = g_Battle.selected_actor;
    SELF(PartyMember)->facing = actor->facing;
    task                      = SELF(PartyMember);
    WorldPos_Copy(&task->pos, &actor->pos);
    task->param.unk_0B = 0;
    for (i = 0, delay = BMAGIC_RING_FIRST_DELAY; i < BMAGIC_RING_COUNT; i++) {
        slot                               = Battle_AllocEffect(1, BMAGIC_EFFECT_EBONFIRE);
        work                               = SELF(PartyMember);
        g_BattleEffects[slot].arg.unk_09   = delay;
        g_BattleEffects[slot].target.party = work;
        SELF(PartyMember)->param.unk_0B += 1;
        delay += BMAGIC_RING_STAGGER;
    }
    i   = 1;
    dst = MEM_PTR(u16, 0x8003AC02u);
    src = MEM_PTR(u16, 0x80036C02u);
    for (; i < 16; i++) {
        *dst++ = *src++ | PSX_COLOR_STP_BIT;
    }
    *MEM_PTR(u16, 0x8003AC00u) = 0;
    g_GfxPalettePending        = 1;
    SND_SEQueueSelection(0x100);
    Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10);
    SELF(PartyMember)->unk_09 = 1;
    SELF(PartyMember)->timer  = 1;
    SELF(PartyMember)->header.mode += 1;
}

#include "overlays/bmagic/shared/BMagic_RingExpand.h"

#include "overlays/bmagic/shared/BMagic_RingEnd.h"

#include "overlays/bmagic/shared/BMagic_RingBandUpdate.h"

/* func_801EEFFC */
#include "overlays/bmagic/shared/BMagic_RingBandWait.h"

#include "overlays/bmagic/shared/BMagic_RingBandShrink.h"

#include "overlays/bmagic/shared/BMagic_RingBandEnd.h"

#include "overlays/bmagic/shared/func_801EF1B8.h"

#include "overlays/bmagic/shared/BMagic_RingBandDraw.h"

/* func_801EF240 */
MATCH void BMagic_RingBandDraw(void) {
    POLY_GT4* prim;
    long      depth;
    long      flag;
    s32       i;
    s32       tpage;
    s32       x;
    s32       y;
    s32       phase;

    BMAGIC_DRAW_RING_BAND(TPAGE_ABR_SUB);
}

#include "overlays/bmagic/shared/Effect_SetActorMatrix.h"

#include "overlays/bmagic/shared/BMagic_RingDrawDisc.h"

#include "overlays/bmagic/shared/BMagic_RingDrawShade.h"
