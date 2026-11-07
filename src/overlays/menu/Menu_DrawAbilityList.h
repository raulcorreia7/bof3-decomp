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

    UI_DrawWindow((panel->pos.x + 3) & HALF_MASK, (panel->pos.y + 3) & HALF_MASK, MENU_ABILITY_LIST_WINDOW_WIDTH,
                  MENU_ABILITY_LIST_WINDOW_HEIGHT, 0, CHARACTER_BLOCK->window_style);
    n    = 0;
    list = Party_GetAbilities(panel->source.abilities.member, panel->source.abilities.type, 0);
    y    = panel->pos.y;
    do {
        if (*list != 0) {
            locked = (u8)func_801AF5B0(panel->unk_08, D_80148656, *list) == 0;
            shade  = locked ? MENU_SHADE_DIM : MENU_SHADE_NORMAL;
            if (n == panel->selected) {
                shade = MENU_SHADE_SELECTED;
            }
            level   = Char_GetAbilityElement(*list);
            ability = (Ability*)&g_Abilities[*list];
            count   = Char_GetAbilityCost(g_CharSlot[g_PartyFieldOrder[(s8)D_80148656]], *list, 0);
            if (n == panel->selected || n == panel->unk_0C) {
                if (shade != MENU_SHADE_DIM) {
                    func_801AF930((s16)(panel->pos.x + MENU_ABILITY_LIST_ICON_X),
                                  (s16)(y + MENU_ABILITY_LIST_ROW_Y + MENU_ABILITY_LIST_SHADOW_DY), MENU_SHADE_DIM,
                                  level, (u8*)ability, count, 1);
                }
                func_801AF930((s16)(panel->pos.x + MENU_ABILITY_LIST_ICON_X), (s16)(y + MENU_ABILITY_LIST_ROW_Y), shade,
                              level, (u8*)ability, count, locked);
            } else {
                func_801AF930((s16)(panel->pos.x + MENU_ABILITY_LIST_ICON_X),
                              (s16)(y + MENU_ABILITY_LIST_ROW_Y + MENU_ABILITY_LIST_SHADOW_DY), shade, level,
                              (u8*)ability, count, locked);
            }
        }
        n++;
        y += MENU_ABILITY_LIST_ROW_HEIGHT;
        list++;
    } while (n < MENU_ABILITY_LIST_ROW_COUNT);
    x = panel->pos.x + MENU_ABILITY_LIST_TITLE_X;
    UI_DrawText((x - strlen(g_MenuAbilityListNames[panel->source.abilities.type]) * 4),
                (panel->pos.y + MENU_ABILITY_LIST_TITLE_Y), MENU_SHADE_NORMAL, MENU_ABILITY_LIST_TITLE_WIDTH,
                (u8*)(g_MenuAbilityListNames[panel->source.abilities.type]));
    UI_DrawSpriteRun(panel->pos.x, panel->pos.y,
                     (panel->flags & MENU_LIST_FLAG_TAB_2) ? g_MenuListTab2OnSprites : g_MenuListTab2OffSprites, 1);
    UI_DrawSpriteRun(panel->pos.x, panel->pos.y,
                     (panel->flags & MENU_LIST_FLAG_TAB_1) ? g_MenuListTab1OnSprites : g_MenuListTab1OffSprites, 1);
    flags = panel->flags;
    if (!(flags & MENU_LIST_FRAME_MASK)) {
        panel->flags = 0;
    } else {
        panel->flags = flags - MENU_LIST_FRAME_STEP;
    }
    for (n = 0; n < MENU_ABILITY_LIST_TOP_CELLS; n++) {
        UI_DrawSprite(panel->pos.x + (n + 5) * MENU_ABILITY_LIST_CELL, panel->pos.y, MENU_LIST_SPRITE_TOP_EDGE, 1);
    }
    for (n = 0; n < MENU_ABILITY_LIST_SIDE_CELLS; n++) {
        UI_DrawSprite(panel->pos.x, panel->pos.y + (n + 3) * MENU_ABILITY_LIST_CELL, MENU_LIST_SPRITE_LEFT_EDGE, 1);
    }
    UI_DrawSprite(panel->pos.x + MENU_ABILITY_LIST_RIGHT_X, panel->pos.y + MENU_ABILITY_LIST_ROW_Y,
                  MENU_LIST_SPRITE_RIGHT_TOP, 1);
    for (n = 0; n < MENU_ABILITY_LIST_RIGHT_CELLS; n++) {
        UI_DrawSprite(panel->pos.x + MENU_ABILITY_LIST_RIGHT_X, panel->pos.y + (n + 4) * MENU_ABILITY_LIST_CELL,
                      MENU_LIST_SPRITE_RIGHT_EDGE, 1);
    }
    UI_DrawSprite(panel->pos.x, panel->pos.y + MENU_ABILITY_LIST_WINDOW_HEIGHT, MENU_LIST_SPRITE_BOTTOM_LEFT, 1);
    UI_DrawSprite(panel->pos.x + MENU_ABILITY_LIST_RIGHT_X,
                  panel->pos.y + MENU_ABILITY_LIST_WINDOW_HEIGHT - MENU_ABILITY_LIST_CELL,
                  MENU_LIST_SPRITE_BOTTOM_RIGHT, 1);
    if (panel->unk_10 != 0) {
        UI_DrawSprite(panel->pos.x + MENU_ABILITY_LIST_CELL, panel->pos.y, MENU_LIST_SPRITE_MARK_LEFT, 1);
        UI_DrawSprite(panel->pos.x + MENU_ABILITY_LIST_RIGHT_X, panel->pos.y, MENU_LIST_SPRITE_MARK_RIGHT, 1);
    }
    for (n = 0; n < MENU_ABILITY_LIST_SIDE_CELLS; n++) {
        UI_DrawSprite(panel->pos.x + (n + 1) * MENU_ABILITY_LIST_CELL, panel->pos.y + MENU_ABILITY_LIST_WINDOW_HEIGHT,
                      MENU_LIST_SPRITE_BOTTOM_EDGE, 1);
    }
}
