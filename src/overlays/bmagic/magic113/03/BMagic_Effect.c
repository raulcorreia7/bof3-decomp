#include "magic113_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC24);
INCLUDE_ASM(func_801EECE0);

INCLUDE_ASM(func_801EEE24);

MATCH void func_801EF000(void) {
    u32           slot;
    PartyBattler* work;
    u8            facing;

    if (g_SpadWork->word_08.byte.unk_0B == 3) {
        slot                                       = Battle_AllocEffect(1, 3) & BYTE_MASK;
        work                                       = g_SpadWork;
        g_BattleEffects[slot].unk_01               = 1;
        g_BattleEffects[slot].target.party         = work;
        facing                                     = D_801EB4E0->word_08.byte.facing_08;
        g_BattleEffects[slot].unk_09               = 0;
        g_BattleEffects[slot].unk_0A               = 0;
        g_BattleEffects[slot].unk_08               = (facing + 2) & 3;
        g_BattleEffects[slot].unk_34               = g_SpadWork->coord_x_34;
        g_BattleEffects[slot].unk_38               = g_SpadWork->coord_y_38;
        g_BattleEffects[slot].word_3C.half.span_3E = g_SpadWork->word_3C.half.span_3E;
        g_SpadWork->step_01 += 1;
    }
}

INCLUDE_ASM(func_801EF0F0);

INCLUDE_ASM(func_801EF1F8);

MATCH void func_801EF35C(void) {
    if (g_SpadWork->word_08.byte.unk_0B == 6) {
        g_SpadWork->word_08.byte.unk_0B = 0x84;
        g_SpadWork->step_01 += 1;
    }
}

MATCH void func_801EF3A0(void) {
    PartyBattler* work;

    work = SP_REF(PartyBattler*, 0x44u);
    if (work->word_08.byte.unk_0B == 0x80) {
        work->step_01 = (u8)(work->step_01 + 1);
    }
}

#include "overlays/bmagic/Effect_CountDownAndPlay.h"

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EF4F0);

MATCH void func_801EF75C(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

INCLUDE_ASM(func_801EF7A0);

MATCH void func_801EF844(void) {
    u8 temp_v1;

    temp_v1                         = g_SpadWork->word_08.byte.unk_09 + 1;
    g_SpadWork->word_08.byte.unk_09 = temp_v1;
    if ((temp_v1 & 0xFF) == 0x21) {
        D_801EB4E0->word_08.byte.unk_0B = 3;
        g_SpadWork->unk_02 += 1;
    }
}

MATCH void func_801EF8A4(void) {
    PartyBattler* active;
    PartyBattler* work;

    active = BATTLE_ACTIVE_WORK;
    if (active->word_08.byte.unk_0B == 132) {
        work         = SP_REF(PartyBattler*, 0x44u);
        work->unk_02 = work->unk_02 + 1;
    }
}

MATCH void func_801EF8E4(void) {
    Effect_CountUpTimer();
}

INCLUDE_ASM(func_801EF944);

MATCH void func_801EFC28(void) {
    SYS_DISPATCH_BYTE(D_801F0BC0, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0) {
        Effect_SetActorMatrix();
        func_801EFDA0();
        PopMatrix();
    }
}

MATCH void func_801EFCA0(void) {
    u8 temp_v1;

    temp_v1                         = g_SpadWork->word_08.byte.unk_09 + 1;
    g_SpadWork->word_08.byte.unk_09 = temp_v1;
    if ((temp_v1 & 0xFF) == 0x28) {
        D_801EB4E0->word_08.byte.unk_0B = 4;
        g_SpadWork->unk_02 += 1;
    }
}

MATCH void func_801EFD00(void) {
    PartyBattler* active;
    PartyBattler* work;

    active = BATTLE_ACTIVE_WORK;
    if (active->word_08.byte.unk_0B == 132) {
        work         = SP_REF(PartyBattler*, 0x44u);
        work->unk_02 = work->unk_02 + 1;
    }
}

MATCH void func_801EFD40(void) {
    Effect_CountUpTimer();
}

INCLUDE_ASM(func_801EFDA0);

MATCH void func_801F0140(void) {
    SYS_DISPATCH_BYTE(D_801F0BCC, g_SpadWork->unk_02);
    if (g_SpadWork->flags_00 != 0) {
        Effect_SetActorMatrix();
        func_801F02CC();
        PopMatrix();
    }
}

MATCH void func_801F01B8(void) {
    u8 temp_v1;

    temp_v1                         = g_SpadWork->word_08.byte.unk_09 + 1;
    g_SpadWork->word_08.byte.unk_09 = temp_v1;
    if ((temp_v1 & 0xFF) == 0x31) {
        D_801EB4E0->word_08.byte.unk_0B = 5;
        g_SpadWork->unk_02 += 1;
    }
}

MATCH void func_801F0218(void) {
    if (D_801EB4E0->word_08.byte.unk_0B == 0x84) {
        SND_PlayCue(0x103U);
        g_SpadWork->unk_02 += 1;
    }
}

MATCH void func_801F026C(void) {
    PartyBattler* work;
    u8            next;

    work                        = g_SpadWork;
    next                        = work->word_08.byte.timer_0A + 1;
    work->word_08.byte.timer_0A = next;
    if (next == 0x10) {
        BATTLE_ACTIVE_WORK->word_08.byte.unk_0B--;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801F02CC);

INCLUDE_ASM(func_801F0764);

#include "overlays/bmagic/Effect_CountDownTimerStep.h"

INCLUDE_ASM(func_801F08B4);

MATCH void func_801F0A80(void) {
    u8 value;

    if (func_8014DAEC() & 0xFF) {
        value                           = g_SpadWork->word_08.byte.unk_09 + 1;
        g_SpadWork->word_08.byte.unk_09 = value;
        if ((u32)(value & 0xFF) >= 3U) {
            D_801EB4E0->word_08.byte.unk_0B += 1;
            func_801E5988();
            return;
        }
        g_SpadWork->unk_2A = ((u8)g_SpadWork->unk_2A + 1) & 1;
        Actor_SelectScript(g_SpadWork->word_08.byte.unk_0B);
        func_8014D290();
        if (g_SpadWork->word_08.byte.unk_0B == 0) {
            if (g_SpadWork->word_08.byte.unk_09 == 1) {
                SND_PlayCue(0x104U);
                return;
            }
            SND_PlayCue(0x100U);
        }
    } else {
        func_8014D290();
    }
}
