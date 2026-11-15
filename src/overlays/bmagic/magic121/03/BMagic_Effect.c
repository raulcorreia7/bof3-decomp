#include "magic121_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Callback handlers[2] = {func_801EEC5C, func_801EEE08};
    SYS_DISPATCH_TASK(handlers, 1, g_Task);
}

MATCH void func_801EEC5C(void) {
    PartyMember* task;
    PartyMember* battler;
    u32          slot;
    u32          i;
    u16*         dst;
    u16*         src;

    g_Task->facing                     = g_BattleEffectBattler->facing;
    battler                            = g_BattleEffectBattler;
    task                               = g_Task;
    task->pos.x.fixed                  = battler->pos.x.fixed;
    task->pos.y.fixed                  = battler->pos.y.fixed;
    task->pos.z.fixed                  = battler->pos.z.fixed;
    slot                               = Battle_AllocEffect(1, 90) & BYTE_MASK;
    g_BattleEffects[slot].target.party = g_Task;
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].arg.unk_09   = 4;
    /* Copies the first three colour rows of arena palette 26 into the work copy, STP set on rows 0 and 2. */
    dst                                = MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW);
    src                                = MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW);
    for (i = 1; i < 16; i++) {
        dst[i] = src[i] | 0x8000;
    }
    dst = MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW);
    src = MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW);
    for (i = 1; i < 16; i++) {
        dst[i + 16] = src[i + 16];
    }
    dst = MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW);
    src = MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW);
    for (i = 1; i < 16; i++) {
        dst[i + 32] = src[i + 32] | 0x8000;
    }
    MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW)[0]  = 0;
    MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW)[16] = 0;
    MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW)[32] = 0;
    g_GfxPalettePending                                         = 1;
    SND_QueueSelectionEffect(EMI_CUE_ID(SND_BANK_COMMON, 0));
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 0;
    g_Task->header.mode += 1;
}

#include "overlays/bmagic/Effect_PlayOnIdleTick.h"

/* func_801EEE68 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void BMagic_UpdateDragonBreath(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 1), 2, g_Task);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        if ((g_FrameCount & 0x7) == 0) {
            g_Task->unk_5D = RANDOM_MASK(1);
            g_Task->unk_5E = RANDOM_MASK(3);
            g_Task->unk_5F = RANDOM_MASK(3);
        }
        func_801F0198(g_Task->unk_5D + 3);
        func_801F0198(g_Task->unk_5E + 7);
        func_801F0198(11 - g_Task->unk_5F);
        func_801F06E8(4 - g_Task->unk_5D);
        func_801F06E8(g_Task->unk_5F + 8);
        func_801F06E8(12 - g_Task->unk_5E);
        BMagic_DrawDragonBreath();
    }
}

/* Aim the dragon breath: stage the target screen point, project the caster, step its screen
 * point once and face the shot from there to the target. */
MATCH void func_801EF03C(void) {
    PartyMember* task;
    PartyMember* battler;
    PartyMember* work;
    PartyMember* effect;
    u8           timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        g_Task->facing = g_BattleEffectBattler->facing;
        Battle_CenterCamera();
        Battle_ProjectRange();
        D_1F800008[2] = g_Task->unk_2E.half;
        D_1F800008[3] = g_Task->unk_30.half;
        func_800B0118();
        battler           = g_BattleEffectBattler;
        task              = g_Task;
        task->pos.x.fixed = battler->pos.x.fixed;
        task->pos.y.fixed = battler->pos.y.fixed;
        task->pos.z.fixed = battler->pos.z.fixed;
        Battle_ProjectRange();
        g_Task->unk_2E.half += g_Task->unk_0C;
        g_Task->unk_30.half += g_Task->unk_10;
        D_1F800008[0]        = g_Task->unk_2E.half;
        D_1F800008[1]        = g_Task->unk_30.half;
        g_Task->unk_14       = ratan2(D_1F800008[2] - D_1F800008[0], D_1F800008[3] - D_1F800008[1]);
        g_Task->unk_5D       = RANDOM_MASK(1);
        g_Task->unk_5E       = RANDOM_MASK(3);
        g_Task->unk_5F       = RANDOM_MASK(3);
        effect               = g_Task;
        effect->unk_04       = 0;
        effect->unk_0C       = 0;
        g_Task->param.unk_0B = 0;
        g_Task->unk_09       = 16;
        g_Task->timer        = 0;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF218(void) {
    u8 timer;

    timer         = g_Task->timer + 8;
    g_Task->timer = timer;
    if (timer == 32) {
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void func_801EF268(void) {
    u8 timer;

    timer                = g_Task->param.unk_0B + 1;
    g_Task->param.unk_0B = timer;
    if (timer == 8) {
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10);
        g_Task->header.step = g_Task->header.step + 1;
    }
}

#include "overlays/bmagic/Effect_CountUpWorkByteAndStep.h"

MATCH void func_801EF324(void) {
    PartyMember* work;

    work = g_Task;
    if (++work->unk_0C == 0x2E) {
        work->header.step++;
    }
}

MATCH void func_801EF35C(void) {
    u8 timer;

    timer          = g_Task->unk_04 - 2;
    g_Task->unk_04 = timer;
    if (timer == 0) {
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void func_801EF3A8(void) {
    u8 ticks;
    u8 count;

    ticks = g_Task->param.unk_0B;
    if (ticks != 0) {
        g_Task->param.unk_0B = ticks - 1;
    }
    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        g_BattleEffectBattler->param.unk_0B = 0xFF;
        func_801E5988();
    }
}

INCLUDE_ASM(BMagic_DrawDragonBreath);

MATCH void func_801F0198(u8 count) {
    LINE_F2* line;
    s32      tpage;
    s32      i;
    s32      run;
    s32      wave;

    MAGIC121_DRAW_BOLT(count, 0x400);
}

MATCH void func_801F06E8(u8 count) {
    LINE_F2* line;
    s32      tpage;
    s32      i;
    s32      run;
    s32      wave;

    MAGIC121_DRAW_BOLT(count, -0x400);
}
