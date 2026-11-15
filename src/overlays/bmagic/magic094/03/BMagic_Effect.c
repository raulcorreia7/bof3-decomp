#include "magic094_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    ACTOR_RUN_MODE_HANDLER(func_801EEC5C, func_801EED60);
}

MATCH void func_801EEC5C(void) {
    PartyMember* actor;
    u32          effect_slot;

    actor                                     = g_Battle.selected_actor;
    g_Task->pos.x.fixed                       = actor->pos.x.fixed;
    g_Task->pos.y.fixed                       = actor->pos.y.fixed;
    g_Task->pos.z.fixed                       = actor->pos.z.fixed;
    g_Task->unk_2E.half                       = actor->unk_2E.half;
    g_Task->unk_30.half                       = actor->unk_30.half - 16;
    effect_slot                               = Battle_AllocEffect(1, 21) & BYTE_MASK;
    g_BattleEffects[effect_slot].target.party = g_Task;
    g_BattleEffects[effect_slot].unk_08       = actor->facing;
    g_BattleEffects[effect_slot].pos.x.fixed  = actor->pos.x.fixed;
    g_BattleEffects[effect_slot].pos.y.fixed  = actor->pos.y.fixed;
    g_BattleEffects[effect_slot].pos.z.fixed  = actor->pos.z.fixed;
    g_Task->param.unk_0B                      = 0;
    g_Task->header.mode++;
    SND_QueueSelectionEffect(0x100);
}

/* Copies the selected actor's unk_2E and unk_30 - 0x10; at unk_0B 0xFF releases the target and plays. */
MATCH void func_801EED60(void) {
    u32          slot;
    u8*          selector;
    PartyMember* battler;

    g_Task->unk_2E.half = g_BattleSelectedActor->unk_2E.half;
    g_Task->unk_30.half = g_BattleSelectedActor->unk_30.half - 0x10;
    if (g_Task->param.unk_0B == 0xFF) {
        BMAGIC_RELEASE_TARGET_AND_PLAY();
    }
}

MATCH void func_801EEE4C(void) {
    SYS_DISPATCH_BYTE(D_801EF988, g_Task->header.mode);
    if (g_BattleEffectBattler->param.unk_0B != 0xFF) {
        func_801EF654();
        func_801EF14C();
        func_801EF710();
        PopMatrix();
    }
    GFX_AddDitheredDrawMode(3, getTPage(0, 0, 320, 256));
}

MATCH void func_801EEF1C(void) {
    Battle_ApplyDamageFlags(g_Battle.target_selector, 32);
    g_Task->unk_09 = 0;
    g_Task->timer  = 0;
    g_Task->header.mode++;
}

MATCH void func_801EEF7C(void) {
    u32          slot;
    u8           step;
    PartyMember* battler;

    g_Task->timer++;
    step           = g_Task->unk_09 + 1;
    g_Task->unk_09 = step;
    if (step == 0x10) {
        slot = LOBU(g_Battle.target_selector);
        if (slot < BATTLE_PARTY_CHARACTERS_COUNT) {
            battler = &g_Game.members[slot];
        } else {
            battler = (PartyMember*)(g_BattleEnemies + slot * BATTLE_ENEMY_STRIDE);
        }
        func_80196718(battler);
        func_8019651C(battler, 6, 4, 8, 0);
        g_Task->unk_09 = 0;
        g_Task->header.mode++;
    }
}

MATCH void func_801EF078(void) {
    u8 timer;
    u8 count;

    timer = g_Task->timer;
    if (timer < 16U) {
        g_Task->timer = timer + 1;
    }
    count          = g_Task->unk_09 + 1;
    g_Task->unk_09 = count;
    if ((count & BYTE_MASK) == 0x10) {
        g_Task->unk_09 = 0;
        g_Task->header.mode += 1;
    }
}

MATCH void func_801EF0FC(void) {
    u8 count;

    count          = g_Task->unk_09 + 1;
    g_Task->unk_09 = count;
    if ((count & BYTE_MASK) == 0x20) {
        g_BattleEffectBattler->param.unk_0B = 0xFF;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF14C);

MATCH void func_801EF654(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    setVector(&rot, 0, 0, g_Task->timer << 4);
    BMAGIC_PROJECT_ACTOR_MATRIX(g_Task);
}

MATCH void func_801EF710(void) {
    POLY_G3* prim;
    s32      tpage;
    s32      i;
    s32      angle;
    s32      next;

    switch (g_Task->header.mode) {
        /* FAKE: retail compare tree needs a third case below 2 on the default body; the bytes do not say which mode. */
        case 1:
        default:
            D_1F800000_WORD[0] = g_Task->unk_09 * 3 + 16;
            break;
        case 2:
            D_1F800000_WORD[0] = 64;
            break;
        case 3:
            D_1F800000_WORD[0] = 64 - g_Task->unk_09 * 2;
            break;
    }
    i = 0;
    do {
        tpage = getTPage(0, 1, 320, 256);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        setXY0(prim, g_BattleEffectBattler->unk_2E.half, g_BattleEffectBattler->unk_30.half);
        angle    = i << 7;
        prim->x1 = g_BattleEffectBattler->unk_2E.half + FIXED_MUL(rsin(angle), D_1F800000_WORD[0]);
        prim->y1 = g_BattleEffectBattler->unk_30.half + FIXED_MUL(rcos(angle), D_1F800000_WORD[0]);
        next     = (i + 1) << 7;
        prim->x2 = g_BattleEffectBattler->unk_2E.half + FIXED_MUL(rsin(next), D_1F800000_WORD[0]);
        prim->y2 = g_BattleEffectBattler->unk_30.half + FIXED_MUL(rcos(next), D_1F800000_WORD[0]);
        setRGB0(prim, 0x20, 0x20, 0xC0);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_G3));
        i++;
    } while (i < 32);
}
