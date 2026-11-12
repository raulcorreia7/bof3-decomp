#include "magic225_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC14(void) {
    Magic225Steps handlers = D_801EEC04;
    PartyMember*  saved_task;
    PartyMember*  saved_battler;
    u8            i;

    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.mode);

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        if (D_801F03BC[i].header.flags & BMAGIC_EFFECT_IN_USE) {
            saved_task            = g_Task;
            saved_battler         = g_BattleEffectBattler;
            g_Task                = (PartyMember*)&D_801F03BC[i];
            g_BattleEffectBattler = D_801F03BC[i].target.party;
            func_801EFE0C();
            g_BattleEffectBattler = saved_battler;
            g_Task                = saved_task;
        }
    }
}

/* Clears the effect slots, centers the camera, claims the first effect slot and reloads palette rows 2 and 26 of
 * the work copy. */
MATCH void func_801EED28(void) {
    u16*         dst;
    u16*         src;
    u16*         row_dst;
    u16*         row_src;
    u16          i;
    u32          slot;
    PartyMember* work;

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        BMAGIC_EFFECT_SLOTS[i].header.flags = 0;
        BMAGIC_EFFECT_SLOTS[i].header.mode  = 0;
        BMAGIC_EFFECT_SLOTS[i].header.step  = 0;
    }
    Battle_CenterCamera();
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 24;
    g_Task->header.mode += 1;
    slot                               = Battle_AllocEffect(1, 101) & BYTE_MASK;
    work                               = g_Task;
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].target.party = work;
    g_Task->param.unk_0B += 1;
    i       = 0;
    row_dst = MEM_PTR(u16, AREA_PALETTE_WORK + 2 * AREA_PALETTE_ROW);
    row_src = MEM_PTR(u16, AREA_PALETTE_ARENA_33C00);
    dst     = MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW);
    src     = MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW);
    for (; i < 256; i++) {
        row_dst[i] = row_src[i];
        dst[i]     = src[i];
    }
    g_GfxPalettePending = 1;
    SND_QueueSelectionFx(EMI_CUE_ID(SND_BANK_COMMON, 1));
}

MATCH void func_801EEE8C(void) {
    u8           count;
    u8           i;
    u8           slot;
    PartyMember* work;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (count == 0) {
        i = 0;
        do {
            SND_QueueSelectionFx(EMI_CUE_ID(SND_BANK_COMMON, 0x00));
            slot = BMagic_AllocEffect();
            if (slot != GAME_NONE) {
                work                                   = g_Task;
                BMAGIC_EFFECT_SLOTS[slot].header.mode  = 0;
                BMAGIC_EFFECT_SLOTS[slot].unk_0B       = i;
                BMAGIC_EFFECT_SLOTS[slot].arg.unk_09   = ((i & BYTE_MASK) * 4) + 8;
                BMAGIC_EFFECT_SLOTS[slot].target.party = work;
                g_Task->param.unk_0B += 1;
            }
            i++;
        } while (i < 16);
        g_Task->header.mode += 1;
    }
}

INCLUDE_ASM(func_801EEF8C);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EF2D8 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF31C(void) {
    g_ScriptTable = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(D_801F0398, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801EFCA0();
        func_801EF7D4(0x30, 0x10, 0x52, 0);
        func_801EF7D4(0x12C, 0, 0x80, 1);
        func_801EF7D4(0x40, 0xF0, 0x6C, 2);
        func_801EF7D4(0x140, 0xF0, 0x5C, 3);
    }
    g_ScriptTable = AREA_SCRIPT_TABLE;
}

MATCH void func_801EF404(void) {
    s32 i;

    BMAGIC_MARK_SELECTED_SIDE(2);
    if (g_Battle.encounter == 55) {
        g_Task->unk_29 = 7;
    } else {
        g_Task->unk_29 = 3;
    }
    g_Task->param.unk_0B = 1;
    g_Task->unk_09       = 0;
    g_Task->timer        = 0;
    g_Task->header.step += 1;
}

MATCH void func_801EF578(void) {
    u8 timer_next;

    timer_next    = g_Task->timer + 2;
    g_Task->timer = timer_next;
    if ((timer_next & BYTE_MASK) == 0x10) {
        g_Task->param.unk_0B = 0;
        g_Task->header.step += 1;
    }
}

#include "overlays/bmagic/Effect_CountUpAndStep.h"

MATCH void func_801EF628(void) {
    if (g_BattleEffectBattler->param.unk_0B < 2U) {
        g_Task->param.unk_0B = 1;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF67C(void) {
    s32 i;

    if (g_Task->unk_09 != 0) {
        g_Task->unk_09 -= 2;
    }
    if (--g_Task->timer == 0) {
        BMAGIC_MARK_SELECTED_SIDE(4);
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF7D4);

INCLUDE_ASM(func_801EFCA0);

MATCH void func_801EFE0C(void) {
    SYS_DISPATCH_TASK(D_801F03AC, 1, g_Task);
}

MATCH void func_801EFE50(void) {
    g_ScriptTable = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(D_801F03AC + 1, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_8014D290();
    }
    g_ScriptTable = AREA_SCRIPT_TABLE;
}

INCLUDE_ASM(func_801EFEE8);

MATCH void func_801F0140(void) {
    s32 value;

    Actor_StepAnimLoop();
    g_Task->scale.x += 0x800;
    g_Task->scale.y += 0x800;
    g_Task->pos.x.fixed += rsin(g_Task->unk_14) * g_Task->unk_0C;
    g_Task->pos.y.fixed += rcos(g_Task->unk_14) * g_Task->unk_0C;
    if (g_FrameCount & 0x1) {
        value = g_Task->unk_0C;
        if (value == 4) {
            g_Task->header.step += 1;
            return;
        }
        g_Task->unk_0C = value - 1;
    }
}

MATCH void func_801F021C(void) {
    Actor_StepAnimLoop();
    g_Task->scale.x += 0x800;
    g_Task->scale.y += 0x800;
    g_Task->pos.x.fixed += rsin(g_Task->unk_14) << 2;
    g_Task->pos.y.fixed += rcos(g_Task->unk_14) << 2;
    if (--g_Task->unk_09 == 0) {
        g_BattleEffectBattler->param.unk_0B--;
        Actor_Clear();
    }
}

/* func_801F02D4 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801F0338 */
#include "overlays/bmagic/Actor_Clear.h"
