#include "magic021_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC28(void) {
    MagicModuleSteps handlers = D_801EEC04;
    PartyMember*     saved_task;
    PartyMember*     saved_battler;
    u8               i;

    SYS_DISPATCH_BYTE(handlers.steps, TASK(PartyMember)->header.mode);

    BMAGIC_RUN_EFFECT_SLOTS(D_801EFE14, func_801EF534);
}

MATCH void func_801EED30(void) {
    BattleEffect* slot;
    PartyMember*  work;
    u32           index;
    u8            active;
    u32           i;

    BMAGIC_CLEAR_EFFECTS(i);
    TASK(PartyMember)->param.unk_0B = 0;
    TASK(PartyMember)->header.mode += 1;
    Battle_SelectActiveBattlerScript(0xC, 2);
    index  = Battle_AllocEffect(1, 9) & BYTE_MASK;
    active = g_Battle.active_battler;
    if (BATTLER_IS_PLAYER(active)) {
        BattleWorkImage* image;

        image                   = (BattleWorkImage*)&g_Game.members[active];
        slot                    = &g_BattleEffects[index];
        *(BattleWorkImage*)slot = *image;
    } else {
        BattleWorkImage* image;
        u32              enemy;

        slot                    = &g_BattleEffects[index];
        enemy                   = active - BATTLE_PARTY_CHARACTERS_COUNT;
        image                   = (BattleWorkImage*)&g_BattleEnemyBattlers[enemy];
        *(BattleWorkImage*)slot = *image;
    }
    work                                = TASK(PartyMember);
    g_BattleEffects[index].unk_06       = 1;
    g_BattleEffects[index].header.mode  = 0;
    g_BattleEffects[index].header.step  = 0;
    g_BattleEffects[index].effect_type  = 9;
    g_BattleEffects[index].target.party = work;
    TASK(PartyMember)->param.unk_0B += 1;
    g_BattleEffectBattler->header.flags |= PARTY_MEMBER_FLAG_HANDLER_BUSY;
}

#include "overlays/bmagic/shared/Effect_ReleaseActiveBattlerOnTickerZero.h"

#include "shared/Effect_StartPlaying.h"

/* func_801EEFDC */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EF020(void) {
    BMagicEffectSteps handlers;

    handlers = D_801EEC10;
    SYS_DISPATCH_BYTE(handlers.steps, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->header.flags != 0) {
        Area_AddGridActor();
    }
}

#include "overlays/bmagic/shared/Effect_SetDuration.h"

MATCH void func_801EF104(void) {
    PartyMember* work;
    u32          slot;
    u8           i;
    u8           timer;

    Script_AnimStepOnce();
    timer                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = timer;
    if (timer != 0) {
        return;
    }
    SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0));
    TASK(PartyMember)->unk_09       = 0;
    TASK(PartyMember)->param.unk_0B = 0;
    for (i = 0; i < 12; i++) {
        slot                                   = BMagic_AllocEffect() & BYTE_MASK;
        work                                   = TASK(PartyMember);
        BMAGIC_EFFECT_SLOTS[slot].arg.unk_09   = (i >> 1) * 3 + 1;
        BMAGIC_EFFECT_SLOTS[slot].target.party = work;
        TASK(PartyMember)->param.unk_0B += 1;
    }
    TASK(PartyMember)->header.step += 1;
}

MATCH void func_801EF208(void) {
    if (Script_AnimStepOnce() != 0u) {
        Battle_MarkDamaged(g_Battle.target_selector);
        TASK(PartyMember)->header.step = TASK(PartyMember)->header.step + 1;
    }
}

MATCH void func_801EF260(void) {
    if ((u8)TASK(PartyMember)->unk_09 < 0xCU) {
        Effect_DrawScreenFade();
        TASK(PartyMember)->unk_09 += 4;
        return;
    }
    TASK(PartyMember)->header.step += 1;
}

MATCH void func_801EF2CC(void) {
    if (TASK(PartyMember)->param.unk_0B == 0) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF328(void) {
    Effect_Reset();
}

#include "overlays/bmagic/shared/Effect_DrawScreenFade.h"

MATCH void func_801EF534(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 1), 1, g_Task);
}

MATCH void func_801EF578(void) {
    SYS_DISPATCH_BYTE(D_801EFE08, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->header.flags != 0 && TASK(PartyMember)->header.step != 0) {
        Battle_ProjectRange();
        func_801EF7FC();
        func_801EFA48();
    }
}

MATCH void func_801EF600(void) {
    PartyMember* actor;
    PartyMember* work;
    s16*         radius_cell;
    u32          offset;
    u16          phase;
    u8           count;

    count                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        offset                 = rand() & 0x7;
        actor                  = g_BattleSelectedActor;
        work                   = TASK(PartyMember);
        work->pos.x.fixed      = actor->pos.x.fixed;
        work->pos.y.fixed      = actor->pos.y.fixed;
        COORD_INT(work->pos.z) = (s16)((u16)COORD_INT(actor->pos.z) + (offset << 5));
        radius_cell            = &g_ScratchPadHalves;
        *radius_cell           = 0xC0 - (offset << 4);
        phase                  = rand() & 0x7;
        D_1F800004             = phase << 9;
        TASK(PartyMember)->pos.x.fixed += (rsin(phase << 9) * *radius_cell) >> 3;
        FAKE_BARRIER(); /* FAKE: keeps the angle load after the x update, as retail does. */
        TASK(PartyMember)->pos.y.fixed += (rcos(D_1F800004) * *radius_cell) >> 3;
        TASK(PartyMember)->unk_09 = 0;
        TASK(PartyMember)->timer  = 16;
        TASK(PartyMember)->header.step += 1;
    }
}

#include "overlays/bmagic/shared/Effect_CountUpByTwoAndStep.h"

MATCH void func_801EF7A0(void) {
    PartyMember* work;

    work        = TASK(PartyMember);
    work->timer = work->timer - 2;
    if (work->timer == 0) {
        work               = (PartyMember*)g_BattleEffectBattler;
        work->param.unk_0B = work->param.unk_0B - 1;
        Actor_Clear();
    }
}

MATCH void func_801EF7FC(void) {
    POLY_G3* prim;
    s32      tpage;
    s32      i;
    u8       red;
    u8       green;
    u8       blue;
    u8       green_edge;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));
    g_ScratchPad.cells.halves[2] = 0;
    red                          = TASK(PartyMember)->timer * 12;
    green                        = TASK(PartyMember)->timer * 11;
    green_edge                   = TASK(PartyMember)->timer * 8;
    blue                         = TASK(PartyMember)->timer * 4;
    g_ScratchPad.cells.halves[0] = TASK(PartyMember)->unk_09 * 2;
    g_ScratchPad.cells.halves[4] = TASK(PartyMember)->screen_x.value;
    g_ScratchPad.cells.halves[5] = TASK(PartyMember)->screen_y.value;
    i                            = 0;
    do {
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        setXY2(prim, g_ScratchPad.cells.halves[4], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[4] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]),
               g_ScratchPad.cells.halves[5] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]));
        g_ScratchPad.cells.halves[2] = (i + 1) << 8;
        prim->x2                     = g_ScratchPad.cells.halves[4] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        prim->y2                     = g_ScratchPad.cells.halves[5] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        setRGB0(prim, red, green, blue);
        setRGB1(prim, red, green_edge, blue);
        setRGB2(prim, red, green_edge, blue);
        Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 2, sizeof(POLY_G3));
        i++;
    } while (i < 16);
}

/* Draw the magic021 ring as sixteen shaded quads between two radii around the effect,
 * tinted on the inner edge by the timer and dark on the outer one. */
MATCH void func_801EFA48(void) {
    POLY_G4* prim;
    s32      tpage;
    s32      i;
    u8       red;
    u8       green;
    u8       blue;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    i = 0;
    Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));
    g_ScratchPad.cells.halves[2] = 0;
    red                          = TASK(PartyMember)->timer * 12;
    green                        = TASK(PartyMember)->timer * 6;
    blue                         = TASK(PartyMember)->timer * 4;
    g_ScratchPad.cells.halves[0] = TASK(PartyMember)->unk_09 * 2;
    g_ScratchPad.cells.halves[1] = TASK(PartyMember)->unk_09 * 3;
    g_ScratchPad.cells.halves[4] = TASK(PartyMember)->screen_x.value;
    g_ScratchPad.cells.halves[5] = TASK(PartyMember)->screen_y.value;
    do {
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setXY0(prim, g_ScratchPad.cells.halves[4] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]),
               g_ScratchPad.cells.halves[5] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]));
        prim->x2                     = g_ScratchPad.cells.halves[4] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[1]);
        prim->y2                     = g_ScratchPad.cells.halves[5] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[1]);
        g_ScratchPad.cells.halves[2] = (i + 1) << 8;
        prim->x1                     = g_ScratchPad.cells.halves[4] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        prim->y1                     = g_ScratchPad.cells.halves[5] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[0]);
        prim->x3                     = g_ScratchPad.cells.halves[4] + FIXED_MUL(rsin(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[1]);
        prim->y3                     = g_ScratchPad.cells.halves[5] + FIXED_MUL(rcos(g_ScratchPad.cells.halves[2]), g_ScratchPad.cells.halves[1]);
        setRGB0(prim, red, green, blue);
        setRGB1(prim, red, green, blue);
        setRGB2(prim, 1, 1, 1);
        setRGB3(prim, 1, 1, 1);
        Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 2, sizeof(POLY_G4));
        i++;
    } while (i < 16);
}

/* func_801EFD4C */
#include "overlays/bmagic/shared/BMagic_AllocEffect.h"

/* func_801EFDB0 */
#include "overlays/bmagic/shared/Actor_Clear.h"
