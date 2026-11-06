#include "bate_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801D1264);

MATCH void func_801D153C(void) {
    SYS_DISPATCH_BYTE(D_801D8720, D_80148652);
}

MATCH void func_801D1578(void) {
    u8* timer = &D_80148654;
    u8  count;

    Menu_DrawClutStrip(D_80144953);
    count  = *timer - 1;
    *timer = count;
    if (count == 0) {
        UI_SetMode(2);
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

INCLUDE_ASM(func_801D1AB8);

INCLUDE_ASM(func_801D1C90);

INCLUDE_ASM(func_801D1E8C);

MATCH void func_801D1FA0(void) {
    u8 slot;

    slot = D_8014833D;
    if (Item_GetEquipability(D_80148338, slot) & 1) {
        D_80148511 = 0;
    } else {
        D_80148511 = 1;
    }
    D_801D8EE0[0]          = D_80144DF2;
    D_801D8EE0[1]          = D_80144DF3;
    D_801D8EE0[2]          = D_80144DF4;
    D_801D8EE0[3]          = D_80144DF5;
    D_801D8EE0[4]          = D_80144DF6;
    D_801D8EE0[4]          = D_80144DF7;
    D_801D8EE0[D_8014835E] = slot;
}

MATCH void func_801D2070(void) {
    SYS_DISPATCH_BYTE(D_801D8764, D_80148651);
}

MATCH void func_801D20AC(void) {
    SYS_DISPATCH_BYTE(D_801D8770, D_80148652);
}

MATCH void func_801D20E8(void) {
    u8* count;

    UI_SetMode(3);
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

INCLUDE_ASM(func_801D2190);

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

INCLUDE_ASM(func_801D2304);

INCLUDE_ASM(func_801D259C);

INCLUDE_ASM(func_801D26E0);

/* blocker: register homes (py in s2, shaded byte in s3). */
INCLUDE_ASM(Menu_DrawCharacterWindow);

#include "overlays/menu/Menu_DrawStatPanel.h"

#include "overlays/menu/Shop_DrawEquipment.h"

INCLUDE_ASM(func_801D31B0);

#include "overlays/menu/Menu_DrawCursorFrame.h"

#include "shared/Menu_DrawPortrait.h"

#include "shared/Menu_DrawCharacterPortrait.h"

#include "overlays/menu/Menu_DrawTintedLine.h"

#include "overlays/menu/Menu_DrawItemRow.h"

#include "overlays/menu/Menu_DrawEquipment.h"

INCLUDE_ASM(func_801D3E18);

#include "overlays/menu/Menu_DrawIcon.h"

MATCH void func_801D4678(u16 x, u16 y, s32 u, s32 v, u16 clut, u8 color) {
    MenuDrawPanelIcon(x, y, u, v, clut, color);
}

#include "overlays/menu/Menu_DrawExperienceLine.h"

#include "overlays/menu/Menu_DrawZennyWindow.h"

#include "overlays/menu/Menu_DrawPlayTimeWindow.h"

#include "overlays/menu/Menu_ToggleOption.h"

#include "overlays/menu/Menu_DrawCommandRow.h"

#include "overlays/menu/Item_GetPrice.h"

#include "overlays/menu/Char_GetExpForLevel.h"

#include "overlays/menu/Char_GetExpProgress.h"

/* First difference: the stack frame, 0x70 bytes against 0x78. */
INCLUDE_ASM(Menu_DrawHeaderBar);

INCLUDE_ASM(func_801D5634);

#include "overlays/menu/Menu_DrawRowIcons.h"

/* blocker: frame 0x58 against 0x50 and save order. */
INCLUDE_ASM(Menu_DrawEquipStatWindow);

#include "overlays/menu/Menu_DrawClutStrip.h"

#include "overlays/menu/Menu_DrawFilledPanel.h"

/* blocker: per-band draw-mode setup; first diff: stack frame, 0x88 bytes against 0x80. */
INCLUDE_ASM(Menu_DrawWindowFrame);

/* blocker: per-row (unk_12 >> 4) == 15 test; first diff: +0x138 lhu v1,18(s1) (template andi v1,s0,0xff). */
INCLUDE_ASM(func_801D6C54);

MATCH void func_801D73B4(BateAbilityPanel* panel) {
    Ability* ability;
    u8*      list;
    s32      level;
    s32      count;
    s32      locked;
    u8       shade;
    s32      x;
    u16      y;
    u8       flags;
    u8       n;

    UI_DrawWindow((panel->x + 3) & HALF_MASK, (panel->y + 3) & HALF_MASK, 154, 160, 0, CHARACTER_BLOCK->window_style);
    n    = 0;
    list = Party_GetAbilities(panel->unk_0A, panel->unk_0B, 0);
    y    = panel->y;
    do {
        if (*list != 0) {
            locked = (u8)func_801AF5B0(panel->unk_08, D_80148656, *list) == 0;
            shade  = locked ? 7 : 0;
            if (n == panel->selected) {
                shade = 2;
            }
            level   = Char_GetAbilityElement(*list);
            ability = (Ability*)&g_Abilities[*list];
            count   = Char_GetAbilityCost(g_CharSlot[D_80144F5A[(s8)D_80148656]], *list, 0);
            if (n == panel->selected || n == panel->unk_0C) {
                if (shade != 7) {
                    func_801AF930((s16)(panel->x + 7), (s16)(y + 0x1A), 7, level, (u8*)ability, count, 1);
                }
                func_801AF930((s16)(panel->x + 7), (s16)(y + 0x18), shade, level, (u8*)ability, count, locked);
            } else {
                func_801AF930((s16)(panel->x + 7), (s16)(y + 0x1A), shade, level, (u8*)ability, count, locked);
            }
        }
        n++;
        y += 0xD;
        list++;
    } while (n < 10);
    x = panel->x + 0x4E;
    UI_DrawText((x - strlen(D_801D8E80[panel->unk_0B]) * 4), (panel->y + 7), 0, 0x10, D_801D8E80[panel->unk_0B]);
    UI_DrawSpriteRun(panel->x, panel->y, (panel->flags & 2) ? D_801D8954 : D_801D893C, 1);
    UI_DrawSpriteRun(panel->x, panel->y, (panel->flags & 1) ? D_801D8978 : D_801D896C, 1);
    flags = panel->flags;
    if (!(flags & 0xF0)) {
        panel->flags = 0;
    } else {
        panel->flags = flags - 0x10;
    }
    for (n = 0; n < 10; n++) {
        UI_DrawSprite(panel->x + (n + 5) * 8, panel->y, 1, 1);
    }
    for (n = 0; n < 17; n++) {
        UI_DrawSprite(panel->x, panel->y + (n + 3) * 8, 4, 1);
    }
    UI_DrawSprite(panel->x + 144, panel->y + 24, 0x20, 1);
    for (n = 0; n < 15; n++) {
        UI_DrawSprite(panel->x + 144, panel->y + (n + 4) * 8, 0x21, 1);
    }
    UI_DrawSprite(panel->x, panel->y + 160, 5, 1);
    UI_DrawSprite(panel->x + 144, panel->y + 152, 0x22, 1);
    if (panel->unk_10 != 0) {
        UI_DrawSprite(panel->x + 8, panel->y, 0x32, 1);
        UI_DrawSprite(panel->x + 144, panel->y, 0x34, 1);
    }
    for (n = 0; n < 17; n++) {
        UI_DrawSprite(panel->x + (n + 1) * 8, panel->y + 160, 6, 1);
    }
}

#include "overlays/menu/Menu_DrawPanelFrame.h"

INCLUDE_ASM(func_801D7AD0);

MATCH void func_801D8208(u8 index, s32 left, s32 top, MenuListRow* row) {
    s16 x;
    s16 y;
    s16 label_x;
    u8  i;
    u8  icon;

    x = left;
    y = top;
    UI_DrawWindow(left + 8, y, 200, 48, 0, D_80144952);
    if (row != NULL) {
        if (GetGraphType() != 1) {
            GetGraphType();
        }
        GFX_AddDrawMode(0xF);
        func_801D4678((left + 9), (top + 5), (u8)(index + 3), 0x1E, GetClut(16, 480), 128);
        for (i = 0; i < BATTLE_PARTY_SLOT_COUNT; i++) {
            icon = *(row->unk_00 + i + 5);
            if (icon != GAME_NONE) {
                Menu_DrawPortrait((u16)(left + 0x56 + i * 0x29), (u16)(y + 2), icon, 0);
            }
        }
        UI_DrawText((x + 21), (y + 3), 0, 5, (u8*)row);
        sprintf((char*)g_UiFormatBuffer, &D_801D0D80, row->unk_00[8]);
        UI_DrawGlyphString((x + 31), (y + 24), 0, g_UiFormatBuffer);
        sprintf((char*)g_UiFormatBuffer, &D_801D0D84, row->unk_00[0xC], row->unk_00[0xD]);
        label_x = x + 0x27;
        UI_DrawGlyphString(label_x, (y + 37), 0, g_UiFormatBuffer);
        UI_DrawGlyphString(label_x, (y + 36), 0, (u8*)&D_801D0D90);
        UI_DrawGlyphString(label_x, (y + 39), 0, (u8*)&D_801D0D90);
        Menu_DrawExperienceLine((x + 0x14), (y + 0x12), 0, row->unk_00[8], ((MenuListRowWords*)row)->unk_10);
    }
    UI_DrawSpriteRun(x, y, D_801D8A3C, row->unk_00[0x14] && row ? 2 : 0);
    if (row != NULL && row->unk_00[0x14] != 0) {
        UI_DrawSprite((x + 50), (y + 22), 0x3D, 0);
    }
}

MATCH void func_801D8508(s16 x, s16 y, u32 flags, u8 row, u8 variant) {
    s16 left;
    s16 right;
    s16 text_y;
    u16 row_offset;
    u8  color;
    u32 shade;
    u8* texture;

    Menu_DrawFilledPanel(x, y, 7, 4);
    func_801644D8(20, (u16)(x + 7), (u16)(y + 5), 16, 16, 128);
    shade = 0x1C;
    if (variant == 0) {
        shade = 0x1B;
    }
    texture = Resource_GetText(shade);
    left    = (x + 6);
    UI_DrawText((x + 42), (y + 7), 0, 0xFF, texture);

    color = (flags & 1) ? 0 : 7;
    UI_DrawText(left, (y + 25), color, 0xFF, Resource_GetText(0x85));
    right  = (x + 94);
    text_y = (y + 25);
    UI_DrawAsciiString(right, text_y, color, &D_801D0D94);

    color = (flags & 2) ? 0 : 7;
    UI_DrawText(left, (y + 41), color, 0xFF, Resource_GetText(0x85));
    text_y = (y + 41);
    UI_DrawAsciiString(right, text_y, color, &D_801D0D98);

    row_offset = (row << 4);
    Menu_DrawCursorSprite((x + 8), (row_offset + y + 28), 0);
}
