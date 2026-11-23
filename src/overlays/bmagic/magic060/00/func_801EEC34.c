#include "magic060_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC34(void) {
    Magic060Steps handlers;

    handlers = D_801EEC04;
    SYS_DISPATCH_TASK(handlers.steps, 1, g_Task);
}

MATCH void func_801EECA4(void) {
    PartyMember* work;
    PartyMember* work2;
    u32          slot;

    slot                               = Battle_AllocEffect(1, 18) & BYTE_MASK;
    work                               = TASK(PartyMember);
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].target.party = work;
    slot                               = Battle_AllocEffect(1, 18) & BYTE_MASK;
    work2                              = TASK(PartyMember);
    g_BattleEffects[slot].header.mode  = 1;
    g_BattleEffects[slot].target.party = work2;
    func_801EEF50();
    TASK(PartyMember)->param.unk_0B = 0;
    TASK(PartyMember)->header.mode += 1;
}

MATCH void func_801EED68(void) {
    u32          slot;
    PartyMember* work;

    if (TASK(PartyMember)->param.unk_0B == 2) {
        slot                               = Battle_AllocEffect(1, 18) & BYTE_MASK;
        work                               = TASK(PartyMember);
        g_BattleEffects[slot].header.mode  = 2;
        g_BattleEffects[slot].target.party = work;
        TASK(PartyMember)->unk_09          = 0x10;
        TASK(PartyMember)->header.mode     = TASK(PartyMember)->header.mode + 1;
    }
}

MATCH void func_801EEE00(void) {
    u8 timer;

    if (g_Battle.target_selector < 3U) {
        func_801EF174();
    } else {
        func_801EF2DC();
    }
    timer                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        TASK(PartyMember)->header.mode += 1;
    }
}

MATCH void func_801EEE84(void) {
    if (g_Battle.target_selector < 3) {
        func_801EF174();
    } else {
        func_801EF2DC();
    }
    if (g_PadStates[0].pressed != 0) {
        TASK(PartyMember)->param.unk_0B = 0x83;
        TASK(PartyMember)->header.mode++;
    }
}

MATCH void func_801EEF04(void) {
    u16* flags;

    if (TASK(PartyMember)->param.unk_0B == 0x80) {
        BATTLE_RAISE_STATE(BATTLE_STATE_EFFECT_PLAYING);
        Effect_Reset();
    }
}

MATCH void func_801EEF50(void) {
    s32 value;
    s32 threshold;
    u8  identified;

    value     = g_Game.members[g_Battle.active_battler].chr.level - ENEMY_COMBATANT(g_Battle.target_selector).level;
    threshold = 16;
    if (value < 15) {
        threshold = 14;
    }
    if (value < 10) {
        threshold = 12;
    }
    if (value < 5) {
        threshold = 10;
    }
    if (value < 0) {
        threshold = 8;
    }
    if (value < -5) {
        threshold = 6;
    }
    if (value < -10) {
        threshold = 4;
    }
    if (value < -15) {
        threshold = 2;
    }
    value      = threshold > (rand() & 0xF);
    identified = Effect_TargetIsIdentified();
    if (identified != 0) {
        TASK(PartyMember)->unk_04 = 1;
    } else if (value != 0 && ENEMY_COMBATANT(g_Battle.target_selector).unk_7F != 0) {
        Effect_MarkTargetIdentified();
        TASK(PartyMember)->unk_04 = 1;
    } else {
        TASK(PartyMember)->unk_04 = 0;
    }
}

/* Sets the bit of the targeted enemy's id in g_IdentifiedEnemies. */
MATCH void Effect_MarkTargetIdentified(void) {
    u8 id;

    id = ENEMY_COMBATANT(g_Battle.target_selector).enemy_id.byte.type;
    BIT_ARRAY_SET(g_IdentifiedEnemies, id);
}

/* Whether the bit of the targeted enemy's id is set in g_IdentifiedEnemies. */
MATCH bool Effect_TargetIsIdentified(void) {
    u8 id;

    id = ENEMY_COMBATANT(g_Battle.target_selector).enemy_id.byte.type;
    return BIT_ARRAY_TEST(g_IdentifiedEnemies, id) != 0;
}

MATCH void func_801EF174(void) {
    u8 id;

    /* kept: retail reloads the target row at each access; a PartyMember* local changes the bytes. */
    id                                                        = g_Game.members[g_Battle.target_selector].chr.character_id;
    g_Game.members[g_Battle.target_selector].chr.character_id = CHAR_ID_RYU_YOUNG;
    Effect_DrawText(g_Game.members[g_Battle.target_selector].chr.name, 112, 48);
    g_Game.members[g_Battle.target_selector].chr.character_id = id;
    func_801EF76C(D_801F0B64, 90, 68);
    func_801EF76C(D_801F0B7C, 128, 68);
    Effect_DrawText(D_801F0B8C, 112, 80);
    Effect_DrawText(D_801F0B88, 156, 100);
    Effect_DrawText(D_801F0B6C, 176, 100);
    Effect_DrawText(D_801F0B88, 156, 120);
    Effect_DrawText(D_801F0B70, 176, 120);
    func_801EF76C(D_801F0B74, 90, 138);
    Effect_DrawText(D_801F0B8C, 112, 152);
    Effect_DrawText(D_801F0B8C, 112, 172);
}

MATCH void func_801EF2DC(void) {
    u8 slot;

    slot = g_Battle.target_selector - BATTLE_PARTY_CHARACTERS_COUNT;
    if (g_BattleEnemyBattlers[slot].unk_7F != 0) {
        func_801EF924(g_BattleEnemyBattlers[slot].name, 112, 48);
        func_801EFB00(g_BattleEnemyBattlers[slot].exp, 112, 100);
        Effect_DrawText(D_801F0B6C, 176, 100);
        func_801EFB00(g_BattleEnemyBattlers[slot].zenny, 112, 120);
    } else {
        func_801EF924(g_BattleEnemyBattlers[slot].name, 112, 48);
        Effect_DrawText(D_801F0B88, 156, 100);
        Effect_DrawText(D_801F0B6C, 176, 100);
        Effect_DrawText(D_801F0B88, 156, 120);
    }
    Effect_DrawText(D_801F0B70, 176, 120);
    func_801EF76C(D_801F0B74, 90, 138);
    func_801EF470(g_BattleEnemyBattlers[slot].drops[0].item & BYTE_MASK, g_BattleEnemyBattlers[slot].drops[0].item >> 8, 152);
    func_801EF470(g_BattleEnemyBattlers[slot].drops[1].item & BYTE_MASK, g_BattleEnemyBattlers[slot].drops[1].item >> 8, 172);
}

MATCH void func_801EF470(u8 item_id, u8 category, s32 y) {
    /* FAKE: the record pointer must stay in s0 through the switch; an unpinned local scales the table index in v1, and the best pure-C body differs in 11 instructions at the same 0x120-byte size. */
    FAKE_REG(u8*, record, "s0");

    if (TASK(PartyMember)->unk_04 != 0) {
        switch (category) {
            case ITEM_CATEGORY_ITEM:
            default:
                record = (u8*)&g_Items[item_id];
                break;
            case ITEM_CATEGORY_WEAPON:
                record = (u8*)&g_Weapons[item_id];
                break;
            case ITEM_CATEGORY_ARMOR:
                record = (u8*)&g_Armors[item_id];
                break;
            case ITEM_CATEGORY_ACCESSORY:
                record = (u8*)&g_Accessories[item_id];
                break;
        }
        UI_TextDraw(112, (s16)y, 0, Game_ReadCommand(record) & BYTE_MASK, record);
    } else {
        Effect_DrawText(D_801F0B8C, 112, (s16)y);
    }
}

MATCH void Effect_DrawText(u8* text, s32 x, s32 y) {
    POLY_FT4* prim;
    s32       mode;
    s32       x1;
    s32       y1;
    s32       i;
    s32       code;
    s16       u;
    s16       v;

    mode = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_FOREGROUND, mode);
    if (*text == 0) {
        return;
    }
    i  = 0;
    y1 = y + 0xC;
    while (*text != 0 && i < 12) {
        prim = GFX_CURSOR(POLY_FT4);
        SetPolyFT4(prim);
        x1 = x + 8;
        setXY4(prim, x, y, x1, y, x, y1, x1, y1);
        setRGB0(prim, 0x80, 0x80, 0x80);
        setTPage(prim, TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y);
        setClut(prim, 0, 0x1E0);
        code = *text - 0x30;
        u    = (code % 31) * 8;
        v    = (code / 31) * 12 + 0x48;
        setUV4(prim, u, v, u + 8, v, u, v + 0xC, u + 8, v + 0xC);
        if (*text != 0xFF) {
            GFX_AddPrim(BMAGIC_LAYER_FOREGROUND, sizeof(POLY_FT4));
        }
        i++;
        text++;
        x = x1;
    }
}

MATCH void func_801EF76C(u8* text, s32 x, s32 y) {
    POLY_FT4* prim;

    GFX_AddDitheredDrawMode(BMAGIC_LAYER_FOREGROUND, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 0x140, 0x100));
    while (*text != 0) {
        prim = GFX_CURSOR(POLY_FT4);
        SetPolyFT4(prim);
        setXYWH(prim, x, y, 8, 8);
        setRGB0(prim, 128, 128, 128);
        setTPage(prim, TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y);
        setClut(prim, 0, 0x1E0);
        setUV4(prim, (*text - 0x40) * 8, 8, (*text - 0x40) * 8 + 8, 8, (*text - 0x40) * 8, 16, (*text - 0x40) * 8 + 8, 16);
        if (*text != 0xFF) {
            GFX_AddPrim(BMAGIC_LAYER_FOREGROUND, sizeof(POLY_FT4));
        }
        text++;
        x += 8;
    }
}

MATCH void func_801EF924(u8* text, s32 x, s32 y) {
    POLY_FT4* prim;
    s32       mode;
    s32       x1;
    s32       y1;
    s32       i;
    s32       code;
    s16       u;
    s16       v;

    mode = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_FOREGROUND, mode);
    if (*text == 0) {
        return;
    }
    i  = 0;
    y1 = y + 0xC;
    while (*text != 0 && i < 8) {
        prim = GFX_CURSOR(POLY_FT4);
        SetPolyFT4(prim);
        x1 = x + 8;
        setXY4(prim, x, y, x1, y, x, y1, x1, y1);
        setRGB0(prim, 0x80, 0x80, 0x80);
        setTPage(prim, TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y);
        setClut(prim, 0, 0x1E0);
        code = *text - 0x30;
        u    = (code % 31) * 8;
        v    = (code / 31) * 12 + 0x48;
        setUV4(prim, u, v, u + 8, v, u, v + 0xC, u + 8, v + 0xC);
        if (*text != 0xFF) {
            GFX_AddPrim(BMAGIC_LAYER_FOREGROUND, sizeof(POLY_FT4));
        }
        i++;
        text++;
        x = x1;
    }
}

/* Draws a five-digit number as 12x12 glyphs, leading zeros hidden. */
MATCH void func_801EFB00(s32 value, s32 x, s32 y) {
    POLY_FT4* prim;
    u16       digit;
    u32       scale;
    s32       i;
    s32       mode;
    s32       started;

    mode = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_FOREGROUND, mode);
    started = 0;
    scale   = 10000;
    for (i = 0; i < 5; i++) {
        prim = GFX_CURSOR(POLY_FT4);
        SetPolyFT4(prim);
        setXYWH(prim, x, y, 12, 12);
        setRGB0(prim, 128, 128, 128);
        setTPage(prim, TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y);
        setClut(prim, 0, 0x1E0);
        digit = (value & HALF_MASK) / (scale & HALF_MASK);
        if (digit != 0) {
            started = 1;
        }
        value -= (value & HALF_MASK) / (scale & HALF_MASK) * scale;
        scale = (scale & HALF_MASK) / 10;
        setUVWH(prim, (digit + 6) * 12, 24, 12, 12);
        if (started != 0 || (scale & HALF_MASK) == 0) {
            GFX_AddPrim(BMAGIC_LAYER_FOREGROUND, sizeof(POLY_FT4));
        }
        x += 12;
    }
}
