#include "magic146_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC10(void) {
    MagicModuleSteps handlers = D_801EEC04;
    PartyMember*     saved_task;
    PartyMember*     saved_battler;
    u8               i;

    SYS_DISPATCH_BYTE(handlers.steps, SELF(PartyMember)->header.mode);

    BMAGIC_RUN_EFFECT_SLOTS(D_801EF9F4, func_801EF2FC);
}

MATCH void func_801EED18(void) {
    PartyMember* owner;
    u16*         dst;
    u16*         src;
    u8           slot;
    u8           index;
    u8           i;

    BMAGIC_CLEAR_EFFECTS(i);
    SELF(PartyMember)->param.unk_0B = 0;
    SELF(PartyMember)->unk_09       = 8;
    SELF(PartyMember)->header.mode++;
    if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
        for (i = 0; i < 8; i++) {
            index = i + 3;
            if (!(Battle_SlotIsBlocked(index) & BYTE_MASK)) {
                slot                               = Battle_AllocEffect(1, 109) & BYTE_MASK;
                owner                              = SELF(PartyMember);
                g_BattleEffects[slot].header.mode  = 0;
                g_BattleEffects[slot].unk_04       = index;
                g_BattleEffects[slot].target.party = owner;
                g_BattleEffects[slot].unk_0B       = SELF(PartyMember)->param.unk_0B;
                g_BattleEffects[slot].arg.unk_09   = (SELF(PartyMember)->param.unk_0B << 4) + 1;
                SELF(PartyMember)->param.unk_0B++;
            }
        }
    } else {
        for (i = 0; i < 3; i++) {
            if (!(Battle_SlotIsBlocked(i) & BYTE_MASK)) {
                slot                               = Battle_AllocEffect(1, 109) & BYTE_MASK;
                owner                              = SELF(PartyMember);
                g_BattleEffects[slot].header.mode  = 0;
                g_BattleEffects[slot].unk_04       = i;
                g_BattleEffects[slot].target.party = owner;
                g_BattleEffects[slot].unk_0B       = SELF(PartyMember)->param.unk_0B;
                g_BattleEffects[slot].arg.unk_09   = (SELF(PartyMember)->param.unk_0B << 4) + 1;
                SELF(PartyMember)->param.unk_0B++;
            }
        }
    }
    i   = 1;
    dst = g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors;
    src = g_AreaPaletteArena->rows[AREA_PALETTE_BATL_OVR_ROW].colors;
    for (; i < 16; i++) {
        dst[i + 32] = src[i + 32] | PSX_COLOR_STP_BIT;
    }
    g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors[32] = 0;
    g_GfxPalettePending                                           = 1;
}

#include "overlays/bmagic/shared/Effect_NextStepOnZeroTick.h"

#include "shared/Effect_PlayOnce.h"

/* func_801EF04C */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EF090(void) {
    SYS_DISPATCH_TASK(D_801EF9B8, 2, g_Self);
}

MATCH void func_801EF0D4(void) {
    PartyMember* battler;
    PartyMember* task;
    PartyMember* owner;
    u8           slot;
    u8           i;

    if (--SELF(PartyMember)->unk_09 == 0) {
        if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
            battler = (PartyMember*)(g_BattleEnemies + SELF(PartyMember)->unk_04 * BATTLE_ENEMY_STRIDE);
        } else {
            battler = &g_Game.members[SELF(PartyMember)->unk_04];
        }
        SND_SEQueueSelection(0x100);
        SELF(PartyMember)->facing = battler->facing;
        task                      = SELF(PartyMember);
        WorldPos_Copy(&task->pos, &battler->pos);
        task->param.unk_0B = 0;
        SELF(PartyMember)->header.step++;
        for (i = 0; i < 3; i++) {
            slot = BMagic_AllocEffect();
            if (slot != 0xFF) {
                owner                                  = SELF(PartyMember);
                BMAGIC_EFFECT_SLOTS[slot].header.mode  = 0;
                BMAGIC_EFFECT_SLOTS[slot].unk_0B       = i;
                BMAGIC_EFFECT_SLOTS[slot].arg.unk_09   = i * 2 + 1;
                BMAGIC_EFFECT_SLOTS[slot].target.party = owner;
                SELF(PartyMember)->param.unk_0B++;
            }
        }
        Battle_ApplyDamageFlags(SELF(PartyMember)->unk_04, 0x10);
    }
}

#include "overlays/bmagic/shared/Effect_EndOnZeroTick.h"

MATCH void func_801EF2FC(void) {
    SYS_DISPATCH_TASK(D_801EF9C0, 1, g_Self);
}

MATCH void func_801EF340(void) {
    SYS_DISPATCH_BYTE(D_801EF9C4, SELF(PartyMember)->header.step);
    if (SELF(PartyMember)->header.flags != 0 && SELF(PartyMember)->header.step != 0) {
        Effect_DrawTexturedQuad();
    }
}

MATCH void func_801EF3B8(void) {
    PartyMember* battler;
    PartyMember* work;

    if (--SELF(PartyMember)->unk_09 == 0) {
        SELF(PartyMember)->facing = g_BattleEffectBattler->facing;
        battler                   = g_BattleEffectBattler;
        work                      = SELF(PartyMember);
        WorldPos_Copy(&work->pos, &battler->pos);
        work->unk_0C = D_801EF9D0[work->param.unk_0B].x;
        work->unk_10 = D_801EF9D0[work->param.unk_0B].y;
        Effect_RotatePosition(work);
        SELF(PartyMember)->pos.x.fixed += SELF(PartyMember)->unk_0C;
        SELF(PartyMember)->pos.y.fixed += SELF(PartyMember)->unk_10;
        SELF(PartyMember)->pos.z.fixed += D_801EF9D0[SELF(PartyMember)->param.unk_0B].z;
        Battle_ProjectRange();
        SELF(PartyMember)->unk_09 = 0;
        SELF(PartyMember)->timer  = 0;
        SELF(PartyMember)->header.step++;
    }
}

#include "overlays/bmagic/shared/Effect_CountUpTimersByTwoNextStep.h"

MATCH void func_801EF58C(void) {
    PartyMember* work;
    PartyMember* active;
    u8           count;

    work = SELF(PartyMember);
    work->unk_09++;
    work        = SELF(PartyMember);
    count       = work->timer - 1;
    work->timer = count;
    if (count == 0) {
        active = BATTLE_ACTIVE_WORK;
        active->param.unk_0B--;
        Actor_Clear();
    }
}

#include "overlays/bmagic/shared/Effect_DrawTexturedQuad.h"

/* func_801EF900 */
#include "overlays/bmagic/shared/BMagic_AllocEffect.h"

/* func_801EF964 */
#include "overlays/bmagic/shared/Actor_Clear.h"
