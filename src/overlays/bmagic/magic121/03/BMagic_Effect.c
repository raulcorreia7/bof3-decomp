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

    TASK(PartyMember)->facing          = g_BattleEffectBattler->facing;
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
    dst                                = g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors;
    src                                = g_AreaPaletteArena->rows[AREA_PALETTE_BATL_OVR_ROW].colors;
    for (i = 1; i < 16; i++) {
        dst[i] = src[i] | PSX_COLOR_STP_BIT;
    }
    dst = g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors;
    src = g_AreaPaletteArena->rows[AREA_PALETTE_BATL_OVR_ROW].colors;
    for (i = 1; i < 16; i++) {
        dst[i + 16] = src[i + 16];
    }
    dst = g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors;
    src = g_AreaPaletteArena->rows[AREA_PALETTE_BATL_OVR_ROW].colors;
    for (i = 1; i < 16; i++) {
        dst[i + 32] = src[i + 32] | PSX_COLOR_STP_BIT;
    }
    g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors[0]  = 0;
    g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors[16] = 0;
    g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors[32] = 0;
    g_GfxPalettePending                                           = 1;
    SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0));
    TASK(PartyMember)->param.unk_0B = 0;
    TASK(PartyMember)->unk_09       = 0;
    TASK(PartyMember)->header.mode += 1;
}

#include "overlays/bmagic/shared/Effect_PlayOnIdleTick.h"

/* func_801EEE68 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void BMagic_UpdateDragonBreath(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 1), 2, g_Task);
    if (TASK(PartyMember)->header.flags != 0 && TASK(PartyMember)->header.step != 0) {
        if ((g_FrameCount & 0x7) == 0) {
            TASK(PartyMember)->unk_5D = RANDOM_MASK(1);
            TASK(PartyMember)->unk_5E = RANDOM_MASK(3);
            TASK(PartyMember)->unk_5F = RANDOM_MASK(3);
        }
        func_801F0198(TASK(PartyMember)->unk_5D + 3);
        func_801F0198(TASK(PartyMember)->unk_5E + 7);
        func_801F0198(11 - TASK(PartyMember)->unk_5F);
        func_801F06E8(4 - TASK(PartyMember)->unk_5D);
        func_801F06E8(TASK(PartyMember)->unk_5F + 8);
        func_801F06E8(12 - TASK(PartyMember)->unk_5E);
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

    timer                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        TASK(PartyMember)->facing = g_BattleEffectBattler->facing;
        Battle_CenterCamera();
        Battle_ProjectRange();
        D_1F800008[2] = TASK(PartyMember)->screen_x.value;
        D_1F800008[3] = TASK(PartyMember)->screen_y.value;
        func_800B0118();
        battler           = g_BattleEffectBattler;
        task              = g_Task;
        task->pos.x.fixed = battler->pos.x.fixed;
        task->pos.y.fixed = battler->pos.y.fixed;
        task->pos.z.fixed = battler->pos.z.fixed;
        Battle_ProjectRange();
        TASK(PartyMember)->screen_x.value += TASK(PartyMember)->unk_0C;
        TASK(PartyMember)->screen_y.value += TASK(PartyMember)->unk_10;
        D_1F800008[0]                   = TASK(PartyMember)->screen_x.value;
        D_1F800008[1]                   = TASK(PartyMember)->screen_y.value;
        TASK(PartyMember)->unk_14       = ratan2(D_1F800008[2] - D_1F800008[0], D_1F800008[3] - D_1F800008[1]);
        TASK(PartyMember)->unk_5D       = RANDOM_MASK(1);
        TASK(PartyMember)->unk_5E       = RANDOM_MASK(3);
        TASK(PartyMember)->unk_5F       = RANDOM_MASK(3);
        effect                          = g_Task;
        effect->unk_04                  = 0;
        effect->unk_0C                  = 0;
        TASK(PartyMember)->param.unk_0B = 0;
        TASK(PartyMember)->unk_09       = 16;
        TASK(PartyMember)->timer        = 0;
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF218(void) {
    u8 timer;

    BMAGIC_STEP_TIMER(timer, 8, 32);
}

MATCH void func_801EF268(void) {
    u8 timer;

    timer                           = TASK(PartyMember)->param.unk_0B + 1;
    TASK(PartyMember)->param.unk_0B = timer;
    if (timer == 8) {
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10);
        TASK(PartyMember)->header.step = TASK(PartyMember)->header.step + 1;
    }
}

#include "overlays/bmagic/shared/Effect_CountUpWorkByteAndStep.h"

MATCH void func_801EF324(void) {
    PartyMember* work;

    work = g_Task;
    if (++work->unk_0C == 0x2E) {
        work->header.step++;
    }
}

MATCH void func_801EF35C(void) {
    u8 timer;

    timer                     = TASK(PartyMember)->unk_04 - 2;
    TASK(PartyMember)->unk_04 = timer;
    if (timer == 0) {
        TASK(PartyMember)->header.step = TASK(PartyMember)->header.step + 1;
    }
}

MATCH void func_801EF3A8(void) {
    u8 ticks;
    u8 count;

    ticks = TASK(PartyMember)->param.unk_0B;
    if (ticks != 0) {
        TASK(PartyMember)->param.unk_0B = ticks - 1;
    }
    count                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        g_BattleEffectBattler->param.unk_0B = 0xFF;
        Effect_Reset();
    }
}

#ifdef NON_MATCHING
NON_MATCHING void BMagic_DrawDragonBreath(void) {
}
#else
INCLUDE_ASM(BMagic_DrawDragonBreath);
#endif

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
