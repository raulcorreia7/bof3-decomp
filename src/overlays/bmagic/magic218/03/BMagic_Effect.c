#include "magic218_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Callback handlers[2] = {func_801EEC5C, func_801EEDB8};

    SYS_DISPATCH_TASK(handlers, 1, g_Task);
}

MATCH void func_801EEC5C(void) {
    PartyMember* task;
    PartyMember* target;
    u16*         src;
    u16*         dst;
    u16          i;
    u32          slot;

    for (i = 0; i < 8; i++) {
        D_801EF790[i] = 0;
    }
    g_Task->facing = g_BattleEffectBattler->facing;
    task           = g_Task;
    WorldPos_Copy(&task->pos, &g_BattleEffectBattler->pos);
    task->param.unk_0B = 0;
    g_Task->header.mode += 1;
    slot                               = Battle_AllocEffect(1, 0x67) & BYTE_MASK;
    target                             = g_Task;
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].arg.unk_09   = 1;
    g_BattleEffects[slot].target.party = target;
    g_Task->param.unk_0B += 1;
    BMAGIC_BRIGHTEN_PALETTE_ROW(dst, src, i);
    g_GfxPalettePending = 1;
    SND_QueueSelectionFx(EMI_CUE_ID(SND_BANK_COMMON, 0x00));
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EEE18 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEE5C(void) {
    SYS_DISPATCH_BYTE(D_801EF774, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801EF250();
        PopMatrix();
    }
}

MATCH void func_801EEEE4(void) {
    PartyMember* src;
    PartyMember* dst;

    if (--g_Task->unk_09 == 0) {
        src              = BATTLE_ACTIVE_WORK;
        dst              = g_Task;
        dst->pos.x.fixed = src->pos.x.fixed;
        dst->pos.y.fixed = src->pos.y.fixed;
        dst->pos.z       = src->pos.z;
        dst->unk_5D      = 0x10;
        g_Task->unk_09   = 0x10;
        g_Task->timer    = 4;
        g_Task->header.step++;
    }
}

MATCH void func_801EEF84(void) {
    s32 i;
    u8  slot;

    g_Task->unk_09 += 2;
    SP_REF(s16, 0) = g_Task->unk_09 << 4;
    i              = 0;
    do {
        if (D_801EF790[i & BYTE_MASK] == 0) {
            slot = (i + BATTLE_PARTY_CHARACTERS_COUNT) & BYTE_MASK;
            if (!(Battle_SlotIsBlocked(slot) & BYTE_MASK)) {
                if (func_801EF70C(&g_BattleEnemyBattlers[i & BYTE_MASK]) != 0) {
                    if (g_Battle.active_battler != (i & BYTE_MASK) + BATTLE_PARTY_CHARACTERS_COUNT) {
                        D_801EF790[i & BYTE_MASK] = -1;
                        func_800A9610(slot, 0x10);
                    }
                }
            }
        }
        i++;
    } while ((u32)(i & BYTE_MASK) < 8);
    if (g_FrameCount & 1) {
        if (g_Task->timer < 32) {
            g_Task->timer += 1;
        }
    }
    if (g_Task->unk_09 == 96) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF0F0(void) {
    u8 count;
    u8 timer;

    if (g_FrameCount & 1) {
        timer = g_Task->timer;
        if (timer < 32U) {
            g_Task->timer = timer + 1;
        }
    }
    g_Task->unk_09 += 1;
    count          = g_Task->unk_5D - 1;
    g_Task->unk_5D = count;
    if ((count << 0x18) == 0) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
    }
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EF250);

INCLUDE_ASM(func_801EF70C);
