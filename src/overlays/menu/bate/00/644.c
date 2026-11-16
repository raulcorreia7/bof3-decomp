#include "bate_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801D1244(void) {
    s32 cursor_x;
    s32 row;
    s32 first;
    s32 category;
    s32 row_offset;
    s32 buttons;
    u16 pad;
    u8  old_cursor;
    u8  first_row;
    u8  last_row;
    u8  next;
    u8* cursor;

    category                         = D_80148338;
    cursor_x                         = (u16)D_80148334;
    row                              = D_8014833B;
    first                            = LOBU(D_8014833A);
    g_MenuPanelTasks[1].flags        = 0;
    g_MenuPanelTasks[4].pos.x        = cursor_x + 7;
    row_offset                       = row - first;
    g_MenuPanelTasks[4].pos.y        = g_MenuPanelTasks[0].pos.y + (row_offset * 13 + 26);
    g_MenuPanelTasks[2].u.message.id = Item_GetDescription(category, g_MenuPanelTasks[0].flags);
    g_MenuPanelTasks[3].u.message.id = 221;
    buttons                          = INPUT_REPEATED(g_InputPressed, (INPUT_DIRECTIONAL | PADL1 | PADR1));
    func_801D1FA0();
    old_cursor = g_MenuPanelTasks[0].unk_0B;
    if (buttons & PADLup) {
        if (old_cursor != 0) {
            g_MenuPanelTasks[0].unk_0B = old_cursor - 1;
        }
        if (g_MenuPanelTasks[0].unk_0B < g_MenuPanelTasks[0].unk_0A) {
            g_MenuPanelTasks[0].u.addr.unk_10 = 240;
        }
    } else if (buttons & PADLdown) {
        if (old_cursor < 127) {
            g_MenuPanelTasks[0].unk_0B = old_cursor + 1;
        }
        if (g_MenuPanelTasks[0].unk_0B >= g_MenuPanelTasks[0].unk_0A + 9) {
            g_MenuPanelTasks[0].u.addr.unk_10 = 16;
        }
    } else if (buttons & PADL1) {
        first_row = g_MenuPanelTasks[0].unk_0A;
        if (first_row == 0) {
            g_MenuPanelTasks[0].unk_0B = 0;
        } else if (first_row < 9) {
            g_MenuPanelTasks[0].unk_0B = old_cursor - first_row;
            g_MenuPanelTasks[0].unk_0A = 0;
        } else {
            g_MenuPanelTasks[0].unk_0B = old_cursor - 9;
            g_MenuPanelTasks[0].unk_0A = first_row - 9;
        }
    } else if (buttons & PADR1) {
        last_row = g_MenuPanelTasks[0].unk_0A;
        if (last_row == 119) {
            g_MenuPanelTasks[0].unk_0B = 127;
        } else if (old_cursor >= 111) {
            next                       = old_cursor + 119;
            g_MenuPanelTasks[0].unk_0B = next - last_row;
            g_MenuPanelTasks[0].unk_0A = 119;
        } else {
            g_MenuPanelTasks[0].unk_0B = old_cursor + 9;
            g_MenuPanelTasks[0].unk_0A = last_row + 9;
        }
    }
    cursor = &g_MenuPanelTasks[0].unk_0B;
    if (old_cursor != *cursor) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
    }
    if ((s16)g_MenuPanelTasks[0].u.addr.unk_10 == 0) {
        pad = g_InputPressed;
        if (pad & g_InputMasks[MENU_INPUT_CONFIRM]) {
            if (g_MenuPanelTasks[0].flags != 0) {
                SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 4));
                Menu_ApplyEquipment();
                *cursor = GAME_NONE;
                g_MenuStep.state -= 1;
            } else {
                SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 7));
            }
        } else if (pad & g_InputMasks[MENU_INPUT_CANCEL]) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
            *cursor = GAME_NONE;
            g_MenuStep.state -= 1;
        }
    }
}

MATCH void func_801D153C(void) {
    SYS_DISPATCH_BYTE(g_MenuBateStep2Sub2Funcs, D_80148652);
}

MATCH void func_801D1578(void) {
    u8* timer = &D_80148654;
    u8  count;

    Menu_DrawClutStrip(D_80144953);
    count  = *timer - 1;
    *timer = count;
    if (count == 0) {
        UI_SetMode(UI_MODE_FAST_FADE_OUT);
        D_80148652 += 1;
    }
}

MATCH void func_801D15E4(void) {
    if (g_UiWindowEffectBusy == 0) {
        D_80148654 = 0;
        D_80148650 = 1;
        D_80148651 = 0;
        D_80148652 = 0;
        strncpy(&D_80144DE4, &D_801D86F0, 5);
        return;
    }
    Menu_DrawClutStrip(D_80144953);
}

INCLUDE_ASM(func_801D165C);

/* Totals the equipment menu's current and trial stat rows and marks each stat up (2), down (1) or equal (0). */
MATCH void func_801D1AB8(u16* base, u16* current, u16* trial, u8* change, u8* equipped, u8 swap, u8 slot) {
    Weapon* weapon;
    Armor*  armor;
    s32     i;

    weapon     = &g_Weapons[equipped[0]];
    armor      = &g_Armors[equipped[1]];
    current[0] = base[0] + weapon->power;
    current[1] = base[1] + armor->power;
    current[2] = base[2];
    current[3] = base[3] - (weapon->weight + armor->weight);
    if ((s16)current[3] < 0)
        current[3] = 0;
    if (swap == 1)
        weapon = &g_Weapons[slot];
    else
        weapon = &g_Weapons[equipped[0]];
    if (swap == 1)
        armor = &g_Armors[equipped[1]];
    else
        armor = &g_Armors[slot];
    trial[0] = base[0] + weapon->power;
    trial[1] = base[1] + armor->power;
    trial[2] = base[2];
    trial[3] = base[3] - (weapon->weight + armor->weight);
    if ((s16)trial[3] < 0)
        trial[3] = 0;
    for (i = 0; (u8)i < 4; i++) {
        if (current[(u8)i] < trial[(u8)i])
            change[(u8)i] = 2;
        else if (trial[(u8)i] < current[(u8)i])
            change[(u8)i] = 1;
        else
            change[(u8)i] = 0;
    }
}

#ifdef NON_MATCHING
/* The item tables hold this address; the reads around it name it one byte at a time. */

NON_MATCHING void func_801D1C90(void) {
    /* FAKE: these homes match the retail index scan and selected-field store. */
    FAKE_REG(u8, i, "a0");
    FAKE_REG(u8, terminator, "a2");
    FAKE_REG(u8*, task, "v1");
    FAKE_REG(u8*, selected, "a1");
    u8 value;

    i                          = 0;
    terminator                 = 7;
    task                       = (u8*)&g_MenuPanelTasks[0].handler;
    selected                   = task + 0xB;
    *task                      = 2;
    g_MenuPanelTasks[0].mode   = 2;
    g_MenuPanelTasks[0].state  = 2;
    g_MenuPanelTasks[0].active = 1;
    g_MenuPanelTasks[0].pos.x  = 0x140;
    g_MenuPanelTasks[0].pos.y  = 0x3E;
    do {
        value = g_PartyFieldOrder[i];
        if (value == 0 || value == terminator) {
            *selected = i;
            break;
        }
        i++;
    } while (i < 3);
    g_MenuPanelTasks[1].pos.x         = -0xAA;
    g_MenuPanelTasks[1].pos.y         = 0x3E;
    g_MenuPanelTasks[1].unk_0C        = 7;
    g_MenuPanelTasks[1].unk_0B        = 0xFF;
    g_MenuPanelTasks[1].item_table    = (s32)D_801D8EE0;
    g_MenuPanelTasks[2].item_table    = (s32)D_801D8EE0;
    g_MenuPanelTasks[2].pos.x         = 0x14;
    g_MenuPanelTasks[2].u.addr.unk_12 = 0x118;
    g_MenuPanelTasks[3].pos.x         = 0xA4;
    g_MenuPanelTasks[0].unk_09        = 0;
    g_MenuPanelTasks[0].unk_0B        = 0;
    g_MenuPanelTasks[0].unk_0A        = 0;
    g_MenuPanelTasks[0].unk_08        = 0;
    g_MenuPanelTasks[0].flags         = 0;
    g_MenuPanelTasks[0].u.addr.unk_10 = 0;
    g_MenuPanelTasks[1].handler       = 2;
    g_MenuPanelTasks[1].mode          = 3;
    g_MenuPanelTasks[1].state         = 2;
    g_MenuPanelTasks[1].active        = 1;
    g_MenuPanelTasks[1].unk_0A        = 0;
    g_MenuPanelTasks[1].flags         = 1;
    g_MenuPanelTasks[2].handler       = 2;
    g_MenuPanelTasks[2].mode          = 4;
    g_MenuPanelTasks[2].state         = 2;
    g_MenuPanelTasks[2].active        = 1;
    g_MenuPanelTasks[2].pos.y         = -0x14;
    g_MenuPanelTasks[2].u.addr.unk_10 = 0;
    g_MenuPanelTasks[3].handler       = 2;
    g_MenuPanelTasks[3].mode          = 4;
    g_MenuPanelTasks[3].state         = 3;
    g_MenuPanelTasks[3].active        = 1;
    g_MenuPanelTasks[3].pos.y         = -0x14;
    g_MenuPanelTasks[3].u.addr.unk_10 = 0;
    g_MenuPanelTasks[3].u.addr.unk_12 = 0x80;
    g_MenuPanelTasks[4].handler       = 2;
    g_MenuPanelTasks[4].mode          = 1;
    g_MenuPanelTasks[4].active        = 0;
}
#else
INCLUDE_ASM(func_801D1C90);
#endif

/* Applies the equipment menu's trial set to the record it edits. */
/* func_801D1E8C */
MATCH void Menu_ApplyEquipment(void) {
    u8* slots[EQUIP_SLOT_COUNT];
    u8  item;
    u8  slot;

    slots[EQUIP_SLOT_WEAPON]      = &g_Characters[MENU_BATE_CHARACTER_RECORD].equip.weapon;
    slots[EQUIP_SLOT_SHIELD]      = &g_Characters[MENU_BATE_CHARACTER_RECORD].equip.shield;
    slots[EQUIP_SLOT_HELMET]      = &g_Characters[MENU_BATE_CHARACTER_RECORD].equip.helmet;
    slots[EQUIP_SLOT_ARMOR]       = &g_Characters[MENU_BATE_CHARACTER_RECORD].equip.armor;
    slots[EQUIP_SLOT_ACCESSORY_1] = &g_Characters[MENU_BATE_CHARACTER_RECORD].equip.accessories[0];
    slots[EQUIP_SLOT_ACCESSORY_2] = &g_Characters[MENU_BATE_CHARACTER_RECORD].equip.accessories[1];

    for (slot = 0; slot < EQUIP_SLOT_COUNT; slot++) {
        item = D_801D8ED4.equipped_items[slot];
        if (item == 0) {
            continue;
        }
        if (item == *slots[slot]) {
            continue;
        }
        Item_Remove(D_801D875C[slot], item, 1, 0);
        Item_Add(D_801D875C[slot], *slots[slot], 1, 0);
        *slots[slot] = D_801D8ED4.equipped_items[slot];
    }
    Char_RebuildStats(&g_Characters[MENU_BATE_CHARACTER_RECORD]);
}

MATCH void func_801D1FA0(void) {
    u8 slot;

    slot = D_8014833D;
    if (Item_GetEquipability(D_80148338, slot) & 0x1) {
        D_80148511 = 0;
    } else {
        D_80148511 = 1;
    }
    D_801D8ED4.equipped_items[0]          = D_80144DF2;
    D_801D8ED4.equipped_items[1]          = D_80144DF3;
    D_801D8ED4.equipped_items[2]          = D_80144DF4;
    D_801D8ED4.equipped_items[3]          = D_80144DF5;
    D_801D8ED4.equipped_items[4]          = D_80144DF6;
    /* @bug The trial set stores both accessories to the first accessory slot, so the second keeps its old value. */
    D_801D8ED4.equipped_items[4]          = D_80144DF7;
    D_801D8ED4.equipped_items[D_8014835E] = slot;
}

MATCH void func_801D2070(void) {
    SYS_DISPATCH_BYTE(g_MenuBateStep3Funcs, D_80148651);
}

MATCH void func_801D20AC(void) {
    SYS_DISPATCH_BYTE(g_MenuBateStep3Sub0Funcs, D_80148652);
}

MATCH void func_801D20E8(void) {
    u8* count;

    UI_SetMode(UI_MODE_FAST_FADE_IN);
    count = &D_80148652;
    *count += 1;
}

MATCH void func_801D211C(void) {
    Menu_DrawClutStrip(D_80144953);
    func_801D2304(0x37, 0x37);
    if (g_UiWindowEffectBusy == 0) {
        func_801D259C();
        D_80148658 = 0;
        D_80148652 = 0;
        D_80148651 += 1;
    }
}

#ifdef NON_MATCHING
NON_MATCHING void func_801D2190(void) {
    s8*           selected;
    volatile s32* tally;
    s32           value;
    s32           maximum;

    Menu_DrawClutStrip(D_80144953);
    func_801D2304(55, 55);
    selected = &D_80148658;
    tally    = D_801D8F00;
    if (*selected < 6) {
        tally[*selected] += D_801D8778[*selected];
        value   = tally[*selected];
        maximum = D_801D8EE8[*selected];
        if ((u32)value < (u32)maximum && LOBU(g_InputPressed) == 0) {
            return;
        }
        tally[*selected] = maximum;
        *selected        = LOBU(*selected) + 1;
    } else if (LOBU(g_InputPressed) != 0) {
        UI_SetMode(UI_MODE_FAST_FADE_OUT);
        D_80148651++;
    }
}
#else
INCLUDE_ASM(func_801D2190);
#endif

MATCH void func_801D2298(void) {
    if (g_UiWindowEffectBusy == 0) {
        D_80148654 = 0;
        D_80148650 = 1;
        D_80148651 = 0;
        D_80148652 = 0;
        return;
    }
    Menu_DrawClutStrip(D_80144953);
    func_801D2304(0x37, 0x37);
}

#ifdef NON_MATCHING
/* The formats and the second counter run the window's rows; the row counters are read through a
 * volatile view, the address retail materializes before indexing it. */

void Menu_DrawPanelFrame(s16 x, s16 y, s32 width, s32 height);
void func_801D26E0(s16 x, s16 y);

NON_MATCHING void func_801D2304(s32 x, s32 y) {
    u16 left;
    u16 top;
    u8  i;

    left = x;
    top  = y;
    UI_DrawWindow((u16)(x - 4), (u16)(y - 8), 0xDC, 0x8C, 0xF0, g_WindowStyle);
    Menu_DrawPanelFrame((s16)(x - 4), (s16)(y - 8), 26, 16);
    UI_DrawText((s16)(x + 0x51), (s16)(y + 6), 0, 0xFF, Message_GetText(0xE7));
    i = 0;
    do {
        UI_DrawText((s16)(left + 6), (s16)(top + (i << 5) + 0x1E), 0, 0xFF, Message_GetText(0xE8 + i));
        UI_DrawText((s16)(left + 0x94), (s16)(top + (i << 5) + 0x1E), 0, 0xFF, Message_GetText(0xEB + i));
        sprintf(g_UiFormatBuffer, D_801D0C18, ((volatile s32*)D_801D8F00)[i]);
        UI_DrawAsciiString((s16)(left + 0x1E), (s16)(top + (i << 5) + 0x2B), 0, g_UiFormatBuffer);
        sprintf(g_UiFormatBuffer, D_801D0C1C, ((volatile s32*)D_801D8F0C)[i]);
        UI_DrawAsciiString((s16)(left + 0x94), (s16)(top + (i << 5) + 0x2B), 0, g_UiFormatBuffer);
        func_801D26E0((s16)(left + 0x94), (s16)(top + (i << 5) + 0x2B));
        i++;
    } while (i < 3);
    UI_DrawText((s16)(left + 0x5A), (s16)(top + 0x2B), 0, 0xFF, Message_GetText(0xF0));
    UI_DrawText((s16)(left + 0x5A), (s16)(top + 0x4B), 0, 0xFF, Message_GetText(0xEF));
    UI_DrawText((s16)(left + 0x5A), (s16)(top + 0x6B), 0, 0xFF, Message_GetText(0xEF));
}
#else
INCLUDE_ASM(func_801D2304);
#endif

MATCH void func_801D259C(void) {
    Character* character;
    u8         i;

    i = 0;
    do {
        D_801D8F00[i] = 0;
        i++;
    } while (i < 6);
    D_801D8EE8[0] = D_801FE4EF;
    D_801D8EE8[1] = D_801FE4E8;
    D_801D8EE8[2] = D_801FE4F0;
    D_801D8EE8[3] = D_801FE4EF;
    D_801D8EE8[4] = D_801FE4E8 / 20;
    if (D_801FE4F0 < 50) {
        D_801D8EE8[5] = 2;
    } else if (D_801FE4F0 - 50 < 30) {
        D_801D8EE8[5] = 4;
    } else if (D_801FE4F0 >= 80) {
        D_801D8EE8[5] = 6;
    }
    character = &g_Characters[MENU_BATE_CHARACTER_RECORD];
    Char_AddStat(&character->base.defense, (s16)D_801D8EE8[3]);
    Char_AddStat(&character->stats.defense, (s16)D_801D8EE8[3]);
    Char_AddCappedStat(&character->base.max_hp, (u16)D_801D8EE8[4]);
    Char_AddCappedStat(&character->stats.max_hp, (u16)D_801D8EE8[4]);
    Char_AddStat(&character->base.power, (s16)D_801D8EE8[5]);
    Char_AddStat(&character->stats.power, (s16)D_801D8EE8[5]);
}

MATCH void func_801D26E0(s16 x, s16 y) {
    LINE_F2* line;

    line = (LINE_F2*)g_GfxPrimCursor;
    SetLineF2(line);
    SetSemiTrans(line, 1);
    setXY2(line, x + 5, y, x + 5, y + 0xA);
    line->b0 = 0x80;
    line->g0 = 0x80;
    line->r0 = 0x80;
    GFX_AddPrim(GFX_LAYER_UI, sizeof(LINE_F2));
    line = (LINE_F2*)g_GfxPrimCursor;
    SetLineF2(line);
    SetSemiTrans(line, 1);
    setXY2(line, x, y + 5, x + 0xA, y + 5);
    line->b0 = 0x80;
    line->g0 = 0x80;
    line->r0 = 0x80;
    GFX_AddPrim(GFX_LAYER_UI, sizeof(LINE_F2));
}

#ifdef NON_MATCHING
NON_MATCHING void Menu_DrawCharacterWindow(s32 px, s32 py, u8 character_index, s32 shaded, s32 unused) {
    Character* records;
    Character* stats;
    u32        clut;
    u32        text_clut;
    s32        text_y;
    s32        x;
    s32        y;

    clut = (u8)shaded ? 7 : 0;
    func_801AE3F0(px + 3, py + 3, MENU_CHARACTER_WINDOW_WIDTH, MENU_CHARACTER_WINDOW_HEIGHT, (u8)shaded, CHARACTER_BLOCK->window_style);
    x = px;
    y = py;
    /* FAKE: the order lock keeps the x and y copies below the window call. */
    FAKE_ORDER_LOCK_BEGIN
        records = (Character*)CHARACTER_BLOCK->records;
        stats   = &records[character_index];
        Menu_DrawCharacterPortrait(px + 0x56, py + 2, stats->character_id, (u8)shaded == 0 ? (stats->status >> 6) & 2 : 1);
        text_clut = clut & BYTE_MASK;
        UI_DrawText(x + 20, y + 3, text_clut, 5, stats);
    FAKE_ORDER_LOCK_END;
    TEXT_Format(g_UiFormatBuffer, g_MenuStatFormat, stats->level);
    text_y = (s16)(y + 0x17);
    UI_DrawGlyphString(x + 22, text_y, text_clut, g_UiFormatBuffer);
    if ((LOWU(stats->status) & (STATUS_CONFUSED | STATUS_POISONED)) == (STATUS_CONFUSED | STATUS_POISONED)) {
        if (g_FrameCount & 0x20) {
            UI_DrawTextString(x + 46, text_y, text_clut != 0 ? text_clut : 1, 0x10, D_801D8B18);
        } else {
            UI_DrawTextString(x + 46, text_y, text_clut != 0 ? text_clut : 1, 0x10, D_801D8B20);
        }
    } else if (stats->status & STATUS_POISONED) {
        UI_DrawTextString(x + 46, text_y, text_clut != 0 ? text_clut : 1, 0x10, D_801D8B18);
    } else if (stats->status & STATUS_CONFUSED) {
        UI_DrawTextString(x + 46, text_y, text_clut != 0 ? text_clut : 1, 0x10, D_801D8B20);
    }
    if (stats->hp < (u32)(stats->stats.max_hp >> 2)) {
        stats->status |= STATUS_LOW_HP;
    } else {
        stats->status &= ~STATUS_LOW_HP;
    }
    if ((u8)shaded == 0) {
        if (stats->status & STATUS_LOW_HP) {
            clut = 4;
        }
        if (stats->hp < 2) {
            clut = 2;
        }
    } else {
        clut = 7;
    }
    TEXT_Format(g_UiFormatBuffer, D_801D0C24, stats->hp);
    UI_DrawGlyphString(x + 22, y + 31, clut, g_UiFormatBuffer);
    if ((u8)shaded == 0) {
        clut = (stats->fatigue != 0) * 4;
    } else {
        clut = 7;
    }
    TEXT_Format(g_UiFormatBuffer, D_801D0C2C, stats->stats.max_hp);
    UI_DrawGlyphString(x + 22, y + 31, clut, g_UiFormatBuffer);
    clut = (u8)shaded ? 7 : 0;
    if ((u8)shaded == 0) {
        if (stats->ap < (u32)(stats->stats.max_ap >> 2)) {
            clut = 4;
        }
        if (stats->ap == 0) {
            clut = 2;
        }
    } else {
        clut = 7;
    }
    TEXT_Format(g_UiFormatBuffer, D_801D0C24, stats->ap);
    UI_DrawGlyphString(x + 22, y + 39, clut, g_UiFormatBuffer);
    clut = (u8)shaded ? 7 : 0;
    TEXT_Format(g_UiFormatBuffer, D_801D0C2C, stats->stats.max_ap);
    UI_DrawGlyphString(x + 22, y + 39, clut, g_UiFormatBuffer);
    func_801AF390(x, y, D_801D8780, 0);
    Menu_DrawExperienceLine(x + 0x14, y + 0x12, character_index, stats->level, stats->exp);
    /* FAKE: dead stores keep px and py the CSE heads of their x and y copies. */
    px = 0;
    py = 0;
}
#else
INCLUDE_ASM(Menu_DrawCharacterWindow);
#endif

#include "overlays/menu/Menu_DrawStatPanel.h"

#include "overlays/menu/Shop_DrawEquipment.h"

#include "overlays/menu/Menu_DrawExperienceWindow.h"

MATCH void func_801D31B0(s16 x, s16 y, u8 index, u8 flag){MENU_DRAW_EXPERIENCE_WINDOW(D_801D8B48, D_801D8B4C, D_801D8984)}
#include "overlays/menu/Menu_DrawCursorFrame.h"

#include "shared/Menu_DrawPortrait.h"

#include "shared/Menu_DrawCharacterPortrait.h"

#include "overlays/menu/Menu_DrawTintedLine.h"

#include "overlays/menu/Menu_DrawItemRow.h"

#include "overlays/menu/Menu_DrawEquipment.h"

#include "overlays/menu/Menu_DrawFormationPreview.h"

#include "overlays/menu/Menu_DrawIcon.h"

/* func_801D4678 */
MATCH void Menu_DrawPanelIcon(u16 x, u16 y, s32 u, s32 v, u16 clut, u8 color) {
    MenuDrawPanelIcon(x, y, u, v, clut, color);
}

#include "overlays/menu/Menu_DrawExperienceLine.h"

#include "overlays/menu/Menu_DrawZennyWindow.h"

#include "overlays/menu/Menu_DrawPlayTimeWindow.h"

#include "overlays/menu/Menu_ChooseYesNo.h"

#include "overlays/menu/Menu_DrawCommandRow.h"

#include "overlays/menu/Item_GetPrice.h"

#include "overlays/menu/Char_GetExpForLevel.h"

#include "overlays/menu/Char_GetExpProgress.h"

INCLUDE_ASM(Menu_DrawHeaderBar);

#include "overlays/menu/Menu_DrawEquipCompareWindow.h"

#include "overlays/menu/Menu_DrawRowIcons.h"

#include "overlays/menu/Menu_DrawEquipStatWindow.h"

const char g_MenuInventoryCountFormat[8] = "%3d/%3d";
const u8   D_801D0D64[4]                 = {0, 0, 0, 0};

#include "overlays/menu/Menu_DrawClutStrip.h"

#include "overlays/menu/Menu_DrawFilledPanel.h"

#include "overlays/menu/Menu_DrawWindowFrame.h"

#include "overlays/menu/Menu_DrawInventoryWindow.h"

/* func_801D73B4 */
#include "overlays/menu/Menu_DrawAbilityList.h"

#include "overlays/menu/Menu_DrawPanelFrame.h"

/* func_801D7AD0 */
#include "overlays/menu/Menu_DrawEquipChoiceWindow.h"

#include "overlays/menu/SAVE_DrawSlotRow.h"

#include "overlays/menu/SAVE_DrawPortTabs.h"
