#include "magic003_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC28(void) {
    PartyMember* saved_task;
    PartyMember* saved_battler;
    u8           i;

    SYS_DISPATCH_BYTE(D_801F0AD8, g_Task->header.mode);

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        if (BMAGIC_EFFECT_SLOTS[i].header.flags & BMAGIC_EFFECT_IN_USE) {
            saved_task            = g_Task;
            saved_battler         = g_BattleEffectBattler;
            g_Task                = (PartyMember*)&BMAGIC_EFFECT_SLOTS[i];
            g_BattleEffectBattler = BMAGIC_EFFECT_SLOTS[i].target.party;
            BMagic_DispatchEffectMode();
            g_BattleEffectBattler = saved_battler;
            g_Task                = saved_task;
        }
    }
}

INCLUDE_ASM(func_801EED14);

MATCH void func_801EEDAC(void) {
    u8 timer;

    func_801F07B0(1);
    func_801F0164(1);
    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        g_Task->unk_09 = 0x1E;
        g_Task->header.mode += 1;
    }
}

MATCH void func_801EEE28(void) {
    u8 timer;

    func_801F07B0(2);
    func_801F0164(2);
    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        g_Task->unk_09 = 0xA;
        g_Task->header.mode += 1;
    }
}

MATCH void func_801EEEA4(void) {
    u8 count;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (count == 0) {
        g_Task->param.unk_0B = RANDOM_MASK(3);
        if (g_Task->timer < 16) {
            g_Task->unk_09 = D_801F0A84[g_Task->timer];
        } else {
            g_Task->unk_09 = 3;
        }
        g_Task->header.mode += 1;
    }
}

MATCH void func_801EEF4C(void) {
    u8 count;
    u8 timer;

    func_801F07B0(4);
    func_801F03F0(g_Task->param.unk_0B);
    if (g_InputPressed & (PADRup | PADRdown | PADRleft | PADRright)) {
        if (g_InputPressed != D_801F0A98[g_Task->param.unk_0B]) {
            g_Task->unk_09      = 6;
            g_Task->header.mode = 5;
        } else {
            g_Task->unk_09 = 6;
            count          = g_Task->timer + 1;
            g_Task->timer  = count;
            if (count < 32) {
                g_Task->header.mode = 3;
            } else {
                g_Task->header.mode = 5;
            }
        }
    } else {
        timer          = g_Task->unk_09 - 1;
        g_Task->unk_09 = timer;
        if (timer == 0) {
            g_Task->unk_09      = 6;
            g_Task->header.mode = 5;
        }
    }
}

MATCH void func_801EF04C(void) {
    u8 timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        g_Task->unk_09      = 0x1E;
        g_Task->header.mode = g_Task->header.mode + 1;
    }
}

MATCH void func_801EF0A8(void) {
    u8 timer;

    func_801F07B0(0);
    func_801F0550(g_Task->timer);
    func_801F0164(0);
    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        g_Task->header.mode += 1;
    }
}

MATCH void func_801EF12C(void) {
    g_Task->facing       = g_BattleEffectBattler->facing;
    g_Task->pos.x.fixed  = g_BattleEffectBattler->pos.x.fixed;
    g_Task->pos.y.fixed  = g_BattleEffectBattler->pos.y.fixed;
    g_Task->pos.z.fixed  = g_BattleEffectBattler->pos.z.fixed;
    g_Task->param.unk_0B = 0;
    g_Task->header.mode += 1;
    func_800AEF98(0xC, 2);
    func_801EFD4C();
    func_801EFEC8();
    g_Task->unk_04 = g_Task->param.unk_0B;
    g_BattleEffectBattler->header.flags |= ACTOR_FLAG_HIDDEN;
    SND_QueueSelectionFx(0x100);
}

MATCH void func_801EF1FC(void) {
    if (g_Task->param.unk_0B == 0) {
        *D_8014637C &= 0xBF;
        func_800AEF98(4, 0);
        g_Task->header.mode += 1;
    }
}

MATCH void func_801EF268(void) {
    SND_QueueSelectionFx(258);
    D_801463D6 = g_Task->timer;
    Battle_MarkDamaged(g_BattleTargetSelector);
    g_BattleState = g_Battle.state | BATTLE_STATE_EFFECT_PLAYING;
    func_801E5988();
}

MATCH void func_801EF2CC(void) {
    Callback handlers[2] = {func_801EF324, func_801EF708};

    SYS_DISPATCH_TASK(handlers, 1, g_Task);
}

MATCH void func_801EF324(void) {
    Magic003Steps handlers;

    handlers = D_801EEC04;
    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if (g_Task->header.step != 0 && g_Task->header.flags != 0) {
        Area_SetDrawMode();
    }
}

MATCH void func_801EF3C8(void) {
    s32 x;
    s32 y;
    u32 z;
    u8  timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        x               = g_Task->pos.x.fixed;
        y               = g_Task->pos.y.fixed;
        z               = g_Task->pos.z.fixed;
        g_Task->unk_0C  = 0x2000;
        g_Task->unk_14  = 0x300000;
        g_Task->unk_10  = 0;
        g_Task->unk_20  = -0x80000;
        g_Task->unk_18  = x;
        g_Task->unk_1C  = y;
        g_Task->scale.y = z;
        func_801DD350(g_Task);
        g_Task->unk_09 = func_800AFF98();
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF478(void) {
    s32 value;
    u8  value2;

    value2 = g_Task->unk_09;
    value  = value2 & BYTE_MASK;
    if (value != 0) {
        if (value != 0xFF) {
            g_Task->unk_09 = value2 - 1;
        }
    } else {
        SND_QueueSelectionFx(0x101);
        func_800AFC98(2, 0);
        func_801F0078();
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10U);
        g_Task->unk_09 = 0xFF;
    }
    g_Task->pos.x.fixed += g_Task->unk_0C;
    g_Task->pos.y.fixed += g_Task->unk_10;
    g_Task->pos.z.fixed += g_Task->unk_14;
    g_Task->unk_14 += g_Task->unk_20;
    Actor_StepAnimOnce();
    if (g_Task->pos.z.fixed == g_Task->scale.y) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF578(void) {
    s32 value;
    u8  value2;

    value2 = g_Task->unk_09;
    value  = value2 & BYTE_MASK;
    if (value != 0) {
        if (value != 0xFF) {
            g_Task->unk_09 = value2 - 1;
        }
    } else {
        SND_QueueSelectionFx(0x101);
        func_800AFC98(2, 0);
        func_801F0078();
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10U);
        g_Task->unk_09 = 0xFF;
    }
    Actor_StepAnimOnce();
    if (g_Task->unk_09 == 0xFF) {
        g_Task->unk_0C = -0x2000;
        g_Task->unk_10 = 0;
        func_801DD350(g_Task);
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF644(void) {
    g_Task->pos.x.fixed += g_Task->unk_0C;
    g_Task->pos.y.fixed += g_Task->unk_10;
    Actor_StepAnimOnce();
    if (g_Task->pos.x.fixed == g_Task->unk_18 && g_Task->pos.y.fixed == g_Task->unk_1C) {
        g_Task->header.step++;
    }
}

MATCH void func_801EF6CC(void) {
    PartyMember* work;
    u8           step;

    work = BATTLE_ACTIVE_WORK;
    step = work->param.unk_0B;
    if (step < 2) {
        work->param.unk_0B = step - 1;
        func_801E5988();
    }
}

MATCH void func_801EF708(void) {
    Magic003SecondSteps handlers;

    handlers = D_801EEC18;
    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if (g_Task->header.step != 0 && g_Task->header.flags != 0) {
        Area_SetDrawMode();
    }
}

INCLUDE_ASM(func_801EF7A8);

MATCH void func_801EF918(void) {
    g_Task->pos.x.fixed += g_Task->unk_0C;
    g_Task->pos.y.fixed += g_Task->unk_10;
    g_Task->pos.z.fixed += g_Task->unk_14;
    g_Task->unk_14 += g_Task->unk_20;
    Actor_StepAnimOnce();
    if (g_Task->pos.z.fixed == g_Task->scale.y) {
        g_Task->header.step++;
    }
}

MATCH void func_801EF9AC(void) {
    g_Task->unk_0C = -0x2000;
    g_Task->unk_10 = 0;
    func_801DD350(g_Task);
    Actor_StepAnimOnce();
    g_Task->header.step += 1;
}

MATCH void func_801EF9FC(void) {
    g_Task->pos.x.fixed += g_Task->unk_0C;
    g_Task->pos.y.fixed += g_Task->unk_10;
    Actor_StepAnimOnce();
    if ((g_Task->pos.x.fixed == g_Task->unk_18) && (g_Task->pos.y.fixed == g_Task->unk_1C)) {
        GFX_FreePaletteFadeTarget(g_Task);
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
    }
}

/* func_801EFA9C */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

#include "overlays/bmagic/BMagic_RunEffectStep.h"

MATCH void func_801EFAE0(void) {
    BMAGIC_RUN_EFFECT_STEP(func_801EFB8C, func_801EFCF8);
}

INCLUDE_ASM(func_801EFB8C);

MATCH void func_801EFCF8(void) {
    PartyMember* work;

    Actor_StepAnimOnce();
    if (Actor_StepAnimOnce() != 0u) {
        work               = (PartyMember*)g_BattleEffectBattler;
        work->param.unk_0B = work->param.unk_0B - 1;
        Actor_Clear();
    }
}

INCLUDE_ASM(func_801EFD4C);

INCLUDE_ASM(func_801EFEC8);

MATCH void func_801F0078(void) {
    PartyMember* battler;
    u8           i;
    u8           slot;

    for (i = 0; i < g_BattleEffectBattler->timer; i++) {
        slot                                   = BMagic_AllocEffect();
        battler                                = g_BattleEffectBattler;
        BMAGIC_EFFECT_SLOTS[slot].header.mode  = 0;
        BMAGIC_EFFECT_SLOTS[slot].header.step  = 0;
        BMAGIC_EFFECT_SLOTS[slot].unk_04       = i;
        BMAGIC_EFFECT_SLOTS[slot].unk_0B       = (i / 2) & 7;
        BMAGIC_EFFECT_SLOTS[slot].arg.unk_09   = (i * 4) + 1;
        BMAGIC_EFFECT_SLOTS[slot].target.party = battler;
        g_BattleEffectBattler->param.unk_0B += 1;
    }
}

INCLUDE_ASM(func_801F0164);

INCLUDE_ASM(func_801F03F0);

INCLUDE_ASM(func_801F0550);

INCLUDE_ASM(func_801F07B0);

/* func_801F09C4 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801F0A28 */
#include "overlays/bmagic/Actor_Clear.h"
