#include "magic169_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC38);

INCLUDE_ASM(func_801EED8C);

INCLUDE_ASM(func_801EEEB0);

MATCH void func_801EEFE0(void) {
    u8 timer;

    if (g_Task->param.unk_0B == 0) {
        timer          = g_Task->unk_09 - 1;
        g_Task->unk_09 = timer;
        if (!(timer & 0xFF)) {
            g_Task->header.mode += 1;
        }
    }
}

#include "shared/Effect_StartPlaying.h"

INCLUDE_ASM(func_801EF070);

MATCH void func_801EF210(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectModes, TASK_BYTES[1]);
}

MATCH void func_801EF254(void) {
    BMagicEffectFuncs handlers;

    BMAGIC_DISPATCH_STEP_HANDLERS(D_801EEC14, header.step);
}

INCLUDE_ASM(func_801EF2CC);

MATCH void func_801EF444(void) {
    PartyBattler* battler;
    u8            timer;
    PartyBattler* work;

    work         = g_Task;
    timer        = work->unk_09 - 1;
    work->unk_09 = timer;
    battler      = &g_BattlePartyBattlers[work->unk_04];
    if (!(timer & BYTE_MASK)) {
        GFX_FreePaletteFadeTarget(battler);
        g_Task->timer  = GFX_AllocPaletteFade(battler, 0, 0, 0, 1);
        g_Task->unk_09 = 8;
        g_Task->header.step += 1;
    }
}

INCLUDE_ASM(func_801EF4FC);

#include "overlays/bmagic/Effect_NextStepUnderTickLimit.h"

INCLUDE_ASM(func_801EF688);

MATCH void func_801EF7D0(void) {
    if (g_Task->param.unk_0B == 0) {
        BATTLE_ACTIVE_WORK->param.unk_0B -= 1;
        if (func_801DB524(g_Task->unk_04) & 0xFF) {
            func_800A9820(g_Task->unk_04);
        }
        func_801E5988();
    }
}

MATCH void func_801EF860(void) {
    SYS_DISPATCH_TASK(D_801F0420, 1, g_Task);
}

INCLUDE_ASM(func_801EF8A4);

MATCH void func_801EFA18(void) {
    s32  phase;
    s32  speed;
    s16* angle_cell;
    u8   count;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (count == 0) {
        g_Task->unk_0C      = 8;
        angle_cell          = &D_1F800004;
        phase               = g_Task->param.unk_0B & 0xF;
        *angle_cell         = phase << 8;
        g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + rsin(*angle_cell) * g_Task->unk_0C;
        g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + rcos(*angle_cell) * g_Task->unk_0C;
        g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed + 0x800000;
        speed               = ((rand() & 3) << 20) + 0x200000;
        g_Task->unk_14      = speed;
        g_Task->unk_20      = speed / 16;
        g_Task->unk_5D      = (rand() & 7) + 6;
        g_Task->unk_5E      = (rand() & 7) + 6;
        g_Task->unk_5F      = (rand() & 7) + 6;
        g_Task->unk_09      = 0;
        g_Task->timer       = 0x10;
        g_Task->header.step++;
    }
}

MATCH void func_801EFBC4(void) {
    s32  phase;
    s32  b;
    s16* angle_cell;
    u8   count;

    angle_cell = &D_1F800004;
    phase      = g_Task->param.unk_0B & 0xF;
    g_Task->unk_0C += 2;
    *angle_cell         = phase << 8;
    g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + rsin(*angle_cell) * g_Task->unk_0C;
    g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + rcos(*angle_cell) * g_Task->unk_0C;
    if (g_Task->unk_20 < g_Task->unk_14) {
        b              = g_Task->unk_14 - g_Task->unk_20;
        g_Task->unk_14 = b;
        g_Task->pos.z.fixed += b;
    }
    count          = g_Task->unk_09 + 2;
    g_Task->unk_09 = count;
    if (count == 0x10) {
        g_Task->header.step++;
    }
}

MATCH void func_801EFCF4(void) {
    s32  phase;
    s32  b;
    s16* angle_cell;
    u8   count;

    angle_cell = &D_1F800004;
    phase      = g_Task->param.unk_0B & 0xF;
    g_Task->unk_0C += 1;
    *angle_cell         = phase << 8;
    g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + rsin(*angle_cell) * g_Task->unk_0C;
    g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + rcos(*angle_cell) * g_Task->unk_0C;
    if (g_Task->unk_20 < g_Task->unk_14) {
        b              = g_Task->unk_14 - g_Task->unk_20;
        g_Task->unk_14 = b;
        g_Task->pos.z.fixed += b;
    }
    if (g_FrameCount & 1) {
        count          = g_Task->unk_09 - 1;
        g_Task->unk_09 = count;
        if (count == 0) {
            g_BattleEffectBattler->param.unk_0B -= 1;
            Actor_Clear();
        }
    }
}

INCLUDE_ASM(func_801EFE3C);

INCLUDE_ASM(func_801F0090);

/* func_801F0368 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801F03CC */
MATCH void Actor_Clear(void) {
    BMagic_ResetLocalWork();
}
