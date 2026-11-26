#include "magic001_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/BMagic_DispatchMode.h"

MATCH void func_801EECC4(void) {
    BattleEffect* slot;
    PartyMember*  work;
    u32           index;
    u8            active;

    SELF(PartyMember)->facing = g_BattleEffectBattler->facing;
    WorldPos_Copy(&SELF(PartyMember)->pos, &g_BattleEffectBattler->pos);
    SELF(PartyMember)->param.unk_0B = 1;
    index                           = Battle_AllocEffect(1, 73);
    active                          = g_Battle.active_battler;
    if (BATTLER_IS_PLAYER(active)) {
        BattleWorkImage* image;

        image                   = (BattleWorkImage*)&g_Game.members[active];
        slot                    = &g_BattleEffects[index & BYTE_MASK];
        *(BattleWorkImage*)slot = *image;
    } else {
        BattleWorkImage* image;
        u32              enemy;

        slot                    = &g_BattleEffects[index & BYTE_MASK];
        enemy                   = active - BATTLE_PARTY_CHARACTERS_COUNT;
        image                   = (BattleWorkImage*)&g_BattleEnemyBattlers[enemy];
        *(BattleWorkImage*)slot = *image;
    }
    work                                            = SELF(PartyMember);
    g_BattleEffects[index & BYTE_MASK].unk_06       = 1;
    g_BattleEffects[index & BYTE_MASK].header.mode  = 0;
    g_BattleEffects[index & BYTE_MASK].header.step  = 0;
    g_BattleEffects[index & BYTE_MASK].effect_type  = 73;
    g_BattleEffects[index & BYTE_MASK].arg.unk_09   = 0;
    g_BattleEffects[index & BYTE_MASK].target.party = work;
    SELF(PartyMember)->unk_27                       = Battle_CopyCellPalette(g_BattleEffectBattler);
    SELF(PartyMember)->unk_28                       = g_BattleEffectBattler->unk_28;
    SELF(PartyMember)->unk_24                       = g_BattleEffectBattler->unk_24;
    Battle_SetCellPaletteStp(SELF(PartyMember));
    g_BattleEffectBattler->header.flags |= PARTY_MEMBER_FLAG_HANDLER_BUSY;
    SELF(PartyMember)->header.mode += 1;
}

MATCH void func_801EEF34(void) {
    BMagic_ClearWorkFlagsAndStep();
}

#include "shared/Effect_StartPlaying.h"

/* func_801EEFD8 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EF01C(void) {
    Magic001Steps handlers;

    handlers = D_801EEC10;
    SYS_DISPATCH_BYTE(handlers.steps, SELF(PartyMember)->header.step);
    if (SELF(PartyMember)->header.flags != 0 && SELF(PartyMember)->header.step != 0) {
        Area_AddGridActor();
    }
}

MATCH void func_801EF0E8(void) {
    func_801E257C(g_Battle.active_battler, 10U);
    SELF(PartyMember)->unk_27 = g_BattleEffectBattler->unk_27;
    SELF(PartyMember)->unk_09 = 0;
    SELF(PartyMember)->timer  = 0;
    SELF(PartyMember)->header.step += 1;
}

MATCH void func_801EF164(void) {
    if (Script_AnimStepOnce() & BYTE_MASK) {
        Battle_PlayActiveBattlerSE(2, 0);
        func_801E257C(g_Battle.active_battler, 11U);
        SELF(PartyMember)->unk_14 = 0x100;
        SELF(PartyMember)->unk_20 = -8;
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF1CC(void) {
    SELF(PartyMember)->unk_14 += SELF(PartyMember)->unk_20;
    SELF(PartyMember)->pos.z.part.integer += SELF(PartyMember)->unk_14;
    if (SELF(PartyMember)->unk_14 == 0) {
        SELF(PartyMember)->pos.x.fixed = g_Battle.selected_actor->pos.x.fixed;
        SELF(PartyMember)->pos.y.fixed = g_Battle.selected_actor->pos.y.fixed;
        SELF(PartyMember)->pos.z.fixed -= g_BattleEffectBattler->pos.z.fixed - g_Battle.selected_actor->pos.z.fixed;
        SELF(PartyMember)->unk_09 = 0x1F;
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF280(void) {
    PartyMember* work;
    u8           timer;

    work         = SELF(PartyMember);
    timer        = work->unk_09 - 1;
    work->unk_09 = timer;
    work->unk_14 += work->unk_20;
    COORD_INT(work->pos.z) += work->unk_14;
    if (timer == 0) {
        SND_SEQueueSelection(0x203);
        func_801E257C(g_Battle.active_battler, 12);
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10);
        SELF(PartyMember)->unk_09 = 3;
        SELF(PartyMember)->header.step++;
    }
}

MATCH void func_801EF324(void) {
    if (Script_AnimStepOnce() != 0u) {
        func_801E257C(g_Battle.active_battler, 10);
        SELF(PartyMember)->header.step = SELF(PartyMember)->header.step + 1;
    }
}

MATCH void func_801EF37C(void) {
    PartyMember* work;

    Script_AnimStepOnce();
    Script_AnimStepOnce();
    if (Script_AnimStepOnce() & BYTE_MASK) {
        Battle_PlayActiveBattlerSE(2, 0);
        func_801E257C(g_Battle.active_battler, 11);
        work         = SELF(PartyMember);
        work->unk_14 = 0x140;
        work->timer  = 9;
        work->unk_20 = -0x40;
        SELF(PartyMember)->header.step++;
    }
}

MATCH void func_801EF408(void) {
    PartyMember* work  = SELF(PartyMember);
    u8           timer = work->timer - 1;
    s32          value = work->unk_14 + work->unk_20;
    work->timer        = timer;
    work->unk_14       = value;
    COORD_INT(work->pos.z) += value;
    if (timer == 0) {
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF468(void) {
    u8 timer;

    Script_AnimStepOnce();
    Script_AnimStepOnce();
    if (Script_AnimStepOnce() & BYTE_MASK) {
        SND_SEQueueSelection(0x203);
        func_801E257C(g_Battle.active_battler, 12);
        timer                     = SELF(PartyMember)->unk_09 - 1;
        SELF(PartyMember)->unk_09 = timer;
        if (timer != 0) {
            SELF(PartyMember)->header.step -= 3;
        } else {
            SELF(PartyMember)->header.step++;
        }
    }
}

MATCH void func_801EF518(void) {
    if (Script_AnimStepOnce() & BYTE_MASK) {
        Battle_MarkDamaged(g_Battle.target_selector);
        SELF(PartyMember)->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
        SELF(PartyMember)->unk_5C = 1;
        SELF(PartyMember)->unk_5D = 0;
        SELF(PartyMember)->unk_5E = 0;
        SELF(PartyMember)->unk_5F = 0;
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF5CC(void) {
    PartyMember* work;
    PartyMember* source;
    s8           count;

    count = SELF(PartyMember)->unk_5D;
    if (count != -0x80) {
        SELF(PartyMember)->unk_5D = count - 0x10;
        SELF(PartyMember)->unk_5E -= 16;
        SELF(PartyMember)->unk_5F -= 16;
    }
    if ((s8)SELF(PartyMember)->unk_5D == -128) {
        work   = SELF(PartyMember);
        source = BATTLE_ACTIVE_WORK;
        WorldPos_Copy(&work->pos, &source->pos);
        work->header.step += 1;
    }
}

#include "overlays/bmagic/shared/Effect_RampTintAndFinish.h"

MATCH void func_801EF688(void) {
    EFFECT_RAMP_TINT_AND_FINISH();
}

MATCH void func_801EF72C(void) {
    Magic001SecondSteps handlers;

    handlers = D_801EEC3C;
    SYS_DISPATCH_TASK(handlers.steps, 1, g_Self);
}

/* Copy the active battler into a new effect as func_801EECC4 does, then take the battler sprite
 * cell and pass it to Battle_SetCellPaletteStp and Battle_ClearCellPaletteEntry. */
MATCH void func_801EF78C(void) {
    BattleEffect* slot;
    PartyMember*  work;
    u32           index;
    u8            active;

    SELF(PartyMember)->facing = g_BattleEffectBattler->facing;
    WorldPos_Copy(&SELF(PartyMember)->pos, &g_BattleEffectBattler->pos);
    SELF(PartyMember)->param.unk_0B = 1;
    Battle_SelectActiveBattlerScript(8, 0);
    index  = Battle_AllocEffect(1, 79);
    active = g_Battle.active_battler;
    if (BATTLER_IS_PLAYER(active)) {
        BattleWorkImage* image;

        image                   = (BattleWorkImage*)&g_Game.members[active];
        slot                    = &g_BattleEffects[index & BYTE_MASK];
        *(BattleWorkImage*)slot = *image;
    } else {
        BattleWorkImage* image;
        u32              enemy;

        slot                    = &g_BattleEffects[index & BYTE_MASK];
        enemy                   = active - BATTLE_PARTY_CHARACTERS_COUNT;
        image                   = (BattleWorkImage*)&g_BattleEnemyBattlers[enemy];
        *(BattleWorkImage*)slot = *image;
    }
    work                                            = SELF(PartyMember);
    g_BattleEffects[index & BYTE_MASK].unk_06       = 1;
    g_BattleEffects[index & BYTE_MASK].header.mode  = 0;
    g_BattleEffects[index & BYTE_MASK].header.step  = 0;
    g_BattleEffects[index & BYTE_MASK].effect_type  = 79;
    g_BattleEffects[index & BYTE_MASK].arg.unk_09   = 0;
    g_BattleEffects[index & BYTE_MASK].target.party = work;
    SELF(PartyMember)->unk_27                       = Battle_CopyCellPalette(g_BattleEffectBattler);
    SELF(PartyMember)->unk_28                       = g_BattleEffectBattler->unk_28;
    SELF(PartyMember)->unk_24                       = g_BattleEffectBattler->unk_24;
    Battle_SetCellPaletteStp(SELF(PartyMember));
    Battle_ClearCellPaletteEntry(g_Self);
    g_BattleEffectBattler->header.flags |= PARTY_MEMBER_FLAG_HANDLER_BUSY;
    SELF(PartyMember)->header.mode += 1;
}

MATCH void func_801EFA14(void) {
    BMagic_ClearWorkFlagsAndStep();
}

MATCH void Effect_StartPlaying6(void) {
    u16* flags;

    BATTLE_RAISE_EFFECT_PLAYING();
}

MATCH void func_801EFAB8(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 1), 1, g_Self);
}

MATCH void func_801EFAFC(void) {
    Callback handlers[7];

    memcpy(handlers, D_801EEC48, sizeof(handlers));
    SYS_DISPATCH_BYTE(handlers, SELF(PartyMember)->header.step);
    if (SELF(PartyMember)->header.flags != 0 && SELF(PartyMember)->header.step != 0) {
        Area_AddGridActor();
        if (SELF(PartyMember)->header.step < 5) {
            func_801F014C();
            func_801F0238();
            PopMatrix();
        }
    }
}

MATCH void func_801EFBEC(void) {
    SELF(PartyMember)->unk_27 = g_BattleEffectBattler->unk_27;
    SELF(PartyMember)->unk_14 = 0x100;
    SELF(PartyMember)->unk_20 = -0x10;
    SELF(PartyMember)->unk_09 = 0;
    SELF(PartyMember)->timer  = 16;
    SELF(PartyMember)->header.step += 1;
}

MATCH void func_801EFC54(void) {
    SELF(PartyMember)->unk_14 += SELF(PartyMember)->unk_20;
    SELF(PartyMember)->pos.z.part.integer += SELF(PartyMember)->unk_14;
    if (SELF(PartyMember)->timer != 0) {
        SELF(PartyMember)->timer -= 1;
    }
    if (SELF(PartyMember)->unk_14 == 0) {
        SELF(PartyMember)->pos.x.fixed = g_Battle.selected_actor->pos.x.fixed;
        SELF(PartyMember)->pos.y.fixed = g_Battle.selected_actor->pos.y.fixed;
        SELF(PartyMember)->pos.z.fixed -= g_BattleEffectBattler->pos.z.fixed - g_Battle.selected_actor->pos.z.fixed;
        SELF(PartyMember)->unk_09 = 0x0F;
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EFD28(void) {
    s32 value;
    u8  timer;
    u8  next;

    timer                               = SELF(PartyMember)->timer;
    value                               = SELF(PartyMember)->unk_14 + SELF(PartyMember)->unk_20;
    SELF(PartyMember)->unk_14           = value;
    COORD_INT(SELF(PartyMember)->pos.z) = COORD_INT(SELF(PartyMember)->pos.z) + value;
    if (timer < 8U) {
        SELF(PartyMember)->timer = timer + 1;
    }
    next                      = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = next;
    if (!(next & BYTE_MASK)) {
        Battle_PlayActiveBattlerSE(2, 0);
        SND_SEQueueSelection(0x203);
        SELF(PartyMember)->unk_14 = 0x40;
        SELF(PartyMember)->unk_20 = -8;
        SELF(PartyMember)->unk_0C = ratan2(g_BattleEffectBattler->pos.x.fixed - SELF(PartyMember)->pos.x.fixed, g_BattleEffectBattler->pos.y.fixed - SELF(PartyMember)->pos.y.fixed);
        Battle_MarkDamaged(g_Battle.target_selector);
        SELF(PartyMember)->unk_09 = 0x10;
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EFE38(void) {
    s32 value;
    u8  value2;
    u8  value3;

    SELF(PartyMember)->pos.x.fixed += (rsin(SELF(PartyMember)->unk_0C) << 0xD) >> 0xC;
    SELF(PartyMember)->pos.y.fixed += (rcos(SELF(PartyMember)->unk_0C) << 0xD) >> 0xC;
    value                               = SELF(PartyMember)->unk_14 + SELF(PartyMember)->unk_20;
    SELF(PartyMember)->unk_14           = value;
    COORD_INT(SELF(PartyMember)->pos.z) = COORD_INT(SELF(PartyMember)->pos.z) + value;
    if (SELF(PartyMember)->unk_09 < 8U) {
        value3 = SELF(PartyMember)->timer;
        if (value3 < 0x10U) {
            SELF(PartyMember)->timer = value3 + 1;
        }
    }
    value2                    = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = value2;
    if (!(value2 & BYTE_MASK)) {
        SELF(PartyMember)->header.step += 1;
    }
}

#include "overlays/bmagic/shared/Effect_PrimeTintOnScriptReady.h"

MATCH void func_801EFFCC(void) {
    PartyMember* work;
    PartyMember* source;
    s8           count;
    u8           timer;

    count = SELF(PartyMember)->unk_5D;
    if (count != -0x80) {
        SELF(PartyMember)->unk_5D = count - 0x10;
        SELF(PartyMember)->unk_5E -= 16;
        SELF(PartyMember)->unk_5F -= 16;
    }
    timer = SELF(PartyMember)->timer;
    if (timer != 0) {
        SELF(PartyMember)->timer = timer - 2;
    }
    if ((s8)SELF(PartyMember)->unk_5D == -128) {
        work   = SELF(PartyMember);
        source = BATTLE_ACTIVE_WORK;
        WorldPos_Copy(&work->pos, &source->pos);
        work->header.step += 1;
    }
}

MATCH void func_801F00A8(void) {
    EFFECT_RAMP_TINT_AND_FINISH();
}

MATCH void func_801F014C(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    rot.vz = 0;
    rot.vy = 0;
    rot.vx = 0;
    pos.vx = (SELF(PartyMember)->pos.x.fixed >> 9) - AREA_CELL_ORIGIN;
    pos.vy = (SELF(PartyMember)->pos.y.fixed >> 9) - AREA_CELL_ORIGIN;
    if (SELF(PartyMember)->header.step < 2) {
        pos.vz = -COORD_INT(g_BattleEffectBattler->pos.z) / 2;
    } else {
        pos.vz = -COORD_INT(g_BattleSelectedActor->pos.z) / 2;
    }
    RotTrans(&pos, (VECTOR*)matrix.t, &flags);
    RotMatrix(&rot, &matrix);
    MulMatrix2(&g_CameraMatrix, &matrix);
    SetRotMatrix(&matrix);
    SetTransMatrix(&matrix);
}

MATCH void func_801F0238(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
    g_ScratchPad.cells.halves[1] = SELF(PartyMember)->timer << 3;
    g_ScratchPad.cells.halves[0] = SELF(PartyMember)->timer << 3;
    g_ScratchPadVectors[2].vx    = FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[0]);
    g_ScratchPadVectors[2].vy    = FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[0]);

    for (i = 1; i <= 16; i++) {
        prim                      = GFX_BeginPolyG3(1);
        g_ScratchPadVectors[0].vx = 0;
        g_ScratchPadVectors[0].vy = 0;
        g_ScratchPadVectors[1].vx = g_ScratchPadVectors[2].vx;
        g_ScratchPadVectors[1].vy = g_ScratchPadVectors[2].vy;
        setVector(&g_ScratchPadVectors[2], FIXED_MUL(rsin(i << 8), g_ScratchPad.cells.halves[0]), FIXED_MUL(rcos(i << 8), g_ScratchPad.cells.halves[0]), 0);
        g_ScratchPadVectors[1].vz = 0;
        g_ScratchPadVectors[0].vz = 0;
        RotTransPers3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[1]);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        GFX_AddPrim(BMAGIC_LAYER_BEHIND_BATTLERS, sizeof(POLY_G3));
    }

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
}
