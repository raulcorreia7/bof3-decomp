#include "magic107_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Callback table[2] = {func_801EEC5C, func_801EED40};

    table[SP_REF(u8*, 0x44)[1]]();
}

/* The g_SpadWork base for the span read must be fetched before the D_801EC364 store and the
 * word_3C member read kept in place; both inline reads or an early span local shift the reload. */
MATCH void func_801EEC5C(void) {
    PartyBattler* work;
    s32           scroll_x;
    u32           offset;

    func_800AFD9C();
    offset                                      = (Battle_AllocEffect(1, 0x19) & BYTE_MASK) * BATTLE_EFFECT_STRIDE;
    FIELD(PartyBattler*, D_801EC3A4, offset)    = g_SpadWork;
    FIELD(u8, D_801EC338, offset)               = ((PartyBattler*)D_8014637C)->word_08.byte.facing_08;
    scroll_x                                    = g_AreaScrollTargetX;
    work                                        = g_SpadWork;
    FIELD(s32, D_801EC364, offset)              = scroll_x;
    FIELD(s32, D_801EC368, offset)              = g_AreaScrollTargetY;
    FIELD(s32, D_801EC36C, offset)              = work->word_3C.word + 0x04000000;
    SND_QueueSelectionFx(0x100);
    g_SpadWork->word_08.byte.unk_0B             = 0;
    g_SpadWork->step_01 += 1;
}

#include "overlays/bmagic/Effect_PlayOnIdleTick.h"

MATCH void func_801EEDA0(void) {
    SYS_DISPATCH_BYTE(D_801F048C, g_SpadWork->step_01);
    if (g_SpadWork->flags_00 != 0) {
        func_801EEFD4();
        func_801EF0E4();
        func_801EF544();
        func_801EF290();
        PopMatrix();
        Effect_SetActorMatrixQuarterRoll();
        func_801F01AC();
        func_801EFAE0();
        func_801EFEA8();
        PopMatrix();
    }
}

MATCH void func_801EEE50(void) {
    g_SpadWork->word_08.byte.unk_0B   = 0;
    g_SpadWork->word_08.byte.unk_09   = 0;
    g_SpadWork->word_08.byte.timer_0A = 0;
    g_SpadWork->step_01++;
}

MATCH void func_801EEEA0(void) {
    g_SpadWork->word_08.byte.unk_09 += 1;
    g_SpadWork->word_08.byte.timer_0A += 1;
    if (g_SpadWork->word_08.byte.unk_09 == 0x20) {
        g_SpadWork->step_01 = g_SpadWork->step_01 + 1;
    }
}

#include "overlays/bmagic/Effect_AdvanceOnTick.h"

MATCH void func_801EEF5C(void) {
    PartyBattler* active;

    g_SpadWork->word_08.byte.unk_09   = g_SpadWork->word_08.byte.unk_09 + 1;
    g_SpadWork->word_08.byte.timer_0A = g_SpadWork->word_08.byte.timer_0A - 1;
    if (g_SpadWork->word_08.byte.timer_0A == 0) {
        active                      = BATTLE_ACTIVE_WORK;
        active->word_08.byte.unk_0B = 255;
        func_801E5988();
    }
}

MATCH void func_801EEFD4(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;
    u8      angle;

    PushMatrix();
    if (g_SpadWork->word_08.byte.facing_08 & 1) {
        rot.vx = 0;
        angle  = g_SpadWork->word_08.byte.unk_09 & 0x3F;
        rot.vy = (u32)rsin(angle << 6) >> 3;
        rot.vz = 0;
    } else {
        angle  = g_SpadWork->word_08.byte.unk_09 & 0x3F;
        rot.vx = (u32)rsin(angle << 6) >> 3;
        rot.vy = 0;
        rot.vz = 0;
    }
    BMAGIC_PROJECT_ACTOR_MATRIX(g_SpadWork);
}

INCLUDE_ASM(func_801EF0E4);

INCLUDE_ASM(func_801EF290);

INCLUDE_ASM(func_801EF544);

#include "overlays/bmagic/Effect_SetActorMatrixQuarterRoll.h"

INCLUDE_ASM(func_801EFAE0);

INCLUDE_ASM(func_801EFEA8);

INCLUDE_ASM(func_801F01AC);
