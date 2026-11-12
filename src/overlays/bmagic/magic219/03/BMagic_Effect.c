#include "magic219_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC14(void) {
    Magic219Steps handlers = D_801EEC04;
    PartyMember*  saved_task;
    PartyMember*  saved_battler;
    u8            i;

    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.mode);

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        if (D_801EFA14[i].header.flags & BMAGIC_EFFECT_IN_USE) {
            saved_task            = g_Task;
            saved_battler         = g_BattleEffectBattler;
            g_Task                = (PartyMember*)&D_801EFA14[i];
            g_BattleEffectBattler = D_801EFA14[i].target.party;
            BMagic_DispatchEffectMode();
            g_BattleEffectBattler = saved_battler;
            g_Task                = saved_task;
        }
    }
}

/* Clears the effect slots, centers the camera and reloads palette rows 2 and 26 of the work copy with the STP bit
 * set. */
MATCH void func_801EED28(void) {
    u16* dst;
    u16* src;
    u16* row_dst;
    u16* row_src;
    u16  i;

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        BMAGIC_EFFECT_SLOTS[i].header.flags = 0;
        BMAGIC_EFFECT_SLOTS[i].header.mode  = 0;
        BMAGIC_EFFECT_SLOTS[i].header.step  = 0;
    }
    Battle_CenterCamera();
    g_Task->param.unk_0B = 0;
    g_Task->header.mode += 1;
    i       = 0;
    row_dst = MEM_PTR(u16, AREA_PALETTE_WORK + 2 * AREA_PALETTE_ROW);
    row_src = MEM_PTR(u16, AREA_PALETTE_ARENA_33C00);
    dst     = MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW);
    src     = MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW);
    for (; i < 256; i++) {
        row_dst[i] = row_src[i] | 0x8000;
        dst[i]     = src[i] | 0x8000;
    }
    *MEM_PTR(u16, AREA_PALETTE_WORK + 2 * AREA_PALETTE_ROW)  = *MEM_PTR(u16, AREA_PALETTE_ARENA_33C00);
    *MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW) = *MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW);
    g_GfxPalettePending                                      = 1;
    SND_QueueSelectionFx(EMI_CUE_ID(SND_BANK_COMMON, 0));
}

MATCH void func_801EEE50(void) {
    u8 i;
    u8 slot;

    for (i = 0; i < 24; i++) {
        slot = BMagic_AllocEffect();
        if (slot != GAME_NONE) {
            volatile void* task           = g_Task;
            D_801EFA14[slot].header.mode  = 0;
            D_801EFA14[slot].unk_0B       = i;
            D_801EFA14[slot].target.party = (PartyMember*)task;
            D_801EFA14[slot].arg.unk_09   = D_801EF9E8[i] + (rand() & 0x1) + 1;
            g_Task->param.unk_0B++;
        }
    }
    g_Task->unk_09 = 8;
    g_Task->header.mode++;
}

MATCH void func_801EEF54(void) {
    u8 timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        SND_QueueSelectionFx(0x101);
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10);
        g_Task->header.mode = g_Task->header.mode + 1;
    }
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EF024 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF068(void) {
    g_ScriptTable = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(D_801EFA04, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_8014D290();
        Effect_SetActiveActorMatrix();
        func_801EF71C();
        PopMatrix();
    }
    g_ScriptTable = AREA_SCRIPT_TABLE;
}

INCLUDE_ASM(func_801EF118);

INCLUDE_ASM(func_801EF3CC);

MATCH void func_801EF530(void) {
    PartyMember* work = g_Task;

    work->unk_25      = 0x1D;
    work->pos.x.fixed = work->unk_0C;
    work->pos.y.fixed = work->unk_10;
    work->pos.z.fixed = work->unk_14;
    g_Task->unk_26    = 0;
    g_Task->unk_27    = 0x1A;
    g_Task->unk_2B    = 1;
    Actor_SelectScript(1);
    g_Task->unk_09 = 0xE;
    g_Task->timer  = 12;
    g_Task->header.step += 1;
}

MATCH void func_801EF5DC(void) {
    u8 timer_next;
    u8 count;

    Actor_StepAnimOnce();
    timer_next = g_Task->timer;
    if (timer_next != 0) {
        g_Task->timer = timer_next - 1;
    }
    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        Actor_Clear();
    }
}

#include "overlays/bmagic/Effect_SetActiveActorMatrix.h"

INCLUDE_ASM(func_801EF71C);

/* func_801EF934 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801EF998 */
#include "overlays/bmagic/Actor_Clear.h"
