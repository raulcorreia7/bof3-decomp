#include "magic015_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EECA0(void) {
    Magic015Steps table = D_801EEC04;

    SYS_DISPATCH_TASK(table.steps, 1, g_Task);
}

#include "overlays/bmagic/Effect_CopyActiveBattlerToSlot.h"

MATCH void func_801EED0C(void) {
    PartyMember* work;
    u32          index;
    PartyMember* owner;
    u8           i;

    g_Task->facing = g_BattleEffectBattler->facing;
    WorldPos_Copy(&g_Task->pos, &g_BattleEffectBattler->pos);
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 0;
    g_Task->header.mode += 1;
    func_800AEF98(8, 2);
    for (i = 0; i < 4; i++) {
        index = Battle_AllocEffect(1, 35);
        Effect_CopyActiveBattlerToSlot(index);
        work                                             = g_Task;
        g_BattleEffects[index & BYTE_MASK].handler_index = 35;
        g_BattleEffects[index & BYTE_MASK].header.mode   = 1;
        g_BattleEffects[index & BYTE_MASK].header.step   = 0;
        g_BattleEffects[index & BYTE_MASK].unk_06        = 1;
        g_BattleEffects[index & BYTE_MASK].arg.unk_09    = (i ^ 3) + 1;
        g_BattleEffects[index & BYTE_MASK].unk_0B        = i ^ 3;
        g_BattleEffects[index & BYTE_MASK].target.party  = work;
        g_Task->param.unk_0B++;
    }
    index = Battle_AllocEffect(1, 35);
    Effect_CopyActiveBattlerToSlot(index);
    owner                                            = g_Task;
    g_BattleEffects[index & BYTE_MASK].unk_06        = 1;
    g_BattleEffects[index & BYTE_MASK].header.mode   = 0;
    g_BattleEffects[index & BYTE_MASK].header.step   = 0;
    g_BattleEffects[index & BYTE_MASK].handler_index = 35;
    g_BattleEffects[index & BYTE_MASK].target.party  = owner;
    g_Task->param.unk_0B++;
    g_BattleEffectBattler->header.flags |= PARTY_MEMBER_FLAG_HANDLER_BUSY;
    g_Task->unk_27 = Battle_CopyCellPalette(g_BattleEffectBattler);
    g_Task->unk_28 = g_BattleEffectBattler->unk_28;
    g_Task->unk_24 = g_BattleEffectBattler->unk_24;
    Battle_SetCellPaletteStp(g_Task);
}

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

MATCH void func_801EF2B4(void) {
    PartyMember* work;
    u32          index;
    u8           i;

    g_Task->facing = g_BattleEffectBattler->facing;
    WorldPos_Copy(&g_Task->pos, &g_BattleEffectBattler->pos);
    g_Task->unk_27 = Battle_CopyCellPalette(g_BattleEffectBattler);
    g_Task->unk_28 = g_BattleEffectBattler->unk_28;
    g_Task->unk_24 = g_BattleEffectBattler->unk_24;
    Battle_SetCellPaletteStp(g_Task);
    Battle_ClearCellPaletteEntry(g_Task);
    func_800AEF98(8, 2);
    g_Task->param.unk_0B = 0;
    for (i = 0; i < 3; i++) {
        index = Battle_AllocEffect(1, 35);
        Effect_CopyActiveBattlerToSlot(index);
        work                                             = g_Task;
        g_BattleEffects[index & BYTE_MASK].header.mode   = 2;
        g_BattleEffects[index & BYTE_MASK].unk_06        = 1;
        g_BattleEffects[index & BYTE_MASK].handler_index = 35;
        g_BattleEffects[index & BYTE_MASK].header.step   = 0;
        g_BattleEffects[index & BYTE_MASK].unk_0B        = i;
        g_BattleEffects[index & BYTE_MASK].arg.unk_09    = i * 2 + 1;
        g_BattleEffects[index & BYTE_MASK].target.party  = work;
        g_Task->param.unk_0B++;
    }
    SND_QueueSelectionEffect(0x100);
    g_BattleEffectBattler->header.flags |= PARTY_MEMBER_FLAG_HANDLER_BUSY;
    g_Task->header.mode++;
}

MATCH void func_801EF594(void) {
    EFFECT_RESTORE_PALETTE_AND_RELEASE_ACTIVE();
}

MATCH void Effect_StartPlaying2(void) {
    u16* flags;

    BATTLE_RAISE_EFFECT_PLAYING();
}

MATCH void func_801EF644(void) {
    Magic015Steps table = D_801EEC24;

    SYS_DISPATCH_TASK(table.steps, 1, g_Task);
}

MATCH void func_801EF6B0(void) {
    PartyMember* work;
    u32          index;

    g_Task->facing             = g_BattleEffectBattler->facing;
    g_Task->pos.x.fixed        = g_BattleEffectBattler->pos.x.fixed;
    g_Task->pos.y.fixed        = g_BattleEffectBattler->pos.y.fixed;
    g_Task->pos.z.part.integer = g_BattleEffectBattler->pos.z.part.integer;
    g_Task->param.unk_0B       = 1;
    func_800AEF98(8, 0);
    index = Battle_AllocEffect(1, 35);
    Effect_CopyActiveBattlerToSlot(index);
    work                                             = g_Task;
    g_BattleEffects[index & BYTE_MASK].header.mode   = 3;
    g_BattleEffects[index & BYTE_MASK].unk_06        = 1;
    g_BattleEffects[index & BYTE_MASK].header.step   = 0;
    g_BattleEffects[index & BYTE_MASK].handler_index = 35;
    g_BattleEffects[index & BYTE_MASK].arg.unk_09    = 0;
    g_BattleEffects[index & BYTE_MASK].target.party  = work;
    g_Task->unk_27                                   = Battle_CopyCellPalette(g_BattleEffectBattler);
    g_Task->unk_28                                   = g_BattleEffectBattler->unk_28;
    g_Task->unk_24                                   = g_BattleEffectBattler->unk_24;
    Battle_SetCellPaletteStp(g_Task);
    Battle_ClearCellPaletteEntry(g_Task);
    g_BattleEffectBattler->header.flags |= PARTY_MEMBER_FLAG_HANDLER_BUSY;
    g_Task->header.mode++;
}

MATCH void func_801EF93C(void) {
    if (g_Task->param.unk_0B == 0) {
        func_800AFC54();
        BATTLE_ACTIVE_WORK->header.flags &= ~PARTY_MEMBER_FLAG_HANDLER_BUSY;
        func_800AEF98(4, 0);
        g_Task->header.mode += 1;
    }
}

MATCH void Effect_StartPlaying4(void) {
    u16* flags;

    BATTLE_RAISE_EFFECT_PLAYING();
}

/* func_801EF9E4 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EFA28(void) {
    Magic015SecondSteps handlers = D_801EEC34;

    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Area_AddGridActor();
    }
}

MATCH void func_801EFAE4(void) {
    if (g_Battle.active_battler < BATTLE_PARTY_CHARACTERS_COUNT) {
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
    if ((Actor_StepAnimOnce() & BYTE_MASK) != 0u) {
        g_Task->header.step += 1u;
    }
}

MATCH void func_801EFBD8(void) {
    PartyMember** actor_cell;
    PartyMember*  record;
    PartyMember*  work;
    s32           heading;

    actor_cell = &g_Battle.selected_actor;
    func_800AF2B4((BattleRange*)*actor_cell, 0x60);
    if (func_800AF66C((BattleRange*)*actor_cell, 0xC000) != 0) {
        if (g_Battle.active_battler < BATTLE_PARTY_CHARACTERS_COUNT) {
            func_800AFC98(2, 0);
        }
        SND_QueueSelectionEffect(0x203);
        Battle_MarkDamaged(g_Battle.target_selector);
        record       = g_Task;
        heading      = ratan2(g_BattleEffectBattler->pos.x.fixed - record->pos.x.fixed, g_BattleEffectBattler->pos.y.fixed - record->pos.y.fixed);
        work         = g_Task;
        work->unk_0C = heading;
        work->unk_14 = 0x40;
        work->unk_09 = 0x10;
        work->unk_20 = -8;
        g_Task->header.step++;
    }
}

MATCH void func_801EFCC4(void) {
    PartyMember* work;
    s32          dz;
    u8           timer;

    g_Task->pos.x.fixed += FIXED_MUL(rsin(g_Task->unk_0C), 0x2000);
    g_Task->pos.y.fixed += FIXED_MUL(rcos(g_Task->unk_0C), 0x2000);
    work                     = g_Task;
    dz                       = work->unk_14 + work->unk_20;
    timer                    = work->unk_09 - 1;
    work->unk_09             = timer;
    work->unk_14             = dz;
    work->pos.z.part.integer = (u16)work->pos.z.part.integer + dz;
    if (timer == 0) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EFD7C(void) {
    if (g_BattleEffectBattler->param.unk_0B == 1) {
        g_Task->scale.x = 0x10000;
        g_Task->scale.y = 0x10000;
        g_Task->unk_48  = 2;
        g_Task->unk_09  = 8;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EFDE8(void) {
    u8 timer;

    timer = g_Task->unk_09 - 1;
    g_Task->scale.x -= 0x2000;
    g_Task->scale.y += 0x3000;
    g_Task->pos.z.part.integer = (u16)g_Task->pos.z.part.integer + 0x20;
    g_Task->unk_09             = timer;
    if (timer == 0) {
        g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;
        g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;
        g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;
        g_Task->unk_09      = 8;
        g_Task->header.step += 1;
    }
}

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
    Effect_Reset();
}

MATCH void func_801EFF1C(void) {
    Magic015ThirdSteps handlers;

    handlers = D_801EEC54;
    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Area_AddGridActor();
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
        if (g_Battle.active_battler < 3) {
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
    if ((Actor_StepAnimOnce() & BYTE_MASK) != 0u) {
        g_Task->header.step += 1u;
    }
}

MATCH void func_801F0194(void) {
    PartyMember** selected;
    PartyMember*  work;

    selected = &g_Battle.selected_actor;
    func_800AF2B4((BattleRange*)*selected, 0x60);
    if (func_800AF66C((BattleRange*)*selected, 0xC000) != 0) {
        g_Task->unk_0C = ratan2(g_BattleEffectBattler->pos.x.fixed - g_Task->pos.x.fixed, g_BattleEffectBattler->pos.y.fixed - g_Task->pos.y.fixed);
        work           = g_Task;
        work->unk_14   = 0x40;
        work->unk_09   = 0x10;
        work->unk_20   = -8;
        g_Task->header.step += 1;
    }
}

MATCH void func_801F0248(void) {
    u8 timer;

    g_Task->pos.x.fixed += FIXED_MUL(rsin(g_Task->unk_0C), 0x2000);
    g_Task->pos.y.fixed += FIXED_MUL(rcos(g_Task->unk_0C), 0x2000);
    g_Task->unk_14 += g_Task->unk_20;
    g_Task->pos.z.part.integer = (u16)g_Task->pos.z.part.integer + g_Task->unk_14;
    timer                      = g_Task->unk_09 - 1;
    g_Task->unk_09             = timer;
    if (timer == 0) {
        g_Task->header.step += 1;
    }
}

#include "overlays/bmagic/Effect_TickDownAndClear.h"

MATCH void func_801F0334(void) {
    Callback handlers[7];

    __builtin_memcpy(handlers, D_801EEC68, sizeof(handlers));
    SYS_DISPATCH_BYTE(handlers, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Area_AddGridActor();
        if (g_Task->unk_09 != 0 && g_Task->param.unk_0B == 0 && g_Task->header.step < 5) {
            if (g_Task->header.step < 4) {
                func_801F1250();
            } else {
                func_801F131C();
            }
            func_801F13D4();
            PopMatrix();
        }
    }
}

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

MATCH void func_801F0570(void) {
    PartyMember** selected;
    PartyMember*  work;
    s32           dz;
    u8            timer;

    selected = &g_Battle.selected_actor;
    func_800AF4A0((BattleRange*)*selected, 0x1800, 0);
    work                     = g_Task;
    timer                    = work->unk_09 - 1;
    dz                       = work->unk_14 + work->unk_20;
    work->unk_14             = dz;
    work->pos.z.part.integer = (u16)work->pos.z.part.integer + dz;
    work->scale.x            = work->scale.x - 0x800;
    work->scale.y            = work->scale.y + 0x1000;
    work->unk_09             = timer;
    if (timer == 0) {
        g_Task->pos.x.fixed        = (*selected)->pos.x.fixed;
        g_Task->pos.y.fixed        = (*selected)->pos.y.fixed;
        g_Task->pos.z.part.integer = (u16)(*selected)->pos.z.part.integer + 0xC00;
        func_800AF4A0((BattleRange*)g_BattleEffectBattler, 0x20000, 0);
        g_Task->header.step += 1;
    }
}

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

MATCH void func_801F0770(void) {
    PartyMember* work;
    PartyMember* object;
    PartyMember* flag;
    u8           countdown;

    func_800AF4A0((BattleRange*)g_Battle.selected_actor, 0x2000, 0);
    work                     = g_Task;
    countdown                = work->unk_09 + 1;
    work->unk_09             = countdown;
    work->pos.z.part.integer = (u16)work->pos.z.part.integer - 0xC0;
    if (countdown == 0x14) {
        object          = g_Task;
        object->unk_48  = 0;
        flag            = g_Task;
        object->unk_14  = 0x48;
        object->unk_20  = -8;
        object->scale.x = 0x10000;
        object->scale.y = 0x10000;
        if (flag->param.unk_0B == 0) {
            Battle_MarkDamaged(g_Battle.target_selector);
            if (g_Battle.active_battler < BATTLE_PARTY_CHARACTERS_COUNT) {
                func_800AFC98(2, 0);
            }
            SND_QueueSelectionEffect(0x203);
        }
        g_Task->header.step++;
    }
}

MATCH void func_801F0864(void) {
    s32 speed;

    if (g_Task->param.unk_0B != 0) {
        if ((s8)g_Task->unk_5D != -0x80) {
            g_Task->unk_5D -= D_801F1640[g_Task->param.unk_0B - 1][0];
            g_Task->unk_5E -= D_801F1640[g_Task->param.unk_0B - 1][1];
            g_Task->unk_5F -= D_801F1640[g_Task->param.unk_0B - 1][1];
        }
    } else {
        if ((s8)g_Task->unk_5D != 0) {
            g_Task->unk_5D -= 3;
            g_Task->unk_5E += 4;
            g_Task->unk_5F += 4;
        }
    }
    if (g_Task->unk_09 != 16) {
        g_Task->unk_09--;
    }
    Actor_StepAnimOnce();
    func_800AF4A0(D_8014637C, 0x2000, 0);
    speed                      = g_Task->unk_14 + g_Task->unk_20;
    g_Task->unk_14             = speed;
    g_Task->pos.z.part.integer = (u16)g_Task->pos.z.part.integer + speed;
    if ((g_Task->unk_14 < 0) && (g_Task->pos.z.fixed < g_Battle.selected_actor->pos.z.fixed)) {
        if (g_Task->param.unk_0B != 0) {
            g_BattleEffectBattler->param.unk_0B--;
            Effect_Reset();
        } else {
            g_Task->unk_5D      = 0;
            g_Task->unk_5E      = 0;
            g_Task->unk_5F      = 0;
            g_Task->pos.z.fixed = g_Battle.selected_actor->pos.z.fixed;
            g_Task->header.step++;
        }
    }
}

MATCH void func_801F0A94(void) {
    s8 tint;

    EFFECT_APPEAR_AT_BATTLER();
}

#include "overlays/bmagic/Effect_RampTintAndFinish.h"

MATCH void func_801F0B8C(void) {
    EFFECT_RAMP_TINT_AND_FINISH();
}

MATCH void func_801F0C30(void) {
    Callback handlers[7];

    __builtin_memcpy(handlers, D_801EEC84, sizeof(handlers));
    SYS_DISPATCH_BYTE(handlers, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Area_AddGridActor();
        if (g_Task->unk_09 != 0 && g_Task->header.step < 4) {
            if (g_Task->header.step < 3) {
                func_801F1250();
            } else {
                func_801F131C();
            }
            func_801F13D4();
            PopMatrix();
        }
    }
}

MATCH void func_801F0D48(void) {
    g_Task->unk_14 = 0x80;
    g_Task->unk_20 = -0x10;
    g_Task->unk_27 = BATTLE_ACTIVE_WORK->unk_27;
    g_Task->unk_09 = 0x14;
    g_Task->timer  = 7;
    g_Task->header.step += 1;
}

MATCH void func_801F0DB4(void) {
    PartyMember* work;
    s32          dz;
    u8           timer;
    func_800AF4A0((BattleRange*)g_BattleSelectedActor, 0x3800, 0);
    work = g_Task;
    dz   = work->unk_14 + work->unk_20;
    work->unk_09 -= 1;
    work->unk_14             = dz;
    work->pos.z.part.integer = (u16)work->pos.z.part.integer + dz;
    timer                    = g_Task->timer - 1;
    g_Task->timer            = timer;
    if (timer == 0) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801F0E54(void) {
    PartyMember** selected;
    u8            count;

    selected = &g_Battle.selected_actor;
    func_800AF2B4((BattleRange*)*selected, 0x60);
    count = g_Task->unk_09;
    if (count < 20) {
        g_Task->unk_09 = count + 1;
    }
    if (func_800AF5FC((BattleRange*)*selected, 0xC000) != 0) {
        g_Task->unk_14 = 0x48;
        g_Task->unk_20 = -8;
        func_800A9820(g_Battle.target_selector);
        if (g_Battle.active_battler < 3) {
            func_800AFC98(2, 0);
        }
        SND_QueueSelectionEffect(EMI_CUE_ID(SND_BANK_AREA, 0x03));
        g_Task->header.step += 1;
    }
}

MATCH void func_801F0F2C(void) {
    s32 speed;
    u8  timer;

    Actor_StepAnimOnce();
    func_800AF4A0(D_8014637C, 0x2000, 0);
    speed                      = g_Task->unk_14 + g_Task->unk_20;
    g_Task->unk_14             = speed;
    g_Task->pos.z.part.integer = (u16)g_Task->pos.z.part.integer + speed;
    if (g_Task->unk_14 < 0) {
        timer = g_Task->unk_09;
        if (timer < 20) {
            g_Task->unk_09 = timer + 1;
        }
    } else if (g_FrameCount & 0x1) {
        g_Task->unk_09 -= 1;
    }
    if ((g_Task->unk_14 < 0) && (g_Task->pos.z.fixed < g_Battle.selected_actor->pos.z.fixed)) {
        g_Task->header.flags |= 0x20;
        g_Task->unk_5C      = 1;
        g_Task->unk_5D      = 0;
        g_Task->unk_5E      = 0;
        g_Task->unk_5F      = 0;
        g_Task->pos.z.fixed = g_Battle.selected_actor->pos.z.fixed;
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
    Effect_Reset();
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
    pos.vx = (g_Task->pos.x.fixed >> 9) - AREA_CELL_ORIGIN;
    pos.vy = (g_Task->pos.y.fixed >> 9) - AREA_CELL_ORIGIN;
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
    BMAGIC_PROJECT_ACTOR_MATRIX(g_Battle.selected_actor);
}

MATCH void func_801F13D4(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
    g_ScratchPad.cells.halves[0] = g_Task->unk_09 << 2;
    g_ScratchPadVectors[2].vx    = FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[0]);
    g_ScratchPadVectors[2].vy    = FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[0]);

    for (i = 1; i <= 8; i++) {
        prim                      = GFX_BeginPolyG3(1);
        g_ScratchPadVectors[0].vx = 0;
        g_ScratchPadVectors[0].vy = 0;
        g_ScratchPadVectors[1].vx = g_ScratchPadVectors[2].vx;
        g_ScratchPadVectors[1].vy = g_ScratchPadVectors[2].vy;
        setVector(&g_ScratchPadVectors[2], FIXED_MUL(rsin(i << 9), g_ScratchPad.cells.halves[0]), FIXED_MUL(rcos(i << 9), g_ScratchPad.cells.halves[0]), 0);
        g_ScratchPadVectors[1].vz = 0;
        g_ScratchPadVectors[0].vz = 0;
        RotTransPers3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, 128, 128, 128);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        GFX_AddPrim(BMAGIC_LAYER_BEHIND_BATTLERS, sizeof(POLY_G3));
    }

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
}
