/* The formation preview of the party formation menu. */

/* The formation table as one block, so the preview copies all of it to the stack. */
typedef struct Formations {
    FormationLayout layouts[FORMATION_COUNT];
} Formations;

/* Centre of the preview inside its frame; the ground arrow sits one pixel left of it. */
#define FORMATION_PREVIEW_CENTER_X 39
#define FORMATION_PREVIEW_CENTER_Y 23
#define FORMATION_PREVIEW_NAME_Y   40

/* Shade of a member that does not blink, and the base of a blinking member's pulse. */
#define FORMATION_SHADE_IDLE       0x70
#define FORMATION_SHADE_PULSE      0x3F

/* The frame's top and bottom edges: one 8-pixel column, six times. */
#define FORMATION_FRAME_COLUMNS    6

/* func_801DCDB8 (start), func_801D98C0 (shop), func_801D3E18 (bate), func_801D4DC0 (shisu) */
MATCH void Menu_DrawFormationPreview(u16 x, u16 y, u8 index, u8 blink, s32 angle) {
    Formations       table;
    FormationOrder   order;
    u8               shade[PARTY_SLOT_COUNT];
    FormationLayout* layout;
    u8               members;
    u8               i;
    u8               j;
    POLY_G3*         poly;
    s8               swap;

    table = *(Formations*)g_MenuFormations;
    order = g_MenuFormationOrder;
    UI_DrawWindow(x + 3, y + 3, MENU_FORMATION_WINDOW_WIDTH, MENU_FORMATION_WINDOW_HEIGHT, 0, CHARACTER_BLOCK->window_style);

    layout = &table.layouts[index];
    UI_DrawTextString(x + FORMATION_PREVIEW_CENTER_X - layout->name_length * 4, y + FORMATION_PREVIEW_NAME_Y, 0, layout->name_length, layout->name);

    switch (index) {
        case 0:
            members = 1;
            break;
        case 1:
        case 2:
        case 3:
            members = 2;
            break;
        default:
            members = 3;
            break;
    }

    /* Turn the arrow and the members by angle, x at twice the scale of y. */
    for (i = 0; i < 3; i++) {
        g_MenuFormationArrowTurned[i][0] = (g_MenuFormationArrow[i][0] * rcos(angle) - g_MenuFormationArrow[i][1] * rsin(angle)) >> 11;
        g_MenuFormationArrowTurned[i][1] = (g_MenuFormationArrow[i][0] * rsin(angle) + g_MenuFormationArrow[i][1] * rcos(angle)) >> 12;
    }

    /* The arrow brightens toward the front. */
    poly = (POLY_G3*)g_GfxPrimCursor;
    SetPolyG3(poly);
    setXY3(poly, x + FORMATION_PREVIEW_CENTER_X - 1 + g_MenuFormationArrowTurned[0][0], y + FORMATION_PREVIEW_CENTER_Y + g_MenuFormationArrowTurned[0][1],
           x + FORMATION_PREVIEW_CENTER_X - 1 + g_MenuFormationArrowTurned[1][0], y + FORMATION_PREVIEW_CENTER_Y + g_MenuFormationArrowTurned[1][1],
           x + FORMATION_PREVIEW_CENTER_X - 1 + g_MenuFormationArrowTurned[2][0], y + FORMATION_PREVIEW_CENTER_Y + g_MenuFormationArrowTurned[2][1]);
    poly->r0 = poly->g0 = g_MenuFormationArrowTurned[0][1] * 8 - 97;
    poly->b0            = 0;
    poly->r1 = poly->g1 = g_MenuFormationArrowTurned[1][1] * 8 - 97;
    poly->b1            = 0;
    poly->r2 = poly->g2 = g_MenuFormationArrowTurned[2][1] * 8 - 97;
    poly->b2            = 0;
    GFX_AddPrim(1, sizeof(POLY_G3));

    j = 1;
    for (i = 0; i < members; i++) {
        if (blink & j) {
            if (g_FrameCount & 8) {
                shade[i] = ((g_FrameCount & 6) << 5) + FORMATION_SHADE_PULSE;
            } else {
                shade[i] = ((~g_FrameCount & 6) << 5) + FORMATION_SHADE_PULSE;
            }
        } else {
            shade[i] = FORMATION_SHADE_IDLE;
        }

        g_MenuFormationSpots[i][0] = (layout->offsets[i].x * rcos(angle) - layout->offsets[i].y * rsin(angle)) >> 11;
        g_MenuFormationSpots[i][1] = (layout->offsets[i].x * rsin(angle) + layout->offsets[i].y * rcos(angle)) >> 12;
        j <<= 1;
    }

    /* Sort the members back to front, so the nearer icons draw over the farther ones. */
    for (i = 0; i < members - 1; i++) {
        for (j = 0; j < members - 1 - i; j++) {
            if (g_MenuFormationSpots[j][1] > g_MenuFormationSpots[j + 1][1]) {
                swap                           = g_MenuFormationSpots[j][0];
                g_MenuFormationSpots[j][0]     = g_MenuFormationSpots[j + 1][0];
                g_MenuFormationSpots[j + 1][0] = swap;

                swap                           = g_MenuFormationSpots[j][1];
                g_MenuFormationSpots[j][1]     = g_MenuFormationSpots[j + 1][1];
                g_MenuFormationSpots[j + 1][1] = swap;

                swap                 = order.members[j];
                order.members[j]     = order.members[j + 1];
                order.members[j + 1] = swap;

                swap         = shade[j];
                shade[j]     = shade[j + 1];
                shade[j + 1] = swap;
            }
        }
    }

    /* Each icon stands on its spot: the spot is the middle of the icon's bottom edge. */
    for (i = 0; i < members; i++) {
        Menu_DrawPanelIcon(x + FORMATION_PREVIEW_CENTER_X + g_MenuFormationSpots[i][0] - 4, y + FORMATION_PREVIEW_CENTER_Y + g_MenuFormationSpots[i][1] - 8, (u8)(order.members[i] + 3), 0x1E,
                           GetClut(16, STAGE_PALETTE_Y), shade[i]);
    }

    UI_DrawSpriteRun(x, y, g_MenuFormationFrameLeft, 0);
    for (i = 0; i < FORMATION_FRAME_COLUMNS; i++) {
        UI_DrawSpriteRun(x + i * 8, y, g_MenuFormationFrameMiddle, 0);
    }
    UI_DrawSpriteRun(x, y, g_MenuFormationFrameRight, 0);
}
