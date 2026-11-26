#include "magic017_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/BMagic_DispatchMode.h"

#include "overlays/bmagic/shared/Effect_CopyActiveBattlerToSlot.h"

MATCH void func_801EEC98(void) {
    PartyMember* work;
    u32          index;
    u8           i;

    SELF(PartyMember)->facing = g_BattleEffectBattler->facing;
    WorldPos_Copy(&SELF(PartyMember)->pos, &g_BattleEffectBattler->pos);
    SELF(PartyMember)->param.unk_0B = 0;
    SELF(PartyMember)->unk_09       = 0;
    SELF(PartyMember)->header.mode += 1;
    Battle_SelectActiveBattlerScript(0xC, 0);
    for (i = 0; i < 6; i++) {
        index = Battle_AllocEffect(1, 33);
        Effect_CopyActiveBattlerToSlot(index);
        work                                            = SELF(PartyMember);
        g_BattleEffects[index & BYTE_MASK].unk_06       = 1;
        g_BattleEffects[index & BYTE_MASK].effect_type  = 33;
        g_BattleEffects[index & BYTE_MASK].header.mode  = 0;
        g_BattleEffects[index & BYTE_MASK].header.step  = 0;
        g_BattleEffects[index & BYTE_MASK].unk_0B       = i;
        g_BattleEffects[index & BYTE_MASK].arg.unk_09   = (i & 0xFE) + 1;
        g_BattleEffects[index & BYTE_MASK].target.party = work;
        SELF(PartyMember)->param.unk_0B++;
    }
    SELF(PartyMember)->unk_27 = Battle_CopyCellPalette(g_BattleEffectBattler);
    SELF(PartyMember)->unk_28 = g_BattleEffectBattler->unk_28;
    SELF(PartyMember)->unk_24 = g_BattleEffectBattler->unk_24;
    Battle_SetCellPaletteStp(SELF(PartyMember));
    g_BattleEffectBattler->header.flags |= PARTY_MEMBER_FLAG_HANDLER_BUSY;
    SND_SEQueueSelection(0x100);
}

#include "overlays/bmagic/shared/Effect_ReleaseActiveBattlerOnTickerZero.h"

MATCH void func_801EEFD8(void) {
    u16* flags;

    func_800AFC54();
    BATTLE_RAISE_STATE(BATTLE_STATE_EFFECT_PLAYING);
    Effect_Reset();
}

/* func_801EF014 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EF058(void) {
    Magic017Steps handlers;

    handlers = D_801EEC10;
    SYS_DISPATCH_BYTE(handlers.steps, SELF(PartyMember)->header.step);
    if (SELF(PartyMember)->header.flags != 0 && SELF(PartyMember)->header.step != 0) {
        Area_AddGridActor();
    }
}

MATCH void func_801EF11C(void) {
    s8 tint;
    u8 count;

    count                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = count;
    if (count != 0) {
        return;
    }
    SELF(PartyMember)->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    tint                      = -64;
    SELF(PartyMember)->unk_5C = 1;
    SELF(PartyMember)->unk_2B = 1;
    SELF(PartyMember)->unk_5D = tint;
    SELF(PartyMember)->unk_5E = tint;
    SELF(PartyMember)->unk_5F = tint;
    SELF(PartyMember)->unk_27 = g_BattleEffectBattler->unk_27;
    if ((SELF(PartyMember)->param.unk_0B & 1) == 0) {
        SELF(PartyMember)->unk_0C = 0;
        SELF(PartyMember)->unk_10 = -ONE;
    } else {
        SELF(PartyMember)->unk_0C = 0;
        SELF(PartyMember)->unk_10 = ONE;
    }
    Effect_RotatePosition(g_Self);
    SELF(PartyMember)->unk_09 = 16;
    SELF(PartyMember)->header.step += 1;
}

MATCH void func_801EF248(void) {
    SELF(PartyMember)->pos.x.fixed += SELF(PartyMember)->unk_0C;
    SELF(PartyMember)->pos.y.fixed += SELF(PartyMember)->unk_10;
    SELF(PartyMember)->unk_5D -= 4;
    SELF(PartyMember)->unk_5E -= 4;
    SELF(PartyMember)->unk_5F -= 4;
    if (--SELF(PartyMember)->unk_09 == 0) {
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF300(void) {
    u8 count;

    count                     = SELF(PartyMember)->unk_09 + 1;
    SELF(PartyMember)->unk_09 = count;
    if ((count & BYTE_MASK) != 0x10) {
        return;
    }
    if ((SELF(PartyMember)->param.unk_0B & 1) != 0) {
        SELF(PartyMember)->unk_0C = -0x20000;
        SELF(PartyMember)->unk_10 = -0x10000;
    } else {
        SELF(PartyMember)->unk_0C = -0x20000;
        SELF(PartyMember)->unk_10 = 0x10000;
    }
    Effect_RotatePosition(g_Self);
    SELF(PartyMember)->pos.x.fixed = g_Battle.selected_actor->pos.x.fixed + SELF(PartyMember)->unk_0C;
    SELF(PartyMember)->pos.y.fixed = g_Battle.selected_actor->pos.y.fixed + SELF(PartyMember)->unk_10;
    SELF(PartyMember)->pos.z.fixed = g_Battle.selected_actor->pos.z.fixed;
    if ((SELF(PartyMember)->param.unk_0B & 1) != 0) {
        SELF(PartyMember)->unk_0C = 0;
        SELF(PartyMember)->unk_10 = 0x1000;
    } else {
        SELF(PartyMember)->unk_0C = 0;
        SELF(PartyMember)->unk_10 = -0x1000;
    }
    Effect_RotatePosition(g_Self);
    if (SELF(PartyMember)->param.unk_0B == 0) {
        SND_SEQueueSelection(0x101);
    }
    SELF(PartyMember)->unk_09 = 0x10;
    SELF(PartyMember)->header.step += 1;
}

MATCH void func_801EF460(void) {
    PartyMember* task;
    u8           timer;

    task = SELF(PartyMember);
    task->pos.x.fixed += task->unk_0C;
    task->unk_5D += 4;
    task->pos.y.fixed += task->unk_10;
    SELF(PartyMember)->unk_5E += 4;
    SELF(PartyMember)->unk_5F += 4;
    timer                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = timer;
    if (timer == 0) {
        if (SELF(PartyMember)->param.unk_0B == 0) {
            SELF(PartyMember)->header.flags &= 0xDF;
            SELF(PartyMember)->unk_5C = 0;
            SELF(PartyMember)->unk_2B = 0;
            SELF(PartyMember)->unk_5D = 0;
            SELF(PartyMember)->unk_5E = 0;
            SELF(PartyMember)->unk_5F = 0;
            if (g_Battle.active_battler >= 3) {
                func_801E257C(g_Battle.active_battler, 2);
            }
            SELF(PartyMember)->unk_09 = func_800AFF98();
            SELF(PartyMember)->header.step += 1;
            return;
        }
        g_BattleEffectBattler->param.unk_0B -= 1;
        Effect_Reset();
    }
}

MATCH void func_801EF5FC(void) {
    u8 counter;

    if (BATTLE_ACTIVE_WORK->param.unk_0B == 1) {
        Script_AnimStepOnce();
        counter                   = SELF(PartyMember)->unk_09 - 1;
        SELF(PartyMember)->unk_09 = counter;
        if (!(counter & BYTE_MASK)) {
            Battle_MarkDamaged(g_Battle.target_selector);
            Battle_PlayActiveBattlerSE(2, 4);
            SELF(PartyMember)->header.step += 1;
        }
    }
}

MATCH void func_801EF694(void) {
    if (Script_AnimStepOnce() != 0u) {
        SELF(PartyMember)->unk_09      = 8;
        SELF(PartyMember)->header.step = SELF(PartyMember)->header.step + 1;
    }
}

MATCH void func_801EF6EC(void) {
    s8 tone;
    u8 timer;

    timer                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        if (g_Battle.active_battler >= 3U) {
            func_801E257C(g_Battle.active_battler, 0);
        }
        SELF(PartyMember)->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
        SELF(PartyMember)->unk_5C = 1;
        SELF(PartyMember)->unk_2B = 1;
        tone                      = -0x40;
        SELF(PartyMember)->unk_5D = tone;
        SELF(PartyMember)->unk_5E = tone;
        SELF(PartyMember)->unk_5F = tone;
        SELF(PartyMember)->unk_09 = 8;
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF7E0(void) {
    u8 timer;

    SELF(PartyMember)->unk_5D -= 8;
    SELF(PartyMember)->unk_5E -= 8;
    SELF(PartyMember)->unk_5F -= 8;
    timer                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = timer;
    if (timer == 0) {
        SELF(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;
        SELF(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;
        SELF(PartyMember)->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;
        SELF(PartyMember)->unk_09      = 8;
        SELF(PartyMember)->header.step++;
    }
}

MATCH void func_801EF8B4(void) {
    u8 count;

    SELF(PartyMember)->unk_5D += 8;
    SELF(PartyMember)->unk_5E += 8;
    SELF(PartyMember)->unk_5F += 8;
    count                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF970(void) {
    Effect_Reset();
}
