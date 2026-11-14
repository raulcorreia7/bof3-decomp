#include "magic068_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC18.h"

MATCH void func_801EEC88(void) {
    u32          slot;
    PartyMember* task;

    g_Task->facing                     = g_BattleEffectBattler->facing;
    g_Task->pos.x.fixed                = g_BattleEffectBattler->pos.x.fixed;
    g_Task->pos.y.fixed                = g_BattleEffectBattler->pos.y.fixed;
    g_Task->pos.z.fixed                = g_BattleEffectBattler->pos.z.fixed;
    slot                               = Battle_AllocEffect(1, 28) & BYTE_MASK;
    task                               = g_Task;
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].target.party = task;
    g_Task->param.unk_0B               = 1;
    g_Task->header.mode += 1;
}

MATCH void func_801EED50(void) {
    s32 i;
    s32 percent;
    s32 adjust;
    s16 score;
    s16 party_count;
    s16 party_levels;
    s16 enemy_count;
    s16 enemy_levels;
    s16 level_gap;

    adjust = 0;
    score  = 0;
    if (g_Task->param.unk_0B == 0) {
        party_count  = 0;
        party_levels = 0;
        for (i = 0; i < 3; i++) {
            if (g_Game.members[i].header.flags) {
                if (g_Game.members[i].chr.status & STATUS_KO) {
                    score -= 24;
                } else {
                    percent = g_Game.members[i].chr.hp * 100 / g_Game.members[i].chr.stats.max_hp;
                    party_count++;
                    party_levels += g_Game.members[i].chr.level;
                    if (percent == 0) {
                        adjust = -24;
                    }
                    if (percent > 0) {
                        adjust = -21;
                    }
                    if (percent > 10) {
                        adjust = -18;
                    }
                    if (percent > 20) {
                        adjust = -15;
                    }
                    if (percent > 30) {
                        adjust = -12;
                    }
                    if (percent > 40) {
                        adjust = -9;
                    }
                    if (percent > 50) {
                        adjust = -6;
                    }
                    if (percent > 60) {
                        adjust = -3;
                    }
                    if (percent > 70) {
                        adjust = 0;
                    }
                    score += adjust;
                }
            }
        }
        enemy_count  = 0;
        enemy_levels = 0;
        for (i = 0; i < 8; i++) {
            if (Battle_SlotIsBlocked((u8)(i + 3)) == 0) {
                percent = g_BattleEnemyBattlers[i].hp * 100 / g_BattleEnemyBattlers[i].stats.max_hp;
                enemy_count++;
                enemy_levels += g_BattleEnemyBattlers[i].level;
                if (percent == 0) {
                    adjust = 24;
                }
                if (percent > 0) {
                    adjust = 21;
                }
                if (percent > 10) {
                    adjust = 18;
                }
                if (percent > 20) {
                    adjust = 15;
                }
                if (percent > 30) {
                    adjust = 12;
                }
                if (percent > 40) {
                    adjust = 9;
                }
                if (percent > 50) {
                    adjust = 8;
                }
                if (percent > 60) {
                    adjust = 3;
                }
                if (percent > 70) {
                    adjust = 0;
                }
                score += adjust;
            }
        }
        score += (g_Battle.enemy_count - enemy_count) * 8;
        level_gap = party_levels / party_count - enemy_levels / enemy_count;
        adjust    = 130;
        if (level_gap < 21) {
            adjust = 120;
        }
        if (level_gap < 16) {
            adjust = 110;
        }
        if (level_gap < 11) {
            adjust = 100;
        }
        if (level_gap < 8) {
            adjust = 95;
        }
        if (level_gap < 6) {
            adjust = 90;
        }
        if (level_gap < 4) {
            adjust = 85;
        }
        if (level_gap < 2) {
            adjust = 80;
        }
        if (level_gap < 0) {
            adjust = 70;
        }
        if (level_gap < -2) {
            adjust = 60;
        }
        if (level_gap < -4) {
            adjust = 45;
        }
        if (level_gap < -6) {
            adjust = 30;
        }
        if (level_gap < -9) {
            adjust = 20;
        }
        if (level_gap < -14) {
            adjust = 10;
        }
        if (level_gap < -19) {
            adjust = 5;
        }
        score += adjust;
        score += D_801EFC9F[party_count - enemy_count];
        if (score < 0) {
            score = 0;
        }
        if (score > 100) {
            score = 100;
        }
        if (score > 90 && score <= 100) {
            func_801DE8C0(1, 60, Message_GetText(0x3C));
        }
        if (score > 70 && score <= 90) {
            func_801DE8C0(1, 60, Message_GetText(0x3D));
        }
        if (score > 50 && score <= 70) {
            func_801DE8C0(1, 60, Message_GetText(0x3E));
        }
        if (score > 30 && score <= 50) {
            func_801DE8C0(1, 60, Message_GetText(0x3F));
        }
        if (score <= 30) {
            func_801DE8C0(1, 60, Message_GetText(0x40));
        }
        for (i = 0; i < 8; i++) {
            if (Battle_SlotIsBlocked((u8)(i + 3)) == 0) {
                if (g_BattleEnemyBattlers[i].stats.resistances[RES_INDEX_FIRE] < 2) {
                    g_Task->param.unk_0B |= 1;
                }
                if (g_BattleEnemyBattlers[i].stats.resistances[RES_INDEX_FROST] < 2) {
                    g_Task->param.unk_0B |= 2;
                }
                if (g_BattleEnemyBattlers[i].stats.resistances[RES_INDEX_ELECTRIC] < 2) {
                    g_Task->param.unk_0B |= 4;
                }
                if (g_BattleEnemyBattlers[i].stats.resistances[RES_INDEX_WIND] < 2) {
                    g_Task->param.unk_0B |= 8;
                }
                if (g_BattleEnemyBattlers[i].stats.resistances[RES_INDEX_EARTH] < 2) {
                    g_Task->param.unk_0B |= 0x10;
                }
                if (g_BattleEnemyBattlers[i].stats.resistances[RES_INDEX_HOLY] < 4) {
                    g_Task->param.unk_0B |= 0x20;
                }
            }
        }
        g_Task->unk_09 = 22;
        g_Task->timer  = 4;
        g_Task->header.mode += 1;
    }
}

MATCH void func_801EF44C(void) {
    u8 timer;

    timer         = g_Task->timer - 1;
    g_Task->timer = timer;
    if (timer == 0) {
        g_Task->timer       = 62;
        g_Task->header.mode = g_Task->header.mode + 1;
    }
}

MATCH void func_801EF4A8(void) {
    func_801EF55C();
    if (g_InputPressed != 0) {
        g_Task->header.mode = 4;
    }
}

MATCH void func_801EF4EC(void) {
    s8 val;

    if (D_801EC2E4 == 0) {
        g_Battle.state |= BATTLE_STATE_EFFECT_PLAYING;
        func_801E5988();
        return;
    }
    val = g_Task->unk_09;
    if (val > 0) {
        g_Task->unk_09 = val - 8;
        func_801EF55C();
    }
}

MATCH void func_801EF55C(void) {
    TILE* prim;
    s32   tpage;
    s32   i;

    if (GetGraphType() == 1) {
        tpage = 0x25;
    } else if (GetGraphType() == 2) {
        tpage = 0x25;
    } else {
        tpage = 0x15;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(0, sizeof(DR_MODE));
    D_1F800000.view.scenario.math_00 = 0xE8;
    D_1F800000.view.scenario.math_04 = g_Task->unk_09;
    for (i = 0; i < 6; i++) {
        if ((g_Task->param.unk_0B >> i) & 1) {
            prim = (TILE*)g_GfxPrimCursor;
            SetTile(prim);
            prim->x0 = D_1F800000.view.scenario.math_00;
            prim->y0 = D_1F800000.view.scenario.math_04;
            D_1F800000.view.scenario.math_00 += 10;
            prim->w  = 8;
            prim->h  = 12;
            prim->r0 = D_801EFCA4[i][0];
            prim->g0 = D_801EFCA4[i][1];
            prim->b0 = D_801EFCA4[i][2];
            GFX_AddPrim(0, sizeof(TILE));
        }
    }
    if (g_Task->param.unk_0B == 0) {
        prim = (TILE*)g_GfxPrimCursor;
        SetTile(prim);
        prim->x0 = D_1F800000.view.scenario.math_00;
        prim->y0 = D_1F800000.view.scenario.math_04;
        prim->w  = 8;
        prim->h  = 12;
        setRGB0(prim, 0x60, 0x60, 0x60);
        GFX_AddPrim(0, sizeof(TILE));
    }
}

/* func_801EF73C */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF780(void) {
    SYS_DISPATCH_TASK(g_BMagicEffectModes + 1, 2, g_Task);
}

MATCH void func_801EF7C4(void) {
    g_Task->facing      = g_BattleEffectBattler->facing;
    g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;
    g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;
    g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed + 0x02000000;
    Battle_ProjectRange();
    SND_QueueSelectionFx(0x100);
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 0xF;
    g_Task->timer        = 3;
    g_Task->header.step += 1;
}

MATCH void func_801EF884(void) {
    u8 count;

    Effect_SetActorMatrix();
    func_801EFA48();
    PopMatrix();
    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        g_Task->unk_09 = 0xF;
        g_Task->header.step += 1;
    }
}

INCLUDE_ASM(func_801EF908);

MATCH void func_801EF9D0(void) {
    u8 timer;

    Effect_SetActorMatrix();
    func_801EFA48();
    PopMatrix();
    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        BMAGIC_TICK_EFFECT_WORK();
        func_801E5988();
    }
}

MATCH void func_801EFA48(void) {
    POLY_FT4* prim;
    s32       tpage;

    if (GetGraphType() == 1 || GetGraphType() == 2) {
        tpage = 0x25;
    } else {
        tpage = 0x15;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(2, sizeof(DR_MODE));
    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    prim->x0 = g_Task->unk_2E.half - 12;
    prim->y0 = g_Task->unk_30.half - 12;
    prim->x1 = g_Task->unk_2E.half + 12;
    prim->y1 = g_Task->unk_30.half - 12;
    prim->x2 = g_Task->unk_2E.half - 12;
    prim->y2 = g_Task->unk_30.half + 12;
    prim->x3 = g_Task->unk_2E.half + 12;
    prim->y3 = g_Task->unk_30.half + 12;
    setRGB0(prim, 128, 128, 128);
    prim->tpage = GetTPage(0, 0, 960, 0);
    prim->clut  = GetClut(0, 480);
    setUV4(prim, g_Task->param.unk_0B, 36, g_Task->param.unk_0B + 11, 36, g_Task->param.unk_0B, 46, g_Task->param.unk_0B + 11, 46);
    GFX_AddPrim(2, sizeof(POLY_FT4));
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"
