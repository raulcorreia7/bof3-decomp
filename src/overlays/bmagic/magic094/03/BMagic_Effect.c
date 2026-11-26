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
    SELF(PartyMember)->pos.x.fixed            = actor->pos.x.fixed;
    SELF(PartyMember)->pos.y.fixed            = actor->pos.y.fixed;
    SELF(PartyMember)->pos.z.fixed            = actor->pos.z.fixed;
    SELF(PartyMember)->screen_x.value         = actor->screen_x.value;
    SELF(PartyMember)->screen_y.value         = actor->screen_y.value - 16;
    effect_slot                               = Battle_AllocEffect(1, 21) & BYTE_MASK;
    g_BattleEffects[effect_slot].target.party = SELF(PartyMember);
    g_BattleEffects[effect_slot].unk_08       = actor->facing;
    g_BattleEffects[effect_slot].pos.x.fixed  = actor->pos.x.fixed;
    g_BattleEffects[effect_slot].pos.y.fixed  = actor->pos.y.fixed;
    g_BattleEffects[effect_slot].pos.z.fixed  = actor->pos.z.fixed;
    SELF(PartyMember)->param.unk_0B           = 0;
    SELF(PartyMember)->header.mode++;
    SND_SEQueueSelection(0x100);
}

/* Copies the selected actor's unk_2E and unk_30 - 0x10; at unk_0B 0xFF releases the target and plays. */
MATCH void func_801EED60(void) {
    u32          slot;
    u8*          selector;
    PartyMember* battler;

    SELF(PartyMember)->screen_x.value = g_BattleSelectedActor->screen_x.value;
    SELF(PartyMember)->screen_y.value = g_BattleSelectedActor->screen_y.value - 0x10;
    if (SELF(PartyMember)->param.unk_0B == 0xFF) {
        BMAGIC_RELEASE_TARGET_AND_PLAY();
    }
}

MATCH void func_801EEE4C(void) {
    SYS_DISPATCH_BYTE(D_801EF988, SELF(PartyMember)->header.mode);
    if (g_BattleEffectBattler->param.unk_0B != 0xFF) {
        func_801EF654();
        func_801EF14C();
        func_801EF710();
        PopMatrix();
    }
    GFX_AddDitheredDrawMode(BMAGIC_LAYER_OVER_BATTLERS, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256));
}

MATCH void func_801EEF1C(void) {
    Battle_ApplyDamageFlags(g_Battle.target_selector, 32);
    SELF(PartyMember)->unk_09 = 0;
    SELF(PartyMember)->timer  = 0;
    SELF(PartyMember)->header.mode++;
}

MATCH void func_801EEF7C(void) {
    u32          slot;
    u8           step;
    PartyMember* battler;

    SELF(PartyMember)->timer++;
    step                      = SELF(PartyMember)->unk_09 + 1;
    SELF(PartyMember)->unk_09 = step;
    if (step == 0x10) {
        slot = LOBU(g_Battle.target_selector);
        if (slot < BATTLE_PARTY_CHARACTERS_COUNT) {
            battler = &g_Game.members[slot];
        } else {
            battler = (PartyMember*)(g_BattleEnemies + slot * BATTLE_ENEMY_STRIDE);
        }
        func_80196718(battler);
        func_8019651C(battler, 6, 4, 8, 0);
        SELF(PartyMember)->unk_09 = 0;
        SELF(PartyMember)->header.mode++;
    }
}

MATCH void func_801EF078(void) {
    u8 timer;
    u8 count;

    timer = SELF(PartyMember)->timer;
    if (timer < 16U) {
        SELF(PartyMember)->timer = timer + 1;
    }
    count                     = SELF(PartyMember)->unk_09 + 1;
    SELF(PartyMember)->unk_09 = count;
    if ((count & BYTE_MASK) == 0x10) {
        SELF(PartyMember)->unk_09 = 0;
        SELF(PartyMember)->header.mode += 1;
    }
}

MATCH void func_801EF0FC(void) {
    u8 count;

    count                     = SELF(PartyMember)->unk_09 + 1;
    SELF(PartyMember)->unk_09 = count;
    if ((count & BYTE_MASK) == 0x20) {
        g_BattleEffectBattler->param.unk_0B = 0xFF;
        Effect_Reset();
    }
}

/* Draws the effect's six rings of Gouraud triangles: the scratch words stage each ring's radius,
 * twist and depth, and the eight segments step around the ring in 0x100 units. */
MATCH void func_801EF14C(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      half_step;
    s32      angle;
    s32      i;
    s32      ring;
    s32      tpage;
    s32      x;
    s32      y;
    s32      depth_step;

    for (ring = 0; ring < 6; ring++) {
        switch (SELF(PartyMember)->header.mode) {
            case 1:
            default:
                D_1F800000_WORD[0] = (ring + 1) * 16;
                D_1F800000_WORD[1] = ((ring + 1) << 2) * SELF(PartyMember)->unk_09;
                depth_step         = ((ring ^ 7) + 1) * 5;
                D_1F800000_WORD[2] = -(depth_step * SELF(PartyMember)->unk_09);
                break;
            case 2:
                D_1F800000_WORD[0] = (ring + 1) * 16;
                D_1F800000_WORD[1] = (ring + 1) * 64;
                D_1F800000_WORD[2] = -(((ring ^ 7) + 1) * 5 << 4);
                break;
            case 3:
                D_1F800000_WORD[0] = (ring + 1) * 16;
                D_1F800000_WORD[1] = (ring + 1) * 64 - SELF(PartyMember)->unk_09;
                D_1F800000_WORD[2] = (SELF(PartyMember)->unk_09 << 1) - (((ring ^ 7) + 1) * 5 << 4);
                break;
        }
        g_ScratchPadVectors[2].vx = FIXED_MUL(rcos(0), D_1F800000_WORD[0]);
        g_ScratchPadVectors[2].vy = FIXED_MUL(rsin(0), D_1F800000_WORD[0]);
        g_ScratchPadVectors[2].vz = 0;
        for (i = 1, half_step = 1; i < 9; i++) {
            angle                     = half_step << 8;
            g_ScratchPadVectors[0].vx = FIXED_MUL(rcos(angle), D_1F800000_WORD[1]);
            g_ScratchPadVectors[0].vy = FIXED_MUL(rsin(angle), D_1F800000_WORD[1]);
            g_ScratchPadVectors[1].vz = 0;
            g_ScratchPadVectors[0].vz = D_1F800000_WORD[2];
            g_ScratchPadVectors[1].vx = g_ScratchPadVectors[2].vx;
            g_ScratchPadVectors[1].vy = g_ScratchPadVectors[2].vy;
            angle                     = i << 9;
            g_ScratchPadVectors[2].vx = FIXED_MUL(rcos(angle), D_1F800000_WORD[0]);
            g_ScratchPadVectors[2].vy = FIXED_MUL(rsin(angle), D_1F800000_WORD[0]);
            g_ScratchPadVectors[2].vz = 0;
            x                         = (g_ScratchPadVectors[2].vx << 9) + SELF(PartyMember)->pos.x.fixed;
            y                         = ((g_ScratchPadVectors[2].vy << 16) >> 7) + SELF(PartyMember)->pos.y.fixed;
            tpage                     = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
            SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, NULL);
            Area_CellAddPrim(x, y, 2, sizeof(DR_MODE));
            prim = (POLY_G3*)g_GfxPrimCursor;
            SetPolyG3(prim);
            PSX_SET_SEMI_TRANSPARENT(prim);
            if (SELF(PartyMember)->header.mode == 3) {
                D_1F800000_WORD[3] = (ring + 1) * 16;
                D_1F800000_WORD[3] = D_1F800000_WORD[3] - (D_1F800000_WORD[3] / 16) * (SELF(PartyMember)->unk_09 >> 1);
                if (D_1F800000_WORD[3] < 0) {
                    D_1F800000_WORD[3] = 1;
                }
                setRGB0(prim, 1, 1, 1);
                setRGB1(prim, D_1F800000_WORD[3], D_1F800000_WORD[3], 0xC1 - SELF(PartyMember)->unk_09 * 6);
                setRGB2(prim, prim->r1, prim->g1, prim->b1);
            } else {
                D_1F800000_WORD[3] = (ring + 1) * 16;
                setRGB0(prim, 1, 1, 1);
                setRGB1(prim, D_1F800000_WORD[3], D_1F800000_WORD[3], 0xC0);
                setRGB2(prim, D_1F800000_WORD[3], D_1F800000_WORD[3], 0xC0);
            }
            RotTransPers3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
            Area_CellAddPrim(x, y, 2, sizeof(POLY_G3));
            half_step += 2;
        }
    }
}

MATCH void func_801EF654(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    setVector(&rot, 0, 0, SELF(PartyMember)->timer << 4);
    BMAGIC_PROJECT_ACTOR_MATRIX(SELF(PartyMember));
}

MATCH void func_801EF710(void) {
    POLY_G3* prim;
    s32      tpage;
    s32      i;
    s32      angle;
    s32      next;

    switch (SELF(PartyMember)->header.mode) {
        /* FAKE: retail compare tree needs a third case below 2 on the default body; the bytes do not say which mode. */
        case 1:
        default:
            D_1F800000_WORD[0] = SELF(PartyMember)->unk_09 * 3 + 16;
            break;
        case 2:
            D_1F800000_WORD[0] = 64;
            break;
        case 3:
            D_1F800000_WORD[0] = 64 - SELF(PartyMember)->unk_09 * 2;
            break;
    }
    i = 0;
    do {
        tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        PSX_SET_SEMI_TRANSPARENT(prim);
        setXY0(prim, g_BattleEffectBattler->screen_x.value, g_BattleEffectBattler->screen_y.value);
        angle    = i << 7;
        prim->x1 = g_BattleEffectBattler->screen_x.value + FIXED_MUL(rsin(angle), D_1F800000_WORD[0]);
        prim->y1 = g_BattleEffectBattler->screen_y.value + FIXED_MUL(rcos(angle), D_1F800000_WORD[0]);
        next     = (i + 1) << 7;
        prim->x2 = g_BattleEffectBattler->screen_x.value + FIXED_MUL(rsin(next), D_1F800000_WORD[0]);
        prim->y2 = g_BattleEffectBattler->screen_y.value + FIXED_MUL(rcos(next), D_1F800000_WORD[0]);
        setRGB0(prim, 0x20, 0x20, 0xC0);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(POLY_G3));
        i++;
    } while (i < 32);
}
