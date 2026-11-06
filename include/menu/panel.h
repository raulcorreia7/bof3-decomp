#ifndef MENU_PANEL_H
#define MENU_PANEL_H

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

/* Shared panel-animation quantities. Steps and clamps are human quantities, so
 * they are decimal (handbook: addresses/masks/encodings hex, pixel steps/clamps
 * decimal). */
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
 *   MATCH void func_800B2218(void) { MENU_ADVANCE_PANEL(x, MENU_PANEL_STEP_X, 320); }
 *   MATCH void func_801E3CB8(void) { MENU_RETREAT_PANEL(x, MENU_PANEL_STEP_X, MENU_PANEL_FLOOR_X); }
 */
#define MENU_ADVANCE_PANEL(member, step, limit) \
    do {                                        \
        MenuPanelTask* panel;                   \
        s16            next;                    \
                                                \
        panel         = g_MenuCurrentPanel;     \
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
        panel         = g_MenuCurrentPanel;     \
        next          = panel->member - (step); \
        panel->member = next;                   \
        if (next < (limit)) {                   \
            next          = (limit);            \
            panel->member = next;               \
            panel->state  = 0;                  \
        }                                       \
    } while (0)

/* The choice-list view of a panel slot. The shop panel (slot 7 of
 * g_MenuPanelTasks, 0x8014842C) and the start-menu panel (slot 13,
 * 0x80148504) walk the same group tables with this record, so the field names
 * and the layout are one record and the overlays include this view instead of
 * redeclaring it.
 *
 * Evidence: `emi/etc/shop/00@0x801D2828` and `@0x801D334C` build the shop
 * panel (group 0, the group's first entry, the cursor, the drawn cursor 0xFF);
 * `emi/etc/start/08@0x801D3D00` reads the same four fields of the start panel
 * through D_801C893C and D_801C8950 and clears the drawn cursor with 0xFF.
 * The x and y are the panel's screen position: the draw calls take x + 7 and
 * y + 7, and the panel animation slides x (MENU_ADVANCE_PANEL). */
typedef struct MenuChoicePanel {
    u8  active; /* 0x00: set while the panel is armed */
    u8  pad_01[0x03];
    u16 x;            /* 0x04: the panel's screen x */
    u16 y;            /* 0x06: the panel's screen y */
    u8  kind;         /* 0x08: the panel's kind, the first argument of func_801AF494 */
    u8  pad_09;       /* 0x09 */
    u8  group;        /* 0x0A: the group the cursor walks */
    u8  group_first;  /* 0x0B: the group's first entry, the page start */
    u8  group_cursor; /* 0x0C: the cursor's entry */
    u8  drawn_cursor; /* 0x0D: the drawn cursor, 0xFF when none */
    u8  pad_0E[0x02];
    u16 unk_10;       /* 0x10: 0x31 or 0x32 after a cursor move; role unknown */
    s16 confirm_gate; /* 0x12: non-zero closes the confirm step */
} MenuChoicePanel;

ASSERT_SIZE(MenuChoicePanel, MENU_CHOICE_PANEL_SIZE);
ASSERT_OFFSET(MenuChoicePanel, x, 0x04);
ASSERT_OFFSET(MenuChoicePanel, y, 0x06);
ASSERT_OFFSET(MenuChoicePanel, group, 0x0A);
ASSERT_OFFSET(MenuChoicePanel, group_first, 0x0B);
ASSERT_OFFSET(MenuChoicePanel, group_cursor, 0x0C);
ASSERT_OFFSET(MenuChoicePanel, drawn_cursor, 0x0D);
ASSERT_OFFSET(MenuChoicePanel, confirm_gate, 0x12);

/* One of the 22 panel task records: the panel's position, state, layer and
 * item-table base. The battle overlays read the first 0x0C bytes through
 * BattlePanelTask (battle/records.h). */
typedef struct MenuPanelTask {
    u8  active; /* set to open the panel, cleared to close it */
    u8  unk_01;
    u8  unk_02;
    u8  state;
    /* x and y are screen positions. Most readers load them with lhu; the slide
     * code compares them as s16 and stores signed constants through LOH, so the
     * field stays u16 and each slide keeps its s16 view. */
    u16 x;
    u16 y;
    u8  unk_08;
    u8  unk_09;
    u8  unk_0A; /* x 16 is the horizontal half-centre */
    u8  unk_0B; /* x 16 is the vertical half-centre */
    u8  unk_0C;
    u8  flags; /* bit 0 tested before the box draw; battle reads it as its cursor */
    u8  unk_0E;
    u8  unk_0F; /* panel layer, tested against the dispatch mode */
    /* Mode-dependent pair. The slide panel uses 0x10/0x12 as remaining x/y and
     * 0x14/0x16 as the x/y step; the battle bar uses 0x14/0x16 as current HP/AP
     * and 0x12 as its row base, so the shared record keeps them unnamed. */
    u16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u16 unk_16;
    u16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
    s32 item_table; /* 0x20: the panel's item-table base; the retail loads it with a word */
} MenuPanelTask;

ASSERT_OFFSET(MenuPanelTask, y, 0x06);
ASSERT_OFFSET(MenuPanelTask, unk_08, 0x08);
ASSERT_OFFSET(MenuPanelTask, unk_10, 0x10);
ASSERT_OFFSET(MenuPanelTask, unk_1A, 0x1A);
ASSERT_OFFSET(MenuPanelTask, item_table, 0x20);
ASSERT_SIZE(MenuPanelTask, MENU_PANEL_TASK_SIZE);

/* The panel icon is the PsyQ SDK's 8x8 sprite primitive: the panel writes the
 * sprite fields itself at the primitive cursor 0x8014598C and `SetSprt8` only
 * tags it. The SDK record owns the layout (x0 at 0x08, y0 at 0x0A, u0 and v0
 * at 0x0C and 0x0D, the clut at 0x0E), so the menu uses that record instead of
 * a copy of it. */
typedef SPRT_8 MenuIconPrim;

/* The shop's choice panel is slot 7 of g_MenuPanelTasks (0x8014842C), built by
 * `emi/etc/shop/00@0x801D2828` and `@0x801D334C`. Its retail symbol is
 * declared in sys/gameui.h, because the same address holds a different byte
 * in the battle overlays (equal addresses in different targets are
 * unrelated); the shop overlay casts it to this record. */

/* D_80148330 */
extern MenuPanelTask  g_MenuPanelTasks[MENU_PANEL_COUNT];
extern s16            D_801485FA;
/* Panel-task block bytes 0x80148648..0x80148652; read by etc/game/00 and etc/shop/00. */
/* D_80148648 */
extern MenuPanelTask* g_MenuCurrentPanel;
extern u8             D_80148651;
extern u8             D_80148652;
extern s8             D_8014865C;
extern u8             D_80148699;

/* func_800B20D4 (battle), func_80199678 (game), func_801E2B94 (shop), func_801EA198 (start) */
void Menu_DrawPanelCursor(void);

/* Draw the panel's icon through the PsyQ 8x8 sprite primitive. The panel writes
 * the sprite fields itself at the primitive cursor; SetSprt8 only tags it. */
static inline void MenuDrawPanelIcon(s16 x, s16 y, s32 u, s32 v, u16 clut, u8 color) {
    MenuIconPrim* icon;

    icon = (MenuIconPrim*)g_GfxPrimCursor;
    SetSprt8((SPRT_8*)icon);
    icon->x0   = x;
    icon->y0   = y;
    icon->u0   = (u8)(u * 8);
    icon->v0   = (u8)(v * 8);
    icon->clut = clut;
    icon->b0   = color;
    icon->g0   = color;
    icon->r0   = color;
    SetSemiTrans(icon, 0);
    GFX_AddPrim(1, 0x10);
}

#endif
