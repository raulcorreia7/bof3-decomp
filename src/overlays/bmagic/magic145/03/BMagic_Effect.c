#include "magic145_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_DispatchMode.h"

MATCH void func_801EEC70(void) {
    u8           i;
    u8           slot;
    PartyMember* work;
    u16*         dst;
    u16*         src;

    g_Task->param.unk_0B = 0;
    g_Task->header.mode += 1;
    for (i = 0; i < 3; i++) {
        slot                               = Battle_AllocEffect(1, 108);
        work                               = g_Task;
        g_BattleEffects[slot].header.mode  = 0;
        g_BattleEffects[slot].unk_0B       = i;
        g_BattleEffects[slot].arg.unk_09   = i * 4 + 1;
        g_BattleEffects[slot].target.party = work;
        g_Task->param.unk_0B += 1;
    }
    /* Copies colours 1 to 15 of CLUT 1 of arena palette row 26 into the work copy with STP set, then clears colour 0. */
    i   = 1;
    dst = MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW);
    src = MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW);
    for (; i < 16; i++) {
        dst[i + 32] = src[i + 32] | 0x8000;
    }
    *MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW + AREA_PALETTE_UNIT) = 0;
    g_GfxPalettePending                                                          = 1;
    SND_QueueSelectionEffect(EMI_CUE_ID(SND_BANK_COMMON, 0));
    Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10);
}

#include "overlays/bmagic/Effect_NextStepOnZeroTick.h"

#include "shared/Effect_PlayOnce.h"

/* func_801EEE2C */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEE70(void) {
    SYS_DISPATCH_BYTE(D_801EF418, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_DrawTexturedQuad();
    }
}

MATCH void func_801EEEE8(void) {
    PartyMember* actor;
    PartyMember* work;
    u8           count;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        actor          = g_Battle.selected_actor;
        g_Task->facing = actor->facing;
        work           = g_Task;
        work->unk_0C   = D_801EF424[work->param.unk_0B].x;
        work->unk_10   = D_801EF424[work->param.unk_0B].y;
        func_801DD350(work);
        g_Task->pos.x.fixed = actor->pos.x.fixed + g_Task->unk_0C;
        g_Task->pos.y.fixed = actor->pos.y.fixed + g_Task->unk_10;
        g_Task->pos.z.fixed = actor->pos.z.fixed + D_801EF424[g_Task->param.unk_0B].z;
        Battle_ProjectRange();
        g_Task->unk_09 = 0;
        g_Task->timer  = 0;
        g_Task->header.step += 1;
    }
}

#include "overlays/bmagic/Effect_CountUpTimersByTwoNextStep.h"

/* func_801EF0A0 */
MATCH void Effect_CountDownTimer(void) {
    BMagic_CountDownEffectTimer(1);
}

#include "overlays/bmagic/Effect_DrawTexturedQuad.h"
