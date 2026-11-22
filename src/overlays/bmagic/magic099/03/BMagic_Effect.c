#include "magic099_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/func_801EEC18.h"

MATCH void func_801EEC88(void) {
    PartyMember* actor;
    PartyMember* work;
    u32          slot;
    u32          i;

    actor                    = g_Battle.selected_actor;
    BMAGIC_WORK->facing      = actor->facing;
    BMAGIC_WORK->pos.x.fixed = actor->pos.x.fixed;
    BMAGIC_WORK->pos.y.fixed = actor->pos.y.fixed;
    BMAGIC_WORK->pos.z.fixed = actor->pos.z.fixed;
    GFX_PaletteFreeFadeTarget(actor);
    BMAGIC_WORK->timer                 = GFX_PaletteAllocFade(actor, 0, 0, 0, 1);
    slot                               = Battle_AllocEffect(1, 12) & BYTE_MASK;
    g_BattleEffects[slot].target.party = g_Task;
    g_BattleEffects[slot].header.mode  = 0;
    for (i = 0; i < 4; i++) {
        slot                               = Battle_AllocEffect(1, 12) & BYTE_MASK;
        work                               = g_Task;
        g_BattleEffects[slot].unk_03       = i;
        g_BattleEffects[slot].header.mode  = 1;
        g_BattleEffects[slot].unk_0B       = i * 4;
        g_BattleEffects[slot].target.party = work;
    }
    for (i = 0; i < 4; i++) {
        slot                               = Battle_AllocEffect(1, 12) & BYTE_MASK;
        g_BattleEffects[slot].target.party = g_Task;
        g_BattleEffects[slot].unk_03       = i;
        g_BattleEffects[slot].header.mode  = 2;
    }
    SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0));
    BMAGIC_WORK->unk_09       = 8;
    BMAGIC_WORK->param.unk_0B = 0;
    BMAGIC_WORK->header.mode += 1;
}

MATCH void func_801EEE70(void) {
    g_PaletteFades[BMAGIC_WORK->timer].offset.r--;
    g_PaletteFades[BMAGIC_WORK->timer].offset.g--;
    g_PaletteFades[BMAGIC_WORK->timer].offset.b--;
    if (--BMAGIC_WORK->unk_09 == 0) {
        Battle_ApplyDamageFlags(g_Battle.target_selector, 16);
        BMAGIC_WORK->header.mode++;
    }
}

MATCH void func_801EEF98(void) {
    PartyMember* work;

    work = g_Task;
    if (work->param.unk_0B != 0) {
        work->unk_09      = 8;
        work              = g_Task;
        work->header.mode = work->header.mode + 1;
    }
}

#include "overlays/bmagic/shared/Effect_BrightenPalette.h"

MATCH void func_801EF0EC(void) {
    if (BMAGIC_WORK->param.unk_0B == 9) {
        GFX_PaletteFreeFadeTarget(g_Battle.selected_actor);
        Battle_FadePoisonedBattler(g_Battle.target_selector);
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Battle.flags |= BATTLE_STATE_EFFECT_PLAYING;
        Effect_Reset();
    }
}

/* func_801EF16C */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

#include "overlays/bmagic/shared/Effect_SetActorMatrixRolled.h"

MATCH void func_801EF264(void) {
    D_801F09A0[BMAGIC_WORK->header.step]();
    Battle_ProjectRange();
    if (BMAGIC_WORK->header.step != 0) {
        Effect_SetActorMatrixRolled();
        func_801EF8F0(0x60, 0x20, 7);
        PopMatrix();
    }
}

MATCH void func_801EF2EC(void) {
    BMAGIC_WORK->param.unk_0B = RANDOM_MASK(0xF);
    BMAGIC_WORK->unk_09       = 0;
    BMAGIC_WORK->timer        = 0;
    BMAGIC_WORK->pos.x.fixed  = g_BattleEffectBattler->pos.x.fixed;
    BMAGIC_WORK->pos.y.fixed  = g_BattleEffectBattler->pos.y.fixed;
    BMAGIC_WORK->pos.z.fixed  = g_BattleEffectBattler->pos.z.fixed;
    BMAGIC_WORK->header.step += 1;
}

MATCH void func_801EF374(void) {
    BattleEffectTimerStep();
}

#include "overlays/bmagic/shared/Effect_Wait.h"

MATCH void func_801EF44C(void) {
    PartyMember* work;
    PartyMember* active;
    u8           count;

    work = g_Task;
    work->param.unk_0B++;
    work        = g_Task;
    count       = work->timer - 1;
    work->timer = count;
    if (count == 0) {
        active = BATTLE_ACTIVE_WORK;
        active->param.unk_0B++;
        Effect_Reset();
    }
}

MATCH void func_801EF4C4(void) {
    PartyMember* work;

    work = g_Task;
    D_801F09B0[work->header.step]();
    Battle_ProjectRange();
    if (BMAGIC_WORK->header.flags != 0) {
        Effect_SetActorMatrixRolled();
        func_801EF8F0(0x20, 0x50, 0xF);
        func_801F070C();
        PopMatrix();
    }
}

MATCH void func_801EF554(void) {
    PartyMember* work;
    s32          temp;
    s32          angle;
    s32*         angle_cell;
    s32          velocity;

    BMAGIC_WORK->unk_09 = 0;
    BMAGIC_WORK->timer  = 0;

    work                             = g_Task;
    temp                             = work->unk_03 << 5;
    angle_cell                       = &D_1F800004;
    angle                            = (temp & 0x7F) << 5;
    FAKE_VOLATILE(s32, work->unk_0C) = temp;
    *angle_cell                      = angle;
    g_ScratchPad                     = 0x28;

    velocity          = rcos(angle) * g_ScratchPad;
    work              = g_Task;
    work->pos.x.fixed = BATTLE_ACTIVE_WORK->pos.x.fixed + velocity;

    velocity                 = rsin(*angle_cell) * g_ScratchPad;
    BMAGIC_WORK->pos.y.fixed = BATTLE_ACTIVE_WORK->pos.y.fixed + velocity;

    BMAGIC_WORK->pos.z.part.integer = BATTLE_ACTIVE_WORK->pos.z.part.integer;
    BMAGIC_WORK->header.step++;
}

MATCH void func_801EF654(void) {
    BattleEffectTimerStep();
}

MATCH void func_801EF6C4(void) {
    MagicOrbitProjectionStep(0x28);
}

MATCH void func_801EF7D8(void) {
    PartyMember* work;
    s32          counter;
    s32          angle;
    s32*         angle_cell;
    s32          velocity;

    BMAGIC_WORK->param.unk_0B++;

    work                             = g_Task;
    counter                          = work->unk_0C + 1;
    FAKE_VOLATILE(s32, work->unk_0C) = counter;
    angle                            = (counter & 0x7F) << 5;
    angle_cell                       = &D_1F800004;
    *angle_cell                      = angle;
    g_ScratchPad                     = 0x28;

    velocity          = rcos(angle) * g_ScratchPad;
    work              = g_Task;
    work->pos.x.fixed = BATTLE_ACTIVE_WORK->pos.x.fixed + velocity;

    velocity                 = rsin(*angle_cell) * g_ScratchPad;
    BMAGIC_WORK->pos.y.fixed = BATTLE_ACTIVE_WORK->pos.y.fixed + velocity;

    if (--BMAGIC_WORK->timer == 0) {
        BATTLE_ACTIVE_WORK->param.unk_0B++;
        Effect_Reset();
    }
}

#ifdef NON_MATCHING
NON_MATCHING void func_801EF8F0(s32 effect_type, s32 effect_index, s16 effect_angle) {
}
#else
INCLUDE_ASM(func_801EF8F0);
#endif

MATCH void func_801F0008(void) {
    D_801F09C0[BMAGIC_WORK->header.step]();
    Battle_ProjectRange();
    if (BMAGIC_WORK->header.step != 0) {
        Effect_SetActorMatrixRolled();
        Effect_DrawBolt();
        func_801F070C();
        PopMatrix();
    }
}

MATCH void func_801F0090(void) {
    PartyMember* work;
    s32          counter;
    s32          angle;
    s32*         angle_cell;
    s32          velocity;

    BMAGIC_WORK->param.unk_0B = RANDOM_MASK(0xF);
    BMAGIC_WORK->unk_09       = 0;
    BMAGIC_WORK->timer        = 0;

    work                             = g_Task;
    counter                          = (work->unk_03 << 5) + 0x10;
    angle                            = (counter & 0x7F) << 5;
    FAKE_VOLATILE(s32, work->unk_0C) = counter;
    angle_cell                       = &D_1F800004;
    *angle_cell                      = angle;
    g_ScratchPad                     = 0x18;

    velocity                 = rcos(angle) * g_ScratchPad;
    BMAGIC_WORK->pos.x.fixed = BATTLE_ACTIVE_WORK->pos.x.fixed + velocity;

    velocity                 = rsin(*angle_cell) * g_ScratchPad;
    BMAGIC_WORK->pos.y.fixed = BATTLE_ACTIVE_WORK->pos.y.fixed + velocity;

    COORD_INT(BMAGIC_WORK->pos.z) = COORD_INT(BATTLE_ACTIVE_WORK->pos.z);
    BMAGIC_WORK->header.step++;
}

MATCH void func_801F01AC(void) {
    PartyMember* work;

    work = g_Task;
    if (work->timer < 16) {
        work->timer += 2;
    } else {
        work->unk_09 = 60;
        work         = g_Task;
        work->header.step++;
    }
}

MATCH void func_801F0200(void) {
    MagicOrbitProjectionStep(0x10);
}

MATCH void func_801F0314(void) {
    PartyMember* work;
    PartyMember* scratch;
    s32          counter;
    s32          angle;
    s32*         angle_cell;
    s32          velocity;

    BMAGIC_WORK->param.unk_0B++;

    work                             = g_Task;
    counter                          = work->unk_0C + 1;
    FAKE_VOLATILE(s32, work->unk_0C) = counter;
    angle                            = (counter & 0x7F) << 5;
    angle_cell                       = &D_1F800004;
    *angle_cell                      = angle;
    g_ScratchPad                     = 0x18;

    velocity          = rcos(angle) * g_ScratchPad;
    work              = g_Task;
    work->pos.x.fixed = BATTLE_ACTIVE_WORK->pos.x.fixed + velocity;

    velocity             = rsin(*angle_cell) * g_ScratchPad;
    scratch              = g_Task;
    scratch->pos.y.fixed = BATTLE_ACTIVE_WORK->pos.y.fixed + velocity;
    scratch->timer -= 2;

    if (BMAGIC_WORK->timer == 0) {
        BATTLE_ACTIVE_WORK->param.unk_0B++;
        Effect_Reset();
    }
}

#include "overlays/bmagic/shared/Effect_DrawBolt.h"

MATCH void func_801F070C(void) {
    POLY_G3* primitive;
    s32*     radius;
    s32      angle;
    s32      i;

    g_ScratchPad = RANDOM_MASK(7) + BMAGIC_WORK->timer * 3;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256), 0);
    i      = 0;
    radius = &g_ScratchPad;
    Area_CellAddPrim(BMAGIC_WORK->pos.x.fixed, BMAGIC_WORK->pos.y.fixed, 2, sizeof(DR_MODE));

    do {
        primitive = GFX_BeginPolyG3(1);

        setXY0(primitive, BMAGIC_WORK->screen_x.value, BMAGIC_WORK->screen_y.value);
        angle         = i << 9;
        primitive->x1 = BMAGIC_WORK->screen_x.value + FIXED_MUL(rsin(angle), *radius);
        primitive->y1 = BMAGIC_WORK->screen_y.value + FIXED_MUL(rcos(angle), *radius);
        i++;
        angle         = i << 9;
        primitive->x2 = BMAGIC_WORK->screen_x.value + FIXED_MUL(rsin(angle), *radius);
        primitive->y2 = BMAGIC_WORK->screen_y.value + FIXED_MUL(rcos(angle), *radius);
        setRGB0(primitive, BMAGIC_WORK->timer * 14, BMAGIC_WORK->timer * 14, BMAGIC_WORK->timer * 12);
        setRGB1(primitive, 1, 1, 1);
        setRGB2(primitive, 1, 1, 1);
        Area_CellAddPrim(BMAGIC_WORK->pos.x.fixed, BMAGIC_WORK->pos.y.fixed, 2, sizeof(POLY_G3));
    } while (i < 8);
}
