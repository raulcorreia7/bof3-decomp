#include "magic020_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/Effect_DispatchMode.h"
#include "overlays/bmagic/shared/Effect_CopyActiveBattlerToSlot.h"

/* Start the magic020 effect: four copies of the caster in mode 1 (arg 4 down to 1), one more
 * in mode 0, then the caster sprite cell, and Battle_PlayActiveBattlerSE(2, 0) for a party caster. */
MATCH void func_801EECC0(void) {
    u32 index;
    s32 i;

    SELF(PartyMember)->facing = g_BattleEffectBattler->facing;
    WorldPos_Copy(&SELF(PartyMember)->pos, &g_BattleEffectBattler->pos);
    SELF(PartyMember)->param.unk_0B = 0;
    SELF(PartyMember)->unk_09       = 0;
    SELF(PartyMember)->header.mode += 1;
    Battle_SelectActiveBattlerScript(0xC, 2);
    for (i = 0; (u32)(i & BYTE_MASK) < 4; i++) {
        index = Battle_AllocEffect(1, 46);
        Effect_CopyActiveBattlerToSlot(index);
        g_BattleEffects[index & BYTE_MASK].target.party = SELF(PartyMember);
        g_BattleEffects[index & BYTE_MASK].header.mode  = 1;
        g_BattleEffects[index & BYTE_MASK].effect_type  = 46;
        g_BattleEffects[index & BYTE_MASK].header.step  = 0;
        g_BattleEffects[index & BYTE_MASK].unk_06       = 1;
        g_BattleEffects[index & BYTE_MASK].arg.unk_09   = (i ^ 3) + 1;
        g_BattleEffects[index & BYTE_MASK].unk_0B       = i ^ 3;
    }
    index = Battle_AllocEffect(1, 46);
    Effect_CopyActiveBattlerToSlot(index);
    g_BattleEffects[index & BYTE_MASK].target.party = SELF(PartyMember);
    g_BattleEffects[index & BYTE_MASK].unk_06       = 1;
    g_BattleEffects[index & BYTE_MASK].header.mode  = 0;
    g_BattleEffects[index & BYTE_MASK].header.step  = 0;
    g_BattleEffects[index & BYTE_MASK].effect_type  = 46;
    SELF(PartyMember)->unk_27                       = Battle_CopyCellPalette(g_BattleEffectBattler);
    SELF(PartyMember)->unk_28                       = g_BattleEffectBattler->unk_28;
    SELF(PartyMember)->unk_24                       = g_BattleEffectBattler->unk_24;
    Battle_SetCellPaletteStp(SELF(PartyMember));
    if (g_Battle.active_battler < BATTLE_PARTY_CHARACTERS_COUNT) {
        Battle_PlayActiveBattlerSE(2, 0);
    }
    g_BattleEffectBattler->header.flags |= PARTY_MEMBER_FLAG_HANDLER_BUSY;
}

MATCH void func_801EF0F8(void) {
    PartyMember* work;
    u32          slot;
    u8           i;
    u8           count;

    if (SELF(PartyMember)->param.unk_0B == 0xFF) {
        func_801EFD88();
        count                     = SELF(PartyMember)->unk_09 + 4;
        SELF(PartyMember)->unk_09 = count;
        if (count == 16) {
            SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0));
            SELF(PartyMember)->param.unk_0B = 0;
            SELF(PartyMember)->header.mode += 1;
            for (i = 0; i < 8; i++) {
                slot                               = Battle_AllocEffect(1, 46) & BYTE_MASK;
                work                               = SELF(PartyMember);
                g_BattleEffects[slot].header.mode  = 2;
                g_BattleEffects[slot].header.step  = 0;
                g_BattleEffects[slot].unk_0B       = i;
                g_BattleEffects[slot].arg.unk_09   = (i * 8) + 1;
                g_BattleEffects[slot].target.party = work;
                SELF(PartyMember)->param.unk_0B += 1;
            }
        }
    }
}

MATCH void func_801EF234(void) {
    u8 timer;

    func_801EFD88();
    if (SELF(PartyMember)->param.unk_0B == 0) {
        timer                     = SELF(PartyMember)->unk_09 - 1;
        SELF(PartyMember)->unk_09 = timer;
        if (timer == 0) {
            SELF(PartyMember)->header.mode = SELF(PartyMember)->header.mode + 1;
        }
    }
}

MATCH void func_801EF2A8(void) {
    if (SELF(PartyMember)->param.unk_0B == 0xFF) {
        func_800AFC54();
        BATTLE_ACTIVE_WORK->header.flags &= ~PARTY_MEMBER_FLAG_HANDLER_BUSY;
        Battle_SelectActiveBattlerScript(4, 0);
        SELF(PartyMember)->header.mode += 1;
    }
}

#include "shared/Effect_StartPlaying.h"

#include "shared/Effect_PlayOnce.h"

/* func_801EF398 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EF3DC(void) {
    Magic020Steps handlers = D_801EEC1C;

    SYS_DISPATCH_BYTE(handlers.steps, SELF(PartyMember)->header.step);
    if (SELF(PartyMember)->header.flags != 0 && SELF(PartyMember)->header.step != 0) {
        Area_AddGridActor();
    }
}

MATCH void func_801EF498(void) {
    PartyMember* work;
    s32          z;

    SELF(PartyMember)->unk_27 = g_BattleEffectBattler->unk_27;
    SELF(PartyMember)->unk_2B = 1;
    work                      = SELF(PartyMember);
    work->pos.x.fixed         = g_BattleEffectBattler->pos.x.fixed;
    work->pos.y.fixed         = g_BattleEffectBattler->pos.y.fixed;
    z                         = g_BattleEffectBattler->pos.z.fixed;
    work->unk_09              = 0x10;
    work->pos.z.fixed         = z;
    SELF(PartyMember)->header.step++;
}

MATCH void func_801EF518(void) {
    PartyMember** selected;

    selected = &g_Battle.selected_actor;
    func_800AF2B4(*selected, 0x60);
    if (func_800AF66C(*selected, 0x20000)) {
        SELF(PartyMember)->unk_09        = func_800AFF98();
        BATTLE_ACTIVE_WORK->param.unk_0B = 0xFF;
        SELF(PartyMember)->header.step++;
    }
}

MATCH void func_801EF5A4(void) {
    u8 timer;

    Script_AnimStepOnce();
    timer                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = timer;
    if (timer == 0) {
        SELF(PartyMember)->header.step = SELF(PartyMember)->header.step + 1;
    }
}

MATCH void func_801EF608(void) {
    if ((BATTLE_ACTIVE_WORK->param.unk_0B == 0) && (Script_AnimStepOnce() & BYTE_MASK)) {
        SELF(PartyMember)->unk_09 = 0x10;
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF678(void) {
    u8 timer;

    timer                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        s8 tone;

        SELF(PartyMember)->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
        SELF(PartyMember)->unk_5C = 1;
        tone                      = -0x40;
        SELF(PartyMember)->unk_5D = tone;
        SELF(PartyMember)->unk_5E = tone;
        SELF(PartyMember)->unk_5F = tone;
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF720(void) {
    PartyMember* work;
    PartyMember* source;

    SELF(PartyMember)->unk_5D -= 8;
    SELF(PartyMember)->unk_5E -= 8;
    SELF(PartyMember)->unk_5F -= 8;
    if ((s8)SELF(PartyMember)->unk_5D == -128) {
        work   = SELF(PartyMember);
        source = BATTLE_ACTIVE_WORK;
        WorldPos_Copy(&work->pos, &source->pos);
        work->header.step += 1;
    }
}

MATCH void func_801EF7D0(void) {
    SELF(PartyMember)->unk_5D += 0x10;
    SELF(PartyMember)->unk_5E += 0x10;
    SELF(PartyMember)->unk_5F += 0x10;
    if ((s8)SELF(PartyMember)->unk_5D == 0) {
        BATTLE_ACTIVE_WORK->param.unk_0B = 0xFF;
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF874(void) {
    Effect_Reset();
}

MATCH void func_801EF894(void) {
    Magic020SecondSteps handlers;

    handlers = D_801EEC3C;
    SYS_DISPATCH_BYTE(handlers.steps, SELF(PartyMember)->header.step);
    if (SELF(PartyMember)->header.flags != 0 && SELF(PartyMember)->header.step != 0) {
        Area_AddGridActor();
    }
}

MATCH void func_801EF928(void) {
    PartyMember* work;
    PartyMember* source;
    u8           count;

    count                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        SELF(PartyMember)->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
        SELF(PartyMember)->unk_5C = 1;
        SELF(PartyMember)->unk_5D = -((SELF(PartyMember)->param.unk_0B + 1) * 20);
        SELF(PartyMember)->unk_5E = -((SELF(PartyMember)->param.unk_0B + 1) * 20);
        SELF(PartyMember)->unk_5F = -((SELF(PartyMember)->param.unk_0B + 1) * 20);
        SELF(PartyMember)->unk_2B = 0;
        SELF(PartyMember)->unk_27 = g_BattleEffectBattler->unk_27;
        work                      = SELF(PartyMember);
        source                    = BATTLE_ACTIVE_WORK;
        WorldPos_Copy(&work->pos, &source->pos);
        work->header.step += 1;
    }
}

MATCH void func_801EFA70(void) {
    PartyMember** selected;

    selected = &g_Battle.selected_actor;
    func_800AF2B4(*selected, 0x60);
    if (func_800AF66C(*selected, 0x20000)) {
        SELF(PartyMember)->header.step++;
    }
}

MATCH void func_801EFAD4(void) {
    Effect_Reset();
}

#include "overlays/bmagic/shared/BMagic_RunEffectStep.h"

MATCH void func_801EFAF4(void) {
    BMAGIC_RUN_EFFECT_STEP(func_801EFBA0, func_801EFD10);
}

MATCH void func_801EFBA0(void) {
    PartyMember* actor;
    PartyMember* work;
    u8           timer;

    timer                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        actor                          = g_BattleSelectedActor;
        SELF(PartyMember)->facing      = actor->facing;
        SELF(PartyMember)->pos.x.fixed = actor->pos.x.fixed;
        SELF(PartyMember)->pos.y.fixed = actor->pos.y.fixed;
        SELF(PartyMember)->pos.z.fixed = actor->pos.z.fixed;
        Battle_ProjectRange();
        SELF(PartyMember)->unk_29 = 0;
        SELF(PartyMember)->unk_25 = 0x1D;
        SELF(PartyMember)->unk_26 = 0;
        SELF(PartyMember)->unk_24 = 0x84;
        work                      = SELF(PartyMember);
        work->unk_2B              = 0;
        work->unk_2C.value        = 0;
        SELF(PartyMember)->unk_28 = 0;
        SELF(PartyMember)->unk_27 = D_801EFEC4[SELF(PartyMember)->param.unk_0B] + 0xB0;
        if (SELF(PartyMember)->facing == 1 || SELF(PartyMember)->facing == 2) {
            SELF(PartyMember)->unk_2A = 1;
        } else {
            SELF(PartyMember)->unk_2A = 0;
        }
        Script_Select(SELF(PartyMember)->param.unk_0B);
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EFD10(void) {
    if (Script_AnimStepLoop() & BYTE_MASK) {
        if (SELF(PartyMember)->param.unk_0B == 7) {
            Battle_MarkDamaged(g_Battle.target_selector);
        }
        BATTLE_ACTIVE_WORK->param.unk_0B -= 1;
        Effect_Reset();
    }
}

/* The full-screen tile's colour scratch, read back for the three channels. */
#define SCREEN_SHADE g_ScratchPad.cells.halves[1]

/* A semi-transparent full-screen tile shaded fifteen times the effect counter, then the draw mode back
 * to plain blending. */
MATCH void func_801EFD88(void) {
    TILE* tile;

    GFX_AddDitheredDrawMode(BMAGIC_LAYER_FOREGROUND, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256));
    tile = (TILE*)g_GfxPrimCursor;
    SetTile(tile);
    SetSemiTrans(tile, 1);
    tile->w      = SCREEN_WIDTH;
    tile->y0     = 0;
    tile->x0     = 0;
    tile->h      = SCREEN_HEIGHT;
    SCREEN_SHADE = SELF(PartyMember)->unk_09 * 15;
    setRGB0(tile, SCREEN_SHADE, SCREEN_SHADE, SCREEN_SHADE);
    GFX_AddPrim(BMAGIC_LAYER_FOREGROUND, sizeof(TILE));
    GFX_AddDitheredDrawMode(BMAGIC_LAYER_FOREGROUND, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256));
}
