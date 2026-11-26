#include "magic009_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/func_801EEC28.h"

MATCH void func_801EEC98(void) {
    BattleEffect* slot;
    PartyMember*  work;
    u16*          dst;
    u16*          src;
    u32           index;
    u32           i;
    u8            active;

    TASK(PartyMember)->param.unk_0B = 0;
    TASK(PartyMember)->header.mode += 1;
    active = g_Battle.active_battler;
    if (BATTLER_IS_PLAYER(active)) {
        g_Game.members[active].unk_4B = 0xFF;
    } else {
        g_BattleEnemyBattlers[active - BATTLE_PARTY_CHARACTERS_COUNT].unk_4B = 0xFF;
    }
    Battle_SelectActiveBattlerScript(0x2C, 6);
    index  = Battle_AllocEffect(1, 42) & BYTE_MASK;
    active = g_Battle.active_battler;
    if (BATTLER_IS_PLAYER(active)) {
        BattleWorkImage* image;

        slot                    = &g_BattleEffects[index & BYTE_MASK];
        image                   = (BattleWorkImage*)&g_Game.members[active];
        *(BattleWorkImage*)slot = *image;
    } else {
        BattleWorkImage* image;
        u32              enemy;

        slot                    = &g_BattleEffects[index & BYTE_MASK];
        enemy                   = active - BATTLE_PARTY_CHARACTERS_COUNT;
        image                   = (BattleWorkImage*)&g_BattleEnemyBattlers[enemy];
        *(BattleWorkImage*)slot = *image;
    }
    work                                            = TASK(PartyMember);
    g_BattleEffects[index & BYTE_MASK].header.mode  = 1;
    g_BattleEffects[index & BYTE_MASK].unk_06       = 1;
    g_BattleEffects[index & BYTE_MASK].header.step  = 0;
    g_BattleEffects[index & BYTE_MASK].effect_type  = 42;
    g_BattleEffects[index & BYTE_MASK].target.party = work;
    TASK(PartyMember)->param.unk_0B += 1;
    i   = 1;
    src = MEM_PTR(u16, AREA_PALETTE_ARENA + 0x3402u);
    dst = MEM_PTR(u16, AREA_PALETTE_WORK + 0x3402u);
    for (; i < 16; i++) {
        dst[0x20] = src[0x20] | PSX_COLOR_STP_BIT;
        src++;
        dst++;
    }
    *MEM_PTR(u16, AREA_PALETTE_WORK + 0x3440u) = 0;
    g_GfxPalettePending                        = 1;
    g_BattleEffectBattler->header.flags |= PARTY_MEMBER_FLAG_HANDLER_BUSY;
}

MATCH void func_801EEF08(void) {
    u32 slot;
    u32 i;

    if (TASK(PartyMember)->param.unk_0B == 0) {
        i = 0;
        do {
            slot                               = Battle_AllocEffect(1, 42) & BYTE_MASK;
            g_BattleEffects[slot].target.party = TASK(PartyMember);
            g_BattleEffects[slot].header.mode  = 0;
            g_BattleEffects[slot].unk_0B       = i;
            g_BattleEffects[slot].arg.unk_09   = i * 4 + 1;
            TASK(PartyMember)->param.unk_0B += 1;
            i++;
        } while (i < 3);
        Battle_SelectActiveBattlerScript(4, 0);
        BATTLE_ACTIVE_WORK->header.flags &= ~PARTY_MEMBER_FLAG_HANDLER_BUSY;
        SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0));
        TASK(PartyMember)->unk_09 = 8;
        TASK(PartyMember)->header.mode += 1;
    }
}

#include "overlays/bmagic/shared/Effect_CountDownTimerNextStep.h"

#include "overlays/bmagic/shared/Effect_NextStepOnZeroTick.h"

MATCH void func_801EF09C(void) {
    u16* battle_flags;

    battle_flags = &g_BattleState;
    *battle_flags |= 0x2004;
    Battle_MarkDamaged(*(battle_flags = &g_Battle.target_selector));
    Effect_Reset();
}

/* func_801EF0DC */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EF120(void) {
    SYS_DISPATCH_BYTE(D_801EF8A4, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->header.flags != 0 && TASK(PartyMember)->header.step != 0) {
        func_801EF3B8();
    }
}

MATCH void func_801EF198(void) {
    PartyMember* actor;
    PartyMember* work;
    u8           count;

    count                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        actor                     = g_BattleSelectedActor;
        TASK(PartyMember)->facing = actor->facing;
        work                      = TASK(PartyMember);
        work->unk_0C              = D_801EF8B0[work->param.unk_0B].x;
        work->unk_10              = D_801EF8B0[work->param.unk_0B].y;
        Effect_RotatePosition(work);
        TASK(PartyMember)->pos.x.fixed = actor->pos.x.fixed + TASK(PartyMember)->unk_0C;
        TASK(PartyMember)->pos.y.fixed = actor->pos.y.fixed + TASK(PartyMember)->unk_10;
        TASK(PartyMember)->pos.z.fixed = actor->pos.z.fixed + D_801EF8B0[TASK(PartyMember)->param.unk_0B].z;
        func_800AF764();
        TASK(PartyMember)->timer = 0;
        TASK(PartyMember)->header.step += 1;
    }
}

#include "overlays/bmagic/shared/Effect_CountUpTimersByTwoNextStep.h"

/* func_801EF340 */
MATCH void Effect_CountDownTimer(void) {
    BMagic_CountDownEffectTimer(1);
}

MATCH void func_801EF3B8(void) {
    POLY_FT4* prim;
    s32       tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));
    g_ScratchPad.cells.words[0] = TASK(PartyMember)->unk_09 << 1;
    prim                        = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    SetSemiTrans(prim, 1);
    setXY4(prim, TASK(PartyMember)->screen_x.value + FIXED_MUL(rcos(512), g_ScratchPad.cells.words[0]), TASK(PartyMember)->screen_y.value + FIXED_MUL(rsin(512), g_ScratchPad.cells.words[0]),
           TASK(PartyMember)->screen_x.value + FIXED_MUL(rcos(1536), g_ScratchPad.cells.words[0]), TASK(PartyMember)->screen_y.value + FIXED_MUL(rsin(1536), g_ScratchPad.cells.words[0]),
           TASK(PartyMember)->screen_x.value + FIXED_MUL(rcos(3584), g_ScratchPad.cells.words[0]), TASK(PartyMember)->screen_y.value + FIXED_MUL(rsin(3584), g_ScratchPad.cells.words[0]),
           TASK(PartyMember)->screen_x.value + FIXED_MUL(rcos(2560), g_ScratchPad.cells.words[0]), TASK(PartyMember)->screen_y.value + FIXED_MUL(rsin(2560), g_ScratchPad.cells.words[0]));
    prim->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 832, 256);
    prim->clut  = GetClut(32, 506);
    setUVWH(prim, 128, 32, 32, 32);
    setRGB0(prim, TASK(PartyMember)->timer * 10, 0, TASK(PartyMember)->timer * 9);
    Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 2, sizeof(POLY_FT4));
}

MATCH void func_801EF6B0(void) {
    Magic009Steps handlers;

    handlers = D_801EEC18;
    SYS_DISPATCH_BYTE(handlers.steps, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->header.flags != 0) {
        Area_AddGridActor();
    }
}

#include "overlays/bmagic/shared/Effect_SetDuration.h"

MATCH void func_801EF788(void) {
    u8 timer;
    u8 next;

    timer = TASK(PartyMember)->unk_09;
    if ((timer & BYTE_MASK) != 0xFF) {
        next                      = timer - 1;
        TASK(PartyMember)->unk_09 = next;
        if (!(next & BYTE_MASK)) {
            Battle_PlayActiveBattlerSE(2, 5);
        }
    }
    if (Script_AnimStepOnce() & BYTE_MASK) {
        TASK(PartyMember)->unk_09 = 8;
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF814(void) {
    u8 count;

    count                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF87C(void) {
    Effect_Reset();
}
