/* Slide the master panel 0x20 left and clamp its x at 0x98. The statements of
 * the battle, game and start overlay members; every change here must verify
 * every member. Members: func_800B254C (battle), func_8019973C (game),
 * func_801EA070 (start), and the start copy Menu_SlidePanelLeft2.
 */
/* The statements of Menu_SlidePanelLeft. */
#define MENU_SLIDE_PANEL_LEFT()                   \
    do {                                          \
        MenuPanelTask* task = g_MenuCurrentPanel; \
        s16            val;                       \
                                                  \
        val         = task->pos.x - 0x20;         \
        task->pos.x = val;                        \
        if (val < 0x98) {                         \
            task->pos.x = 152;                    \
            task->state = 0;                      \
        }                                         \
    } while (0)
