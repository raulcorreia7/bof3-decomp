#ifndef MENU_PANEL_H
#define MENU_PANEL_H

#include "common/vector.h"
#include "gfx/prim.h"
#include "psx/psyq.h"
#include "types.h"

/* The menu system: a screen is a set of panel task records animated into place,
 * with a choice list (group, page and cursor) driving the menu screens. The
 * shop and start-menu overlays share the choice-panel view and the animation
 * macros below; the party, inventory and save headers own the data those
 * screens read. */

/* retail addresses */
#define MENU_PANEL_COUNT       22

/* Shared panel-animation quantities. */
#define MENU_PANEL_STEP_X      32
#define MENU_PANEL_STEP_Y      16
#define MENU_PANEL_FLOOR_X     (-170)
#define MENU_PANEL_HIDDEN_X    (-150)
#define MENU_PANEL_HIDDEN_Y    (-20)

#define MENU_CHOICE_PANEL_SIZE 0x14
#define MENU_PANEL_TASK_SIZE   0x24

/* One panel animation body: the panel moves along the member in fixed pixel
 * steps toward a bound and stops there, clearing its state. An advance tests
 * above the limit after the overshooting step; a retreat tests below the bound,
 * so the two directions are two bodies. Kept as macros: as inlines 38 of 67
 * members diverge (the limit moves to $a0 and a label is added).
 *
 * Usage:
 *   MATCH void UI_PanelSlideOutOption_800B2218(void) { MENU_ADVANCE_PANEL(pos.x, MENU_PANEL_STEP_X, 320); }
 *   MATCH void func_801E3CB8(void) { MENU_RETREAT_PANEL(pos.x, MENU_PANEL_STEP_X, MENU_PANEL_FLOOR_X); }
 */
#define MENU_ADVANCE_PANEL(member, step, limit) \
    do {                                        \
        MenuPanelTask* panel;                   \
        s16            next;                    \
                                                \
        panel         = g_UiPanelCurrent;       \
        next          = panel->member + (step); \
        panel->member = next;                   \
        if (next >= (limit) + 1) {              \
            panel->member = (limit);            \
            panel->state  = 0;                  \
        }                                       \
    } while (0)

#define MENU_RETREAT_PANEL(member, step, limit) \
    do {                                        \
        MenuPanelTask* panel;                   \
        s16            next;                    \
                                                \
        panel         = g_UiPanelCurrent;       \
        next          = panel->member - (step); \
        panel->member = next;                   \
        if (next < (limit)) {                   \
            next          = (limit);            \
            panel->member = next;               \
            panel->state  = 0;                  \
        }                                       \
    } while (0)

/* The choice-list view of a panel slot. The shop panel (slot 7 of
 * g_UiPanelTasks, 0x8014842C) and the start-menu panel (slot 13,
 * 0x80148504) walk the same group tables with this record, so the field names
 * and the layout are one record and the overlays include this view instead of
 * redeclaring it.
 *
 * Writers and readers: `emi/etc/shop/00@0x801D2828` and `@0x801D334C` build the shop
 * panel (group 0, the group's first entry, the cursor, the drawn cursor 0xFF);
 * `emi/etc/start/08@0x801D3D00` reads the same four fields of the start panel
 * through g_ItemCategoryIds and g_ItemCategoryCounts and clears the drawn cursor with 0xFF.
 * The x and y are the panel's screen position: the draw calls take x + 7 and
 * y + 7, and the panel animation slides x (MENU_ADVANCE_PANEL). */
typedef struct MenuChoicePanel {
    u8    active; /* 0x00: set while the panel is armed */
    u8    pad_01[0x03];
    Pos2u pos;          /* 0x04 */
    u8    type;         /* 0x08: the panel's type, the first argument of Item_PassesTest */
    u8    pad_09;       /* 0x09 */
    u8    group;        /* 0x0A: the group the cursor walks */
    u8    group_first;  /* 0x0B: the group's first entry, the page start */
    u8    group_cursor; /* 0x0C: the cursor's entry */
    u8    drawn_cursor; /* 0x0D: the drawn cursor, 0xFF when none */
    u8    pad_0E[0x02];
    u16   unk_10;        /* 0x10: 0x31 or 0x32 after a cursor move; role unknown */
    s16   confirm_timer; /* 0x12: non-zero closes the confirm step */
} MenuChoicePanel;

ASSERT_OFFSET(MenuChoicePanel, pos, 0x04);
ASSERT_OFFSET(MenuChoicePanel, group, 0x0A);
ASSERT_OFFSET(MenuChoicePanel, group_first, 0x0B);
ASSERT_OFFSET(MenuChoicePanel, group_cursor, 0x0C);
ASSERT_OFFSET(MenuChoicePanel, drawn_cursor, 0x0D);
ASSERT_OFFSET(MenuChoicePanel, confirm_timer, 0x12);
ASSERT_SIZE(MenuChoicePanel, MENU_CHOICE_PANEL_SIZE);

/* What a list panel lists: the shop's item list reads a price discount (and
 * dims the whole list when it is set), the ability lists read whose abilities
 * and which type (Party_GetAbilities' arguments). */
typedef union MenuListParams {
    struct {
        u8 dimmed;        /* non-zero draws every row greyed out */
        u8 price_percent; /* Shop_ApplyPercent's percent */
    } items;

    struct {
        u8 member; /* the party formation index */
        u8 type;   /* AbilityType: also the index of the list name */
    } abilities;
} MenuListParams;

ASSERT_SIZE(MenuListParams, 2);

/* The widest menu label or title, in glyphs. */
#define MENU_LABEL_LENGTH 16

/* The frame sprites of a panel border: the top edge and its corners, the side edges, and the flat bottom edge that closes the short panels. */
enum {
    MENU_FRAME_SPRITE_TOP_LEFT          = 0x28,
    MENU_FRAME_SPRITE_TOP               = 0x29,
    MENU_FRAME_SPRITE_TOP_RIGHT         = 0x2A,
    MENU_FRAME_SPRITE_LEFT              = 0x2B,
    MENU_FRAME_SPRITE_RIGHT             = 0x2C,
    MENU_FRAME_SPRITE_FLAT_BOTTOM_LEFT  = 0x3A,
    MENU_FRAME_SPRITE_FLAT_BOTTOM       = 0x3B,
    MENU_FRAME_SPRITE_FLAT_BOTTOM_RIGHT = 0x3C,
};

/* MenuListPanel.flags: two cursor-tab bits, and a frame countdown in the high nibble that the drawer steps down once per draw. */
#define MENU_LIST_FLAG_TAB_1 0x01
#define MENU_LIST_FLAG_TAB_2 0x02
#define MENU_LIST_FRAME_MASK 0xF0
#define MENU_LIST_FRAME_STEP 0x10

/* The list panel record, handed to the panel drawers as a pointer: the
 * shop's ability and item lists (Menu_DrawAbilityList, Shop_DrawItems) and the
 * ability list of the bate overlay read the same cells. The record's extent
 * is unknown; 0x24, the names pointer, is the last known cell. */
typedef struct MenuListPanel {
    u8             pad_00[4];
    Pos2u          pos;      /* 0x04 */
    u8             type;     /* 0x08 the ability list passes it to func_801AF5B0: 1 outside battle, 2 in battle */
    u8             flags;    /* 0x09 bit 0 and bit 1 pick the cursor; the high nibble counts the frame down */
    MenuListParams source;   /* 0x0A */
    u8             unk_0C;   /* 0x0C a row the drawer draws an icon for */
    u8             selected; /* 0x0D the selected row; the drawer shades it 2 */
    u8             pad_0E[2];
    s16            unk_10; /* 0x10 tested against zero for the extra frame marks */
    u8             pad_12[0xE];
    u8*            names; /* 0x20 the name table: a row count, then 2-byte rows */
} MenuListPanel;

ASSERT_SIZE(MenuListPanel, 0x24);

/* Views of MenuPanelTask cells 0x10..0x1F. */
typedef struct MenuPanelGrow {
    u16 w;            /* 0x10 current width, 12.4 fixed point */
    u16 h;            /* 0x12 current height, 12.4 fixed point */
    u16 width_delta;  /* 0x14 width added per frame */
    u16 height_delta; /* 0x16 height added per frame */
    u16 target_x;     /* 0x18 the x the panel settles at */
    u16 target_y;     /* 0x1A the y the panel settles at */
} MenuPanelGrow;

typedef struct MenuPanelMessage {
    u16 id; /* 0x10 the message the bar draws, 0 for none */
    u16 w;  /* 0x12 the bar's width */
} MenuPanelMessage;

typedef struct MenuPanelList {
    u16 tabs;   /* 0x10 the tab marks; the high nibble counts the frame down */
    u16 scroll; /* 0x12 the scroll position, row in the high nibbles */
} MenuPanelList;

typedef struct MenuPanelIcons {
    u16 grow; /* 0x10 pixels the selected icon is grown by, up to 3 */
} MenuPanelIcons;

typedef struct MenuPanelBattle {
    u16 cursor;   /* 0x10 */
    u16 row_base; /* 0x12 the list's first row */
    u16 hp;       /* 0x14 */
    u16 ap;       /* 0x16 */
    u16 pad_18[2];
    u16 max_hp; /* 0x1C */
    u16 max_ap; /* 0x1E */
} MenuPanelBattle;

/* Cells read by address where the bytes change from use to use. */
typedef struct MenuPanelRaw {
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
} MenuPanelRaw;

/* Where a message panel opens: x and y in screen units, 16 per panel position step. Bank 0 is for the wide panels
 * (UI_MessageOpenPanel gives them width 0xC8), bank 1 for the narrow ones (width 0x78, panel flags & 2). */
#define UI_PANEL_ORIGIN_BANKS 2
#define UI_PANEL_ORIGIN_COUNT 8

typedef struct UIPanelOrigin {
    u8 x;
    u8 y;
} UIPanelOrigin;

ASSERT_SIZE(UIPanelOrigin, 2);

/* One of the 22 panel task records: the panel's position, state, layer and
 * item-table base. The battle overlays read the first 0x0C bytes through
 * BattlePanelTask (battle/records.h). */
typedef struct MenuPanelTask {
    u8    active; /* set to open the panel, cleared to close it */
    u8    panel;  /* UI_PanelUpdateTasks calls g_UiPanels.handlers[panel] */
    u8    mode;   /* the panel's own mode: g_UiPanelModes[mode], the slide target choice, and the battle mode_00 */
    u8    state;
    /* x and y are screen positions. Most readers load them with lhu; the slide
     * code compares them as s16 and stores signed constants through LOH, so the
     * field stays u16 and each slide keeps its s16 view. */
    Pos2u pos;
    u8    unk_08;
    u8    unk_09;
    u8    unk_0A; /* x 16 is the horizontal half-centre */
    u8    unk_0B; /* x 16 is the vertical half-centre */
    u8    unk_0C;
    u8    flags; /* bit 0 tested before the box draw; battle reads it as its cursor */
    u8    unk_0E;
    u8    layer; /* panel layer, tested against the dispatch mode */

    /* The cells 0x10..0x1F mean different things to each panel mode; each user reads the view that names what the mode keeps there. */
    union {
        MenuPanelGrow    grow;    /* the window-grow animation (slus) */
        MenuPanelMessage message; /* the header bar that shows a message */
        MenuPanelList    list;    /* the list windows: tab marks and scroll */
        MenuPanelIcons   icons;   /* the camp menu icon row */
        MenuPanelBattle  battle;  /* the battle panels: cursor, first row and the HP/AP bars */
        MenuPanelRaw     addr;    /* cells whose purpose is not read yet, by address */
    } u;

    s32 item_table; /* 0x20: the panel's item-table base; the retail loads it with a word */
} MenuPanelTask;

ASSERT_OFFSET(MenuPanelTask, pos, 0x04);
ASSERT_OFFSET(MenuPanelTask, unk_08, 0x08);
ASSERT_OFFSET(MenuPanelTask, u, 0x10);
ASSERT_OFFSET(MenuPanelTask, item_table, 0x20);
ASSERT_SIZE(MenuPanelTask, MENU_PANEL_TASK_SIZE);

/* The shop's choice panel is slot 7 of g_UiPanelTasks (0x8014842C), built by
 * `emi/etc/shop/00@0x801D2828` and `@0x801D334C`. Its retail symbol is
 * declared in menu/gameui.h, because the same address holds a different byte
 * in the battle overlays (equal addresses in different targets are
 * unrelated); the shop overlay casts it to this record. */

/* First slot of a group of per-member panels in g_UiPanelTasks. */
#define MENU_PANEL_BATTLER_FIRST    0xD /* battle: slot 0xD plus the battler holds the battler's panel */
#define MENU_PANEL_CARD_FIRST       0xC /* start menu: one card per party member; its state follows the cursor */
#define MENU_PANEL_MEMBER_ROW_FIRST 0xD /* start menu: the second per-member group, set to state 9 on cancel */

/* D_80148330 */
extern MenuPanelTask  g_UiPanelTasks[MENU_PANEL_COUNT];
extern s16            D_801485FA;
/* Panel-task block bytes 0x80148648..0x80148652; read by etc/game/00 and etc/shop/00. */
/* D_80148648 */
extern MenuPanelTask* g_UiPanelCurrent;
extern s8             D_8014865C;
extern u8             D_80148699;

/* Draw the panel's icon through the PsyQ 8x8 sprite primitive. The panel writes
 * the sprite fields itself at the primitive cursor; SetSprt8 only tags it. */
static inline void MenuDrawPanelIcon(s16 x, s16 y, s32 u, s32 v, u16 clut, u8 color) {
    SPRT_8* icon;

    icon = (SPRT_8*)g_GfxPrimCursor;
    SetSprt8(icon);
    setXY0(icon, x, y);
    setUV0(icon, (u8)(u * 8), (u8)(v * 8));
    icon->clut = clut;
    icon->b0   = color;
    icon->g0   = color;
    icon->r0   = color;
    SetSemiTrans(icon, 0);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(SPRT_8));
}

#endif
