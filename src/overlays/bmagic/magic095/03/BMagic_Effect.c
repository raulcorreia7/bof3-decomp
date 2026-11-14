#include "magic095_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC18(void) {
    Callback handlers[5];

    memcpy(handlers, D_801EEC04, sizeof(handlers));
    Effect_SetActorMatrix();
    SYS_DISPATCH_BYTE(handlers, g_Task->header.mode);
    PopMatrix();
}

MATCH void func_801EEC9C(void) {
    PartyMember* actor;
    s8*          jitter;
    u8           slot;
    u32          i;

    actor               = g_Battle.selected_actor;
    g_Task->unk_2E.half = actor->unk_2E.half;
    g_Task->unk_30.half = actor->unk_30.half;
    g_Task->pos.x.fixed = actor->pos.x.fixed;
    g_Task->pos.y.fixed = actor->pos.y.fixed;
    g_Task->pos.z.fixed = actor->pos.z.fixed;
    jitter              = D_801F065C;
    do {
        if (rand() & 1) {
            *jitter = -(rand() & 0xF);
        } else {
            *jitter = rand() & 0xF;
        }
        jitter++;
    } while (jitter < &D_801F065C[56]);
    for (i = 0; i < 12; i++) {
        slot                               = Battle_AllocEffect(1, 23);
        g_BattleEffects[slot].target.party = g_Task;
        g_BattleEffects[slot].unk_08       = actor->facing;
        g_BattleEffects[slot].pos.x.fixed  = g_Task->pos.x.fixed;
        g_BattleEffects[slot].pos.y.fixed  = g_Task->pos.y.fixed;
        g_BattleEffects[slot].pos.z.fixed  = g_Task->pos.z.fixed;
        g_BattleEffects[slot].arg.unk_09   = 48 - i * 4;
        g_BattleEffects[slot].unk_0B       = i;
        g_BattleEffects[slot].unk_0A       = 0;
    }
    SND_QueueSelectionEffect(EMI_CUE_ID(SND_BANK_COMMON, 0));
    g_Task->unk_09 = 0;
    g_Task->timer  = 0;
    g_Task->header.mode += 1;
}

MATCH void func_801EEE60(void) {
    u32          slot;
    PartyMember* battler;
    s32          timer;

    func_801EFDDC();
    if (g_Task->timer == 12) {
        slot = LOBU(g_Battle.target_selector);
        if (slot < BATTLE_PARTY_CHARACTERS_COUNT) {
            battler = &g_Game.members[slot];
        } else {
            battler = (PartyMember*)(g_BattleEnemies + slot * BATTLE_ENEMY_STRIDE);
        }
        GFX_FreePaletteFadeTarget(battler);
        GFX_AllocPaletteFade(battler, 6, 4, 8, 0);
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x200);
    }
    timer         = g_Task->timer + 1;
    g_Task->timer = timer;
    if ((timer & BYTE_MASK) == 16) {
        g_Task->header.mode += 1;
    }
}

MATCH void func_801EEF64(void) {
    u8 counter;

    func_801EF1FC();
    func_801EF804();
    func_801EFDDC();
    counter        = g_Task->unk_09 + 1;
    g_Task->unk_09 = counter;
    if ((counter & BYTE_MASK) == 0x40) {
        SND_QueueSelectionEffect(0x101);
        SND_QueueSelectionEffect(0x102);
        g_Task->unk_09 = 0x30;
        g_Task->header.mode += 1;
    }
}

MATCH void func_801EEFFC(void) {
    u8 timer;

    func_801EF1FC();
    func_801EF804();
    func_801EFDDC();
    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        g_Task->header.mode = g_Task->header.mode + 1;
    }
}

MATCH void func_801EF070(void) {
    u8           timer;
    u32          slot;
    u8*          selector;
    PartyMember* battler;

    func_801EFDDC();
    timer         = g_Task->timer - 1;
    g_Task->timer = timer;
    if (timer == 0) {
        BMAGIC_RELEASE_TARGET_AND_PLAY();
    }
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"

/* Draws a six-row ring of semi-transparent gouraud line quads around the effect, eight steps per
 * turn: row r runs from radius 0x100 - 41r (plus the row table) at z -(72r + table) to the next row,
 * the last row closing to the centre. A quad lights once unk_09 passes 7r, 6 shades per step up to
 * 0x30, alternating its lit edge between odd and even steps. */
MATCH void func_801EF1FC(void) {
    LINE_G4* prim;
    long     depth;
    long     flag;
    s32      row;
    s32      i;
    s32      x;
    s32      y;
    s32      tpage;
    s32      fade;

    for (row = 0; row < 6; row++) {
        D_1F800000.view.scenario.math_04 = 0x100 - row * 41;
        D_1F800000.view.scenario.math_00 = D_1F800000.view.scenario.math_04 + D_801F065C[row * 8];
        D_1F800014[0].vx                 = FIXED_MUL(rsin(0), D_1F800000.view.scenario.math_00);
        D_1F800014[0].vy                 = FIXED_MUL(rcos(0), D_1F800000.view.scenario.math_00);
        D_1F800014[0].vz                 = -(D_801F065C[row * 8] + row * 72);
        D_1F800000.view.scenario.math_04 = 0x100 - (row + 1) * 41;
        D_1F800000.view.scenario.math_00 = D_1F800000.view.scenario.math_04 + D_801F065C[row * 8 + 8];
        D_1F800014[1].vx                 = FIXED_MUL(rsin(0), D_1F800000.view.scenario.math_00);
        D_1F800014[1].vy                 = FIXED_MUL(rcos(0), D_1F800000.view.scenario.math_00);
        D_1F800014[1].vz                 = -((row + 1) * 72 + D_801F065C[row * 8 + 8]);
        if (row == 5) {
            D_1F800014[1].vy = 0;
            D_1F800014[1].vx = 0;
        }
        for (i = 1; i < 9; i++) {
            D_1F800014[2].vx                 = D_1F800014[1].vx;
            D_1F800014[2].vy                 = D_1F800014[1].vy;
            D_1F800014[2].vz                 = D_1F800014[1].vz;
            D_1F800014[3].vx                 = D_1F800014[0].vx;
            D_1F800014[3].vy                 = D_1F800014[0].vy;
            D_1F800014[3].vz                 = D_1F800014[0].vz;
            D_1F800000.view.scenario.math_04 = 0x100 - row * 41;
            D_1F800000.view.scenario.math_00 = D_1F800000.view.scenario.math_04 + D_801F065C[row * 8 + (i & 7)];
            D_1F800014[0].vx                 = FIXED_MUL(rsin(i << 9), D_1F800000.view.scenario.math_00);
            D_1F800014[0].vy                 = FIXED_MUL(rcos(i << 9), D_1F800000.view.scenario.math_00);
            D_1F800014[0].vz                 = -(D_801F065C[row * 8 + (i & 7)] + row * 72);
            D_1F800000.view.scenario.math_04 = 0x100 - (row + 1) * 41;
            D_1F800000.view.scenario.math_00 = D_1F800000.view.scenario.math_04 + D_801F065C[(row + 1) * 8 + (i & 7)];
            D_1F800014[1].vx                 = FIXED_MUL(rsin(i << 9), D_1F800000.view.scenario.math_00);
            D_1F800014[1].vy                 = FIXED_MUL(rcos(i << 9), D_1F800000.view.scenario.math_00);
            D_1F800014[1].vz                 = -(D_801F065C[(row + 1) * 8 + (i & 7)] + (row + 1) * 72);
            if (row == 5) {
                D_1F800014[1].vy = 0;
                D_1F800014[1].vx = 0;
            }
            x     = (D_1F800014[0].vx << 9) + g_Task->pos.x.fixed;
            y     = (D_1F800014[0].vy << 9) + g_Task->pos.y.fixed;
            tpage = GetGraphType() == 1 || GetGraphType() == 2 ? 0xA5 : 0x35;
            SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
            Area_AddCellPrim(x, y, 0, sizeof(DR_MODE));
            prim = GFX_CURSOR(LINE_G4);
            SetLineG4(prim);
            SetSemiTrans(prim, 1);
            RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
            fade = g_Task->unk_09 - row * 7;
            if (fade > 0) {
                D_1F800000.view.scenario.math_08 = fade * 6;
                if (D_1F800000.view.scenario.math_08 > 0x30) {
                    D_1F800000.view.scenario.math_08 = 0x30;
                }
                if (i & 1) {
                    setRGB0(prim, D_1F800000.view.scenario.math_08, D_1F800000.view.scenario.math_08, D_1F800000.view.scenario.math_08);
                    setRGB1(prim, 1, 1, 1);
                    setRGB2(prim, D_1F800000.view.scenario.math_08, D_1F800000.view.scenario.math_08, D_1F800000.view.scenario.math_08);
                    setRGB3(prim, 1, 1, 1);
                } else {
                    setRGB0(prim, 1, 1, 1);
                    setRGB1(prim, D_1F800000.view.scenario.math_08, D_1F800000.view.scenario.math_08, D_1F800000.view.scenario.math_08);
                    setRGB2(prim, 1, 1, 1);
                    setRGB3(prim, D_1F800000.view.scenario.math_08, D_1F800000.view.scenario.math_08, D_1F800000.view.scenario.math_08);
                }
                Area_AddCellPrim(x, y, 0, sizeof(LINE_G4));
            }
        }
    }
}

/* Draws the same six-row ring as func_801EF1FC with semi-transparent gouraud quads: a quad lights
 * once unk_09 passes 8r and its row-r edge brightens 48 shades per frame up to 0xC0 for four frames,
 * then its edge on row r + 1 does the same. */
MATCH void func_801EF804(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      row;
    s32      i;
    s32      x;
    s32      y;
    s32      tpage;
    s32      fade;

    for (row = 0; row < 6; row++) {
        D_1F800000.view.scenario.math_04 = 0x100 - row * 41;
        D_1F800000.view.scenario.math_00 = D_1F800000.view.scenario.math_04 + D_801F065C[row * 8];
        D_1F800014[0].vx                 = FIXED_MUL(rsin(0), D_1F800000.view.scenario.math_00);
        D_1F800014[0].vy                 = FIXED_MUL(rcos(0), D_1F800000.view.scenario.math_00);
        D_1F800014[0].vz                 = -(D_801F065C[row * 8] + row * 72);
        D_1F800000.view.scenario.math_04 = 0x100 - (row + 1) * 41;
        D_1F800000.view.scenario.math_00 = D_1F800000.view.scenario.math_04 + D_801F065C[row * 8 + 8];
        D_1F800014[1].vx                 = FIXED_MUL(rsin(0), D_1F800000.view.scenario.math_00);
        D_1F800014[1].vy                 = FIXED_MUL(rcos(0), D_1F800000.view.scenario.math_00);
        D_1F800014[1].vz                 = -((row + 1) * 72 + D_801F065C[row * 8 + 8]);
        if (row == 5) {
            D_1F800014[1].vy = 0;
            D_1F800014[1].vx = 0;
        }
        for (i = 1; i < 9; i++) {
            D_1F800014[2].vx                 = D_1F800014[0].vx;
            D_1F800014[2].vy                 = D_1F800014[0].vy;
            D_1F800014[2].vz                 = D_1F800014[0].vz;
            D_1F800014[3].vx                 = D_1F800014[1].vx;
            D_1F800014[3].vy                 = D_1F800014[1].vy;
            D_1F800014[3].vz                 = D_1F800014[1].vz;
            D_1F800000.view.scenario.math_04 = 0x100 - row * 41;
            D_1F800000.view.scenario.math_00 = D_1F800000.view.scenario.math_04 + D_801F065C[row * 8 + (i & 7)];
            D_1F800014[0].vx                 = FIXED_MUL(rsin(i << 9), D_1F800000.view.scenario.math_00);
            D_1F800014[0].vy                 = FIXED_MUL(rcos(i << 9), D_1F800000.view.scenario.math_00);
            D_1F800014[0].vz                 = -(D_801F065C[row * 8 + (i & 7)] + row * 72);
            D_1F800000.view.scenario.math_04 = 0x100 - (row + 1) * 41;
            D_1F800000.view.scenario.math_00 = D_1F800000.view.scenario.math_04 + D_801F065C[(row + 1) * 8 + (i & 7)];
            D_1F800014[1].vx                 = FIXED_MUL(rsin(i << 9), D_1F800000.view.scenario.math_00);
            D_1F800014[1].vy                 = FIXED_MUL(rcos(i << 9), D_1F800000.view.scenario.math_00);
            D_1F800014[1].vz                 = -(D_801F065C[(row + 1) * 8 + (i & 7)] + (row + 1) * 72);
            if (row == 5) {
                D_1F800014[1].vy = 0;
                D_1F800014[1].vx = 0;
            }
            x     = (D_1F800014[0].vx << 9) + g_Task->pos.x.fixed;
            y     = (D_1F800014[0].vy << 9) + g_Task->pos.y.fixed;
            tpage = GetGraphType() == 1 || GetGraphType() == 2 ? 0xA5 : 0x35;
            SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
            Area_AddCellPrim(x, y, 0, sizeof(DR_MODE));
            prim = GFX_CURSOR(POLY_G4);
            SetPolyG4(prim);
            SetSemiTrans(prim, 1);
            RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
            fade = g_Task->unk_09 - row * 8;
            if (fade > 0) {
                D_1F800000.view.scenario.math_08 = fade;
                if (fade < 5) {
                    D_1F800000.view.scenario.math_08 = fade * 48;
                    if (D_1F800000.view.scenario.math_08 > 0xC0) {
                        D_1F800000.view.scenario.math_08 = 0xC0;
                    }
                    setRGB0(prim, 1, 1, D_1F800000.view.scenario.math_08);
                    setRGB1(prim, 1, 1, 1);
                    setRGB2(prim, 1, 1, D_1F800000.view.scenario.math_08);
                    setRGB3(prim, 1, 1, 1);
                } else {
                    D_1F800000.view.scenario.math_08 = (fade - 4) * 48;
                    if (D_1F800000.view.scenario.math_08 > 0xC0) {
                        D_1F800000.view.scenario.math_08 = 0xC0;
                    }
                    setRGB0(prim, 1, 1, 0xC0);
                    setRGB1(prim, 1, 1, D_1F800000.view.scenario.math_08);
                    setRGB2(prim, 1, 1, 0xC0);
                    setRGB3(prim, 1, 1, D_1F800000.view.scenario.math_08);
                }
                Area_AddCellPrim(x, y, 0, sizeof(POLY_G4));
            }
        }
    }
}

MATCH void func_801EFDDC(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;

    D_1F800000.view.scenario.math_00 = 0x1C0;
    D_1F800014[2].vx                 = FIXED_MUL(rsin(0), D_1F800000.view.scenario.math_00);
    D_1F800014[2].vy                 = FIXED_MUL(rcos(0), D_1F800000.view.scenario.math_00);
    for (i = 1; i <= 16; i++) {
        D_1F800014[0].vx = 0;
        D_1F800014[0].vy = 0;
        D_1F800014[0].vz = 0;
        D_1F800014[1].vz = 0;
        D_1F800014[1].vx = D_1F800014[2].vx;
        D_1F800014[1].vy = D_1F800014[2].vy;
        D_1F800014[2].vx = FIXED_MUL(rsin(i << 8), D_1F800000.view.scenario.math_00);
        D_1F800014[2].vy = FIXED_MUL(rcos(i << 8), D_1F800000.view.scenario.math_00);
        D_1F800014[2].vz = 0;
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(0, 1, 320, 256), 0);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
        prim                             = GFX_BeginPolyG3(1);
        D_1F800000.view.scenario.math_08 = g_Task->timer * 8;
        setRGB0(prim, D_1F800000.view.scenario.math_08, D_1F800000.view.scenario.math_08, D_1F800000.view.scenario.math_08);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        RotTransPers3(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_G3));
    }
}

extern Callback D_801F0654[];

MATCH void func_801F0018(void) {
    Effect_SetActorMatrix();
    D_801F0654[g_Task->header.mode]();
    PopMatrix();
}

MATCH void func_801F0070(void) {
    u8 counter;

    if (BATTLE_ACTIVE_WORK->header.mode == 3) {
        counter        = g_Task->unk_09 - 1;
        g_Task->unk_09 = counter;
        if (!(counter & BYTE_MASK)) {
            g_Task->header.mode += 1;
        }
    }
}

MATCH void func_801F00D8(void) {
    u8 count;

    func_801F012C();
    count          = g_Task->unk_09 + 1;
    g_Task->unk_09 = count;
    if ((count & BYTE_MASK) == 0x20) {
        func_801E5988();
    }
}

/* Draws 32 semi-transparent flat triangles on a ring around the effect, one per 1/32 turn: the ring
 * radius comes from the row table (row = param.unk_0B / 2) widened by the timer, or by unk_09 while the
 * timer is 0, and its z is lowered by 72 per row; each triangle turns and shrinks with unk_09 while
 * its z rises by 4 per unk_09, and once z passes 0 it is clamped there and the timer takes unk_09.
 * The blue is random. */
MATCH void func_801F012C(void) {
    POLY_F3* prim;
    SVECTOR  center;
    long     depth;
    long     flag;
    s32      i;
    s32      row;
    s32      x;
    s32      y;
    s32      tpage;
    s16      z;

    row = g_Task->param.unk_0B >> 1;
    for (i = 1; i < 33; i++) {
        D_1F800000.view.scenario.math_04 = 0x100 - row * 41;
        D_1F800000.view.scenario.math_00 = D_1F800000.view.scenario.math_04 + D_801F065C[row * 8 + (i / 8 & 7)];
        if (g_Task->timer != 0) {
            D_1F800000.view.scenario.math_00 += g_Task->timer * 4;
        } else {
            D_1F800000.view.scenario.math_00 += g_Task->unk_09 * 4;
        }
        center.vx = FIXED_MUL(rsin(i << 7), D_1F800000.view.scenario.math_00);
        center.vy = FIXED_MUL(rcos(i << 7), D_1F800000.view.scenario.math_00);
        center.vz = -(D_801F065C[row * 8 + (i / 8 & 7)] + row * 72);
        if (g_Task->param.unk_0B & 1) {
            center.vz -= 0x24;
        }
        center.vx += D_801F065C[i + row];
        center.vy += D_801F065C[i + row];
        center.vz += D_801F065C[i + row];
        x     = (center.vx << 9) + g_Task->pos.x.fixed;
        y     = (center.vy << 9) + g_Task->pos.y.fixed;
        tpage = GetGraphType() == 1 || GetGraphType() == 2 ? 0xA5 : 0x35;
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_AddCellPrim(x, y, 0, sizeof(DR_MODE));
        prim = GFX_CURSOR(POLY_F3);
        SetPolyF3(prim);
        SetSemiTrans(prim, 1);
        D_1F800000.view.scenario.math_00 = 0x21 - g_Task->unk_09;
        D_1F800014[0].vx                 = center.vx + FIXED_MUL(rsin(((g_Task->unk_09 + 0x10) & 0x3F) << 6), D_1F800000.view.scenario.math_00);
        D_1F800014[0].vy                 = center.vy + FIXED_MUL(rcos(((g_Task->unk_09 + 0x10) & 0x3F) << 6), D_1F800000.view.scenario.math_00);
        D_1F800014[1].vx                 = center.vx + FIXED_MUL(rsin(((g_Task->unk_09 + 0x28) & 0x3F) << 6), D_1F800000.view.scenario.math_00);
        D_1F800014[1].vy                 = center.vy + FIXED_MUL(rcos(((g_Task->unk_09 + 0x28) & 0x3F) << 6), D_1F800000.view.scenario.math_00);
        D_1F800014[2].vx                 = center.vx + FIXED_MUL(rsin(((g_Task->unk_09 + 0x31) & 0x3F) << 6), D_1F800000.view.scenario.math_00);
        D_1F800014[2].vy                 = center.vy + FIXED_MUL(rcos(((g_Task->unk_09 + 0x31) & 0x3F) << 6), D_1F800000.view.scenario.math_00);
        z                                = center.vz + g_Task->unk_09 * 4;
        D_1F800014[2].vz                 = z;
        D_1F800014[1].vz                 = z;
        D_1F800014[0].vz                 = z;
        if (z > 0) {
            D_1F800014[2].vz = 0;
            D_1F800014[1].vz = 0;
            D_1F800014[0].vz = 0;
            if (g_Task->timer == 0) {
                g_Task->timer = g_Task->unk_09;
            }
        }
        setRGB0(prim, 0x40, 0x40, (rand() & 0x7F) + 0x40);
        RotTransPers3(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        Area_AddCellPrim(x, y, 0, sizeof(POLY_F3));
    }
}
