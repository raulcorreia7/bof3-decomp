#include "magic154_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/func_801EEC24.h"

#include "overlays/bmagic/shared/Effect_CopyActiveBattlerToSlot.h"

MATCH void func_801EEC90(void) {
    PartyMember* work;
    u32          slot;
    u32          i;
    u16*         dst;
    u16*         src;

    Battle_SelectActiveBattlerScript(12, 2);
    slot = Battle_AllocEffect(1, 82) & BYTE_MASK;
    Effect_CopyActiveBattlerToSlot(slot);
    BMAGIC_POINT_AT_PALETTE_ROW(dst, src, i);
    work                               = SELF(PartyMember);
    g_BattleEffects[slot].header.mode  = 1;
    g_BattleEffects[slot].unk_06       = 1;
    g_BattleEffects[slot].header.step  = 0;
    g_BattleEffects[slot].effect_type  = 82;
    g_BattleEffects[slot].target.party = work;
    for (; i < 16; i++) {
        *dst++ = *src++;
    }
    g_GfxPalettePending = 1;
    g_BattleEffectBattler->header.flags |= 0x40;
    SELF(PartyMember)->param.unk_0B = 1;
    SELF(PartyMember)->unk_09       = 1;
    SELF(PartyMember)->header.mode++;
}

MATCH void func_801EEE94(void) {
    u32          i;
    s8           anchor;
    u8           slot;
    PartyMember* actor;
    PartyMember* work;

    if (SELF(PartyMember)->param.unk_0B == 0) {
        actor                     = g_Battle.selected_actor;
        SELF(PartyMember)->facing = actor->facing;
        SELF(PartyMember)->unk_0C = 0;
        SELF(PartyMember)->unk_10 = -TO_COORD_HALF(1);
        Effect_RotatePosition(g_Self);
        SELF(PartyMember)->pos.x.fixed = actor->pos.x.fixed + SELF(PartyMember)->unk_0C;
        SELF(PartyMember)->pos.y.fixed = actor->pos.y.fixed + SELF(PartyMember)->unk_10;
        SELF(PartyMember)->pos.z.fixed = actor->pos.z.fixed;
        SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0x00));
        for (i = 0, anchor = 1; i < 6; i++) {
            slot                               = Battle_AllocEffect(1, 82) & BYTE_MASK;
            work                               = SELF(PartyMember);
            g_BattleEffects[slot].header.mode  = 0;
            g_BattleEffects[slot].unk_0B       = i;
            g_BattleEffects[slot].arg.unk_09   = anchor;
            g_BattleEffects[slot].target.party = work;
            SELF(PartyMember)->param.unk_0B += 1;
            anchor += 3;
        }
        SELF(PartyMember)->header.mode += 1;
    }
}

MATCH void func_801EEFE0(void) {
    if (SELF(PartyMember)->unk_09 == 0) {
        Battle_SelectActiveBattlerScript(4, 0);
        BATTLE_ACTIVE_WORK->header.flags &= ~PARTY_MEMBER_FLAG_HANDLER_BUSY;
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10U);
        SELF(PartyMember)->header.mode += 1;
    }
}

#include "overlays/bmagic/shared/Effect_MarkDamagedOnZeroTick.h"

/* func_801EF0C0 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EF104(void) {
    GFX_AddDitheredDrawMode(BMAGIC_LAYER_OVER_BATTLERS, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256));
    g_Scripts = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(g_BMagicEffectModes + 2, SELF(PartyMember)->header.step);
    if (SELF(PartyMember)->header.flags != 0 && SELF(PartyMember)->header.step != 0) {
        Area_AddGridActor();
    }
    g_Scripts = AREA_SCRIPT_TABLE;
}

MATCH void func_801EF1EC(void) {
    u8 timer;

    timer                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        SELF(PartyMember)->facing = g_BattleEffectBattler->facing;
        SELF(PartyMember)->unk_0C = 0;
        SELF(PartyMember)->unk_10 = SELF(PartyMember)->param.unk_0B << 0xF;
        Effect_RotatePosition(g_Self);
        SELF(PartyMember)->pos.x.fixed  = g_BattleEffectBattler->pos.x.fixed + SELF(PartyMember)->unk_0C;
        SELF(PartyMember)->pos.y.fixed  = g_BattleEffectBattler->pos.y.fixed + SELF(PartyMember)->unk_10;
        SELF(PartyMember)->pos.z.fixed  = g_BattleEffectBattler->pos.z.fixed;
        SELF(PartyMember)->scale.x      = 0x8000;
        SELF(PartyMember)->scale.y      = 0x8000;
        SELF(PartyMember)->unk_48       = 2;
        SELF(PartyMember)->unk_25       = 0x1D;
        SELF(PartyMember)->unk_26       = 0;
        SELF(PartyMember)->unk_27       = 0xA0;
        SELF(PartyMember)->unk_28       = 0;
        SELF(PartyMember)->unk_2A       = SELF(PartyMember)->facing & 0x1;
        SELF(PartyMember)->unk_29       = 3;
        SELF(PartyMember)->unk_24       = 4;
        SELF(PartyMember)->unk_2C.value = 0;
        SELF(PartyMember)->unk_2B       = 0;
        Script_Select(0U);
        Script_AnimStepLoop();
        SELF(PartyMember)->unk_09 = 0;
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF380(void) {
    PartyMember* work;
    u8           count;

    work = SELF(PartyMember);
    work->scale.x += 0x4000;
    count        = work->unk_09 + 1;
    work->unk_09 = count;
    work->scale.y += 0x8000;
    if (count == 4) {
        SELF(PartyMember)->header.step++;
    }
}

MATCH void func_801EF3E4(void) {
    PartyMember* work = SELF(PartyMember);
    u8           timer;
    work->scale.x -= 0x4000;
    timer        = work->unk_09 - 1;
    work->unk_09 = timer;
    work->scale.y -= 0x8000;
    if (timer == 0) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        Effect_Reset();
    }
}

MATCH void func_801EF454(void) {
    SELF(PartyMember)->scale.y -= 0x1000;
    if ((s8)SELF(PartyMember)->unk_5F == -0x80) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        Effect_Reset();
    }
}

MATCH void func_801EF4B4(void) {
    Magic154Steps handlers = D_801EEC14;

    SYS_DISPATCH_BYTE(handlers.steps, SELF(PartyMember)->header.step);
    if (SELF(PartyMember)->header.flags != 0) {
        Area_AddGridActor();
    }
}

#include "overlays/bmagic/shared/Effect_SetDuration.h"

MATCH void func_801EF58C(void) {
    u8 timer;

    timer                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        Script_AnimStepOnce();
        Battle_PlayActiveBattlerSE(2, 4);
        g_BattleEffectBattler->param.unk_0B -= 1;
        SELF(PartyMember)->header.step += 1;
    } else if (Script_AnimStepOnce() & BYTE_MASK) {
        Battle_PlayActiveBattlerSE(2, 4);
        SELF(PartyMember)->unk_09 = 0;
        g_BattleEffectBattler->param.unk_0B -= 1;
        SELF(PartyMember)->header.step += 1;
    }
}

/* Lowers the effect ticker step once the effect is ready. */
/* func_801EF648 */
MATCH void Effect_LowerTickerStepOnReady(void) {
    if (Script_AnimStepOnce() & BYTE_MASK) {
        BATTLE_ACTIVE_WORK->unk_09--;
        SELF(PartyMember)->header.step++;
    }
}

MATCH void func_801EF6AC(void) {
    Effect_Reset();
}
