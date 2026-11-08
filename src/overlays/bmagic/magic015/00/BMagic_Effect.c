#include "magic015_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EECA0(void) {
    Magic015Steps table = D_801EEC04;

    SYS_DISPATCH_TASK(table.steps, 1, g_Task);
}

INCLUDE_ASM(func_801EED0C);

#include "overlays/bmagic/Effect_RestorePaletteAndReleaseActive.h"

MATCH void func_801EF150(void) {
    EFFECT_RESTORE_PALETTE_AND_RELEASE_ACTIVE();
}

#include "shared/Effect_StartPlaying.h"

#include "shared/Effect_PlayOnce.h"

MATCH void func_801EF248(void) {
    Magic015Steps table = D_801EEC14;

    SYS_DISPATCH_TASK(table.steps, 1, g_Task);
}

INCLUDE_ASM(func_801EF2B4);

MATCH void func_801EF594(void) {
    EFFECT_RESTORE_PALETTE_AND_RELEASE_ACTIVE();
}

MATCH void Effect_StartPlaying_801EF610(void) {
    u16* flags;

    BATTLE_RAISE_EFFECT_PLAYING();
}

MATCH void func_801EF644(void) {
    Magic015Steps table = D_801EEC24;

    SYS_DISPATCH_TASK(table.steps, 1, g_Task);
}

INCLUDE_ASM(func_801EF6B0);

MATCH void func_801EF93C(void) {
    if (g_Task->param.unk_0B == 0) {
        func_800AFC54();
        BATTLE_ACTIVE_WORK->header.flags &= ~PARTY_MEMBER_FLAG_HANDLER_BUSY;
        func_800AEF98(4, 0);
        g_Task->header.mode += 1;
    }
}

MATCH void Effect_StartPlaying_801EF9B0(void) {
    u16* flags;

    BATTLE_RAISE_EFFECT_PLAYING();
}

MATCH void func_801EF9E4(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectModes, TASK_BYTES[1]);
}

MATCH void func_801EFA28(void) {
    Magic015SecondSteps handlers = D_801EEC34;

    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_8014D290();
    }
}

MATCH void func_801EFAE4(void) {
    if (g_BattleActiveBattler < BATTLE_PARTY_CHARACTERS_COUNT) {
        g_Task->header.step += 1;
    } else {
        g_Task->header.step += 2;
    }
    g_Task->unk_27      = g_BattleEffectBattler->unk_27;
    g_Task->unk_2B      = 1;
    g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;
    g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;
    g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;
}

MATCH void func_801EFB90(void) {
    if ((func_8014DAEC() & BYTE_MASK) != 0u) {
        g_Task->header.step += 1u;
    }
}

/* hint: a MATCH_FAKE_BARRIER before the unk_20 store reloads g_Task as retail does; first differing instruction is li v0,-8 at +0xC0 (candidate nop in the load delay slot). */
INCLUDE_ASM(func_801EFBD8);

/* Blocker: the z halfword at +0x3E is loaded unsigned (lhu) and summed with the 0x14 cell; COORD_INT is s16, so it gives lh. Same blocker as func_801F0DB4. */
INCLUDE_ASM(func_801EFCC4);

MATCH void func_801EFD7C(void) {
    if (g_BattleEffectBattler->param.unk_0B == 1) {
        g_Task->scale.x = 0x10000;
        g_Task->scale.y = 0x10000;
        g_Task->unk_48  = 2;
        g_Task->unk_09  = 8;
        g_Task->header.step += 1;
    }
}

/* blocker: the halfword at +0x3E (the z-span halfword, upper half of pos.z) has no PartyMember member; needs: type. */
INCLUDE_ASM(func_801EFDE8);

MATCH void func_801EFE84(void) {
    PartyMember* work = g_Task;
    u8           timer;

    timer        = work->unk_09 - 1;
    work->unk_09 = timer;
    work->scale.x += 0x2000;
    work->scale.y -= 0x3000;
    if (timer == 0) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EFEFC(void) {
    func_801E5988();
}

MATCH void func_801EFF1C(void) {
    Magic015ThirdSteps handlers;

    handlers = D_801EEC54;
    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_8014D290();
    }
}

MATCH void func_801EFFC0(void) {
    u8 timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        g_Task->header.flags |= 0x20;
        g_Task->unk_5C = 1;
        g_Task->unk_5D = (u8) - ((g_Task->param.unk_0B + 1) * 0x14);
        g_Task->unk_5E = (u8) - ((g_Task->param.unk_0B + 1) * 0x14);
        g_Task->unk_5F = (u8) - ((g_Task->param.unk_0B + 1) * 0x14);
        g_Task->unk_2B = 0;
        g_Task->unk_27 = g_BattleEffectBattler->unk_27;
        if (g_BattleActiveBattler < 3) {
            g_Task->header.step += 1;
        } else {
            g_Task->header.step += 2;
        }
        g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;
        g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;
        g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;
    }
}

MATCH void func_801F014C(void) {
    if ((func_8014DAEC() & BYTE_MASK) != 0u) {
        g_Task->header.step += 1u;
    }
}

/* hint: a MATCH_FAKE_BARRIER before the unk_20 store reloads g_Task as retail does; first differing instruction is li v0,-8 at +0x88 (candidate nop in the load delay slot). */
INCLUDE_ASM(func_801F0194);

/* hint: blocker is the z halfword at +0x3E, read and stored unsigned (lhu/sh) by this function; COORD_INT is s16 (lh). Needs an unsigned view of pos.z. */
INCLUDE_ASM(func_801F0248);

#include "overlays/bmagic/Effect_TickDownAndClear.h"

INCLUDE_ASM(func_801F0334);

MATCH void func_801F045C(void) {
    PartyMember* task;
    s8           tint;
    u8           timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        g_Task->unk_27 = g_BattleEffectBattler->unk_27;
        g_Task->unk_2B = g_Task->param.unk_0B == 0;
        if (g_Task->param.unk_0B != 0) {
            g_Task->header.flags |= 0x20;
            g_Task->unk_5C = 1;
            task           = g_Task;
            tint           = -0x40;
            task->unk_5F   = tint;
            task->unk_5E   = tint;
            task->unk_5D   = tint;
        }
        task           = g_Task;
        task->unk_14   = 0x80;
        task->unk_20   = -2;
        task->scale.x  = 0x10000;
        task->scale.y  = 0x10000;
        task->unk_48   = 2;
        g_Task->unk_09 = 0x10;
        g_Task->header.step += 1;
    }
}

/* hint: blocker is the z halfword at +0x3E, read unsigned (lhu at +0x3C and +0x9C) and stored with sh; COORD_INT is s16. Needs the unsigned z view. */
INCLUDE_ASM(func_801F0570);

MATCH void func_801F0654(void) {
    PartyMember* task;
    s8           tint;
    u8           timer;

    timer          = g_Task->unk_09 + 1;
    g_Task->unk_09 = timer;
    if (timer == 4) {
        task          = g_Task;
        task->scale.x = 0x8000;
        task->scale.y = 0x18000;
        if (task->param.unk_0B != 0) {
            task->unk_5D   = -((task->param.unk_0B * 0x10) + 0x30);
            g_Task->unk_5E = -((g_Task->param.unk_0B * 0x10) + 0x40);
            g_Task->unk_5F = -((g_Task->param.unk_0B * 0x10) + 0x40);
        } else {
            g_Task->header.flags |= 0x20;
            g_Task->unk_5C = 1;
            g_Task->unk_5D = 0x30;
            tint           = -0x40;
            g_Task->unk_5E = tint;
            g_Task->unk_5F = tint;
        }
        g_Task->header.step += 1;
    }
}

/* hint: m2c draft with the task cached in a0 and unk_48..scale in a second local is 12 over; first differing instruction: lbu v0,9(a0) at +0x28 where retail holds the timer in v1 and the z in v0. */
INCLUDE_ASM(func_801F0770);

INCLUDE_ASM(func_801F0864);

MATCH void func_801F0A94(void) {
    s8 tint;

    EFFECT_APPEAR_AT_BATTLER();
}

#include "overlays/bmagic/Effect_RampTintAndFinish.h"

MATCH void func_801F0B8C(void) {
    EFFECT_RAMP_TINT_AND_FINISH();
}

INCLUDE_ASM(func_801F0C30);

MATCH void func_801F0D48(void) {
    g_Task->unk_14 = 0x80;
    g_Task->unk_20 = -0x10;
    g_Task->unk_27 = BATTLE_ACTIVE_WORK->unk_27;
    g_Task->unk_09 = 0x14;
    g_Task->timer  = 7;
    g_Task->header.step += 1;
}

/* Blocker: retail reads the z halfword at +0x3E unsigned (lhu) and loads the 0x14 cell before the 0x09 decrement; COORD_INT is s16 (lh). Needs an unsigned halfword view of pos.z. */
INCLUDE_ASM(func_801F0DB4);

/* hint: first differing instruction is the beqz at +0x50 (candidate one instruction short): retail reloads g_Task (lui/lw) before the unk_14 store; a MATCH_FAKE_BARRIER there moves the li 0x48 out of the branch delay slot. */
INCLUDE_ASM(func_801F0E54);

MATCH void func_801F0F2C(void) {
    s32 speed;
    u8  timer;

    func_8014DAEC();
    func_800AF4A0(D_8014637C, 0x2000, 0);
    speed                      = g_Task->unk_14 + g_Task->unk_20;
    g_Task->unk_14             = speed;
    g_Task->pos.z.part.integer = (u16)g_Task->pos.z.part.integer + speed;
    if (g_Task->unk_14 < 0) {
        timer = g_Task->unk_09;
        if (timer < 0x14) {
            g_Task->unk_09 = timer + 1;
        }
    } else if (g_FrameCount & 1) {
        g_Task->unk_09 -= 1;
    }
    if ((g_Task->unk_14 < 0) && (g_Task->pos.z.fixed < g_BattleSelectedActor->pos.z.fixed)) {
        g_Task->header.flags |= 0x20;
        g_Task->unk_5C      = 1;
        g_Task->unk_5D      = 0;
        g_Task->unk_5E      = 0;
        g_Task->unk_5F      = 0;
        g_Task->pos.z.fixed = g_BattleSelectedActor->pos.z.fixed;
        g_Task->header.step++;
    }
}

MATCH void func_801F1088(void) {
    s8 tint;

    EFFECT_APPEAR_AT_BATTLER();
}

MATCH void func_801F1180(void) {
    g_Task->unk_5D += 0x10;
    g_Task->unk_5E += 0x10;
    g_Task->unk_5F += 0x10;
    if ((s8)g_Task->unk_5D == -0x40) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        g_Task->header.step += 1;
    }
}

MATCH void func_801F1230(void) {
    func_801E5988();
}

MATCH void func_801F1250(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;
    s16     height;

    PushMatrix();
    rot.vz = 0;
    rot.vy = 0;
    rot.vx = 0;
    pos.vx = (g_Task->pos.x.fixed >> 9) - 0x4000;
    pos.vy = (g_Task->pos.y.fixed >> 9) - 0x4000;
    height = Area_SampleHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed);
    pos.vz = -height / 2;
    RotTransMatrix(&pos, matrix, &flags);
    Camera_SetModelMatrix(&rot, &matrix);
}

MATCH void func_801F131C(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    rot.vz = 0;
    rot.vy = 0;
    rot.vx = 0;
    BMAGIC_PROJECT_ACTOR_MATRIX(g_BattleSelectedActor);
}

INCLUDE_ASM(func_801F13D4);
