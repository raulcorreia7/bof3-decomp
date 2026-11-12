#include "magic113_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC24(void) {
    Magic113Steps handlers;

    BMAGIC_DISPATCH_STEP_HANDLERS(D_801EEC04, header.mode);
    if (g_Task->header.flags != 0) {
        Effect_SetActorMatrix();
        func_801EF4F0();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EECE0);

INCLUDE_ASM(func_801EEE24);

MATCH void func_801EF000(void) {
    u32          slot;
    PartyMember* work;
    u8           facing;

    if (g_Task->param.unk_0B == 3) {
        MAGIC113_SPAWN_EFFECT(1);
    }
}

MATCH void func_801EF0F0(void) {
    u32          slot;
    PartyMember* work;
    u8           facing;

    if (g_Task->param.unk_0B == 4) {
        MAGIC113_SPAWN_EFFECT(2);
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0x02));
        g_SndVoiceTargetVolume[20] = 0x7F;
        g_SndVoiceVolume[20]       = 0;
    }
}

INCLUDE_ASM(func_801EF1F8);

MATCH void func_801EF35C(void) {
    if (g_Task->param.unk_0B == 6) {
        g_Task->param.unk_0B = 0x84;
        g_Task->header.mode += 1;
    }
}

MATCH void func_801EF3A0(void) {
    PartyMember* work;

    work = g_Task;
    if (work->param.unk_0B == 0x80) {
        work->header.mode = (work->header.mode + 1);
    }
}

#include "overlays/bmagic/Effect_CountDownAndPlay.h"

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EF4F0);

/* func_801EF75C */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF7A0(void) {
    SYS_DISPATCH_BYTE(D_801F0BAC, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        Effect_SetActorMatrix();
        s_Magic113OrbitRadius = D_801F0BA4[g_Task->param.unk_0B];
        func_801EF944();
        PopMatrix();
    }
}

MATCH void func_801EF844(void) {
    u8 count;

    count          = g_Task->unk_09 + 1;
    g_Task->unk_09 = count;
    if ((count & BYTE_MASK) == 0x21) {
        g_BattleEffectBattler->param.unk_0B = 3;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF8A4(void) {
    PartyMember* active;
    PartyMember* work;

    active = BATTLE_ACTIVE_WORK;
    if (active->param.unk_0B == 132) {
        work              = g_Task;
        work->header.step = work->header.step + 1;
    }
}

MATCH void func_801EF8E4(void) {
    Effect_CountUpTimer();
}

INCLUDE_ASM(func_801EF944);

MATCH void func_801EFC28(void) {
    SYS_DISPATCH_BYTE(D_801F0BC0, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        Effect_SetActorMatrix();
        func_801EFDA0();
        PopMatrix();
    }
}

MATCH void func_801EFCA0(void) {
    u8 count;

    count          = g_Task->unk_09 + 1;
    g_Task->unk_09 = count;
    if ((count & BYTE_MASK) == 0x28) {
        g_BattleEffectBattler->param.unk_0B = 4;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EFD00(void) {
    PartyMember* active;
    PartyMember* work;

    active = BATTLE_ACTIVE_WORK;
    if (active->param.unk_0B == 132) {
        work              = g_Task;
        work->header.step = work->header.step + 1;
    }
}

MATCH void func_801EFD40(void) {
    Effect_CountUpTimer();
}

INCLUDE_ASM(func_801EFDA0);

MATCH void func_801F0140(void) {
    SYS_DISPATCH_BYTE(D_801F0BCC, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        Effect_SetActorMatrix();
        func_801F02CC();
        PopMatrix();
    }
}

MATCH void func_801F01B8(void) {
    u8 count;

    count          = g_Task->unk_09 + 1;
    g_Task->unk_09 = count;
    if ((count & BYTE_MASK) == 0x31) {
        g_BattleEffectBattler->param.unk_0B = 5;
        g_Task->header.step += 1;
    }
}

MATCH void func_801F0218(void) {
    if (g_BattleEffectBattler->param.unk_0B == 0x84) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0x03));
        g_Task->header.step += 1;
    }
}

MATCH void func_801F026C(void) {
    PartyMember* work;
    u8           next;

    work        = g_Task;
    next        = work->timer + 1;
    work->timer = next;
    if (next == 0x10) {
        BATTLE_ACTIVE_WORK->param.unk_0B--;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801F02CC);

MATCH void func_801F0764(void) {
    GFX_AddDitheredDrawMode(3, getTPage(1, 1, 320, 256));
    g_ScriptTable = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(D_801F0BD8, g_Task->header.step);
    g_ScriptTable = AREA_SCRIPT_TABLE;
    GFX_AddDitheredDrawMode(3, getTPage(1, 0, 320, 256));
}

#include "overlays/bmagic/Effect_CountDownTimerStep.h"

MATCH void func_801F08B4(void) {
    PartyMember* task;
    s8           tint;

    g_Task->pos.x.fixed        = g_Task->pos.x.fixed;
    g_Task->pos.y.fixed        = g_Task->pos.y.fixed;
    g_Task->pos.z.part.integer = (s16)g_Task->pos.z.part.integer;
    if (g_Task->param.unk_0B == 2) {
        g_Task->pos.z.fixed += 0x01800000;
    }
    if (g_Task->unk_04 != 0) {
        g_Task->pos.z.fixed += 0x02000000;
    }
    g_Task->unk_25 = 0x1D;
    g_Task->unk_26 = 0;
    g_Task->unk_27 = 0xA0;
    g_Task->unk_28 = 0;
    g_Task->header.flags |= 0x20;
    tint              = -0x40;
    g_Task->unk_5D    = tint;
    g_Task->unk_5E    = tint;
    g_Task->unk_5F    = tint;
    g_Task->unk_5C    = 1;
    g_Task->unk_2A    = g_Task->unk_04;
    g_Task->unk_29    = 4;
    g_Task->unk_24    = 4;
    task              = g_Task;
    task->unk_2B      = 1;
    task->unk_2C.half = 0;
    g_Task->unk_09    = 0;
    g_Task->header.step += 1;
    if (g_Task->param.unk_0B == 0) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0x00));
    }
    Actor_SelectScript(g_Task->param.unk_0B);
}

MATCH void func_801F0A80(void) {
    u8 value;

    if (Actor_StepAnimOnce() & BYTE_MASK) {
        value          = g_Task->unk_09 + 1;
        g_Task->unk_09 = value;
        if ((value & BYTE_MASK) >= 3U) {
            g_BattleEffectBattler->param.unk_0B += 1;
            func_801E5988();
            return;
        }
        g_Task->unk_2A = (g_Task->unk_2A + 1) & 1;
        Actor_SelectScript(g_Task->param.unk_0B);
        func_8014D290();
        if (g_Task->param.unk_0B == 0) {
            if (g_Task->unk_09 == 1) {
                SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0x04));
                return;
            }
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0x00));
        }
    } else {
        func_8014D290();
    }
}
