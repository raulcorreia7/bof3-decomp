#include "magic154_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC24.h"

#include "overlays/bmagic/Effect_CopyActiveBattlerToSlot.h"

MATCH void func_801EEC90(void) {
    PartyMember* work;
    u32          slot;
    u32          i;
    u16*         dst;
    u16*         src;

    func_800AEF98(12, 2);
    slot = Battle_AllocEffect(1, 82) & BYTE_MASK;
    Effect_CopyActiveBattlerToSlot(slot);
    i                                   = 0;
    dst                                 = MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW);
    src                                 = MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW);
    work                                = g_Task;
    g_BattleEffects[slot].header.mode   = 1;
    g_BattleEffects[slot].unk_06        = 1;
    g_BattleEffects[slot].header.step   = 0;
    g_BattleEffects[slot].handler_index = 82;
    g_BattleEffects[slot].target.party  = work;
    for (; i < 16; i++) {
        *dst++ = *src++;
    }
    g_GfxPalettePending = 1;
    g_BattleEffectBattler->header.flags |= 0x40;
    g_Task->param.unk_0B = 1;
    g_Task->unk_09       = 1;
    g_Task->header.mode++;
}

MATCH void func_801EEE94(void) {
    u32          i;
    s8           anchor;
    u8           slot;
    PartyMember* actor;
    PartyMember* work;

    if (g_Task->param.unk_0B == 0) {
        actor          = g_Battle.selected_actor;
        g_Task->facing = actor->facing;
        g_Task->unk_0C = 0;
        g_Task->unk_10 = -TO_COORD_HALF(1);
        func_801DD350(g_Task);
        g_Task->pos.x.fixed = actor->pos.x.fixed + g_Task->unk_0C;
        g_Task->pos.y.fixed = actor->pos.y.fixed + g_Task->unk_10;
        g_Task->pos.z.fixed = actor->pos.z.fixed;
        SND_QueueSelectionFx(EMI_CUE_ID(SND_BANK_COMMON, 0x00));
        for (i = 0, anchor = 1; i < 6; i++) {
            slot                               = Battle_AllocEffect(1, 82) & BYTE_MASK;
            work                               = g_Task;
            g_BattleEffects[slot].header.mode  = 0;
            g_BattleEffects[slot].unk_0B       = i;
            g_BattleEffects[slot].arg.unk_09   = anchor;
            g_BattleEffects[slot].target.party = work;
            g_Task->param.unk_0B += 1;
            anchor += 3;
        }
        g_Task->header.mode += 1;
    }
}

MATCH void func_801EEFE0(void) {
    if (g_Task->unk_09 == 0) {
        func_800AEF98(4, 0);
        BATTLE_ACTIVE_WORK->header.flags &= ~PARTY_MEMBER_FLAG_HANDLER_BUSY;
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10U);
        g_Task->header.mode += 1;
    }
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EF0C0 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF104(void) {
    GFX_AddDitheredDrawMode(3, getTPage(0, 1, 320, 256));
    g_ScriptTable = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(g_BMagicEffectModes + 2, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_8014D290();
    }
    g_ScriptTable = AREA_SCRIPT_TABLE;
}

MATCH void func_801EF1EC(void) {
    u8 timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        g_Task->facing = g_BattleEffectBattler->facing;
        g_Task->unk_0C = 0;
        g_Task->unk_10 = g_Task->param.unk_0B << 0xF;
        func_801DD350(g_Task);
        g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + g_Task->unk_0C;
        g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + g_Task->unk_10;
        g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;
        g_Task->scale.x     = 0x8000;
        g_Task->scale.y     = 0x8000;
        g_Task->unk_48      = 2;
        g_Task->unk_25      = 0x1D;
        g_Task->unk_26      = 0;
        g_Task->unk_27      = 0xA0;
        g_Task->unk_28      = 0;
        g_Task->unk_2A      = g_Task->facing & 0x1;
        g_Task->unk_29      = 3;
        g_Task->unk_24      = 4;
        g_Task->unk_2C.half = 0;
        g_Task->unk_2B      = 0;
        Actor_SelectScript(0U);
        Actor_StepAnimLoop();
        g_Task->unk_09 = 0;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF380(void) {
    PartyMember* work;
    u8           count;

    work = g_Task;
    work->scale.x += 0x4000;
    count        = work->unk_09 + 1;
    work->unk_09 = count;
    work->scale.y += 0x8000;
    if (count == 4) {
        g_Task->header.step++;
    }
}

MATCH void func_801EF3E4(void) {
    PartyMember* work = g_Task;
    u8           timer;
    work->scale.x -= 0x4000;
    timer        = work->unk_09 - 1;
    work->unk_09 = timer;
    work->scale.y -= 0x8000;
    if (timer == 0) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
    }
}

MATCH void func_801EF454(void) {
    g_Task->scale.y -= 0x1000;
    if ((s8)g_Task->unk_5F == -0x80) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
    }
}

MATCH void func_801EF4B4(void) {
    Magic154Steps handlers = D_801EEC14;

    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        func_8014D290();
    }
}

#include "overlays/bmagic/Effect_SetDuration.h"

MATCH void func_801EF58C(void) {
    u8 timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        Actor_StepAnimOnce();
        func_800AFC98(2, 4);
        g_BattleEffectBattler->param.unk_0B -= 1;
        g_Task->header.step += 1;
    } else if (Actor_StepAnimOnce() & BYTE_MASK) {
        func_800AFC98(2, 4);
        g_Task->unk_09 = 0;
        g_BattleEffectBattler->param.unk_0B -= 1;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF648(void) {
    if (Actor_StepAnimOnce() & BYTE_MASK) {
        BATTLE_ACTIVE_WORK->unk_09--;
        g_Task->header.step++;
    }
}

MATCH void func_801EF6AC(void) {
    func_801E5988();
}
