#include "magic060_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC34(void) {
    Magic060Steps handlers;

    handlers = D_801EEC04;
    SYS_DISPATCH_TASK(handlers.steps, 1, g_Task);
}

INCLUDE_ASM(func_801EECA4);

MATCH void func_801EED68(void) {
    u32          slot;
    PartyMember* work;

    if (g_Task->param.unk_0B == 2) {
        slot                               = Battle_AllocEffect(1, 0x12) & BYTE_MASK;
        work                               = g_Task;
        g_BattleEffects[slot].header.mode  = 2;
        g_BattleEffects[slot].target.party = work;
        g_Task->unk_09                     = 0x10;
        g_Task->header.mode                = g_Task->header.mode + 1;
    }
}

MATCH void func_801EEE00(void) {
    u8 timer;

    if (g_Battle.target_selector < 3U) {
        func_801EF174();
    } else {
        func_801EF2DC();
    }
    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        g_Task->header.mode += 1;
    }
}

MATCH void func_801EEE84(void) {
    if (g_Battle.target_selector < 3) {
        func_801EF174();
    } else {
        func_801EF2DC();
    }
    if (g_InputPressed != 0) {
        g_Task->param.unk_0B = 0x83;
        g_Task->header.mode++;
    }
}

MATCH void func_801EEF04(void) {
    u16* flags;

    if (g_Task->param.unk_0B == 0x80) {
        BATTLE_RAISE_STATE(BATTLE_STATE_EFFECT_PLAYING);
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EEF50);

/* Sets the bit of the targeted enemy's id in g_IdentifiedEnemies. */
MATCH void Effect_MarkTargetIdentified(void) {
    u8 id;

    id = ENEMY_COMBATANT(g_Battle.target_selector).enemy_id.byte.kind;
    BIT_ARRAY_SET(g_IdentifiedEnemies, id);
}

/* Whether the bit of the targeted enemy's id is set in g_IdentifiedEnemies. */
MATCH bool Effect_TargetIsIdentified(void) {
    u8 id;

    id = ENEMY_COMBATANT(g_Battle.target_selector).enemy_id.byte.kind;
    return BIT_ARRAY_TEST(g_IdentifiedEnemies, id) != 0;
}

INCLUDE_ASM(func_801EF174);

INCLUDE_ASM(func_801EF2DC);

INCLUDE_ASM(func_801EF470);

INCLUDE_ASM(func_801EF590);

INCLUDE_ASM(func_801EF76C);

INCLUDE_ASM(func_801EF924);

INCLUDE_ASM(func_801EFB00);

#ifdef NON_MATCHING
NON_MATCHING void func_801EFCE8(s32 x, s32 y) {
    POLY_FT4* prim;
    u16*      u;
    u16*      v;
    s32       index;
    s32       i;

    index = g_Battle.target_selector - 3;
    v     = D_801F0B9A;
    u     = v - 1;
    i     = 0;
    do {
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        setXY4(prim, x, y, x + 12, y, x, y + 12, x + 12, y + 12);
        D_1F800004 = 0x30;
        switch (i) {
            case 0:
                if (g_BattleEnemyBattlers[index].stats.resistances[RES_INDEX_FIRE] < 2) {
                    D_1F800004 = 0x80;
                }
                break;
            case 1:
                if (g_BattleEnemyBattlers[index].stats.resistances[RES_INDEX_FROST] < 2) {
                    D_1F800004 = 0x80;
                }
                break;
            case 2:
                if (g_BattleEnemyBattlers[index].stats.resistances[RES_INDEX_ELECTRIC] < 2) {
                    D_1F800004 = 0x80;
                }
                break;
            case 3:
                if (g_BattleEnemyBattlers[index].stats.resistances[RES_INDEX_WIND] < 2) {
                    D_1F800004 = 0x80;
                }
                break;
            case 4:
                if (g_BattleEnemyBattlers[index].stats.resistances[RES_INDEX_EARTH] < 2) {
                    D_1F800004 = 0x80;
                }
                break;
            case 5:
                if (g_BattleEnemyBattlers[index].stats.resistances[RES_INDEX_HOLY] < 4) {
                    D_1F800004 = 0x80;
                }
                break;
        }
        setRGB0(prim, D_1F800004, D_1F800004, D_1F800004);
        prim->tpage = GetTPage(0, 1, 960, 256);
        prim->clut  = GetClut(0, 480);
        prim->u0    = *u;
        prim->v0    = *v;
        prim->u1    = (u8)*u + 12;
        prim->v1    = *v;
        prim->u2    = *u;
        prim->v2    = (u8)*v + 12;
        prim->u3    = (u8)*u + 12;
        prim->v3    = (u8)*v + 12;
        i++;
        x += 20;
        u += 2;
        v += 2;
        GFX_AddPrim(2, sizeof(POLY_FT4));
    } while (v < D_801F0B9A + 12);
}
#else
INCLUDE_ASM(func_801EFCE8);
#endif

/* func_801EFF44 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EFF88(void) {
    SYS_DISPATCH_BYTE(D_801F0BBC, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801F012C();
    }
}

#include "overlays/bmagic/Effect_ClearTimerNextStep.h"

MATCH void func_801F0030(void) {
    u8 count;

    count          = g_Task->unk_09 + 1;
    g_Task->unk_09 = count;
    if ((count & BYTE_MASK) == 0x10) {
        g_BattleEffectBattler->param.unk_0B = 1;
        g_Task->header.step += 1;
    }
}

MATCH void func_801F0090(void) {
    PartyMember* work;

    work = (PartyMember*)g_BattleEffectBattler;
    if (work->param.unk_0B == 0x83) {
        g_Task->header.step++;
    }
}

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

INCLUDE_ASM(func_801F012C);

MATCH void func_801F0254(void) {
    SYS_DISPATCH_BYTE(D_801F0BCC, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801F0428();
    }
}

MATCH void func_801F02CC(void) {
    if (g_BattleEffectBattler->param.unk_0B == 1) {
        g_Task->unk_09 = 0;
        g_Task->header.step += 1;
    }
}

MATCH void func_801F031C(void) {
    u8 count;

    count          = g_Task->unk_09 + 1;
    g_Task->unk_09 = count;
    if ((count & BYTE_MASK) == 0x1E) {
        g_BattleEffectBattler->param.unk_0B = 2;
        g_Task->header.step += 1;
    }
}

MATCH void func_801F037C(void) {
    PartyMember* work;

    work = (PartyMember*)g_BattleEffectBattler;
    if (work->param.unk_0B == 0x83) {
        g_Task->header.step++;
    }
}

MATCH void func_801F03BC(void) {
    PartyMember* active;

    g_Task->unk_09 = g_Task->unk_09 - 2;
    if (g_Task->unk_09 == 0) {
        active               = BATTLE_ACTIVE_WORK;
        active->param.unk_0B = active->param.unk_0B - 1;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801F0428);

MATCH void func_801F07E8(void) {
    SYS_DISPATCH_TASK(g_BMagicEffectModes + 11, 2, g_Task);
}

MATCH void func_801F082C(void) {
    PartyMember** actor;

    actor = &g_Battle.selected_actor;
    GFX_FreePaletteFadeTarget(*actor);
    g_Task->param.unk_0B = GFX_AllocPaletteFade(*actor, 0, 0, 0, 1);
    g_Task->unk_09       = 0;
    g_Task->header.step += 1;
}

INCLUDE_ASM(func_801F08B8);

INCLUDE_ASM(func_801F09E0);
