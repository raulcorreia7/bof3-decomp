#include "magic146_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC10(void) {
    Magic146Steps handlers = D_801EEC04;
    PartyMember*  saved_task;
    PartyMember*  saved_battler;
    u8            i;

    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.mode);

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        if (D_801EF9F4[i].header.flags & BMAGIC_EFFECT_IN_USE) {
            saved_task            = g_Task;
            saved_battler         = g_BattleEffectBattler;
            g_Task                = (PartyMember*)&D_801EF9F4[i];
            g_BattleEffectBattler = D_801EF9F4[i].target.party;
            func_801EF2FC();
            g_BattleEffectBattler = saved_battler;
            g_Task                = saved_task;
        }
    }
}

MATCH void func_801EED18(void) {
    PartyMember* owner;
    u16*         dst;
    u16*         src;
    u8           slot;
    u8           index;
    u8           i;

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        BMAGIC_EFFECT_SLOTS[i].header.flags = 0;
        BMAGIC_EFFECT_SLOTS[i].header.mode  = 0;
        BMAGIC_EFFECT_SLOTS[i].header.step  = 0;
    }
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 8;
    g_Task->header.mode++;
    if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
        for (i = 0; i < 8; i++) {
            index = i + 3;
            if (!(Battle_SlotIsBlocked(index) & BYTE_MASK)) {
                slot                               = Battle_AllocEffect(1, 109) & BYTE_MASK;
                owner                              = g_Task;
                g_BattleEffects[slot].header.mode  = 0;
                g_BattleEffects[slot].unk_04       = index;
                g_BattleEffects[slot].target.party = owner;
                g_BattleEffects[slot].unk_0B       = g_Task->param.unk_0B;
                g_BattleEffects[slot].arg.unk_09   = (g_Task->param.unk_0B << 4) + 1;
                g_Task->param.unk_0B++;
            }
        }
    } else {
        for (i = 0; i < 3; i++) {
            if (!(Battle_SlotIsBlocked(i) & BYTE_MASK)) {
                slot                               = Battle_AllocEffect(1, 109) & BYTE_MASK;
                owner                              = g_Task;
                g_BattleEffects[slot].header.mode  = 0;
                g_BattleEffects[slot].unk_04       = i;
                g_BattleEffects[slot].target.party = owner;
                g_BattleEffects[slot].unk_0B       = g_Task->param.unk_0B;
                g_BattleEffects[slot].arg.unk_09   = (g_Task->param.unk_0B << 4) + 1;
                g_Task->param.unk_0B++;
            }
        }
    }
    i   = 1;
    dst = MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW);
    src = MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW);
    for (; i < 16; i++) {
        dst[i + 32] = src[i + 32] | 0x8000;
    }
    MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW)[32] = 0;
    g_GfxPalettePending                                         = 1;
}

#include "overlays/bmagic/Effect_NextStepOnZeroTick.h"

#include "shared/Effect_PlayOnce.h"

/* func_801EF04C */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF090(void) {
    SYS_DISPATCH_TASK(D_801EF9B8, 2, g_Task);
}

MATCH void func_801EF0D4(void) {
    PartyMember* battler;
    PartyMember* task;
    PartyMember* owner;
    u8           slot;
    u8           i;

    if (--g_Task->unk_09 == 0) {
        if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
            battler = (PartyMember*)(g_BattleEnemies + g_Task->unk_04 * BATTLE_ENEMY_STRIDE);
        } else {
            battler = &g_Game.members[g_Task->unk_04];
        }
        SND_QueueSelectionEffect(0x100);
        g_Task->facing = battler->facing;
        task           = g_Task;
        WorldPos_Copy(&task->pos, &battler->pos);
        task->param.unk_0B = 0;
        g_Task->header.step++;
        for (i = 0; i < 3; i++) {
            slot = BMagic_AllocEffect();
            if (slot != 0xFF) {
                owner                                  = g_Task;
                BMAGIC_EFFECT_SLOTS[slot].header.mode  = 0;
                BMAGIC_EFFECT_SLOTS[slot].unk_0B       = i;
                BMAGIC_EFFECT_SLOTS[slot].arg.unk_09   = i * 2 + 1;
                BMAGIC_EFFECT_SLOTS[slot].target.party = owner;
                g_Task->param.unk_0B++;
            }
        }
        Battle_ApplyDamageFlags(g_Task->unk_04, 0x10);
    }
}

#include "overlays/bmagic/Effect_FinishOnZeroTick.h"

MATCH void func_801EF2FC(void) {
    SYS_DISPATCH_TASK(D_801EF9C0, 1, g_Task);
}

MATCH void func_801EF340(void) {
    SYS_DISPATCH_BYTE(D_801EF9C4, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_DrawTexturedQuad();
    }
}

MATCH void func_801EF3B8(void) {
    PartyMember* battler;
    PartyMember* work;

    if (--g_Task->unk_09 == 0) {
        g_Task->facing = g_BattleEffectBattler->facing;
        battler        = g_BattleEffectBattler;
        work           = g_Task;
        WorldPos_Copy(&work->pos, &battler->pos);
        work->unk_0C = D_801EF9D0[work->param.unk_0B].x;
        work->unk_10 = D_801EF9D0[work->param.unk_0B].y;
        func_801DD350(work);
        g_Task->pos.x.fixed += g_Task->unk_0C;
        g_Task->pos.y.fixed += g_Task->unk_10;
        g_Task->pos.z.fixed += D_801EF9D0[g_Task->param.unk_0B].z;
        Battle_ProjectRange();
        g_Task->unk_09 = 0;
        g_Task->timer  = 0;
        g_Task->header.step++;
    }
}

#include "overlays/bmagic/Effect_CountUpTimersByTwoNextStep.h"

MATCH void func_801EF58C(void) {
    PartyMember* work;
    PartyMember* active;
    u8           count;

    work = g_Task;
    work->unk_09++;
    work        = g_Task;
    count       = work->timer - 1;
    work->timer = count;
    if (count == 0) {
        active = BATTLE_ACTIVE_WORK;
        active->param.unk_0B--;
        Actor_Clear();
    }
}

#include "overlays/bmagic/Effect_DrawTexturedQuad.h"

/* func_801EF900 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801EF964 */
#include "overlays/bmagic/Actor_Clear.h"
