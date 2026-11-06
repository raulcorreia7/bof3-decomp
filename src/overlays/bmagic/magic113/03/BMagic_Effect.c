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

    if (g_Task->unk_0B == 3) {
        slot                                   = Battle_AllocEffect(1, 3) & BYTE_MASK;
        work                                   = g_Task;
        g_BattleEffects[slot].mode             = 1;
        g_BattleEffects[slot].target.party     = work;
        facing                                 = D_801EB4E0->facing;
        g_BattleEffects[slot].unk_09           = 0;
        g_BattleEffects[slot].unk_0A           = 0;
        g_BattleEffects[slot].unk_08           = (facing + 2) & 3;
        g_BattleEffects[slot].pos.x            = g_Task->pos.x;
        g_BattleEffects[slot].pos.y            = g_Task->pos.y;
        COORD_INT(g_BattleEffects[slot].pos.z) = COORD_INT(g_Task->pos.z);
        g_Task->mode += 1;
    }
}

INCLUDE_ASM(func_801EF0F0);

INCLUDE_ASM(func_801EF1F8);

MATCH void func_801EF35C(void) {
    if (g_Task->unk_0B == 6) {
        g_Task->unk_0B = 0x84;
        g_Task->mode += 1;
    }
}

MATCH void func_801EF3A0(void) {
    PartyBattler* work;

    work = g_Task;
    if (work->unk_0B == 0x80) {
        work->mode = (work->mode + 1);
    }
}

#include "overlays/bmagic/Effect_CountDownAndPlay.h"

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EF4F0);

MATCH void func_801EF75C(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_Task->mode);
}

INCLUDE_ASM(func_801EF7A0);

MATCH void func_801EF844(void) {
    u8 temp_v1;

    temp_v1        = g_Task->unk_09 + 1;
    g_Task->unk_09 = temp_v1;
    if ((temp_v1 & 0xFF) == 0x21) {
        D_801EB4E0->unk_0B = 3;
        g_Task->step += 1;
    }
}

MATCH void func_801EF8A4(void) {
    PartyBattler* active;
    PartyBattler* work;

    active = BATTLE_ACTIVE_WORK;
    if (active->unk_0B == 132) {
        work       = g_Task;
        work->step = work->step + 1;
    }
}

MATCH void func_801EF8E4(void) {
    Effect_CountUpTimer();
}

INCLUDE_ASM(func_801EF944);

MATCH void func_801EFC28(void) {
    SYS_DISPATCH_BYTE(D_801F0BC0, g_Task->step);
    if (g_Task->flags != 0) {
        Effect_SetActorMatrix();
        func_801EFDA0();
        PopMatrix();
    }
}

MATCH void func_801EFCA0(void) {
    u8 temp_v1;

    temp_v1        = g_Task->unk_09 + 1;
    g_Task->unk_09 = temp_v1;
    if ((temp_v1 & 0xFF) == 0x28) {
        D_801EB4E0->unk_0B = 4;
        g_Task->step += 1;
    }
}

MATCH void func_801EFD00(void) {
    PartyBattler* active;
    PartyBattler* work;

    active = BATTLE_ACTIVE_WORK;
    if (active->unk_0B == 132) {
        work       = g_Task;
        work->step = work->step + 1;
    }
}

MATCH void func_801EFD40(void) {
    Effect_CountUpTimer();
}

INCLUDE_ASM(func_801EFDA0);

MATCH void func_801F0140(void) {
    SYS_DISPATCH_BYTE(D_801F0BCC, g_Task->step);
    if (g_Task->flags != 0) {
        Effect_SetActorMatrix();
        func_801F02CC();
        PopMatrix();
    }
}

MATCH void func_801F01B8(void) {
    u8 temp_v1;

    temp_v1        = g_Task->unk_09 + 1;
    g_Task->unk_09 = temp_v1;
    if ((temp_v1 & 0xFF) == 0x31) {
        D_801EB4E0->unk_0B = 5;
        g_Task->step += 1;
    }
}

MATCH void func_801F0218(void) {
    if (D_801EB4E0->unk_0B == 0x84) {
        SND_PlayCue(0x103U);
        g_Task->step += 1;
    }
}

MATCH void func_801F026C(void) {
    PartyBattler* work;
    u8            next;

    work        = g_Task;
    next        = work->timer + 1;
    work->timer = next;
    if (next == 0x10) {
        BATTLE_ACTIVE_WORK->unk_0B--;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801F02CC);

INCLUDE_ASM(func_801F0764);

#include "overlays/bmagic/Effect_CountDownTimerStep.h"

/* First difference at 0x801F08C4: coordinate loads reversed; resolve self-copy semantics. */
INCLUDE_ASM(func_801F08B4);

MATCH void func_801F0A80(void) {
    u8 value;

    if (func_8014DAEC() & 0xFF) {
        value          = g_Task->unk_09 + 1;
        g_Task->unk_09 = value;
        if ((value & 0xFF) >= 3U) {
            D_801EB4E0->unk_0B += 1;
            func_801E5988();
            return;
        }
        g_Task->unk_2A = (g_Task->unk_2A + 1) & 1;
        Actor_SelectScript(g_Task->unk_0B);
        func_8014D290();
        if (g_Task->unk_0B == 0) {
            if (g_Task->unk_09 == 1) {
                SND_PlayCue(0x104U);
                return;
            }
            SND_PlayCue(0x100U);
        }
    } else {
        func_8014D290();
    }
}
