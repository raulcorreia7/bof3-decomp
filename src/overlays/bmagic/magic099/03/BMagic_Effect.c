#include "magic099_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC18.h"

MATCH void func_801EEC88(void) {
    PartyMember* actor;
    PartyMember* work;
    u32          slot;
    u32          i;

    actor               = g_Battle.selected_actor;
    g_Task->facing      = actor->facing;
    g_Task->pos.x.fixed = actor->pos.x.fixed;
    g_Task->pos.y.fixed = actor->pos.y.fixed;
    g_Task->pos.z.fixed = actor->pos.z.fixed;
    GFX_FreePaletteFadeTarget(actor);
    g_Task->timer                      = GFX_AllocPaletteFade(actor, 0, 0, 0, 1);
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
    SND_QueueSelectionEffect(EMI_CUE_ID(SND_BANK_COMMON, 0));
    g_Task->unk_09       = 8;
    g_Task->param.unk_0B = 0;
    g_Task->header.mode += 1;
}

MATCH void func_801EEE70(void) {
    g_PaletteFades[g_Task->timer].offset.red--;
    g_PaletteFades[g_Task->timer].offset.green--;
    g_PaletteFades[g_Task->timer].offset.blue--;
    if (--g_Task->unk_09 == 0) {
        Battle_ApplyDamageFlags(g_Battle.target_selector, 16);
        g_Task->header.mode++;
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

#include "overlays/bmagic/Effect_BrightenPalette.h"

MATCH void func_801EF0EC(void) {
    if (g_Task->param.unk_0B == 9) {
        GFX_FreePaletteFadeTarget(g_Battle.selected_actor);
        func_800AF814(g_Battle.target_selector);
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Battle.state |= BATTLE_STATE_EFFECT_PLAYING;
        func_801E5988();
    }
}

/* func_801EF16C */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

#include "overlays/bmagic/Effect_SetActorMatrixRolled.h"

MATCH void func_801EF264(void) {
    D_801F09A0[g_Task->header.step]();
    Battle_ProjectRange();
    if (g_Task->header.step != 0) {
        Effect_SetActorMatrixRolled();
        func_801EF8F0(0x60, 0x20, 7);
        PopMatrix();
    }
}

MATCH void func_801EF2EC(void) {
    g_Task->param.unk_0B = RANDOM_MASK(0xF);
    g_Task->unk_09       = 0;
    g_Task->timer        = 0;
    g_Task->pos.x.fixed  = g_BattleEffectBattler->pos.x.fixed;
    g_Task->pos.y.fixed  = g_BattleEffectBattler->pos.y.fixed;
    g_Task->pos.z.fixed  = g_BattleEffectBattler->pos.z.fixed;
    g_Task->header.step += 1;
}

MATCH void func_801EF374(void) {
    BattleEffectTimerStep();
}

#include "overlays/bmagic/Effect_Wait.h"

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
        func_801E5988();
    }
}

MATCH void func_801EF4C4(void) {
    PartyMember* work;

    work = g_Task;
    D_801F09B0[work->header.step]();
    Battle_ProjectRange();
    if (g_Task->header.flags != 0) {
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

    g_Task->unk_09 = 0;
    g_Task->timer  = 0;

    work                   = g_Task;
    temp                   = work->unk_03 << 5;
    angle_cell             = &D_1F800004;
    angle                  = (temp & 0x7F) << 5;
    VOL(s32, work->unk_0C) = temp;
    *angle_cell            = angle;
    D_1F800000             = 0x28;

    velocity          = rcos(angle) * D_1F800000;
    work              = g_Task;
    work->pos.x.fixed = BATTLE_ACTIVE_WORK->pos.x.fixed + velocity;

    velocity            = rsin(*angle_cell) * D_1F800000;
    g_Task->pos.y.fixed = BATTLE_ACTIVE_WORK->pos.y.fixed + velocity;

    g_Task->pos.z.part.integer = BATTLE_ACTIVE_WORK->pos.z.part.integer;
    g_Task->header.step++;
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

    g_Task->param.unk_0B++;

    work                   = g_Task;
    counter                = work->unk_0C + 1;
    VOL(s32, work->unk_0C) = counter;
    angle                  = (counter & 0x7F) << 5;
    angle_cell             = &D_1F800004;
    *angle_cell            = angle;
    D_1F800000             = 0x28;

    velocity          = rcos(angle) * D_1F800000;
    work              = g_Task;
    work->pos.x.fixed = BATTLE_ACTIVE_WORK->pos.x.fixed + velocity;

    velocity            = rsin(*angle_cell) * D_1F800000;
    g_Task->pos.y.fixed = BATTLE_ACTIVE_WORK->pos.y.fixed + velocity;

    if (--g_Task->timer == 0) {
        BATTLE_ACTIVE_WORK->param.unk_0B++;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF8F0);

MATCH void func_801F0008(void) {
    D_801F09C0[g_Task->header.step]();
    Battle_ProjectRange();
    if (g_Task->header.step != 0) {
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

    g_Task->param.unk_0B = RANDOM_MASK(0xF);
    g_Task->unk_09       = 0;
    g_Task->timer        = 0;

    work                   = g_Task;
    counter                = (work->unk_03 << 5) + 0x10;
    angle                  = (counter & 0x7F) << 5;
    VOL(s32, work->unk_0C) = counter;
    angle_cell             = &D_1F800004;
    *angle_cell            = angle;
    D_1F800000             = 0x18;

    velocity            = rcos(angle) * D_1F800000;
    g_Task->pos.x.fixed = BATTLE_ACTIVE_WORK->pos.x.fixed + velocity;

    velocity            = rsin(*angle_cell) * D_1F800000;
    g_Task->pos.y.fixed = BATTLE_ACTIVE_WORK->pos.y.fixed + velocity;

    COORD_INT(g_Task->pos.z) = COORD_INT(BATTLE_ACTIVE_WORK->pos.z);
    g_Task->header.step++;
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

    g_Task->param.unk_0B++;

    work                   = g_Task;
    counter                = work->unk_0C + 1;
    VOL(s32, work->unk_0C) = counter;
    angle                  = (counter & 0x7F) << 5;
    angle_cell             = &D_1F800004;
    *angle_cell            = angle;
    D_1F800000             = 0x18;

    velocity          = rcos(angle) * D_1F800000;
    work              = g_Task;
    work->pos.x.fixed = BATTLE_ACTIVE_WORK->pos.x.fixed + velocity;

    velocity             = rsin(*angle_cell) * D_1F800000;
    scratch              = g_Task;
    scratch->pos.y.fixed = BATTLE_ACTIVE_WORK->pos.y.fixed + velocity;
    scratch->timer -= 2;

    if (g_Task->timer == 0) {
        BATTLE_ACTIVE_WORK->param.unk_0B++;
        func_801E5988();
    }
}

#include "overlays/bmagic/Effect_DrawBolt.h"

MATCH void func_801F070C(void) {
    POLY_G3* primitive;
    s32*     radius;
    s32      angle;
    s32      i;

    D_1F800000 = RANDOM_MASK(7) + g_Task->timer * 3;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(0, 1, 320, 256), 0);
    i      = 0;
    radius = &D_1F800000;
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));

    do {
        primitive = GFX_BeginPolyG3(1);

        setXY0(primitive, g_Task->unk_2E.half, g_Task->unk_30.half);
        angle         = i << 9;
        primitive->x1 = g_Task->unk_2E.half + FIXED_MUL(rsin(angle), *radius);
        primitive->y1 = g_Task->unk_30.half + FIXED_MUL(rcos(angle), *radius);
        i++;
        angle         = i << 9;
        primitive->x2 = g_Task->unk_2E.half + FIXED_MUL(rsin(angle), *radius);
        primitive->y2 = g_Task->unk_30.half + FIXED_MUL(rcos(angle), *radius);
        setRGB0(primitive, g_Task->timer * 14, g_Task->timer * 14, g_Task->timer * 12);
        setRGB1(primitive, 1, 1, 1);
        setRGB2(primitive, 1, 1, 1);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_G3));
    } while (i < 8);
}
