/* Menu_DrawAbilityList: the ability list panel of the shop (0x801DCE5C) and bate (0x801D73B4) overlays. The including image
 * supplies g_MenuAbilityListNames and the four g_MenuListTab*Sprites runs. */

/* Layout in pixels: the window and the frame cells around it. */
#define MENU_ABILITY_LIST_WINDOW_WIDTH  154
#define MENU_ABILITY_LIST_WINDOW_HEIGHT 160
#define MENU_ABILITY_LIST_ROW_COUNT     10
#define MENU_ABILITY_LIST_ROW_HEIGHT    13
#define MENU_ABILITY_LIST_ICON_X        7
#define MENU_ABILITY_LIST_ROW_Y         24
#define MENU_ABILITY_LIST_SHADOW_DY     2
#define MENU_ABILITY_LIST_TITLE_X       78
#define MENU_ABILITY_LIST_TITLE_Y       7
#define MENU_ABILITY_LIST_TITLE_WIDTH   16
#define MENU_ABILITY_LIST_RIGHT_X       144
#define MENU_ABILITY_LIST_CELL          8
#define MENU_ABILITY_LIST_TOP_CELLS     10
#define MENU_ABILITY_LIST_SIDE_CELLS    17
#define MENU_ABILITY_LIST_RIGHT_CELLS   15
#define MENU_ABILITY_LIST_SHADOW_OFFSET 3
#define MENU_ABILITY_LIST_TOP_FIRST     5
#define MENU_ABILITY_LIST_SIDE_FIRST    3
#define MENU_ABILITY_LIST_RIGHT_FIRST   4
#define MENU_ABILITY_LIST_GLYPH_HALF    4

/* The flags argument of UI_DrawSprite and UI_DrawSpriteRun, and the dim-icon flag of func_801AF930. */
#define MENU_ABILITY_LIST_SPRITE_FLAGS  1
#define MENU_ABILITY_LIST_ICON_ENABLED  0
#define MENU_ABILITY_LIST_ICON_DIMMED   1

/* The frame sprites, by the edge they sit on. */
#define MENU_LIST_SPRITE_TOP_EDGE       1
#define MENU_LIST_SPRITE_LEFT_EDGE      4
#define MENU_LIST_SPRITE_BOTTOM_LEFT    5
#define MENU_LIST_SPRITE_BOTTOM_EDGE    6
#define MENU_LIST_SPRITE_RIGHT_TOP      0x20
#define MENU_LIST_SPRITE_RIGHT_EDGE     0x21
#define MENU_LIST_SPRITE_BOTTOM_RIGHT   0x22
#define MENU_LIST_SPRITE_MARK_LEFT      0x32
#define MENU_LIST_SPRITE_MARK_RIGHT     0x34

MATCH void Menu_DrawAbilityList(MenuListPanel* panel) {
    volatile Ability* ability;
    u8*               list;
    s32               element;
    s32               cost;
    u8                locked;
    u8                shade;
    s32               x;
    u16               y;
    u8                flags;
    u8                n;

    UI_DrawWindow((panel->pos.x + MENU_ABILITY_LIST_SHADOW_OFFSET) & HALF_MASK, (panel->pos.y + MENU_ABILITY_LIST_SHADOW_OFFSET) & HALF_MASK, MENU_ABILITY_LIST_WINDOW_WIDTH,
                  MENU_ABILITY_LIST_WINDOW_HEIGHT, 0, CHARACTER_BLOCK->window_style);

    n    = 0;
    list = Party_GetAbilities(panel->source.abilities.member, panel->source.abilities.type, 0);
    y    = panel->pos.y;
    do {
        if (*list != 0) {
            locked = func_801AF5B0(panel->use_context, D_80148656, *list) == 0;
            shade  = locked ? MENU_SHADE_DIM : MENU_SHADE_NORMAL;
            if (n == panel->selected) {
                shade = MENU_SHADE_SELECTED;
            }
            element = Char_GetAbilityElement(*list);
            ability = &g_Abilities[*list];
            /* needs: type: D_80148656 is read signed here and unsigned above */
            /* FAKE: retail reads Char_GetAbilityCost as s32(s32, s32, s32). */
            cost    = ((s32 (*)(s32, s32, s32))Char_GetAbilityCost)(g_CharSlot[g_PartyFieldOrder[(s8)D_80148656]], *list, 0);
            if (n == panel->selected || n == panel->unk_0C) {
                if (shade != MENU_SHADE_DIM) {
                    func_801AF930(panel->pos.x + MENU_ABILITY_LIST_ICON_X, y + MENU_ABILITY_LIST_ROW_Y + MENU_ABILITY_LIST_SHADOW_DY, MENU_SHADE_DIM, element, ability, cost,
                                  MENU_ABILITY_LIST_ICON_DIMMED);
                }
                func_801AF930(panel->pos.x + MENU_ABILITY_LIST_ICON_X, y + MENU_ABILITY_LIST_ROW_Y, shade, element, ability, cost, locked);
            } else {
                func_801AF930(panel->pos.x + MENU_ABILITY_LIST_ICON_X, y + MENU_ABILITY_LIST_ROW_Y + MENU_ABILITY_LIST_SHADOW_DY, shade, element, ability, cost, locked);
            }
        }
        n++;
        y += MENU_ABILITY_LIST_ROW_HEIGHT;
        list++;
    } while (n < MENU_ABILITY_LIST_ROW_COUNT);

    x = panel->pos.x + MENU_ABILITY_LIST_TITLE_X;
    UI_DrawText(x - strlen(g_MenuAbilityListNames[panel->source.abilities.type]) * MENU_ABILITY_LIST_GLYPH_HALF, panel->pos.y + MENU_ABILITY_LIST_TITLE_Y, MENU_SHADE_NORMAL,
                MENU_ABILITY_LIST_TITLE_WIDTH, g_MenuAbilityListNames[panel->source.abilities.type]);

    UI_DrawSpriteRun(panel->pos.x, panel->pos.y, (panel->flags & MENU_LIST_FLAG_TAB_2) ? g_MenuListTab2OnSprites : g_MenuListTab2OffSprites, MENU_ABILITY_LIST_SPRITE_FLAGS);
    UI_DrawSpriteRun(panel->pos.x, panel->pos.y, (panel->flags & MENU_LIST_FLAG_TAB_1) ? g_MenuListTab1OnSprites : g_MenuListTab1OffSprites, MENU_ABILITY_LIST_SPRITE_FLAGS);

    flags = panel->flags;
    if (!(flags & MENU_LIST_FRAME_MASK)) {
        panel->flags = 0;
    } else {
        panel->flags = flags - MENU_LIST_FRAME_STEP;
    }

    for (n = 0; n < MENU_ABILITY_LIST_TOP_CELLS; n++) {
        UI_DrawSprite(panel->pos.x + (n + MENU_ABILITY_LIST_TOP_FIRST) * MENU_ABILITY_LIST_CELL, panel->pos.y, MENU_LIST_SPRITE_TOP_EDGE, MENU_ABILITY_LIST_SPRITE_FLAGS);
    }
    for (n = 0; n < MENU_ABILITY_LIST_SIDE_CELLS; n++) {
        UI_DrawSprite(panel->pos.x, panel->pos.y + (n + MENU_ABILITY_LIST_SIDE_FIRST) * MENU_ABILITY_LIST_CELL, MENU_LIST_SPRITE_LEFT_EDGE, MENU_ABILITY_LIST_SPRITE_FLAGS);
    }

    UI_DrawSprite(panel->pos.x + MENU_ABILITY_LIST_RIGHT_X, panel->pos.y + MENU_ABILITY_LIST_ROW_Y, MENU_LIST_SPRITE_RIGHT_TOP, MENU_ABILITY_LIST_SPRITE_FLAGS);
    for (n = 0; n < MENU_ABILITY_LIST_RIGHT_CELLS; n++) {
        UI_DrawSprite(panel->pos.x + MENU_ABILITY_LIST_RIGHT_X, panel->pos.y + (n + MENU_ABILITY_LIST_RIGHT_FIRST) * MENU_ABILITY_LIST_CELL, MENU_LIST_SPRITE_RIGHT_EDGE,
                      MENU_ABILITY_LIST_SPRITE_FLAGS);
    }

    UI_DrawSprite(panel->pos.x, panel->pos.y + MENU_ABILITY_LIST_WINDOW_HEIGHT, MENU_LIST_SPRITE_BOTTOM_LEFT, MENU_ABILITY_LIST_SPRITE_FLAGS);
    UI_DrawSprite(panel->pos.x + MENU_ABILITY_LIST_RIGHT_X, panel->pos.y + MENU_ABILITY_LIST_WINDOW_HEIGHT - MENU_ABILITY_LIST_CELL, MENU_LIST_SPRITE_BOTTOM_RIGHT, MENU_ABILITY_LIST_SPRITE_FLAGS);

    if (panel->unk_10 != 0) {
        UI_DrawSprite(panel->pos.x + MENU_ABILITY_LIST_CELL, panel->pos.y, MENU_LIST_SPRITE_MARK_LEFT, MENU_ABILITY_LIST_SPRITE_FLAGS);
        UI_DrawSprite(panel->pos.x + MENU_ABILITY_LIST_RIGHT_X, panel->pos.y, MENU_LIST_SPRITE_MARK_RIGHT, MENU_ABILITY_LIST_SPRITE_FLAGS);
    }

    for (n = 0; n < MENU_ABILITY_LIST_SIDE_CELLS; n++) {
        UI_DrawSprite(panel->pos.x + (n + 1) * MENU_ABILITY_LIST_CELL, panel->pos.y + MENU_ABILITY_LIST_WINDOW_HEIGHT, MENU_LIST_SPRITE_BOTTOM_EDGE, MENU_ABILITY_LIST_SPRITE_FLAGS);
    }
}
